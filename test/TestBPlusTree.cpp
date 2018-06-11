//
// Created by ms1511 on 01.05.18.
//

#include "gtest.h"
#include "SortList.h"
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
    ProfilingResults *profilingResults = new ProfilingResults();

    BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 2);
    tree->insert(&data, profilingResults);
    ASSERT_EQ(profilingResults->insertFileAccess, 1);
    ASSERT_EQ(profilingResults->insertComparisons, 0);

    const string* result1 = tree->search(key, profilingResults);
    ASSERT_EQ(profilingResults->searchFileAccess, 1);
    ASSERT_EQ(profilingResults->searchComparisons, 2);
    const string* result2 = tree->search(1, profilingResults);
    ASSERT_EQ(profilingResults->searchFileAccess, 2);
    ASSERT_EQ(profilingResults->searchComparisons, 4);
    const string* result3 = tree->search(8, profilingResults);
    ASSERT_EQ(profilingResults->searchFileAccess, 3);
    ASSERT_EQ(profilingResults->searchComparisons, 6);

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

    cout << *tree << endl;

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
    ProfilingResults *profilingResults = new ProfilingResults();

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    tree->remove(keys[removeElementIndex], profilingResults);
    cout << *tree << endl;
    ASSERT_EQ(profilingResults->removeFileAccess, 2);
    ASSERT_EQ(profilingResults->removeComparisons, 3);

    cout << *tree << endl;

    for (int i = 0; i < elementCount; ++i) {
        if(i == removeElementIndex) {
            ASSERT_EQ(tree->search(keys[i], profilingResults), nullptr);
        } else {
            ASSERT_EQ(*tree->search(keys[i], profilingResults), data[i]);
        }
    }

    ASSERT_EQ(profilingResults->searchFileAccess, 14);
    ASSERT_EQ(profilingResults->searchComparisons, 25);
}

TEST(BPlusTree, InsertTwentyOneElementsRemoveFirst) {
    int elementCount = 21;
    int removeElementIndex = 0;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
    ProfilingResults *profilingResults = new ProfilingResults();

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i], profilingResults);
    }

    tree->remove(keys[removeElementIndex], profilingResults);
    ASSERT_EQ(profilingResults->removeFileAccess, 3);
    ASSERT_EQ(profilingResults->removeComparisons, 4);

    cout << *tree << endl;

    for (int i = 0; i < elementCount; ++i) {
        if(i == removeElementIndex) {
            ASSERT_EQ(tree->search(keys[i], profilingResults), nullptr);
        } else {
            ASSERT_EQ(*tree->search(keys[i], profilingResults), data[i]);
        }
    }
    ASSERT_EQ(profilingResults->searchFileAccess, 63);
    ASSERT_EQ(profilingResults->searchComparisons, 115);
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



TEST(SortList, SearchInAEmptyTree) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };

    SortList<string> * tree = new SortList<string>(keyConverter, 2);
    const string* result = tree->search(5);

    ASSERT_EQ(result, nullptr);
}


TEST(SortList, InsertAndSearchOneElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    SortList<string> * tree = new SortList<string>(keyConverter, 2);
    tree->insert(&data);

    const string* result = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(*result, data);
}

TEST(SortList, InsertAndSearchTwoElementsLowerKeyFirst) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
}

TEST(SortList, InsertAndSearchTwoElementsLowerKeySecond) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(*result2, data2);
}
/*
TEST(SortList, InsertAndSearchThreeElements) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
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

TEST(SortList, RemoveFromEmptyTree) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };

    SortList<string> * tree = new SortList<string>(keyConverter, 2);
    tree->remove(2);

    const string* result = tree->search(2);

    cout << *tree << endl;

    ASSERT_EQ(result, nullptr);
}

TEST(SortList, RemoveNotExisingElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    SortList<string> * tree = new SortList<string>(keyConverter, 2);
    tree->insert(&data);
    tree->remove(2);
    const string* result1 = tree->search(2);
    const string* result2 = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data);
}

TEST(SortList, InsertAndRemoveOneElement) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    SortList<string> * tree = new SortList<string>(keyConverter, 2);
    tree->insert(&data);
    tree->remove(key);

    const string* result = tree->search(key);

    cout << *tree << endl;

    ASSERT_EQ(result, nullptr);
}
//problem before here

TEST(SortList, InsertTwoElementsRemoveTheLowerKeyElement) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->remove(key1);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(result1, nullptr);
    ASSERT_EQ(*result2, data2);
}

TEST(SortList, InsertTwoElementsRemoveTheUpperKeyElement) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "tes";
    const string data2 = "test";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
    tree->insert(&data1);
    tree->insert(&data2);
    tree->remove(key2);

    const string *result1 = tree->search(key1);
    const string *result2 = tree->search(key2);

    cout << *tree << endl;

    ASSERT_EQ(*result1, data1);
    ASSERT_EQ(result2, nullptr);
}

TEST(SortList, InsertThreeElementsRemoveLeft) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
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

TEST(SortList, InsertThreeElementsRemoveMiddle) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
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

TEST(SortList, InsertThreeElementsRemoveRight) {
    std::function<int(string)> keyConverter = [](string s) { return (int) s.size(); };
    const string data1 = "test";
    const string data2 = "tes";
    const string data3 = "test5";
    int key1 = keyConverter(data1);
    int key2 = keyConverter(data2);
    int key3 = keyConverter(data3);

    SortList<string> *tree = new SortList<string>(keyConverter, 2);
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

TEST(SortList, InsertSixElements) {
    int elementCount = 6;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *tree = new SortList<string>(keyConverter, 2);

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

TEST(SortList, InsertTwentyOneElements) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *tree = new SortList<string>(keyConverter, 2);

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

TEST(SortList, InsertSixElementsRemoveFirst) {
    int elementCount = 6;
    int removeElementIndex = 0;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *tree = new SortList<string>(keyConverter, 2);

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

TEST(SortList, InsertTwentyOneElementsRemoveAllFromFirstToLast) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *tree = new SortList<string>(keyConverter, 2);

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

TEST(SortList, InsertTwentyOneElementsRemoveAllFromLastToFirst) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *tree = new SortList<string>(keyConverter, 2);

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

TEST(SortList, UltimateInsertAndDeleteTest) {
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
        SortList<string> *tree = new SortList<string>(keyConverter, lowerBtreeCriteria);

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

TEST(SortList, InsertTwentyOneElementsRemoveAllAndRefill) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *tree = new SortList<string>(keyConverter, 2);

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

TEST(SortListMemory, InsertTwentyOneElementsRemoveAllFromLastToFirstMemory) {
    int elementCount = 21;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *tree = new SortList<string>(keyConverter, 2);

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

 */
