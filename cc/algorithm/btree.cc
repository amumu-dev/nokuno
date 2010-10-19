#include <stdio.h>

struct Node {
    Node *left;
    Node *right;
    int value;
    Node(int value) {
        left = right = NULL;
        this->value = value;
    }
    ~Node() {
        delete left;
        delete right;
    }
    void print(int depth) {
        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        printf("%d\n", value);
        if (left) {
            left->print(depth+1);
        }
        if (right) {
            right->print(depth+1);
        }
    }
};
int main() {
    Node root(1);
    root.left = new Node(2);
    root.left->left = new Node(3);
    root.right = new Node(4);
    root.right->left = new Node(5);
    root.right->right = new Node(6);
    root.print(0);
    return 0;
}
