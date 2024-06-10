#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "NodeLinkedList.h"

template <class T>
class LinkedList {
  private:
    NodeLinkedList<T> *head;
    NodeLinkedList<T> *tail;
    int numElements;

  public:
    LinkedList();
    ~LinkedList();
    int getNumElements();
    void printList();
    void addFirst(T value);
    void addLast(T value);
    bool deleteData(T value);
    bool deleteAt(int position);
    T getData(int position);
    void updateData(T value, T newValue);
    void updateAt(int position, T newValue);
    void findData(T value);
    NodeLinkedList<T> *getHead();
};

// Complejidad O(1)
template <class T>
LinkedList<T>::LinkedList() {
  //std::cout << "--> Creando una lista ligada vacia: " << this << std::endl; 
  head = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T>
LinkedList<T>::~LinkedList() {
  //std::cout << "--> Liberando memoria de la lista ligada: " << this << std::endl;
    NodeLinkedList<T> *p, *q;
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
template <class T>
int LinkedList<T>::getNumElements() {
  return numElements;  
}

// Complejidad O(n)
template <class T>
void LinkedList<T>::printList() {
  if (head == nullptr && tail == nullptr)
    std::cout << "La lista esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la lista es: " << std::endl;
    NodeLinkedList<T> *p = head;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }    
}

// Complejidad O(1)
template <class T>
void LinkedList<T>::addFirst(T value) {
  // 1. crear nuevo nodo
  NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
  // 2. apuntar newNode->next al nodo apuntado por head
  newNode->next = head;
  // 3. actualizar head para apuntar a newNode
  head = newNode;
  if (numElements == 0)
    tail = newNode;
  numElements++;
}

// Complejidad O(1)
template <class T>
void LinkedList<T>::addLast(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr)
    addFirst(value);
  else {
      // 1. crear nuevo nodo
      NodeLinkedList<T> *newNode = new NodeLinkedList<T>(value);
      // 2. apuntar tail->next a newNode
      tail->next = newNode;
      // 3. actualizar tail para apuntar a newNode
      tail = newNode;
      numElements++;
  }
}

// Complejidad O(n)
template <class T>
bool LinkedList<T>::deleteData(T value) {
  // La lista esta vacia
  if (head == nullptr && tail == nullptr) {
    std::cout << "La lista esta vacia" << std::endl;
    return false;
  }
  else {
    // Buscar value en la lista
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    while(p != nullptr && p->data != value) {
      prev = p;
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
    }
    else if (p->next == nullptr) { // borrar el ultimo nodo
      prev->next = nullptr;
      tail = prev;
    }
    else {
      prev->next = p->next;
    }
    // borrar el nodo apuntado por p
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
}

// Complejidad O(n)
template <class T>
bool LinkedList<T>::deleteAt(int position) {
  // Validar position
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } 
  else if (position == 0) { // primer nodo 
    NodeLinkedList<T> *p = head;
    // si la lista contiene un solo nodo
    if (p != nullptr && p->next == nullptr) {
      head = nullptr;
      tail = nullptr;
    }
    else
      head = p->next;
    delete p;
    p = nullptr;
    numElements--;
    return true;
  }
  else {
    // Buscar position en la lista
    NodeLinkedList<T> *p = head;
    NodeLinkedList<T> *prev = nullptr;
    int index = 0;
    while(index != position) {
      prev = p;
      p = p->next;
      index++;
    }
    // debo borrar el ultimo nodo
    if (p->next == nullptr) {
      prev->next = nullptr;
      tail = prev;
    }
    else { // borrar cualquier otro nodo
      prev->next = p->next;
    }
    delete p;
    p = nullptr;
    numElements--;
    return true;    
  }
}

// Complejidad O(n)
template <class T>
T LinkedList<T>::getData(int position) {
  // Validar position
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  } 
  else if (position == 0) { // primer nodo 
    return head->data;
  }
  else { // si es cualquier otra posicion
    // Buscar position en la lista
    NodeLinkedList<T> *p = head;
    int index = 0;
    while(index != position) {
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
template <class T>
void LinkedList<T>::updateData(T value, T newValue) {
  // Buscar value en la lista
  NodeLinkedList<T> *p = head;
  while(p != nullptr && p->data != value) {
    p = p->next;
  }
  if (p != nullptr)
    p->data = newValue;
  else
    throw std::out_of_range("El elemento a actualizar no existe en la lista");
}


// Complejidad O(n)
template <class T>
void LinkedList<T>::updateAt(int position, T newValue) {
  // Validar position
  if (position < 0 || position >= numElements) {
    throw std::out_of_range("Indice fuera de rango");
  }
  else {
    // Buscar position en la lista
    NodeLinkedList<T> *p = head;
    int index = 0;
    while(index != position) {
      p = p->next;
      index++;
    }
    if (p != nullptr)
      p->data = newValue;
  }
}

template <class T> 
NodeLinkedList<T> * LinkedList<T>::getHead() { 
  return head; 
}

#endif  // _LINKEDLIST_H_