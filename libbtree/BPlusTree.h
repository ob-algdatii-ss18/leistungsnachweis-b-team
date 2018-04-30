//
// Created by Wolfgang on 27.03.18.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
#define LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H

#include <vector>
#include <functional>

#include "Collection.h"
#include <iostream>

template<class T>
class BPlusTree : public Collection<T> {


public:

    BPlusTree(std::function<int(T)> keyConverter, const int mSize ):m(mSize), Collection<T>(keyConverter) {

    }

    bool insert(T* t) override {
        if (root == nullptr) {
            this->root = new Node(m, nullptr);
            this->root->keys;
            this->root->children.push_back(new Leaf(t));
        } else {

        }
        return false;
    }


    T* search(int key) override {
        if (root == nullptr) {
            return nullptr;
        }
        return nullptr;
    }

    T* remove(int key) override {
        if (root == nullptr) {
            return nullptr;
        }
        return nullptr;
    }


    std::ostream& operator<<(std::ostream& os, const BPlusTree& dt)
    {
        // 2m as max key count, 3 digits per key max, 2-Times because of comma, plus 2 for ()
        int blocksize = 2 * m * 3 * 2 + 2;
        int depth = treeDepth();
        os << std::string(blocksize * (depth/2), ' ') << this->root << std::string(blocksize * (depth/2), ' ') << std::endl;


        return os;
    }






private:
  struct Element {
  };

    int treeDepth(){
        const Node * currentNode = this->root;
        int depth = 0;
        while(!currentNode && currentNode->nodeSize > 0){
            ++depth;
            currentNode = &currentNode->children[0];
        }

        return depth;
    }
  struct Node : public Element {
    Node(int m, Node * parent):nodeSize(2*m), keys(new int[2*m]), parent(parent), children((Node*)malloc(sizeof(Node) * (2 * m + 1))){

    }
    const Node * parent;
    const int* keys;
    const int nodeSize;
    const Node* children;
    std::ostream& operator<<(std::ostream& os, const BPlusTree& dt)
    {
          os << "(";
           for(int i = 0; i < nodeSize; i++){
              os <<  keys[i] << ",";
          }
          os << ")" << std::endl;

          return os;
    }


  };

  struct Leaf : public Element {
    int key;
    T* data;
      std::ostream& operator<<(std::ostream& os, const BPlusTree& dt)
      {

          os << "<" << data << ">" << std::endl;
          return os;
      }
  };

  const int m;
  Node* root = nullptr;


};

#endif //LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
