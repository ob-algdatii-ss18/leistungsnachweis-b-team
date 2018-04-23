//
// Created by Wolfgang on 27.03.18.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
#define LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H

#include <vector>
#include <functional>

#include "Collection.h"


template<class T>
class BPlusTree : public Collection<T> {


public:
    BPlusTree(std::function<int(T)> keyConverter, const int mSize ):m(mSize), Collection<T>(keyConverter) {

    }

    bool insert(T* t) override ;
    T* search(int key) override;
    T* remove(int key) override;

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

  const int m;
  Node* root = nullptr;


};

#endif //LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
