#include <stdio.h>

//Node class
struct Node {
    //member variables
    Node *prev;
    Node *next;
    int value;

    //constructer default: sentinel
    Node(int value = -1) {
        prev = next = this;
        this->value = value;
    }
    //destructer
    ~Node() {
        if (prev != NULL) {
            prev->next = NULL;
        }
        delete next;
    }
    //insert node
    void insert(Node *node) {
        node->prev = this;
        node->next = next;
        next->prev = node;
        next = node;
    }
    //insert integer
    void insert(int value) {
        Node *node = new Node(value);
        insert(node);
    }
    //display all after this nodes
    void display() {
        Node *node = next;
        while (node != this) {
            printf("%d->", node->value);
            node = node->next;
        }
        printf("\n");
    }
};
//main function
int main() {
    Node node;
    node.insert(1);
    node.insert(2);
    node.insert(3);
    node.insert(4);
    node.display();
    return 0;
}
