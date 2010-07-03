#include <stdio.h>

#include "list.h"

const int SIZE = 100;
struct HashTable {
    Node *table[SIZE];

    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = NULL;
        }
    }
    ~HashTable() {
        for (int i = 0; i < SIZE; i++) {
            delete table[i];
        }
    }
    void insert(int key) {
        int h = hash(key);
        if (table[h] == NULL) {
            table[h] = new Node();
        }
        table[h]->insert(key);
    }
    void display() {
        for (int i = 0; i < SIZE; i++) {
            if (table[i] != NULL) {
                int h = hash(table[i]->next->value);
                printf("%d : ", h);
                table[i]->display();
            }
        }
    }
    static int hash(int key) {
        return key % SIZE;
    }
};

int main() {
    HashTable ht;
    ht.insert(0);
    ht.insert(10);
    ht.insert(56);
    ht.insert(99);
    ht.insert(100);
    ht.insert(256);
    ht.display();
    return 0;
}
