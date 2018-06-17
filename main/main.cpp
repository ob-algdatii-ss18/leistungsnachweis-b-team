#include <iostream>
#include <functional>
#include <BPlusTree.h>
#include <SortList.h>

using namespace std;

void benchamrk() {
    int elementCount = 21;
    string *data = new string[elementCount];

    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
    SortList<string> *list = new SortList<string>(keyConverter, 2);

    ProfilingResults *treeProfile = new ProfilingResults();
    ProfilingResults *listProfile = new ProfilingResults();

    for (int i = 0; i < elementCount; ++i) {
        data[i] = std::to_string(i * 2 + 2);
    }

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i], treeProfile);
        list->insert(&data[i], listProfile);
    }

    for (int i = 0; i < elementCount; ++i) {
        int key = keyConverter(data[i]);

        if(tree->search(key, treeProfile) != list->search(key, listProfile)) {
            cout << "ERROR" << endl;
        }
    }

    cout << "treeProfile->insertComparisons: " << treeProfile->insertComparisons << endl;
    cout << "listProfile->insertComparisons: " << listProfile->insertComparisons << endl;
    cout << "treeProfile->insertFileAccess: " << treeProfile->insertFileAccess << endl;
    cout << "listProfile->insertFileAccess: " << listProfile->insertFileAccess << endl;
    cout << "treeProfile->searchComparisons: " << treeProfile->searchComparisons << endl;
    cout << "listProfile->searchComparisons: " << listProfile->searchComparisons << endl;
    cout << "treeProfile->searchFileAccess: " << treeProfile->searchFileAccess << endl;
    cout << "listProfile->searchFileAccess: " << listProfile->searchFileAccess << endl;
}

void dotcode() {
  int elementCount = 21;
  string *data = new string[elementCount];
  std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
  BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);
  ProfilingResults *treeProfile = new ProfilingResults();

  for (int i = 0; i < elementCount; ++i) {
    data[i] = std::to_string(i * 2 + 2);
  }

  for (int i = 0; i < elementCount; ++i) {
    tree->insert(&data[i], treeProfile);
    tree->generateDotFile();
  }
}

// main program for benchmarking
int main(int argc, char *argv[]) {

//    benchamrk();

  dotcode();
}
