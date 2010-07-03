#include <stdio.h>

struct Node {
    Node *child;
    Node *sibling;
    int value;
    Node(int value) {
        child = sibling = NULL;
        this->value = value;
    }
    ~Node() {
        delete child;
        delete sibling;
    }
    void print(int depth) {
        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        printf("%d\n", value);
        if (child) {
            child->print(depth+1);
        }
        if (sibling) {
            sibling->print(depth);
        }
    }
};
int main() {
    Node root(1);
    root.child = new Node(2);
    root.child->sibling = new Node(3);
    root.child->child = new Node(4);
    root.child->child->child = new Node(5);
    root.child->sibling->sibling = new Node(6);
    root.print(0);
    return 0;
}
