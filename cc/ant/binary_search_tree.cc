#include <iostream>
using namespace std;

struct node {
  int val;
  node *lch, *rch;
};

node *insert(node *p, int x) {
  if (p == NULL) {
    node *q = new node;
    q->val = x;
    q->lch = q->rch = NULL;
    return q;
  } else {
    if (x < p->val) p->lch = insert(p->lch, x);
    else p->rch = insert(p->rch, x);
    return p;
  }
}

bool find(node *p, int x) {
  if (p == NULL) return false;
  else if (x == p->val) return true;
  else if (x < p->val) return find(p->lch, x);
  else return find(p->rch, x);
}

node *remove(node *p, int x) {
  if (p == NULL) return NULL;
  else if (x < p->val) p->lch = remove(p->lch, x);
  else if (x > p->val) p->rch = remove(p->rch, x);
  else if (p->lch == NULL) {
    node *q = p->rch;
    delete p;
    return q;
  } else if (p->lch->rch == NULL) {
    node *q = p->lch;
    q->rch = p->rch;
    delete p;
    return q;
  } else {
    node *q;
    for (q = p->lch; q->rch->rch != NULL; q = q->rch);
    node *r = q->rch;
    q->rch = r->lch;
    r->lch = p->lch;
    r->rch = p->rch;
    delete p;
    return r;
  }
  return p;
}
int main() {
  node root;
  insert(&root, 2);
  insert(&root, 5);
  insert(&root, 1);
  insert(&root, 3);

  cout << find(&root, 1) << endl;
  cout << find(&root, 2) << endl;
  cout << find(&root, 3) << endl;
  cout << find(&root, 4) << endl;
  cout << find(&root, 5) << endl;

  remove(&root, 2);
  remove(&root, 5);
  remove(&root, 4);

  cout << find(&root, 1) << endl;
  cout << find(&root, 2) << endl;
  cout << find(&root, 3) << endl;
  cout << find(&root, 4) << endl;
  cout << find(&root, 5) << endl;
}
