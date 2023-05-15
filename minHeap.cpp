#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
    vector<int> tree;
    int sz = 0;

public:
    void push(int v) {
        tree.push_back(v);
        heapifyUp(sz++);
    }

    void heapifyUp(int i) {
        int par = (i - 1) / 2;
        while (tree[par] > tree[i]) {
            swap(tree[i], tree[par]);
            i = par;
            par = (par - 1) / 2;
        }
    }

    int peek() {
        if (sz == 0) {
            throw new runtime_error("The heap is empty");
        }
        return tree[0];
    }

    void remove(int val) {
        int i = 0;
        while (i < sz && tree[i] != val)
            i++;
        if (i == sz)
            throw new invalid_argument("Value not present in heap");
        swap(tree[i], tree[sz - 1]);
        tree.pop_back();
        sz--;
        heapifyDown(i);
    }
    void heapifyDown(int i) {
        while (i < sz) {
            int left = 2 * i + 1, right = 2 * i + 2;
            if (left < sz) {
                if (right < sz) {
                    int minChild = (tree[left] < tree[right]) ? left : right;
                    if (tree[minChild] < tree[i]) {
                        swap(tree[i], tree[minChild]);
                        i = minChild;
                    } else {
                        break;
                    }
                } else if (tree[left] < tree[i]) {
                    swap(tree[i], tree[left]);
                    i = left;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }

    void pop() {
        remove(tree[0]);
    }
};

vector<int> minHeapSort(vector<int> nums) {
    MinHeap minHeap;
    for (int i : nums) {
        minHeap.push(i);
    }

    int n = nums.size();
    vector<int> sortedNums(n);
    for (int i = 0; i < n; i++) {
        sortedNums[i] = minHeap.peek();
        minHeap.pop();
    }
    return sortedNums;
}

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;
    vector<int> randoms(n);
    cout << "Original Array" << endl;
    for (int i = 0; i < n; i++) {
        randoms[i] = rand() % 1000000;
        cout << randoms[i] << " ";
    }
    cout << endl;
    cout << "After sorting" << endl;
    vector<int> sortedNums = minHeapSort(randoms);
    for (int i = 0; i < n; i++) {
        cout << sortedNums[i] << " ";
    }
    cout << endl;
}