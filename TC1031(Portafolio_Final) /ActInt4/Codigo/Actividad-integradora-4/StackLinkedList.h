#ifndef _STACKLINKEDLIST_H_
#define _STACKLINKEDLIST_H_

#include <iostream>
#include <stdexcept>
#include "StackNode.h"

template <class T>
class StackLinkedList {
  private:
    StackNode<T> *top;
    StackNode<T> *tail;
    int numElements;

  public:
    StackLinkedList();
    ~StackLinkedList();
    int getNumElements();
    void printStack();
    bool isEmpty();
    void push(T value);
    void pop();
    T getTop();
};

// Complejidad O(1)
template <class T>
StackLinkedList<T>::StackLinkedList() {
  top = nullptr;
  tail = nullptr;
  numElements = 0;
}

// Complejidad O(n)
template <class T>
StackLinkedList<T>::~StackLinkedList() {
    StackNode<T> *p, *q;
    p = top;
    while (p != nullptr) {
      q = p->next;
      delete p;
      p = q;
    }
    top = nullptr;
    tail = nullptr;
    numElements = 0;
}

// Complejidad O(1)
template <class T>
int StackLinkedList<T>::getNumElements() {
  return numElements;  
}

// Complejidad O(n)
template <class T>
void StackLinkedList<T>::printStack() {
  if (isEmpty())
    std::cout << "La pila esta vacia" << std::endl;
  else {
    std::cout << "El contenido de la pila es: " << std::endl;
    StackNode<T> *p = top;
    while(p != nullptr) {
      std::cout << p->data << " ";
      p = p->next;
    }
    std::cout << std::endl;
  }    
}

// Complejidad O(1)
template <class T>
bool StackLinkedList<T>::isEmpty() {
  return (top == nullptr && tail == nullptr);
}

// Complejidad O(1)
template <class T>
void StackLinkedList<T>::push(T value) {
  // 1. crear nuevo nodo
  StackNode<T> *newNode = new StackNode<T>(value);
  // 2. apuntar newNode->next al nodo apuntado por head
  newNode->next = top;
  // 3. actualizar head para apuntar a newNode
  top = newNode;
  if (numElements == 0)
    tail = newNode;
  numElements++;
}

// Complejidad O(1)
template <class T>
void StackLinkedList<T>::pop() {
    // La pila esta vacia
  if (isEmpty()) {
    throw std::out_of_range("La pila esta vacia");
  } 
  else {
    StackNode<T> *p = top;
    // si la pila contiene un solo nodo
    if (p != nullptr && p->next == nullptr) {
      top = nullptr;
      tail = nullptr;
    }
    else
      top = p->next;
    delete p;
    p = nullptr;
    numElements--;
  }
}

// Complejidad O(1)
template <class T>
T StackLinkedList<T>::getTop() {
  if (isEmpty())
    throw std::out_of_range("La pila esta vacia");
  else
    return top->data;
}


#endif  // _STACKLINKEDLIST_H_