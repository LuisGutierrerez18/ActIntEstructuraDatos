/*
  Integrantes:
    Moisés Abel Díaz Nava. A01799628
    Luis Enrique Gutierrez Mendioroz. A00837481
  Compilar:
  Compilación para ejecutar:
  g++ -O3 -Wall -o main main.cpp
  ejecutar:
  ./main
*/

#ifndef _DLINKEDLIST_H_
#define _DLINKEDLIST_H_

#include "DLLNode.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <vector>
#include <fstream>
#include <utility>
#include <algorithm>
#include <sstream>


template <class T> void swap(T *a, T *b) {
  T t = *a;
  *a = *b;
  *b = t;
}

template <class T>
bool compare(const T &a, const T &b) {
    // Ejemplo de comparación personalizada
    return a.first < b.first; // Compara solo el primer elemento del par
}

template <class T> class DLinkedList {
private:
  DLLNode<T> *head;
  DLLNode<T> *tail;
  int numElements;

void heapifyDown(DLLNode<T> *node) {
while (node->next != nullptr && node->data < node->next->data) {
        // Implementar tu lógica de comparación personalizada si es necesario
        if (compare(node->data, node->next->data)) {
            swap(&(node->data), &(node->next->data));
        }
        node = node->next;
    }
}

public:
  DLinkedList();
  ~DLinkedList();
  int getNumElements();
  void printList();
  void printReverseList();
  void addFirst(T value);
  void addLast(T value);
  bool deleteData(T value);
  bool deleteAt(int position);
  T getData(int position);
  void updateData(T value, T newValue);
  // TO-DO act 2.2
  void updateAt(int position, T newValue);
  void findData(T value);
  void invert();
  
  void heapify();
  void heapSort();
  
  void readFromFile(const std::string &filename);
};


// Complejidad O(1)
template <class T> DLinkedList<T>::DLinkedList() {
  std::cout << "--> Creando una lista doblemente ligada vacia: " << this
            << std::endl;
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T> DLinkedList<T>::~DLinkedList() {
  std::cout << "--> Liberando memoria de la lista doblemente ligada: " << this
            << std::endl;
  DLLNode<T> *p, *q;
  p = head;
  while (p != nullptr) {
    q = p->next;
    delete p;
    p = q;
  }
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(1)
template <class T> int DLinkedList<T>::getNumElements() { return numElements; }

// Complejidad O(n)
template <class T> void DLinkedList<T>::printList() {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la lista es: " << std::endl;
    DLLNode<T> *p = head;
    while (p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }
}

// Complejidad O(n)
template <class T> void DLinkedList<T>::printReverseList() {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido inverso de la lista es: " << std::endl;
    DLLNode<T> *p = tail;
    while (p != nullptr) {
      std::cout << p->data << " ";
      p = p->prev;
    }
    std::cout << std::endl;
  }
}

// Complejidad O(1)
template <class T> void DLinkedList<T>::addFirst(T value) {
  // 1. crear nuevo nodo
  DLLNode<T> *newNode = new DLLNode<T>(value);
  // si la lista esta vacia
  if (head == nullptr && tail == nullptr) {
    head = newNode;
    tail = newNode;
  } else {
    // 2. apuntar newNode->next al nodo apuntado por head
    newNode->next = head;
    // 3. apuntar head->prev a newNode
    head->prev = newNode;
    // 4. actualizar head para apuntar a newNode
    head = newNode;
  }
  numElements++;
}

// Complejidad O(1)
template <class T> void DLinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
    // 1. crear nuevo nodo
    DLLNode<T> *newNode = new DLLNode<T>(value);
    // 2. apuntar tail->next a newNode
    tail->next = newNode;
    // 3. apuntar newNode->prev a tail
    newNode->prev = tail;
    // 4. actualizar tail para apuntar a newNode
    tail = newNode;
    numElements++;
  }
}

