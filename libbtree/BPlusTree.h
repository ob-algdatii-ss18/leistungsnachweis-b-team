//
// Created by Wolfgang on 27.03.18.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H
#define LEISTUNGSNACHWEIS_B_TEAM_BPLUSTREE_H

#include <vector>
#include <functional>

#include "Collection.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <string>

template<class T>
class BPlusTree : public Collection<T> {
private:
    int fileCount = 0;
public:

    BPlusTree(std::function<int(T)> keyConverter, const int mSize) : m(mSize), Collection<T>(keyConverter) {
        root = new Node(m, true);
        root->children[0] = nullptr;
        if(m <= 1) {
            throw std::invalid_argument("The minimum size of the tree have to be at least 2");
        }
    }

    bool insert(const T *t) override {
        auto *profilingResults = new ProfilingResults();
        return insert(t, profilingResults);
    }
    bool insert(const T *t, ProfilingResults *profilingResults) override {
        int newElementKey = Collection<T>::valueToKeyConverter(*t);
        auto newLeaf = new Leaf(newElementKey, t);

        Node *result = root->insert(newLeaf, profilingResults);

        if (result != nullptr) {
            Node *left = root;
            root = new Node(m, false);
            root->children[0] = left;
            root->children[1] = result;
            root->keys[0] = result->leftKey();
            root->filling = 1;
        }

        return true;
    }


    const T *search(int key) override {
        auto *profilingResults = new ProfilingResults();
        return search(key, profilingResults);
    }

    const T *search(int key, ProfilingResults *profilingResults) override {
        return root->search(key, profilingResults);
    }

    bool remove(int key) override {
        auto *profilingResults = new ProfilingResults();
        return remove(key, profilingResults);
    }

    bool remove(int key, ProfilingResults *profilingResults) override {
        bool *removeResult = new bool(false);
        Node *result = root->remove(key, profilingResults, removeResult);
        if (result != nullptr) {
            root = result;
        }
        bool returnResult = *removeResult;
        delete removeResult;
        return returnResult;
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

    std::string generateDotCode() {
        std::stringstream stream;
        stream << "digraph BTREE {" << std::endl;
        stream << "node [shape = record,height=.1];" << std::endl;
        stream << root->generateDotCode();
        stream << "}" << std:: endl;
        return stream.str();
    }

    void generateDotFile() {
        std::stringstream filestream;
        filestream << "/tmp/example_" << fileCount++ << ".dot";
        std::string filename = filestream.str();

        std::ofstream dotfile;
        dotfile.open (filename);
        dotfile << this->generateDotCode() << std::endl;
        dotfile.close();
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

        std::string generateDotCode() {
            std::stringstream stream;
            stream << "\"" << this << "\"[label = \"";
            for (int i = 0; i < filling; i++) {
                stream << "<f" << i << "> |" << keys[i] << "|";
            }
            stream << "<f" << filling << ">\"];" << std::endl;

            for (int i = 0; i <= filling; i++) {
                if (deepest) {
                    if(children[i] == nullptr) {
                        stream << "\"" << children[i] << "\"[label = \"0\", shape=ellipse];" << std::endl;
                    } else {
                        stream << "\"" << children[i] << "\"[label = \"" << static_cast<Leaf *>(children[i])->key
                                  << "\", shape=ellipse];" << std::endl;
                    }
                } else {
                    stream << static_cast<Node *>(children[i])->generateDotCode();
                }
                stream << "\"" << this << "\":f" << i << " -> \"" << children[i] << "\";" << std::endl;

            }

            return stream.str();
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

        Node *insert(Leaf *leaf, ProfilingResults *profiling) {
            Node *result = nullptr;
            profiling->insertFileAccess++;

            int index = 0;
            if(filling > 0) {
                profiling->insertComparisons++;

            }
            while (index < filling && keys[index] <= leaf->key) {
                ++index;
                if(index < filling) {
                    profiling->insertComparisons++;
                }
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
                        if(leaf->key < static_cast<Leaf *>(children[0])->key) {
                            children[0] = leaf;
                        } else {
                            children[0] = children[1];
                            children[1] = leaf;
                        }
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
                res = static_cast<Node *>(children[index])->insert(leaf,profiling);

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

        const T *search(int key, ProfilingResults *profiling) {
            const T *result = nullptr;
            profiling->searchFileAccess++;

            if (filling > 0) {
                int index = 0;
                if(filling > 0) {
                    profiling->searchComparisons++;
                }
                while (index < filling && keys[index] <= key) {
                    ++index;
                    if(index < filling) {
                        profiling->searchComparisons++;
                    }
                }

                if (deepest) {
                    profiling->searchComparisons++;
                    if (children[index] != nullptr && static_cast<Leaf *>(children[index])->key == key) {
                        result = static_cast<Leaf *>(children[index])->data;

                    }
                } else {
                    result = static_cast<Node *>(children[index])->search(key, profiling);
                }
            }

            return result;
        }

        Node *remove(int key, ProfilingResults *profiling, bool* removeResult) {
            Node *result = nullptr;
            profiling->removeFileAccess++;

            if (filling > 0) {
                int index = 0;
                if(filling > 0) {
                    profiling->removeComparisons++;
                }
                while (index < filling && keys[index] <= key) {
                    ++index;
                    if(index < filling) {
                        profiling->removeComparisons++;
                    }
                }

                if (deepest) {
                    profiling->removeComparisons++;
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
                        *removeResult = true;
                    }
                } else {
                    Node *res = static_cast<Node *>(children[index])->remove(key,profiling,removeResult);
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

                    for (int i = leftFormerFilling; i > overallFilling / 2 + 1; --i) {
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
