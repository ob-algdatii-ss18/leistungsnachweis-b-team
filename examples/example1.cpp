#include <iostream>
#include <functional>
#include <BPlusTree.h>

using namespace std;

int main(int argc, char **argv) {
    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 3);

    int elementCount = 8;
    string data[] = {"2", "4", "6", "8", "10", "12", "14", "1"};

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    tree->generateDotFile();

    tree->remove(14);

    tree->generateDotFile();
}