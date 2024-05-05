// disjoint set union
// with ranking and path compression

class DisjointSetUnion {
private:
  vector<int> parent;
  vector<int> rank;

public:
  DisjointSetUnion(int size) {
      parent.resize(size);  
      rank.resize(size, 0);
        for (int i = 0; i < size; i++) {
          parent[i] = i;
        }
  }

  int find(int node) {
    if (node != parent[node]) {
      parent[node] = find(parent[node]); 
    }
    return parent[node];
  }

  void Union(int u, int v) {
    int uParent = find(u);
    int vParent = find(v);

    if (uParent == vParent) {
      return;
    }

    if (rank[uParent] > rank[vParent]) {
      parent[vParent] = uParent;
    } else if (rank[uParent] < rank[vParent]) {
      parent[uParent] = vParent;
    } else {
      parent[vParent] = uParent;
      rank[uParent]++;
    }
  }
};

// problem axample
 vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        unordered_map<string, int> mailsNode;
        int n = accounts.size();
        DisjointSetUnion ds(n);
        for(int i = 0; i<n; i++) {
            for(int j = 1; j<accounts[i].size(); j++) {
                string email = accounts[i][j];
                if(mailsNode.find(email) == mailsNode.end()) {
                    mailsNode[email] = i;
                } else {
                    ds.Union(i, mailsNode[email]);
                }
            }
        }
        
        vector<string> mergedMails[n];
        
        for(auto &it: mailsNode){
            string mail = it.first;
            int node = it.second;
            int parent = ds.find(node);
            mergedMails[parent].push_back(mail);
        }
        
        vector<vector<string>> ans;
        
        for(int i = 0; i<n; i++) {
            if(mergedMails[i].size() == 0) continue;
            
            sort(mergedMails[i].begin(), mergedMails[i].end());
            
            vector<string> temp;
            temp.push_back(accounts[i][0]);
            for(auto it: mergedMails[i]) {
                temp.push_back(it);
            }
            
            ans.push_back(temp);
        }
        
        return ans;
    }