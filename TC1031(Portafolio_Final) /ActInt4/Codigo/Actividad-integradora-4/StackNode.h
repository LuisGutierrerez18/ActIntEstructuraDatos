#ifndef _STACKNODE_H_
#define _STACKNODE_H_

template <class T>
class StackNode {
  private:
    T data;
    StackNode<T> *next;

  public:
    StackNode();
    StackNode(T value);
    // El template StackLinkedList<U> tiene acceso a los elementos privados de esta clase
    template<typename U> friend class StackLinkedList;

};

template <class T>
StackNode<T>::StackNode() : data{}, next{nullptr} {}

template <class T>
StackNode<T>::StackNode(T value) : data{value}, next{nullptr} {}


#endif  // _STACKNODE_H_