// Complejidad O(n)
template <class T> bool DLinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    std::cout << "La lista esta vacia" << std::endl;
    return false;
  } else {
    // Buscar value en la lista
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    while (p != nullptr && p->data != value) {
      previous = p;
      p = p->next;
    }
    // si value no esta en la lista
    if (p == nullptr) {
      std::cout << "El valor no existe en la lista" << std::endl;
      return false;
    }
    // si debo borrar el primer nodo de la lista
    if (p != nullptr && p == head) {
      head = p->next;
      if (head == nullptr) // habia solo un nodo en la lista
        tail = nullptr;
      else
        head->prev = nullptr;
    } else if (p->next == nullptr) { // borrar el ultimo nodo
      previous->next = nullptr;
      tail = previous;
    } else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    // borrar el nodo apuntado por p
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T> bool DLinkedList<T>::deleteAt(int position) {
  // La lista esta vacia
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // primer nodo
    DLLNode<T> *p = head;
    // si la lista contiene un solo nodo
    if (p != nullptr && p->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = p->next;
      head->prev = nullptr;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  } else {
    // Buscar position en la lista
    DLLNode<T> *p = head;
    DLLNode<T> *previous = nullptr;
    int index = 0;
    while (index != position) {
      previous = p;
      p = p->next;
      index++;
    }
    // debo borrar el ultimo nodo
    if (p->next == nullptr) {
      previous->next = nullptr;
      tail = previous;
    } else { // borrar cualquier otro nodo
      previous->next = p->next;
      p->next->prev = previous;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T> T DLinkedList<T>::getData(int position) {
  // Validar position
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } else if (position == 0) { // primer nodo
    return head->data;
  } else { // si es cualquier otra posicion
    // Buscar position en la lista
    DLLNode<T> *p = head;
    int index = 0;
    while (index != position) {
      p = p->next;
      index++;
    }
    if (p != nullptr)
      return p->data;
    else
      return {};
  }
}

// Complejidad O(n)
template <class T> void DLinkedList<T>::updateData(T value, T newValue) {
  // Buscar value en la lista
  DLLNode<T> *p = head;
  while (p != nullptr && p->data != value) {
    p = p->next;
  }
  if (p != nullptr)
    p->data = newValue;
  else
    throw std::out_of_range("El elemento a actualizar no existe en la lista");
}




// Metodo invert
// Invierte la lista encadenada doble
// Complejidad O(n)
template <class T> void DLinkedList<T>::invert() {
  if (head == nullptr || head == tail) // Si la lista está vacía o tiene solo un
                                       // elemento, no es necesario invertirla
    std::cout << "La lista no puede ser invertida/Esta vacia" << std::endl;

  DLLNode<T> *current = head;
  DLLNode<T> *temp = nullptr;

  // Intercambiar los punteros prev y next de cada nodo en la lista
  while (current != nullptr) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev; // Mover al siguiente nodo (ahora prev) en la lista
  }

  // Actualizar los punteros head y tail
  temp = head;
  head = tail;
  tail = temp;
}

template <class T> void DLinkedList<T>::updateAt(int ini, T fin) {
  // Validar posicion
  if (ini < 0 || fin < 0 || fin >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }

  DLLNode<T> *p = head;
  int index = 0;
  for (int i = index; i < ini; i++) {
    p = p->next;
  }

  int producto = 1;
  for (int i = ini; i < fin; i++) {
    producto *= p->data;
    p = p->next;
  }
}


template <class T> void DLinkedList<T>::heapify() {
  // Comenzamos desde el último nodo y ajustamos cada nodo hacia abajo
  DLLNode<T> *current = tail;
  while (current != nullptr) {
    heapifyDown(current);
    current = current->prev;
  }
}

//Complejidad O(n log n)
template <class T> void DLinkedList<T>::heapSort() {
  // Convertimos la lista en un max heap
heapify();

  DLLNode<T> *last = tail;
  while (last != nullptr) {
    // Movemos el nodo raíz (el máximo) al final de la lista
    swap(&(head->data), &(last->data));
    // Volvemos a ajustar el heap después de la extracción
    heapify();
    // Movemos el puntero 'last' al nodo anterior en la lista
    last = last->prev;
  }
}
// Complejidad O(n)


#endif // _LINKEDLIST_H_