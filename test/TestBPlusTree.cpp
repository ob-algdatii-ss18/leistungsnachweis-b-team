//
// Created by ms1511 on 01.05.18.
//

#include "gtest.h"
#include "BPlusTree.h"

using namespace std;


TEST(BPlusTreeM1, SearchInAEmptyTree) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    const string* result = tree->search(5);

    ASSERT_EQ(result, nullptr);
}

TEST(BPlusTreeM1, SearchNotExistingElemnt) {
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

TEST(BPlusTreeM1, InsertAndSearchOneElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data);

    const string* result = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(*result, data);
}

TEST(BPlusTreeM1, InsertAndSearchTwoElementsLowerKeyFirst) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
}

TEST(BPlusTreeM1, InsertAndSearchTwoElementsLowerKeySecond) {
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

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
}

TEST(BPlusTreeM1, InsertAndSearchThreeElements) {
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

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
}

TEST(BPlusTreeM1, InsertAndSearchFourElements) {
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

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
}

TEST(BPlusTreeM1, InsertAndSearchFiveElements) {
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
    tree->insert(&data2);
    tree->insert(&data3);
    tree->insert(&data4);
    tree->insert(&data5);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);
    const string *result5 = tree->search(key5);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
    ASSERT_EQ(*result5, data5);
}

TEST(BPlusTreeM1, InsertAndSearchNineElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    const string data4 = "te";
    const string data5 = "t";
    const string data6 = "666666";
    const string data7 = "7777777";
    const string data8 = "88888888";
    const string data9 = "999999999";

    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);
    int key4 = keyConverter(data4);
    int key5 = keyConverter(data5);
    int key6 = keyConverter(data6);
    int key7 = keyConverter(data7);
    int key8 = keyConverter(data8);
    int key9 = keyConverter(data9);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->insert(&data3);
    tree->insert(&data4);
    tree->insert(&data5);
    tree->insert(&data6);
    tree->insert(&data7);
    tree->insert(&data8);
    tree->insert(&data9);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);
    const string *result5 = tree->search(key5);
    const string *result6 = tree->search(key6);
    const string *result7 = tree->search(key7);
    const string *result8 = tree->search(key8);
    const string *result9 = tree->search(key9);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
    ASSERT_EQ(*result5, data5);
    ASSERT_EQ(*result6, data6);
    ASSERT_EQ(*result7, data7);
    ASSERT_EQ(*result8, data8);
    ASSERT_EQ(*result9, data9);
}

TEST(BPlusTreeM1, InsertAndSearchTenElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    const string data4 = "te";
    const string data5 = "t";
    const string data6 = "666666";
    const string data7 = "7777777";
    const string data8 = "88888888";
    const string data9 = "999999999";
    const string data10 = "";

    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);
    int key4 = keyConverter(data4);
    int key5 = keyConverter(data5);
    int key6 = keyConverter(data6);
    int key7 = keyConverter(data7);
    int key8 = keyConverter(data8);
    int key9 = keyConverter(data9);
    int key10 = keyConverter(data10);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->insert(&data3);
    tree->insert(&data4);
    tree->insert(&data5);
    tree->insert(&data6);
    tree->insert(&data7);
    tree->insert(&data8);
    tree->insert(&data9);
    tree->insert(&data10);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);
    const string *result5 = tree->search(key5);
    const string *result6 = tree->search(key6);
    const string *result7 = tree->search(key7);
    const string *result8 = tree->search(key8);
    const string *result9 = tree->search(key9);
    const string *result10 = tree->search(key10);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
    ASSERT_EQ(*result5, data5);
    ASSERT_EQ(*result6, data6);
    ASSERT_EQ(*result7, data7);
    ASSERT_EQ(*result8, data8);
    ASSERT_EQ(*result9, data9);
    ASSERT_EQ(*result10, data10);
}

