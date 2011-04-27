#include <iostream>
using namespace std;

template <typename T>
class mylist {
  struct node {
    node *next;
    node *prev;
    T value;
  };
 public:
  mylist() {
    head = NULL;
    tail = NULL;
  }
  bool push_back(T value) {
    node *n = new node;
    n->value = value;
    n->next = NULL;
    if (tail != NULL) {
      n->prev = tail->prev;
      tail->next = n;
    } else {
      n->prev = NULL;
      head = n;
    }
    tail = n;
  }
  node *get_head() {return head;}
  node *get_tail() {return tail;}

 protected:
  node *head;
  node *tail;
};

int main() {
  mylist<int> l;
  l.push_back(1);
  cout << l.get_head()->value << endl;
  cout << l.get_tail()->value << endl;
  return 0;
}
