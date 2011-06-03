#include <iostream>
using namespace std;

class Hello {
 public:
  Hello() {}
  Hello(string message) : message_(message) {}
  virtual ~Hello() {}
  void run() {
    cout << "Hello, " << message_ << endl;
  }
 protected:
  string message_;
};
  
int main() {
  Hello hello("World");
  hello.run();
  return 0;
}
