//
// Created by ms1511 on 01.05.18.
//

#include "gtest.h"
#include "BPlusTree.h"

using namespace std;


TEST(BPlusTree, SearchInAEmptyTree) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    const string* result = tree->search(5);

    ASSERT_EQ(result, nullptr);
}

TEST(BPlusTree, SearchNotExistingElemnt) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data);

    const string* result1 = tree->search(key);
    const string* result2 = tree->search(1);
    const string* result3 = tree->search(8);

    ASSERT_EQ(*result1, data);
    ASSERT_EQ(result2, nullptr);
    ASSERT_EQ(result3, nullptr);
}

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
    const string *result3 = tree->search(key3);;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
}

TEST(BPlusTree, InsertAndSearchFourElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    const string data4 = "te";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);
    int key4 = keyConverter(data4);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->insert(&data3);
    tree->insert(&data4);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
}

TEST(BPlusTree, InsertAndSearchFiveElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    const string data4 = "te";
    const string data5 = "t";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);
    int key4 = keyConverter(data4);
    int key5 = keyConverter(data5);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    cout << *tree << endl;
    tree->insert(&data2);
    cout << *tree << endl;
    tree->insert(&data3);
    cout << *tree << endl;
    tree->insert(&data4);
    cout << *tree << endl;
    tree->insert(&data5);
    cout << *tree << endl;

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);
    const string *result5 = tree->search(key5);

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
    ASSERT_EQ(*result5, data5);
}

TEST(BPlusTree, InsertAndSearchSevenElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    const string data4 = "te";
    const string data5 = "t";
    const string data6 = "666666";
    const string data7 = "7777777";

    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);
    int key4 = keyConverter(data4);
    int key5 = keyConverter(data5);
    int key6 = keyConverter(data6);
    int key7 = keyConverter(data7);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->insert(&data3);
    tree->insert(&data4);
    tree->insert(&data5);
    tree->insert(&data6);
    tree->insert(&data7);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);
    const string *result5 = tree->search(key5);
    const string *result6 = tree->search(key6);
    const string *result7 = tree->search(key7);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
    ASSERT_EQ(*result5, data5);
    ASSERT_EQ(*result6, data6);
    ASSERT_EQ(*result7, data7);
}