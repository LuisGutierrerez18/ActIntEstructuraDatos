#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

#include "HashNode.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <vector>

template <class K, class T> class HashTable {
private:
  std::vector<HashNode<K, T>> table;
  int numElements;
  // Es preferible usar un numero primo
  // https://numerosprimos.org/numeros-primos-de-1-a-100000/
  int maxSize;
  double alfa;             // factor de carga (numElements / maxSize)
  unsigned int colisiones; // colisiones totales hasta el momento

public:
  HashTable();
  ~HashTable();
  void split(std::string line, std::vector<int> &res);
  void setMaxSize(int selectedMaxSize);
  // Funcion hash (metodo de residuales)
  int getHashIndex(K keyValue);
  int getNumElements();
  void readHash(const std::string &filename);
  void print();
  void add(K keyValue, T dataValue);
  int find(K keyValue);
  T getDataAt(int index);
  void remove(K keyValue);
  double getAlfa();
  unsigned int getColisiones();
  int findIPSummary(std::string);
  void getIpSummary(int);
};

template <class K, class T>
void HashTable<K, T>::split(std::string line, std::vector<int> &res) {
  size_t strPos = line.find(",");
  size_t lastPos = 0;
  while (strPos != std::string::npos) {
    res.push_back(stoi(line.substr(lastPos, strPos - lastPos)));
    lastPos = strPos + 1;
    strPos = line.find(" ", lastPos);
  }
  res.push_back(stoi(line.substr(lastPos, line.size() - lastPos)));
}

// O(1)
template <class K, class T> HashTable<K, T>::HashTable() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<HashNode<K, T>>(maxSize);
  colisiones = 0;
  alfa = 0.0;
}
// O(1)
template <class K, class T> HashTable<K, T>::~HashTable() {
  maxSize = 0;
  numElements = 0;
  table = std::vector<HashNode<K, T>>(maxSize);
  colisiones = 0;
  alfa = 0.0;
}
// O(1)
template <class K, class T>
void HashTable<K, T>::setMaxSize(int selectedMaxSize) {
  maxSize = selectedMaxSize;
  numElements = 0;
  table = std::vector<HashNode<K, T>>(maxSize);
  colisiones = 0;
  alfa = 0.0;
}
// Funcion hash (metodo de residuales) O(1)
template <class K, class T> int HashTable<K, T>::getHashIndex(K keyValue) {
  // metodo de residuales (key mod maxSize)
  return keyValue % maxSize;
}
// O(1)
template <class K, class T> int HashTable<K, T>::getNumElements() {
  return numElements;
}

//O(n)
template <class K, class T>
void HashTable<K, T>::readHash(const std::string &filename) {
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    std::cerr << "Error al abrir el archivo: " << filename << std::endl;
    return;
  }
  int i = 0;
  std::string line;
  std::getline(inputFile, line); // Skip header

  while (std::getline(inputFile, line)) {
    std::istringstream iss(line);
    std::string ip;
    int outDegree, inDegree;

    std::getline(iss, ip, ',');
    iss >> outDegree;
    iss.ignore(1, ',');
    iss >> inDegree;

    // Store the tuple (ip, outDegree, inDegree) in the hash table
    add(i, std::make_tuple(ip, outDegree, inDegree));
    i++;
  }
  inputFile.close();
}

