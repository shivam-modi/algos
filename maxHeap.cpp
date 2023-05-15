/*
Implement max heap using vector. 

Write functions to insert, delete max, print heap, print heap in sorted order, 
print heap in level order, 
print heap in sorted order.
*/

#include<iostream>
#include<vector>
#include<climits>

using namespace std;

class MaxHeap{
    vector<int> heap_array;
    int heap_size;

public:
    MaxHeap(){
        heap_size = 0;
    }

    void MaxHeapify(int i){
        int l = left(i);
        int r = right(i);

        int largest = i;
        if (l < heap_size && heap_array[l] > heap_array[i])
            largest = l;
        if (r < heap_size && heap_array[r] > heap_array[largest])
            largest = r;

        if (largest != i){
            swap(heap_array[i], heap_array[largest]);
            MaxHeapify(largest);
        }
    }

    void printHeapInLevelOrder(){
        int n = heap_size;
        for (int i = 0; i < n; i++)
            cout << heap_array[i] << " ";
        cout << endl;
    }

    void printHeapInSortedOrder(){
        int n = heap_size;
        for (int i = 0; i < n; i++)
            cout << extractMax() << " ";
        cout << endl;
    }

    int getMax(){ return heap_array[0]; }

    int parent(int i){ return (i-1)/2; }

    int left(int i){ return (2*i + 1); }

    int right(int i){ return (2*i + 2); }

    int extractMax(){
        if (heap_size == 0)
            return INT_MAX;
        if (heap_size == 1){
            heap_size--;
            return heap_array[0];
        }

        int root = heap_array[0];
        heap_array[0] = heap_array[heap_size-1];
        heap_size--;
        MaxHeapify(0);

        return root;
    }

    void insertKey(int k){
        heap_array.push_back(k);
        heap_size++;

        int i = heap_size - 1;
        while (i != 0 && heap_array[parent(i)] < heap_array[i]){
            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }
    }

    void deleteKey(int i){
        if (i >= heap_size)
            return;

        heap_array[i] = INT_MAX;
        while (i != 0 && heap_array[parent(i)] < heap_array[i]){
            swap(heap_array[i], heap_array[parent(i)]);
            i = parent(i);
        }

        extractMax();
        heap_array.pop_back();
    }
};

int main(){
    MaxHeap heap;
    int n;
    cout<<"Enter the number of elements you want to insert: ";
    cin >> n;
    for(int i = 0; i < n; i++){
        int data;
        cout << "Enter data: ";
        cin >> data;
        heap.insertKey(data);
        cout<<endl;
    }
    cout << "Max Heap: \n";
    cout << "Heap in level order: ";
    heap.printHeapInLevelOrder();
    cout << "Extract Max: " << heap.extractMax() << endl;
    cout << "Max: " << heap.getMax() << endl;
    cout << "Enter the index of the element you want to delete: ";
    cin >> n;
    heap.deleteKey(n);
    cout << "Heap Now: ";
    heap.printHeapInLevelOrder();

    cout << endl;
    return 0;
}

