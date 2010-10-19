#include <stdio.h>
#include <assert.h>

struct Node {
    Node *left;
    Node *right;
    Node *parrent;
    int key;

    Node(int key, Node *parrent = NULL) {
        left = right = NULL;
        this->parrent = parrent;
        this->key = key;
    }
    Node(int *keys, int size, Node *parrent = NULL) {
        left = right = NULL;
        this->parrent = parrent;
        key = keys[0];
        insert(keys+1, size-1);
    }
    ~Node() {
        delete left;
        delete right;
    }
    void print(int depth) {
        for (int i = 0; i < depth; i++) {
            printf("\t");
        }
        printf("%d\n", key);
    }
    void preorder(int depth) {
        print(depth);
        if (left) {
            left->preorder(depth+1);
        }
        if (right) {
            right->preorder(depth+1);
        }
    }
    void inorder(int depth) {
        if (left) {
            left->inorder(depth+1);
        }
        print(depth);
        if (right) {
            right->inorder(depth+1);
        }
    }
    void postorder(int depth) {
        if (left) {
            left->postorder(depth+1);
        }
        if (right) {
            right->postorder(depth+1);
        }
        print(depth);
    }
    Node *search(int key) {
        if (key == this->key) {
            return this;
        } else if (key < this->key && left != NULL) {
            return left->search(key);
        } else if (key > this->key && right != NULL) {
            return right->search(key);
        }
        return NULL;
    }
    Node *iterative_search(int key) {
        Node *node = this;
        while (node != NULL && key != node->key) {
            if (key < node->key) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return node;
    }
    Node *minimum() {
        Node *node = this;
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }
    Node *maximum() {
        Node *node = this;
        while (node->right != NULL) {
            node = node->right;
        }
        return node;
    }
    Node *successor() {
        if (right != NULL) {
            return right->minimum();
        }
        Node *x = this;
        Node *y = parrent;
        while (y != NULL && x == y->right) {
            x = y;
            y = y->parrent;
        }
        return y;
    }
    Node *predecessor() {
        if (left != NULL) {
            return left->maximum();
        }
        Node *x = this;
        while (x->parrent != NULL && x == x->parrent->left) {
            x =  x->parrent;
        }
        return x->parrent;
    }
    Node *next(int key) {
        if (key < this->key) {
            return left;
        } else {
            return right;
        }
    }
    void insert(Node *node) {
        Node *x = this;
        while (x->next(node->key) != NULL) {
            x = x->next(node->key);
        }
        node->parrent = x;
        if (x == NULL) {
            key = node->key;
        } else if (node->key < x->key) {
            x->left = node;
        } else {
            x->right = node;
        }
    }
    void insert(int *keys, int size) {
        for (int i = 0; i < size; i++) {
            insert(new Node(keys[i]));
        }
    }
    void del() {
        if (left == NULL && right == NULL) {
            printf("%d: case leaf!\n", key);
            if (parrent->left == this) {
                parrent->left = NULL;
            } else {
                parrent->right = NULL;
            }
            delete this;
        } else if (left != NULL && right != NULL) {
            printf("%d: case two child!\n", key);
            Node *p = successor();
            Node *pa = p->parrent;
            if (pa->left == p) {
                printf("left case!\n");
                pa->left = p->right;
                if (pa->left != NULL) {
                    pa->left->parrent = pa;
                }
            } else {
                printf("right case!\n");
                pa->right = p->right;
                if (pa->right != NULL) {
                    pa->right->parrent = pa;
                }
            }
            key = p->key;
            p->left = p->right = NULL;
            delete p;
        } else {
            printf("%d: case single child!\n", key);
            Node *child;
            if (left != NULL) {
                child = left;
            } else {
                child = right;
            }
            left = child->left;
            right = child->right;
            key = child->key;
            if (left != NULL)
                left->parrent = this;
            if (right != NULL)
                right->parrent = this;
            child->left = child->right = NULL;
            delete child;
        }
    }

};
int main() {
    int keys[] = {6,3,1,5,4,2,8,10,7,9};
    Node root(keys, sizeof(keys)/sizeof(int));
    root.search(7)->del();
    root.search(6)->del();
    root.search(3)->del();
    root.search(8)->del();
    root.search(4)->del();
    root.search(9)->del();
    root.search(10)->del();
    root.search(5)->del();
    root.search(2)->del();

    printf("inorder:\n");
    root.inorder(0);
    {
        printf("successor: ");
        Node *p = root.minimum();
        do {
            printf("%d ", p->key);
        } while (p = p->successor());
        printf("\n");
    }
    /*
       Node root(6);
       root.left = new Node(5, &root);
       root.left->left = new Node(2, root.left);
       root.left->right = new Node(5, root.left);
       root.right = new Node(7, &root);
       root.right->right = new Node(8, root.right);
       root.insert(new Node(3));
       root.insert(new Node(1));
       root.insert(new Node(5));
       root.insert(new Node(4));
       root.insert(new Node(2));
       root.insert(new Node(8));
       root.insert(new Node(10));
       root.insert(new Node(6));
       root.insert(new Node(7));
       root.insert(new Node(9));
       */
    /*
       root.search(6)->del();
       root.search(9)->del();
       root.search(1)->del();
       root.search(5)->del();
       root.search(3)->del();
       root.search(7)->del();
       root.search(2)->del();
       root.search(8)->del();
       */
    /*
       printf("preorder:\n");
       root.preorder(0);
       printf("postorder:\n");
       root.postorder(0);
       */
    /*
       printf("search(2): %s\n", root.search(2) ? "true" : "false");
       printf("search(-1): %s\n", root.search(-1) ? "true" : "false");
       printf("search(7): %s\n", root.search(7) ? "true" : "false");

       printf("iterative_search(2): %s\n", root.iterative_search(2) ? "true" : "false");
       printf("iterative_search(-1): %s\n", root.iterative_search(-1) ? "true" : "false");
       printf("iterative_search(7): %s\n", root.iterative_search(7) ? "true" : "false");

       printf("minimum(): %d\n", root.minimum()->key);
       printf("maximum(): %d\n", root.maximum()->key);

*/
    /*
       {
       printf("predecessor: ");
       Node *p = root.maximum();
       do {
       printf("%d ", p->key);
       } while (p = p->predecessor());
       printf("\n");
       }
       */
    return 0;
}