TEST(BPlusTreeM1, RemoveFromEmptyTree) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    tree->remove(2);

    const string* result = tree->search(2);

    cout << *tree << endl;

    ASSERT_EQ(result, nullptr);
}

TEST(BPlusTreeM1, RemoveNotExisingElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data);
    tree->remove(2);
    const string* result1 = tree->search(2);
    const string* result2 = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data);
}

TEST(BPlusTreeM1, InsertAndRemoveOneElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data);
    tree->remove(key);

    const string* result = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(result, nullptr);
}

TEST(BPlusTreeM1, InsertTwoElementsRemoveTheLowerKeyElement) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->remove(key1);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data2);
}

TEST(BPlusTreeM1, InsertTwoElementsRemoveTheUpperKeyElement) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->remove(key2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(result2, nullptr);
}

TEST(BPlusTreeM1, InsertThreeElementsRemoveLeft) {
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

    tree->remove(key2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);;

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(result2, nullptr);
    ASSERT_EQ(*result3, data3);
}

TEST(BPlusTreeM1, InsertThreeElementsRemoveMiddle) {
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

    tree->remove(key1);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);;

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
}

TEST(BPlusTreeM1, InsertThreeElementsRemoveRight) {
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

    tree->remove(key3);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);;

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(result3, nullptr);
}

TEST(BPlusTreeM1, InsertFourElementsRemoveOne) {
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

    tree->remove(key1);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
}

TEST(BPlusTreeM1, InsertFiveElementsRemoveOne) {
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
    tree->insert(&data2);
    tree->insert(&data3);
    tree->insert(&data4);
    tree->insert(&data5);
    tree->remove(key1);


    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);
    const string *result3 = tree->search(key3);
    const string *result4 = tree->search(key4);
    const string *result5 = tree->search(key5);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data2);
    ASSERT_EQ(*result3, data3);
    ASSERT_EQ(*result4, data4);
    ASSERT_EQ(*result5, data5);
}

/*
TEST(BPlusTreeM1, InsertTwentyOneElementsRemoveAllFromFirstToLast) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    cout << "*tree: " << *tree << endl;

    for (int removeElementIndex = 0; removeElementIndex < elementCount; ++removeElementIndex) {
        cout << "keys[removeElementIndex]: " << keys[removeElementIndex] << endl;
        cout << *tree << endl;
        tree->remove(keys[removeElementIndex]);
        for (int i = 0; i < elementCount; ++i) {
            if (i <= removeElementIndex) {
                ASSERT_EQ(tree->search(keys[i]), nullptr);
            } else {
                ASSERT_EQ(*tree->search(keys[i]), data[i]);
            }
        }
    }
}

TEST(BPlusTreeM1, InsertTwentyOneElementsRemoveAllFromLastToFirst) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 1);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    cout << *tree << endl;

    for (int removeElementIndex = elementCount-1; removeElementIndex >= 0; --removeElementIndex) {

        tree->remove(keys[removeElementIndex]);

        cout << *tree << endl;

        for (int i = elementCount -1; i >= 0; --i) {
            if (i >= removeElementIndex) {
                ASSERT_EQ(tree->search(keys[i]), nullptr);
            } else {
                ASSERT_EQ(*tree->search(keys[i]), data[i]);
            }
        }
    }
}
*/

TEST(BPlusTreeM2, InsertSixElements) {
    int elementCount = 6;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    cout << *tree << endl;

    for (int i = 0; i < elementCount; ++i) {
        ASSERT_EQ(*tree->search(keys[i]), data[i]);
    }
}

TEST(BPlusTreeM2, InsertTwentyOneElements) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    cout << *tree << endl;

    for (int i = 0; i < elementCount; ++i) {
        ASSERT_EQ(*tree->search(keys[i]), data[i]);
    }
}

