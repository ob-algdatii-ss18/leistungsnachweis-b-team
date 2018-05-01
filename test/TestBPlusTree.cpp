//
// Created by ms1511 on 01.05.18.
//
/*
#include "gtest.h"
#include "BPlusTree.h"

using namespace std;

TEST(BPlusTree, InsertAndSearch) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data);

    string* result = tree->search(key);

    ASSERT_EQ(*result, data);
}
 */