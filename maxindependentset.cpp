#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

class IndependentSetFinder {
public:
    static vector<vector<int>> find(vector<vector<int>>& adjacencyList, int numOfVertices);
private:
    static void findIndependentSetsHelper(vector<vector<int>>& adjacencyList, int vertexIdx, int numOfVertices,
                                          vector<vector<int>>& independentSets, unordered_set<int>& currentSet);
};

vector<vector<int>> IndependentSetFinder::find(vector<vector<int>>& adjacencyList, int numOfVertices) {
    vector<vector<int>> independentSets;
    unordered_set<int> currentSet;
    findIndependentSetsHelper(adjacencyList, 0, numOfVertices, independentSets, currentSet);

    int maxLen = 0;
    for (auto independentSet : independentSets) {
        maxLen = max(maxLen, (int)independentSet.size());
    }

    cout << "The maximum independent set length is " << maxLen << endl;
    cout << "And the sets having " <<maxLen<< " length are: " << endl;
    for (auto independentSet : independentSets) {
        if (independentSet.size() == maxLen) {
            cout << "{ ";
            for (auto vertexIdx : independentSet) {
                cout << vertexIdx << " ";
            }
            cout << "}, ";
        }
    }
    cout<<endl;

    return independentSets;
}

void IndependentSetFinder::findIndependentSetsHelper(vector<vector<int>>& adjacencyList, int vertexIdx, int numOfVertices,
                                                     vector<vector<int>>& independentSets, unordered_set<int>& currentSet) {
    if (vertexIdx == numOfVertices) {
        vector<int> independentSet;
        for (auto vertex : currentSet) {
            independentSet.push_back(vertex);
        }
        independentSets.push_back(independentSet);
        return;
    }

    bool isSafeToAddToCurrentSet = true;
    for (auto neighbor : adjacencyList[vertexIdx]) {
        if (currentSet.find(neighbor) != currentSet.end()) {
            isSafeToAddToCurrentSet = false;
            break;
        }
    }

    if (isSafeToAddToCurrentSet) {
        currentSet.insert(vertexIdx);
        findIndependentSetsHelper(adjacencyList, vertexIdx + 1, numOfVertices, independentSets, currentSet);
        currentSet.erase(vertexIdx);
    }
    findIndependentSetsHelper(adjacencyList, vertexIdx + 1, numOfVertices, independentSets, currentSet);
}

int main() {
    vector<vector<int>> adjacencyList = {
            {1, 2},
            {0, 2, 3},
            {0, 1, 4},
            {1, 4, 5},
            {2, 3, 6},
            {3, 7},
            {4, 7},
            {5, 6}
    };

    IndependentSetFinder::find(adjacencyList, 8);

    return 0;
}
