#include <stdio.h>

class Test {
public:
    void test() {
        delete this;
    }
};
int main() {
    Test *test = new Test();
    test->test();
    printf("ok?\n");
    return 0;
}
