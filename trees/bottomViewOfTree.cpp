struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Using number line stratergy considering root as 0 left movement decrease by -1 and right movement increase by 1 

vector<int> bottomView(Node* root){
        // Vector to store the result
        vector<int> ans;
        
        // Check if the tree is empty
        if(root == NULL){
            return ans;
        }
        
        // Map to store the bottom view nodes
        // based on their vertical positions
        map<int, int> mpp;
        
        // Queue for BFS traversal, each
        // element is a pair containing node
        // and its vertical position
        queue<pair<Node*, int>> q;
        
        // Push the root node with its vertical
        // position (0) into the queue
        q.push({root, 0});
        
        // BFS traversal
        while(!q.empty()){
            // Retrieve the node and its vertical
            // position from the front of the queue
            auto it = q.front();
            q.pop();
            Node* node = it.first;
            int line = it.second;
            
            // Update the map with the node's data
            // for the current vertical position
            mpp[line] = node->data;
            
            // Process left child
            if(node->left != NULL){
                // Push the left child with a decreased
                // vertical position into the queue
                q.push({node->left, line - 1});
            }
            
            // Process right child
            if(node->right != NULL){
                // Push the right child with an increased
                // vertical position into the queue
                q.push({node->right, line + 1});
            }
        }
        
        // Transfer values from the
        // map to the result vector
        for(auto it : mpp){
            ans.push_back(it.second);
        }
        
        return ans;
    }
