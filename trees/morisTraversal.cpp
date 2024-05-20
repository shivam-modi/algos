vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inorder;
        
        TreeNode* curr = root;
        
        while(curr != nullptr) {
            if(curr->left == nullptr) {
                inorder.push_back(curr->val);
                curr = curr->right;
            }else {
                TreeNode* leftChild = curr->left;
                
                while(leftChild->right != nullptr) {
                    leftChild = leftChild->right;
                }
                
                leftChild->right = curr;
                TreeNode* temp = curr;
                curr = curr->left;
                temp->left = nullptr;
            }
        }
        
        return inorder;
    }
