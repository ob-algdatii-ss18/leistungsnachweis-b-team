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
        root = new Node(m, true);
        root->children[0] = nullptr;
        if(m <= 1) {
            throw std::invalid_argument("The minimum size of the tree have to be at least 2");
        }
    }

    bool insert(const T *t) override {
        int newElementKey = Collection<T>::valueToKeyConverter(*t);
        auto newLeaf = new Leaf(newElementKey, t);

        Node *result = root->insert(newLeaf);

        if (result != nullptr) {
            Node *left = root;
            root = new Node(m, false);
            root->children[0] = left;
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

        Node *result = root->remove(key);
        if (result != nullptr) {
            root = result;
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

    void generateDotCode() {
        std::cout << "digraph BTREE {" << std:: endl;
        std::cout << "node [shape = record,height=.1];" << std:: endl;
        root->generateDotCode();
        std::cout << "}" << std:: endl;
    }


private:
    struct Element {
    };

    struct Leaf : public Element {
        Leaf(int key, const T *data) : key(key), data(data) {

        }

        ~Leaf() {
            //std::cout << "~Leaf()" << std::endl;
            //std::cout << "data: " << data << std::endl;
            //delete data;
        }

        const int key;
        const T *data;

        friend std::ostream &operator<<(std::ostream &os, const Leaf &leaf) {

            os << "<key:" << leaf.key << ",data:" << leaf.data << ">" << std::endl;
            return os;
        }
    };

    struct Node : public Element {
        Node(int m, bool deepest) : nodeSize(2 * m), keys(new int[2 * m + 1]),
                                                  children((Element **) malloc(sizeof(Element *) * (2 * m + 2))),
                                                  deepest(deepest) {

        }

        ~Node() {

            delete[] keys;
            for(int i = 0; i < nodeSize + 2; i++) {
                if(children[i] != nullptr) {
                    std::cout << "DANGER" << std::endl;
                }
                delete children[i];
            }
        }

        int *keys; //Array
        const int nodeSize;
        int filling = 0;
        Element **children;
        const bool deepest;

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

        void generateDotCode() {
            std::cout << "\"" << this << "\"[label = \"";
            for (int i = 0; i < filling; i++) {
                std::cout << "<f" << i << "> |" << keys[i] << "|";
            }
            std::cout << "<f" << filling << ">\"];" << std::endl;

            for (int i = 0; i <= filling; i++) {
                if (deepest) {
                    std::cout << "\"" << children[i] << "\"[label = \"" << static_cast<Leaf *>(children[i])->key << "\", shape=ellipse];" << std::endl;
                } else {
                    static_cast<Node *>(children[i])->generateDotCode();
                }
                std::cout << "\"" << this << "\":f" << i << " -> \"" << children[i] << "\";" << std::endl;

            }

            //<f0> |10|<f1> |20|<f2> |30|<f3>"]; << std::endl;
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
                if (filling == 1 && children[0] == nullptr) {
                    if (index == 0) {
                        children[0] = leaf;
                    } else {
                        children[0] = children[1];
                        children[1] = leaf;
                        keys[0] = leaf->key;
                    }
                } else {
                    moveElementsRight(index);
                    if (index == 0 && filling > 0) {
                        children[0] = leaf;
                        keys[0] = static_cast<Leaf *>(children[1])->key;
                    } else {
                        keys[index] = leaf->key;
                        children[index + 1] = leaf;
                    }
                    if (filling == nodeSize) {
                        result = splitNode();
                    } else {
                        ++filling;
                    }

                }
            } else {
                Node *res;
                res = static_cast<Node *>(children[index])->insert(leaf);

                if (res != nullptr) {

                    moveElementsRight(index);
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
            //std::cout << "INSERT RESULT:  " << *this << std::endl;
            //std::cout << "INSERT RETURN: " << result << std::endl;


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

        Node *remove(int key) {
            Node *result = nullptr;

            if (filling > 0) {
                int index = 0;
                while (index < filling && keys[index] <= key) {
                    ++index;
                }

                if (deepest) {
                    if (children[index] != nullptr && static_cast<Leaf *>(children[index])->key == key) {
                        static_cast<Leaf *>(children[index])->~Leaf();
                        if (filling == 1) {
                            if (children[0] == nullptr && index == 1) {
                                filling = 0;
                            } else {
                                if (index == 1) {
                                    children[1] = children[0];
                                    keys[0] = static_cast<Leaf *>(children[1])->key;
                                }
                                children[0] = nullptr;
                                result = this;
                            }
                        } else {
                            moveElementsLeft(index);
                            if (filling < nodeSize / 2) {
                                result = this;
                            }
                        }
                    }
                } else {
                    Node *res = static_cast<Node *>(children[index])->remove(key);
                    if (res != nullptr) {
                        Node *concated;
                        Node *left;
                        if (index == 0) {
                            left = static_cast<Node *>(children[0]);
                            concated = concatNodes(static_cast<Node *>(children[0]), static_cast<Node *>(children[1]));
                        } else {
                            left = static_cast<Node *>(children[index - 1]);
                            concated = concatNodes(static_cast<Node *>(children[index - 1]),
                                                   static_cast<Node *>(children[index]));
                        }
                        if (concated == nullptr) {
                            if (filling == 1) {
                                result = left;
                            } else {
                                moveElementsLeft(index);
                                if(index < filling) { //only if it's not the last element
                                    children[index] = left;
                                }
                                if (filling < nodeSize / 2) {
                                    result = this;
                                }
                            }
                        } else {
                            if (filling == 1) {
                                children[0] = concated->children[0];
                                children[1] = concated->children[1];
                                keys[0] = concated->keys[0];
                            } else {
                                moveElementsLeft(index);
                                if (filling < nodeSize / 2) {
                                    result = concated;
                                }
                            }
                        }
                    }
                }


            }

            /*
            // DEBUG output
            std::cout << "DELETE RESULT:  " << *this << std::endl;
            if (result == nullptr) {
                std::cout << "DELETE RETURN: " << result << std::endl;
            } else {
                std::cout << "DELETE RETURN: " << *result << std::endl;
            }
            */
            return result;
        }

    private:
        void moveElementsRight(int index) {
            for (int i = filling; i >= index; i--) {
                keys[i] = keys[i - 1];
                children[i + 1] = children[i];
            }
        }

        void moveElementsLeft(int index) {
            for (int i = index; i <= filling; i++) {
                keys[i] = keys[i + 1];
                children[i] = children[i + 1];
            }
            children[filling + 1] = nullptr;
            keys[filling + 1] = 0;
            --filling;
        }

        Node *splitNode() {
            Node *rightNode = nullptr;
            if (filling == nodeSize) {
                rightNode = new Node(nodeSize / 2, deepest);
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

        Node *concatNodes(Node *left, Node *right) {
            Node *result = nullptr;

            int overallFilling = left->filling + right->filling;

            if(left->children[0] == nullptr || right->children[0] == nullptr) {
                --overallFilling;
            }

            if (overallFilling < nodeSize) {
                int index = left->filling + 1;

                for (int i = 0; i <= right->filling; i++) {
                    if (right->children[i] != nullptr) {
                        left->children[index] = right->children[i];
                        right->children[i] = nullptr;
                        if (left->deepest) {
                            left->keys[index - 1] = static_cast<Leaf *>(left->children[index])->key;
                        } else {
                            left->keys[index - 1] = static_cast<Node *>(left->children[index])->leftKey();
                        }
                        ++left->filling;
                        ++index;
                    }
                }

                // delete of right node
                right->~Node();
            } else {
                auto newUpper = new Node(nodeSize / 2, deepest);

                if (left->filling < overallFilling / 2) {
                    for (int i = left->filling + 1; i <= overallFilling / 2; ++i) {
                        left->children[i] = right->children[0];
                        right->moveElementsLeft(0);
                        if (left->deepest) {
                            left->keys[i - 1] = static_cast<Leaf *>(left->children[i])->key;
                        } else {
                            left->keys[i - 1] = static_cast<Node *>(left->children[i])->leftKey();
                        }
                        ++left->filling;
                    }
                } else {
                    int leftFormerFilling = left->filling;
                    for (int i = overallFilling / 2 + 1; i <= leftFormerFilling; ++i) {
                        if(right->children[0] == nullptr) {
                            --right->filling;
                        } else {
                            right->moveElementsRight(0);
                        }
                        right->children[0] = left->children[i];
                        left->children[i] = nullptr;
                        --left->filling;
                        ++right->filling;

                        if (right->deepest) {
                            right->keys[0] = static_cast<Leaf *>(right->children[1])->key;
                        } else {
                            right->keys[0] = static_cast<Node *>(right->children[1])->leftKey();
                        }

                    }


                }

                newUpper->children[0] = left;
                newUpper->children[1] = right;
                newUpper->keys[0] = right->leftKey();
                newUpper->filling = 1;

                result = newUpper;
            }
            return result;
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
