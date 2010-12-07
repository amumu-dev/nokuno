#include <iostream>
#include <vector>
#include <string>
using namespace std;
typedef basic_string<uint16_t> ustring;

const uint8_t len_table[256] = {
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
  3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4
};
int get_len(char c) {
  return (int)len_table[(uint8_t)c];
}
ustring decode(string input) {
  ustring result;
  for (int i = 0; i < input.length(); i+= get_len(input[i])) {
    switch (get_len(input[i])) {
      case 1:
        result += (uint16_t) input[i];
        break;
      case 3:
        result += (uint16_t) input[i+1] + ((uint16_t) input[i+2] << 8);
        break;
    }
  }
  return result;
}
string encode(ustring input) {
  string result;
  for (int i = 0; i < input.length(); i++) {
    uint8_t up = input[i] >> 8;
    uint8_t down = (uint8_t) input[i];
    if (up == 0) {
      result += (char) down;
    } else {
      result += (char) 0xe3;
      result += (char) down;
      result += (char) up;
    }
  }
  return result;
}
int main() {
  string test = "あいうえお abcde";
  ustring result = decode(test);
  cout << encode(result) << endl;

  cout << "ustring" << endl;
  for (int i = 0; i < result.length(); i++) {
    printf("0x%04x\n", result[i]);
  }
  cout << "string" << endl;
  for (int i = 0; i < test.length(); i++) {
    printf("0x%02x\n", (uint8_t) test[i]);
  }
  return 0;
}
