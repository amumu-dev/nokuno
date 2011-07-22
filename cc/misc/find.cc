#include <iostream>

int main() {
  std::string a = "abc";
  std::cout << a.find("");
  std::cout << std::string::npos;
  return 0;
}
