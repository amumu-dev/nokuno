#include <iostream>
using namespace std;

namespace test {
class Test {
 public:
  void hello() {
    cout << "Hello, World!" << endl;
  }
};
}
int main() {
  test::Test obj;
  obj.hello();
  return 0;
}
