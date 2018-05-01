//
// Created by ms1511 on 01.05.18.
//

#include "gtest.h"
#include "BPlusTree.h"

using namespace std;

TEST(BPlusTree, InsertAndSearchOneElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data);

    const string* result = tree->search(key);

    ASSERT_EQ(*result, data);
}

TEST(BPlusTree, InsertAndSearchTwoElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
}

TEST(BPlusTree, InsertAndSearchThreeElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->insert(&data3);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
}