//
// Created by offline on 04.06.2018.
//

#ifndef LEISTUNGSNACHWEIS_B_TEAM_SORTLIST_H
#define LEISTUNGSNACHWEIS_B_TEAM_SORTLIST_H

#include "Collection.h"
#include <iostream>

template<class T>
class SortList : public Collection<T>  {

private:
    struct Element {
        Element(int key, const T *data) : key(key), data(data) {

        }

        int key;
        const T *data;
        Element *next = nullptr;
    };
    Element *root = nullptr;
    int mSize;

public:
    SortList(const std::function<int(T)> &keyConverter, int mSize) : Collection<T>(keyConverter), mSize(mSize){
        root = nullptr;
    }

    bool insert(const T *t) override{
        int newElementKey = Collection<T>::valueToKeyConverter(*t);
        Element *elem = new Element(newElementKey,t);
        if (nullptr == root){
            root = elem;
            return true;
        }
        Element* runner = root;
        while (runner->next != nullptr && runner->next->key < root->key){
            //Iterate
            runner = runner->next;
            //insert counting here
        }
        //insert at place
        Element *other = runner->next;
        elem->next = other;
        runner->next = elem;
        return true;
    }

    const T *search(int key){

        if (root== nullptr){
            return nullptr;
        }
        else
        {
            Element *runner = root;
            while (runner != nullptr && runner->key < key){
                runner = runner->next;
            }
            if (runner == nullptr){
                return nullptr;
            }
            else if (runner->key == key){
                return runner->data;
            }
            else {
                return nullptr;
            }
        }

    }

    bool remove(int key){
        if (root== nullptr){
            return false;
        }
        else if (root->key = key){
            root = root->next;
        }
        else
        {
            //remove first object
            Element *runner = root;
            while (runner->next != nullptr && runner->next->key < key){
                runner = runner->next;
            }
            //check if existant
            if (runner->next == nullptr){
                return false;
            }
            else if (runner->next->key == key){
                Element *result = runner->next;
                runner->next = result->next;
                return true;
            }else
            {
                return false;
            }
        }
    };

    friend std::ostream &operator<<(std::ostream &os, const SortList &list) {
        // 2m as max key count, 3 digits per key max, 2-Times because of comma, plus 2 for ()
        /*
        int blocksize = 2 * tree.m * 3 * 2 + 2;
        int depth = tree.treeDepth();
        os << std::string(blocksize * (depth / 2), ' ') << tree.root << std::string(blocksize * (depth / 2), ' ')
           << std::endl;
        */

        //os << *tree.root;

        //return os;
        os << "nix";
        return os;
    }


};


#endif //LEISTUNGSNACHWEIS_B_TEAM_SORTLIST_H
