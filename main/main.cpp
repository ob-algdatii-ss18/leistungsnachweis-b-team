#include <iostream>
#include <functional>
#include <BPlusTree.h>
#include <test.h>


using namespace std;

// main program for benchmarking
int main (int argc, char *argv[]) {
  std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };


  BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 4);



  cout << keyConverter("test");


}
