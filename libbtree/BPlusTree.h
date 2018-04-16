//
// Created by Wolfgang on 27.03.18.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
#define LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H

#include <vector>

#include "Collection.h"


template<class T>
class BPlusTree : public Collection<T> {
private:
  struct Element {
  };

  struct Node : public Element {
    BPlusTree* tree;
    std::vector<int> keys;
    std::vector<Element*> children;
  };

  struct Leaf : public Element {
    int key;
    T* data;
  };

  int m;
  Node* root = nullptr;

public:
  bool insert(int ket, T* t);

  T* search(int key) override;

  T* remove(int key) override;
};

#endif //LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
