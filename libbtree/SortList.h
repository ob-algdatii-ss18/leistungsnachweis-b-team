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

    bool insert(const T *t) override {
        auto profilingResults = new ProfilingResults();
        return insert (t, profilingResults);
    }

    bool insert(const T* t, ProfilingResults* p) override {
        int newElementKey = Collection<T>::valueToKeyConverter(*t);
        auto elem = new Element(newElementKey,t);
        int comparisonCount = 0;
        if (nullptr == root){
            root = elem;
            return true;
        }
        if (root->key > newElementKey){
            p->insertComparisons++;
            p->insertFileAccess++;
            elem->next = root;
            root = elem;
            return true;
        }
        Element* runner = root;
        while (runner->next != nullptr && runner->next->key < newElementKey){
            comparisonCount++;
            //Iterate
            runner = runner->next;
            //insert counting here
        }
        comparisonCount++;
        p->insertComparisons += comparisonCount;
        p->insertFileAccess += comparisonCount / (2 * mSize);
        //insert at place
        Element *other = runner->next;
        elem->next = other;
        runner->next = elem;
        return true;
    }

    const T *search(int key) override {
        auto profilingResults = new ProfilingResults();
        return search (key, profilingResults);

    }

    const T *search(int key, ProfilingResults* p) override {
        int comparisonCount = 0;
        const T* result = nullptr;
        if (root== nullptr){
            return nullptr;
        }
        else
        {
            Element *runner = root;
            while (runner != nullptr && runner->key < key){
                comparisonCount++;
                runner = runner->next;
            }
            comparisonCount++;
            if (runner != nullptr && runner->key == key){
                comparisonCount++;
                result = runner->data;
            }
        }
        p->searchComparisons += comparisonCount;
        p->searchFileAccess += comparisonCount / (2 * mSize) + 1;
        return result;
    }

    bool remove(int key) override {
        auto profilingResults = new ProfilingResults();
        return remove (key, profilingResults);

    }

    bool remove(int key, ProfilingResults* p) override {
        bool totalResult = false;
        int comparisonCount = 0;
        if (root== nullptr){
            return false;
        }
        else if (root->key == key){
            p->removeComparisons++;
            root = root->next;
        }
        else
        {
            //remove first object
            Element *runner = root;
            while (runner->next != nullptr && runner->next->key < key){
                comparisonCount++;
                runner = runner->next;
            }
            comparisonCount++;
            //check if existant
            if (runner->next != nullptr && runner->next->key == key){
                comparisonCount++;
                Element *result = runner->next;
                runner->next = result->next;
                totalResult = true;
            }
            p->removeComparisons += comparisonCount;
            p->removeFileAccess += comparisonCount / (2 * mSize) + 1;
        }
        return totalResult;
    }

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
