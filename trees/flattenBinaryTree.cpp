class TreeNode{
   public:
     TreeNode* right;
     TreeNode* left;
     int val;

    TreeNode(int new_val){
      val = new_val;
      right =  nullptr;
      left  = nullptr;
    }

   TreeNode(){}
};

void flatten(TreeNode* root) {
      TreeNode* curr = root;
      while (curr) {
        
          if (curr->left) {
    
              TreeNode* pre = curr->left;
              while (pre->right) {
                  pre = pre->right;
              }
              pre->right = curr->right;
              curr->right = curr->left;
              curr->left = NULL;
          }
          curr = curr->right;
      }
  }
