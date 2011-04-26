#include <iostream>
using namespace std;

class HelloWorld {
 private:
  string hello;
 public:
  HelloWorld() : hello("Hello, World!") {}
  void set(string hello_) {
    hello = hello_;
  }
  void run() {
    cout << hello << endl;
  }
};

int main(int argc, char **argv) {
  HelloWorld hello;
  if (argc > 1) {
    hello.set(argv[1]);
  }
  hello.run();
}
