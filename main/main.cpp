#include <iostream>
#include <functional>


using namespace std;

// main program for benchmarking
int main (int argc, char *argv[]) {
  std::function<int(string)> keyConverter = [](string s){ return s.size(); };

  cout << keyConverter("test");


}
