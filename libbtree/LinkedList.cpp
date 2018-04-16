//
// Created by Wolfgang on 06.04.18.
//

#include "LinkedList.h"

template<class T>
T *LinkedList<T>::search(int key) {
  Node *current = this->head;
  while (current != nullptr) {
    if (current->key == key) {
      return current;
    }
    current = current->next;
  }
  return nullptr;
}

template<class T>
bool LinkedList<T>::insert(int key, T *t) {
  auto *node = new Node(key, t);
  if (this->head == nullptr) {
    this->head = node;
    this->tail = node;
  } else {
    this->tail->next = node;
    this->tail = node;
  }
  return true;
}

template<class T>
T *LinkedList<T>::remove(int key) {

  return nullptr;
}
