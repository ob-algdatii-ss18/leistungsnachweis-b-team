//
// Created by ms1511 on 01.05.18.
//

#include "gtest.h"
#include "BPlusTree.h"

using namespace std;


TEST(BPlusTree, SearchInAEmptyTree) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 2);
    const string* result = tree->search(5);

    ASSERT_EQ(result, nullptr);
}

TEST(BPlusTree, SearchNotExistingElemnt) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 2);
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

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data);

    const string* result = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(*result, data);
}

TEST(BPlusTree, InsertAndSearchTwoElementsLowerKeyFirst) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
}

TEST(BPlusTree, InsertAndSearchTwoElementsLowerKeySecond) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

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

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
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

TEST(BPlusTree, RemoveFromEmptyTree) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 2);
    tree->remove(2);

    const string* result = tree->search(2);

    cout << *tree << endl;

    ASSERT_EQ(result, nullptr);
}

TEST(BPlusTree, RemoveNotExisingElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data);
    tree->remove(2);
    const string* result1 = tree->search(2);
    const string* result2 = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data);
}

TEST(BPlusTree, InsertAndRemoveOneElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data);
    tree->remove(key);

    const string* result = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(result, nullptr);
}

TEST(BPlusTree, InsertTwoElementsRemoveTheLowerKeyElement) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->remove(key1);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data2);
}

TEST(BPlusTree, InsertTwoElementsRemoveTheUpperKeyElement) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->remove(key2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(result2, nullptr);
}

TEST(BPlusTree, InsertThreeElementsRemoveLeft) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
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

TEST(BPlusTree, InsertThreeElementsRemoveMiddle) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
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

TEST(BPlusTree, InsertThreeElementsRemoveRight) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
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

TEST(BPlusTree, InsertSixElements) {
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

TEST(BPlusTree, InsertTwentyOneElements) {
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
    tree->generateDotCode();

    for (int i = 0; i < elementCount; ++i) {
        ASSERT_EQ(*tree->search(keys[i]), data[i]);
    }
}

TEST(BPlusTree, InsertSixElementsRemoveFirst) {
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

TEST(BPlusTree, InsertSevenElementsRemoveFirst) {
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

TEST(BPlusTree, InsertTwentyOneElementsRemoveFirst) {
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

TEST(BPlusTree, InsertTwentyOneElementsRemoveAllFromFirstToLast) {
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

TEST(BPlusTree, InsertTwentyOneElementsRemoveAllFromLastToFirst) {
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

        cout << keys[removeElementIndex] << endl;

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

TEST(BPlusTree, InsertTwentyOneElementsRemoveAllAndRefill) {
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

    for (int elementIndex = elementCount-1; elementIndex >= 0; --elementIndex) {

        tree->insert(&data[elementIndex]);

        cout << *tree << endl;
    }

    delete[] data;
    delete[] keys;
}

TEST(BPlusTreeMemory, InsertTwentyOneElementsRemoveAllFromLastToFirstMemory) {
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

    delete[] data;
    delete[] keys;
}