#include <iostream>
#include <sys/types.h>
using namespace std;

// Table of UTF-8 character lengths, based on first byte
const unsigned char kUTF8LenTbl[256] = {
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
  2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
  3,3,3,3,3,3,3,3, 3,3,3,3,3,3,3,3, 4,4,4,4,4,4,4,4, 4,4,4,4,4,4,4,4
};
// Return length of a single UTF-8 source character
size_t OneCharLen(const char *src) {
  return kUTF8LenTbl[*reinterpret_cast<const unsigned char*>(src)];
}

size_t CharsLen(const char *src, size_t length) {
  const char *begin = src;
  const char *end = src + length;
  int result = 0;
  while (begin < end) {
    ++result;
    begin += OneCharLen(begin);
  }
  return result;
}

void SubString(const string &src,
                     const size_t start,
                     const size_t length,
                     string *result) {
  size_t l = start;
  const char *begin = src.c_str();
  const char *end = begin + src.size();
  while (l > 0) {
    begin += OneCharLen(begin);
    --l;
  }

  l = length;
  while (l > 0 && begin < end) {
    const size_t len = OneCharLen(begin);
    result->append(begin, len);
    begin += len;
    --l;
  }

  return;
}
int main() {
    string input;
    while (getline(cin, input)) {
        cout << "CharLen: " << CharsLen(input.c_str(), input.length()) << endl;
        for (int i = 0; i < input.length(); i++) {
            cout << "OneCharLen " << i << ": " << (int)OneCharLen(input.c_str()+i) << endl;
        }
        string result;
        SubString(input, 1, 4, &result);
        cout << "SubSring: " << result << endl;
    }
    return 0;
}
