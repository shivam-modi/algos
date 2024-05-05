string topologicalSort(unordered_map<int, vector<int>> graph, int k) {
    vector<int> indegree(k, 0);
    string ans = "";
    for(int u = 0; u<graph.size(); u++) {
        for(auto v : graph[u]) {
           indegree[v]++;
        }
    }

    queue<int> q;

    for(int i = 0; i<k; i++) {
        if(indegree[i] == 0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int node = q.front();
        ans += 'a' + node;
        q.pop();

        for(int& v: graph[node]) {
            indegree[v]--;
            if(indegree[v] == 0) {
               q.push(v);
            }
        }
    }

    return ans;
}

// Associated Problem
string getAlienLanguage(vector<string> &dictionary, int k){
    unordered_map<int, vector<int>> graph;
    int N = dictionary.size();
    for (int i = 0; i<N-1; i++) {
         string s1 = dictionary[i];
         string s2 = dictionary[i+1];

         int len = min(s1.size(), s2.size());

         for(int p1 = 0; p1 < len; p1++) {
             if(s1[p1] != s2[p1]) {
                 graph[s1[p1]-'a'].push_back(s2[p1]-'a');
                 break;
             }
         }
    }

    return topologicalSort(graph, k);
}