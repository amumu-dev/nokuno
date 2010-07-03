#include <iostream>
#include <string>
using namespace std;

int main() {
    string input = "aabbbcc";
    char c = '\0';
    int count = 1;
    for (int i = 0; i < input.length(); i++) {
        char now = input[i];
        if (now != c) {
            if (c != '\0')
                cout << c << count;
            c = now;
            count = 1;
        } else {
            count++;
        }
    }
    cout << c << count;
    return 0;
}
