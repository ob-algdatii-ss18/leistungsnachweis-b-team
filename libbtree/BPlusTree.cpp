//
// Created by Wolfgang on 27.03.18.
//

#include "BPlusTree.h"

template<class T>
bool BPlusTree<T>::insert(T* t) {
  if (root == nullptr) {
      this->root = new Node();
  } else {
    ;
  }
  return false;
}

template<class T>
T* BPlusTree<T>::search(int key) {
  if (root == nullptr) {
    return nullptr;
  }
  return nullptr;
}

template<class T>
T* BPlusTree<T>::remove(int key) {
  if (root == nullptr) {
    return nullptr;
  }
  return nullptr;
}
