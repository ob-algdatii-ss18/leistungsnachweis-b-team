#include <iostream>
#include <functional>
#include <BPlusTree.h>
#include <test.h>

using namespace std;


void test1();
void test2();
void test3();


// main program for benchmarking
int main (int argc, char *argv[]) {

  test1();
  test2();
  test3();

/*
  string t = "test1";
  tree->insert(&t);
  string u = "tes";
  tree->insert(&u);
  string* res = tree->search(5);
  cout << "res: " << *res << endl;


  string v = "test66";
  tree->insert(&v);
*/
}

void test1() {
  std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
  string data = "test";
  int key = keyConverter(data);

  cout << "------------------" << endl;
  cout << "TEST 1" << endl;
  BPlusTree<string> * tree1 = new BPlusTree<string>(keyConverter, 1);
  tree1->insert(&data);
  string* result1 = tree1->search(key);
  if(*result1 == data) {
    cout << "-> SUCCESS" << endl;
  } else {
    cout << "-> FAILED" << endl;
  }
  cout << "------------------" << endl;
}

void test2() {
  std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
  string data1 = "test";
  string data2 = "tes";
  int key1 = keyConverter(data1);
  int key2 = keyConverter(data2);

  cout << "------------------" << endl;
  cout << "TEST 2" << endl;
  BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
  tree->insert(&data1);
  tree->insert(&data2);

  string* result1 = tree->search(key1);
  if(*result1 == data1) {
    cout << "-> SUCCESS1" << endl;
  } else {
    cout << "-> FAILED1" << endl;
  }
  string* result2 = tree->search(key2);

  if(*result2 == data2) {
    cout << "-> SUCCESS2" << endl;
  } else {
    cout << "-> FAILED2" << endl;
  }
  cout << "------------------" << endl;
}

void test3() {
  std::function<int(string)> keyConverter = [](string s){ return (int)s.size(); };
  string data1 = "test";
  string data2 = "tes";
  string data3 = "test5";
  int key1 = keyConverter(data1);
  int key2 = keyConverter(data2);
  int key3 = keyConverter(data3);

  cout << "------------------" << endl;
  cout << "TEST 3" << endl;
  BPlusTree<string> * tree = new BPlusTree<string>(keyConverter, 1);
  tree->insert(&data1);
  tree->insert(&data2);
  tree->insert(&data3);

  string* result1 = tree->search(key1);
  if(*result1 == data1) {
    cout << "-> SUCCESS1" << endl;
  } else {
    cout << "-> FAILED1" << endl;
  }

  string* result2 = tree->search(key2);
  if(*result2 == data2) {
    cout << "-> SUCCESS2" << endl;
  } else {
    cout << "-> FAILED2" << endl;
  }

  string* result3 = tree->search(key3);
  if(*result3 == data3) {
    cout << "-> SUCCESS3" << endl;
  } else {
    cout << "-> FAILED3" << endl;
  }
  cout << "------------------" << endl;
}
