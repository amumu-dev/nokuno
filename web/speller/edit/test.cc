#include "edit.h"

#define LIMIT (100000)

int main() {
  string line;
  while (getline(cin, line)) {
    run(line, LIMIT);
  }
  return 0;
}
