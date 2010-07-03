#include <stdio.h>
class Test {
    public:
    void test(Test *p) {
        this = p;
    }
};
int main() {
    Test t1;
    Test t2;
    t1.test(&t2);
}
    
