class Interface {
    virtual int add(int a, int b) = 0;
};
class Class {
    virtual int add(int a, int b) {
        return a + b;
    }
};
int main() {
    Class obj;
    //Interface &reference = obj; // error!
    Class &reference = obj;
    return 0;
}