TEST(BPlusTreeM2, InsertSixElementsRemoveFirst) {
    int elementCount = 6;
    int removeElementIndex = 0;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    tree->remove(keys[removeElementIndex]);

    cout << *tree << endl;

    for (int i = 0; i < elementCount; ++i) {
        if(i == removeElementIndex) {
            ASSERT_EQ(tree->search(keys[i]), nullptr);
        } else {
            ASSERT_EQ(*tree->search(keys[i]), data[i]);
        }
    }
}

TEST(BPlusTreeM2, InsertSevenElementsRemoveFirst) {
    int elementCount = 7;
    int removeElementIndex = 0;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    tree->remove(keys[removeElementIndex]);

    cout << *tree << endl;

    for (int i = 0; i < elementCount; ++i) {
        if(i == removeElementIndex) {
            ASSERT_EQ(tree->search(keys[i]), nullptr);
        } else {
            ASSERT_EQ(*tree->search(keys[i]), data[i]);
        }
    }
}

TEST(BPlusTreeM2, InsertTwentyOneElementsRemoveFirst) {
    int elementCount = 21;
    int removeElementIndex = 0;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    tree->remove(keys[removeElementIndex]);

    cout << *tree << endl;

    for (int i = 0; i < elementCount; ++i) {
        if(i == removeElementIndex) {
            ASSERT_EQ(tree->search(keys[i]), nullptr);
        } else {
            ASSERT_EQ(*tree->search(keys[i]), data[i]);
        }
    }
}

TEST(BPlusTreeM2, InsertTwentyOneElementsRemoveAllFromFirstToLast) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    cout << *tree << endl;

    for (int removeElementIndex = 0; removeElementIndex < elementCount; ++removeElementIndex) {

        tree->remove(keys[removeElementIndex]);

        cout << *tree << endl;

        for (int i = 0; i < elementCount; ++i) {
            if (i <= removeElementIndex) {
                ASSERT_EQ(tree->search(keys[i]), nullptr);
            } else {
                ASSERT_EQ(*tree->search(keys[i]), data[i]);
            }
        }
    }
}

TEST(BPlusTreeM2, InsertTwentyOneElementsRemoveAllFromLastToFirst) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    cout << *tree << endl;

    for (int removeElementIndex = elementCount-1; removeElementIndex >= 0; --removeElementIndex) {

        tree->remove(keys[removeElementIndex]);

        cout << *tree << endl;

        for (int i = elementCount -1; i >= 0; --i) {
            if (i >= removeElementIndex) {
                ASSERT_EQ(tree->search(keys[i]), nullptr);
            } else {
                ASSERT_EQ(*tree->search(keys[i]), data[i]);
            }
        }
    }
}

TEST(BPlusTree, UltimateInsertAndDeleteTest) {
    int elementCount = 1000;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };


    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int lowerBtreeCriteria = 2; lowerBtreeCriteria < 10; ++lowerBtreeCriteria) {
        cout << "lowerBtreeCriteria: " << lowerBtreeCriteria << endl;
        BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, lowerBtreeCriteria);

        for (int i = 0; i < elementCount; ++i) {
            tree->insert(&data[i]);
        }

        for (int removeElementIndex = 0; removeElementIndex < elementCount; ++removeElementIndex) {
            tree->remove(keys[removeElementIndex]);

            for (int i = 0; i < elementCount; ++i) {
                if(i <= removeElementIndex) {
                    ASSERT_EQ(tree->search(keys[i]), nullptr);
                } else {
                    ASSERT_EQ(*tree->search(keys[i]), data[i]);
                }
            }
        }

        for (int i = 0; i < elementCount; ++i) {
            tree->insert(&data[i]);
        }

        for (int removeElementIndex = elementCount - 1; removeElementIndex >= 0; --removeElementIndex) {
            tree->remove(keys[removeElementIndex]);

            for (int i = elementCount - 1; i >= 0; --i) {
                if(i >= removeElementIndex) {
                    ASSERT_EQ(tree->search(keys[i]), nullptr);
                } else {
                    ASSERT_EQ(*tree->search(keys[i]), data[i]);
                }
            }
        }
    }
}