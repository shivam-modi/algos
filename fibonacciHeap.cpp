#include <iostream>
#include <cmath>
using namespace std;
class FibonacciHeapNode
{
private:
  int key, degree;
  FibonacciHeapNode *parent, *child, *left, *right;
  bool mark;

public:
  FibonacciHeapNode(int _key) : key(_key),
                                degree(0),
                                parent(nullptr), child(nullptr), left(nullptr),
                                right(nullptr),
                                mark(false)
  {
  }
  void addChild(FibonacciHeapNode *other);
  static FibonacciHeapNode *findInList(FibonacciHeapNode *lst, int
                                                                   k);
  FibonacciHeapNode *findKey(int k);
  friend class FibonacciHeap;
};
void FibonacciHeapNode::addChild(FibonacciHeapNode *other)
{
  if (!child)
  {
    child = other;
    child->left = child;
    child->right = child;
    return;
  }
  child->left->right = other;
  other->left = child->left;
  other->right = child;
}
class FibonacciHeap
{
  static FibonacciHeap *singletonHeap(int);
  void unionWith(FibonacciHeap *other);
  void mergeLists(FibonacciHeapNode *a, FibonacciHeapNode *b);
  FibonacciHeapNode *mergeRoots(FibonacciHeapNode *a,
                                FibonacciHeapNode *b);
  void removeRoot(FibonacciHeapNode *node);
  void addRoot(FibonacciHeapNode *node);
  FibonacciHeapNode *findKey(int k);

public:
  FibonacciHeapNode *min;
  int n;
  FibonacciHeap()
  {
    min = nullptr;
    n = 0;
  }
  int getMin();
  void insert(int key);
  int extractMin();
  void decreaseKey(int oldKey, int newKey);
  void deleteKey(int delKey);
};
int FibonacciHeap::getMin()
{
  if (!min)
  {
    throw runtime_error("Heap is Empty!");
  }
  return min->key;
}
void FibonacciHeap::insert(int key)
{
  FibonacciHeap *newHeap = singletonHeap(key);
  unionWith(newHeap);
}
void FibonacciHeap::mergeLists(FibonacciHeapNode *a,
                               FibonacciHeapNode *b)
{
  if (!a || !b)
    return;
  FibonacciHeapNode *a_last = a->left, *b_last = b->left;
  a_last->right = b;
  b->left = a_last;
  a->left = b_last;
  b_last->right = a;
}
void FibonacciHeap::unionWith(FibonacciHeap *other)
{
  if (!other)
    return;
  if (!min)
  {
    min = other->min;
    n = other->n;
  }
  else
  {
    mergeLists(min, other->min);
    if (other->min->key < min->key)
    {
      min = other->min;
    }
    n += other->n;
  }
}
FibonacciHeap *FibonacciHeap::singletonHeap(int key)
{
  FibonacciHeap *newHeap = new FibonacciHeap;
  FibonacciHeapNode *node = new FibonacciHeapNode(key);
  node->left = node;
  node->right = node;
  newHeap->min = node;
  newHeap->n = 1;
  return newHeap;
}
int FibonacciHeap::extractMin()
{
  if (!min)
  {
    throw runtime_error("Heap is Empty!");
    return -1;
  }
  int minKey = min->key;
  FibonacciHeapNode *delNode = min;
  mergeLists(min, min->child);
  if (delNode->left == delNode)
  {
    // only one root was left
    min = nullptr;
  }
  else
  {
    // more than one
    min->left->right = min->right;
    min->right->left = min->left;
    min = min->right; // min will be deleted
    delete delNode;
    // consolidate (merge nodes with same degree)
    int max_sz = log2(n) + 2;
    FibonacciHeapNode *mp[max_sz] = {nullptr};
    FibonacciHeapNode *ptr = min, *start = min;
    do
    {
      if (mp[ptr->degree])
      {
        // two roots with the same degree
        // merge
        bool wasMin = ptr == min;
        ptr = mergeRoots(ptr, mp[ptr->degree]);
        if (wasMin)
          min = ptr;
      }
      mp[ptr->degree] = ptr;
    } while (ptr != start);
    // update the min
    ptr = min->right;
    start = min;
    while (ptr != start)
    {
      if (ptr->key < min->key)
        min = ptr;
      ptr = ptr->right;
    }
  }
  return minKey;
}
FibonacciHeapNode *FibonacciHeap::mergeRoots(FibonacciHeapNode *a,
                                             FibonacciHeapNode *b)
{
  if (!a)
    return b;
  else if (!b)
    return a;
  if (a->key < b->key)
  {
    removeRoot(b);
    a->addChild(b);
    a->degree++;
    return a;
  }
  else
  {
    removeRoot(a);
    b->addChild(a);
    b->degree++;
    return b;
  }
}
void FibonacciHeap::removeRoot(FibonacciHeapNode *node)
{
  if (node->left == node)
  {
    // the only root
    // unreachable case
    min = nullptr;
    return;
  }
  node->left->right = node->right;
  node->right->left = node->left;
}
void FibonacciHeap::addRoot(FibonacciHeapNode *node)
{
  if (min)
    min->left->right = node;
  node->right = min;
  if (min)
    min->left = node;
  if (!min || node->key < min->key)
    min = node;
}
void FibonacciHeap::decreaseKey(int oldKey, int newKey)
{
  FibonacciHeapNode *node = findKey(oldKey);
  if (!node)
  {
    throw invalid_argument("Key not found in the Heap!");
    return;
  }
  node->key = newKey;
  while (node->parent && node->parent->key > node->key)
  {
    // i.e while the heap property is not satisfied
    // cut/cascading cut
    FibonacciHeapNode *delNode = node;
    delNode->left->right = delNode->right;
    delNode->right->left = delNode->left;
    addRoot(delNode);
    node = node->parent;
    if (!node->mark)
    {
      node->mark = true;
      break;
    }
  }
  if (!node->parent && node->key < min->key)
  {
    min = node;
  }
}
FibonacciHeapNode *FibonacciHeapNode::findInList(FibonacciHeapNode
                                                     *lst,
                                                 int k)
{
  if (!lst)
    return nullptr;
  FibonacciHeapNode *ptr = lst, *start = lst;
  do
  {
    FibonacciHeapNode *found = ptr->findKey(k);
    if (found)
      return found;
    ptr = ptr->right;
  } while (ptr != lst);
  return nullptr;
}
FibonacciHeapNode *FibonacciHeapNode::findKey(int k)
{
  if (key == k)
    return this;
  else
    return findInList(child, k);
}
FibonacciHeapNode *FibonacciHeap::findKey(int k)
{
  return FibonacciHeapNode::findInList(min, k);
}
void FibonacciHeap::deleteKey(int k)
{
  decreaseKey(k, INT8_MIN);
  extractMin();
}
int main()
{
  int arr[10] = {5, 3, 2, 1, 4, 6, 7, 8, 9, 10};
  FibonacciHeap fh;
  for (int i = 0; i < 10; i++)
  {
    cout << "inserting " << arr[i] << endl;
    fh.insert(arr[i]);
  }
  for (int i = 0; i < 5; i++)
  {
    int del;
    cout << "enter key to delete :" << endl;
    cin >> del;
    fh.deleteKey(del);
  }
  for (int i = 0; i < 5; i++)
  {
    cout << "min: " << fh.getMin() << endl;
    fh.extractMin();
    cout << "extracted min" << endl;
  }
}
