//
// Created by offline on 04.06.2018.
//

#include "gtest.h"
#include "SortList.h"

using namespace std;


TEST(SortListM1, InsertSearchRemoveOne) {
    std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
    const string data = "test";
    int key = keyConverter(data);

    SortList<string> * list = new SortList<string>(keyConverter, 1);
    const string *isNotThere = list->search(5);
    list->insert(&data);
    const string *isThere = list->search(4);
    const string *isNotThere2 = list->search(5);
    ASSERT_EQ(&data , isThere);
    ASSERT_EQ(nullptr, isNotThere);
    ASSERT_EQ(nullptr, isNotThere2);
    bool removed = list->remove(4);
    ASSERT_TRUE(removed);
}
TEST(SortListM1, InsertSearchRemoveTwenty) {
    int elementCount = 2;

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    SortList<string> *list = new SortList<string>(keyConverter, 2);

    string *data = new string[elementCount];
    int *keys = new int[elementCount];
    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
        keys[i] = keyConverter(data[i]);
    }

    for (int i = 0; i < elementCount; ++i) {
        list->insert(&data[i]);
    }

    //cout << *list << endl;

    for (int i = 0; i < elementCount; ++i) {
        ASSERT_EQ(*list->search(keys[i]), data[i]);
    }
}

