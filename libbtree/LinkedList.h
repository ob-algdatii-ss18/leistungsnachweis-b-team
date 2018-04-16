//
// Created by Wolfgang on 06.04.18.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_LINKEDLIST_H
#define LEISTUNGSNACHWEIS_B_TEAM_LINKEDLIST_H


#include "Collection.h"

template<class T>
class LinkedList : public Collection<T> {

private:

  struct Node {
    int key;
    T *value;
    Node *next;
    Node(int key, T *value): key(key), value(value) {}
  };

  Node *head;
  Node *tail;

public:

  bool insert(int ket, T* t) override;

  T* search(int key) override;

  T* remove(int key) override;

};

#endif //LEISTUNGSNACHWEIS_B_TEAM_LINKEDLIST_H
