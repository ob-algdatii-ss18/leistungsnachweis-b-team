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

    BPlusTree(std::function<int(T)> keyConverter, const int mSize) : m(mSize), Collection<T>(keyConverter) {
        root = new Node(m, nullptr, true);
        root->children[0] = nullptr;
    }

    bool insert(const T *t) override {
        int newElementKey = Collection<T>::valueToKeyConverter(*t);
        Leaf *newLeaf = new Leaf(newElementKey, t);

        Node *result = root->insert(newLeaf);

        if (result != nullptr) {
            Node *left = root;
            root = new Node(m, nullptr, false);
            left->parent = root;
            root->children[0] = left;
            result->parent = root;
            root->children[1] = result;
            root->keys[0] = result->leftKey();
            root->filling = 1;
        }

        return false;
    }


    const T *search(int key) override {
        return root->search(key);
    }

    T *remove(int key) override {
        if (root == nullptr) {
            return nullptr;
        }
        return nullptr;
    }


    friend std::ostream &operator<<(std::ostream &os, const BPlusTree &tree) {
        // 2m as max key count, 3 digits per key max, 2-Times because of comma, plus 2 for ()
        /*
        int blocksize = 2 * tree.m * 3 * 2 + 2;
        int depth = tree.treeDepth();
        os << std::string(blocksize * (depth / 2), ' ') << tree.root << std::string(blocksize * (depth / 2), ' ')
           << std::endl;
        */

        os << *tree.root;

        return os;
    }


private:
    struct Element {
    };

    int treeDepth() const {
        const Node *currentNode = this->root;
        int depth = 0;
        while (!currentNode && currentNode->nodeSize > 0) {
            ++depth;
            currentNode = &currentNode->children[0];
        }

        return depth;
    }

    struct Leaf : public Element {
        Leaf(int key, const T *data) : key(key), data(data) {

        }

        const int key;
        const T *data;

        friend std::ostream &operator<<(std::ostream &os, const Leaf &leaf) {

            os << "<key:" << leaf.key << ",data:" << leaf.data << ">" << std::endl;
            return os;
        }
    };

    struct Node : public Element {
        Node(int m, Node *parent, bool deepest) : nodeSize(2 * m), keys(new int[2 * m + 1]), parent(parent),
                                                  children((Element **) malloc(sizeof(Element *) * (2 * m + 2))),
                                                  deepest(deepest) {

        }

        Node *parent;
        int *keys; //Array
        const int nodeSize;
        int filling = 0;
        Element **children;
        bool deepest;

        friend std::ostream &operator<<(std::ostream &os, const Node &node) {

            os << "(";
            for (int i = 0; i < node.filling; i++) {
                if (node.deepest) {
                    //os << static_cast<Leaf *>(node.children[i]) << " | " << node.keys[i] << " | ";
                    os << node.children[i] << " | " << node.keys[i] << " | ";
                } else {
                    os << *static_cast<Node *>(node.children[i]) << " | " << node.keys[i] << " | ";
                }

            }
            if (node.deepest) {
                //os << *static_cast<Leaf *>(node.children[node.filling]);
                os << node.children[node.filling];
            } else {
                os << *static_cast<Node *>(node.children[node.filling]);
            }
            os << ")";

            return os;
        }

        int leftKey() {
            int result;
            if (deepest) {
                result = static_cast<Leaf *>(children[0])->key;
            } else {
                result = static_cast<Node *>(children[0])->leftKey();
            }
            return result;
        }

        Node *insert(Leaf *leaf) {
            Node *result = nullptr;

            int index = 0;
            while (index < filling && keys[index] <= leaf->key) {
                ++index;
            }

            if (deepest) {
                moveElements(index);

                keys[index] = leaf->key;
                children[index + 1] = leaf;

                if (filling == nodeSize) {
                    result = splitNode();
                } else {
                    ++filling;
                }
            } else {
                Node *res;
                res = static_cast<Node *>(children[index])->insert(leaf);

                if (res != nullptr) {
                    moveElements(index);
                    keys[index] = res->leftKey();
                    children[index + 1] = res;

                    if (filling == nodeSize) {
                        result = splitNode();
                    } else {
                        ++filling;
                    }
                }

            }

            // DEBUG output
            std::cout << "INSERT RESULT: | ";
            for (int j = 0; j < filling; ++j) {
                std::cout << children[j] << " | " << keys[j] << " | ";
            }
            std::cout << children[filling] << " |" << std::endl;
            std::cout << "INSERT RETURN: " << result << std::endl;


            return result;
        }

        const T *search(int key) {
            const T *result = nullptr;

            if (filling > 0) {
                int index = 0;
                while (index < filling && keys[index] <= key) {
                    ++index;
                }

                if (deepest) {
                    if (children[index] != nullptr && static_cast<Leaf *>(children[index])->key == key) {
                        result = static_cast<Leaf *>(children[index])->data;
                    }
                } else {
                    result = static_cast<Node *>(children[index])->search(key);
                }
            }

            return result;
        }

    private:
        void moveElements(int index) {
            for (int i = filling; i > index; i--) {
                keys[i] = keys[i - 1];
                children[i + 1] = children[i];
            }
        }

        Node *splitNode() {
            Node *rightNode = nullptr;
            if (filling == nodeSize) {
                rightNode = new Node(nodeSize / 2, parent, deepest);
                int rightNodeIndex = 0;
                for (int i = nodeSize / 2; i <= nodeSize; i++) {
                    rightNode->keys[rightNodeIndex] = keys[i + 1];
                    rightNode->children[rightNodeIndex] = children[i + 1];
                    keys[i + 1] = 0;
                    children[i + 1] = nullptr;
                    ++rightNodeIndex;
                }
                filling = nodeSize / 2;
                rightNode->filling = nodeSize / 2;

            }
            return rightNode;
        }


    };

    /**
     * Lower B-tree criteria -> Upper B-tree criteria = 2*m
     */
    const int m;

    /**
     * Root node
     */
    Node *root = nullptr;
};

#endif //LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
