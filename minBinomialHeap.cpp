/*
 * C++ Program to Implement Min Binomial Heap
 */

#include <iostream>

using namespace std;

class BinomialHeap;

class BinomialNode {
private:
    int key, degree;
    BinomialNode *parent, *child, *sibling;

public:
    BinomialNode(int k) : key(k), degree(0), parent(nullptr), child(nullptr), sibling(nullptr){};
    void insertSibling(BinomialNode *);
    void insertChild(BinomialNode *);
    BinomialNode *find(int);
    friend BinomialHeap;
};

BinomialNode *BinomialNode::find(int k){
    if (key == k)
        return this;
    BinomialNode *ptr = child;
    while (ptr){
        BinomialNode *res = ptr->find(k);
        if (res)
            return res;
        ptr = ptr->sibling;
    }

    return nullptr;
}

void BinomialNode::insertChild(BinomialNode *node){
    node->sibling = child;
    child = node;

    node->parent = this;
}

class BinomialHeap{
private:
    BinomialNode *head;
    BinomialNode *minNode, *preMinNode;
    BinomialNode *linkTrees(BinomialNode *, BinomialNode *);

    void updateMin();
    void consolidate();
    void addTrees(BinomialNode *);
public:
    BinomialHeap() : head(nullptr), minNode(nullptr){};
    void insert(int);
    int getMin();
    void extractMin();
    void decreaseKey(int, int);
    void deleteKey(int);
    bool empty();

    BinomialNode *find(int);
};

bool BinomialHeap::empty(){
    return head == nullptr;
}

void BinomialHeap::insert(int k){
    BinomialNode *node = new BinomialNode(k);
    if (!head){
        head = node;
    } else {
        node->sibling = head;
        head = node;
    }
    consolidate();
    updateMin();
}

void BinomialHeap::consolidate() {
    if (!head) {
        return;
    }

    BinomialNode *prev = nullptr, *curr = head, *next = head->sibling;
    while (next){
        if (curr->degree == next->degree){
            BinomialNode *linked = linkTrees(curr, next);
            if (prev){
                prev->sibling = linked;
            } else {
                head = linked;
            }

            curr = linked;
            next = curr->sibling;
        } else {
            prev = curr;
            curr = next;
            next = next->sibling;
        }
    }
}

BinomialNode *BinomialHeap::linkTrees(BinomialNode *node1, BinomialNode *node2){
    if (node1->key >= node2->key) {
        swap(node1, node2);
    }

    if (node2->sibling != node1) {
        node1->sibling = node2->sibling;
    }

    node1->insertChild(node2);
    node1->degree++;

    return node1;
}

void BinomialHeap::updateMin(){
    BinomialNode *ptr = head;
    BinomialNode *preptr = nullptr;
    minNode = ptr;
    preMinNode = nullptr;

    while (ptr){
        if (ptr->key < minNode->key){
            minNode = ptr;
            preMinNode = preptr;
        }
        preptr = ptr;
        ptr = ptr->sibling;
    }
}

int BinomialHeap::getMin() {
    if (!minNode){
        throw "Heap is Empty!";
    }
    return minNode->key;
}

void BinomialHeap::extractMin() {
    if (!minNode) {
        throw "Heap is Empty!";
    }
    if (!preMinNode) {
        head = minNode->sibling;
    } else {
        preMinNode->sibling = minNode->sibling;
    }

    addTrees(minNode->child);
    delete minNode;

    consolidate();
    updateMin();
}

void BinomialHeap::addTrees(BinomialNode *child){
    if (!child){
        return;
    }

    BinomialNode *ptr = head, *preptr = nullptr;
    while (child) {
        child->parent = nullptr;
        BinomialNode *next = child->sibling;

        while (ptr && ptr->degree < child->degree) {
            preptr = ptr;
            ptr = ptr->sibling;
        }
        if (!preptr) {
            child->sibling = head;
            head = child;
        } else if (!ptr) {
            preptr->sibling = child;
        } else {
            preptr->sibling = child;
            child->sibling = ptr;
        }
        preptr = child;
        child = next;
    }
}

BinomialNode *BinomialHeap::find(int k) {
    BinomialNode *ptr = head;
    while (ptr){
        BinomialNode *res = ptr->find(k);
        if (res)
            return res;
        ptr = ptr->sibling;
    }
    return nullptr;
}

void BinomialHeap::decreaseKey(int oldKey, int newKey){
    BinomialNode *node = find(oldKey);
    if (!node) {
        throw "Key not found!";
    }

    node->key = newKey;
    BinomialNode *par = node->parent;

    while (par && node->key < par->key) {
        swap(node->key, par->key);
        node = par;
        par = par->parent;
    }
    updateMin();
}

void BinomialHeap::deleteKey(int k) {
    decreaseKey(k, INT8_MIN);
    extractMin();
}
int main() {
    BinomialHeap heap;
    for (int i = 0; i < 15; i++){
        int r = rand() % 100;
        cout << "inserting " << r << endl;
        heap.insert(r);
    }
    cout << "Select key to decrease: ";
    int oldKey;
    cin >> oldKey;
    int newKey;
    cout << "new key: ";
    cin >> newKey;

    heap.decreaseKey(oldKey, newKey);

    while (!heap.empty()) {
        cout << heap.getMin() << " ";
        heap.extractMin();
    }

    cout << endl;
}