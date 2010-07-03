#include <stdio.h>

//Node class
struct Node {
    //member variables
    Node *prev;
    Node *next;
    int value;

    //constructer
    Node(int value) {
        prev = next = 0;
        this->value = value;
    }
    //destructer
    ~Node() {
        if (next != NULL) {
            delete next;
        }
    }
    //insert node
    void insert(Node *node) {
        if (next != NULL) {
            next->prev = node;
            node->next = next;
        }
        next = node;
    }
    //insert integer
    void insert(int value) {
        Node *node = new Node(value);
        insert(node);
    }
    //display all after this nodes
    void display() {
        Node *node = this;
        while (node != NULL) {
            printf("%d->", node->value);
            node = node->next;
        }
        printf("\n");
    }
    //return final node
    Node *end() {
        Node *node = this;
        while (node->next != NULL) {
            node = node->next;
        }
        return node;
    }
};
//List class which is a wrapper of Node class
struct List{
    Node *head;
    Node *tail;
    List(Node *head=NULL, Node *tail=NULL) {
        this->head = head;
        this->tail = tail;
    }
    ~List() {
        if (head != NULL) {
            delete head;
        }
    }
    void insert(int value) {
        Node *node = new Node(value);
        if (head == NULL) {
            head = tail = node;
        } else {
            tail->insert(node);
            tail = node;
        }
    }
    void display() {
       if (head != NULL) {
           head->display();
       }
    }
};
//main function
int main() {
    //use node direct
    Node node(1);
    node.end()->insert(2);
    node.end()->insert(3);
    node.end()->insert(4);
    node.display();

    //use list wrapper
    List list;
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    list.display();
    return 0;
}
