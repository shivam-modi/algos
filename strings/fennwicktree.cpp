#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class FenwickTree {
public:
    vector<int> BIT;
    int size;
    
    FenwickTree(int n) : size(n), BIT(n + 1, 0) {}

    void update(int index, int delta) {
        while (index <= size) {
            BIT[index] += delta;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += BIT[index];
            index -= index & -index;
        }
        return sum;
    }
};

vector<int> solve(vector<int>& array) {
    int n = array.size();
    vector<int> sortedArray = array;

    // Step 1: Coordinate compression
    sort(sortedArray.begin(), sortedArray.end());
    unordered_map<int, int> rank;
    for (int i = 0; i < n; i++) {
        rank[sortedArray[i]] = i + 1; // rank starts from 1
    }

    // Step 2: Initialize the Fenwick Tree
    FenwickTree fenwickTree(n);
    vector<int> result(n);

    // Step 3: Process the array from left to right
    for (int i = 0; i < n; i++) {
        int elementRank = rank[array[i]];
        result[i] = fenwickTree.query(elementRank - 1); // Get count of smaller elements
        fenwickTree.update(elementRank, 1); // Add current element to the Fenwick Tree
    }

    return result;
}