// O(n)
template <class K, class T> void HashTable<K, T>::print() {
  std::cout << "Contenido de la tabla hash" << std::endl;
  for (int i = 0; i < maxSize; i++) {
    // 0 empty,  1 used,  2 deleted
    if (table[i].getStatus() == 1) {
      std::cout << "Celda: " << i << " Key: " << table[i].getKey()
                << ", Value: (" << std::get<0>(table[i].getData()) << ", "
                << std::get<1>(table[i].getData()) << ", "
                << std::get<2>(table[i].getData()) << ")"
                << ", Overflow.size: " << table[i].getOverflowSize()
                << std::endl;
    }
  }
}
// O(1) en promedio
template <class K, class T> void HashTable<K, T>::add(K keyValue, T dataValue) {
  if (numElements == maxSize) {
    throw std::out_of_range("La hash table esta llena");
  }
  if (find(keyValue) != -1) {
    throw std::out_of_range("El elemento ya existe en la tabla hash");
  }
  // Calcular el index en la tabla hash
  int hashIndex = getHashIndex(keyValue);
  HashNode<K, T> node = table[hashIndex];
  // 0 empty,  1 used,  2 deleted
  if (node.getStatus() != 1) { // la celda esta libre
    node.setKey(keyValue);
    node.setData(dataValue);
    table[hashIndex] = node;
  } else { // la celda NO esta libre (colision)
    // Muestreo cuadratico para manejo de colisiones
    colisiones++;
    int i = 1;
    int currentHashIndex = getHashIndex(hashIndex + i * i);
    HashNode<K, T> currentNode = table[currentHashIndex];
    while (currentNode.getStatus() == 1) { // la celda esta ocupada
      i++;
      currentHashIndex = getHashIndex(hashIndex + i * i);
      currentNode = table[currentHashIndex];
      colisiones++;
    }
    // Se ha encontrado una celda libre
    currentNode.setKey(keyValue);
    currentNode.setData(dataValue);
    node.addToOverflow(currentHashIndex);
    table[currentHashIndex] = currentNode;
    table[hashIndex] = node;
  }
  numElements++;
}
// O(1) en promedio
template <class K, class T> int HashTable<K, T>::find(K keyValue) {
  // Calcular el index en la tabla hash
  int hashIndex = getHashIndex(keyValue);
  HashNode<K, T> node = table[hashIndex];
  // 0 empty,  1 used,  2 deleted
  if (node.getStatus() == 1) {
    if (node.getKey() == keyValue)
      return hashIndex;
    for (int i = 0; i < (int)node.getOverflowSize(); i++) {
      int overflowIndex = node.getOverflowAt(i);
      if (table[overflowIndex].getKey() == keyValue)
        return overflowIndex;
    }
    return -1;
  }
  return -1;
}
// O(1)
template <class K, class T> T HashTable<K, T>::getDataAt(int index) {
  return table[index].getData();
}
// O(1) en promedio
template <class K, class T> void HashTable<K, T>::remove(K keyValue) {
  int pos, hashIndex;
  pos = find(keyValue);
  if (pos == -1) {
    throw std::out_of_range("El elemento no existe en la tabla hash");
  }
  hashIndex = getHashIndex(keyValue);
  if (pos != hashIndex) {
    HashNode<K, T> node = table[hashIndex];
    node.removeFromOverflow(pos);
    table[hashIndex] = node;
  }
  table[pos].clearData();
  numElements--;
}
// O(1)
template <class K, class T> double HashTable<K, T>::getAlfa() {
  double tmp = (double)numElements / (double)maxSize;
  return tmp;
}
// O(1)
template <class K, class T> unsigned int HashTable<K, T>::getColisiones() {
  return colisiones;
}

//O(v * e)
template <class K, class T>
int HashTable<K, T>::findIPSummary(std::string dataValue) {
  for (int i = 0; i < maxSize; i++) {
    // Verificar si la celda está en uso
    if (table[i].getStatus() == 1 &&
        std::get<0>(table[i].getData()) == dataValue) {
      return i;
    }
    // Verificar las celdas de overflow
    if (table[i].getStatus() == 1) {
      for (int j = 0; j < (int)table[i].getOverflowSize(); j++) {
        int overflowIndex = table[i].getOverflowAt(j);
        if (std::get<0>(table[overflowIndex].getData()) == dataValue) {
          return overflowIndex;
        }
      }
    }
  }
  // Si no se encuentra el valor, devolver -1
  return -1;
}

//Complejidad O(1)
template <class K, class T>
void HashTable<K,T>::getIpSummary(int index){
  std::cout << "Celda: " << index << " Key: " << table[index].getKey()
              << ", Values: "<< std::endl  << "IP: " << std::get<0>(table[index].getData()) << std::endl  << "Total de direcciones accesadas:  "
              << std::get<1>(table[index].getData()) << std::endl  <<"Total de direcciones que accesaron a esta IP:  "
              << std::get<2>(table[index].getData()) << std::endl
              << "Overflow.size: " << table[index].getOverflowSize()
              << std::endl;
  
}

#endif // _HASH_TABLE_H_