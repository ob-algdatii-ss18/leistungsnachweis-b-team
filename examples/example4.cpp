#include <iostream>
#include <functional>
#include <BPlusTree.h>

using namespace std;

int main(int argc, char **argv) {
    std::function<int(string)> keyConverter = [](string s) { return (int) std::stoi(s); };
    BPlusTree<string> *tree = new BPlusTree<string>(keyConverter, 2);

    int removeElement = 22;
    int elementCount = 17;
    string data[] = {"2", "4", "6", "8", "10", "12", "14", "16", "18", "20", "22", "24", "26", "28", "30", "32", "34"};

    for (int i = 0; i < elementCount; ++i) {
        tree->insert(&data[i]);
    }

    tree->generateDotFile();

    tree->insert(new string("36"));

    tree->generateDotFile();

    tree->remove(removeElement);

    tree->generateDotFile();
}