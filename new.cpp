/**
 * Find the Tree longest route in complete binary tree. 
 * 
 * write code in c++
 * 
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class TreeNode{
    public:
        TreeNode(int data);
        ~TreeNode();
        int data;
        TreeNode* left;
        TreeNode* right;
};

TreeNode::TreeNode(int data){
    this->data = data;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode(){
    delete left;
    delete right;
}

class BSTree{
    public:
        BSTree();
        ~BSTree();
        void insert(int data);
        pair<int, pair<TreeNode*, TreeNode*>> maxDistance();
        void printTree();
    private:
        TreeNode* root;
        void insert(TreeNode* node, int data);
        pair<int, pair<TreeNode*, TreeNode*>> maxDistance(TreeNode* node);
        void printTree(TreeNode* node);
};


BSTree::BSTree(){
    root = NULL;
}

BSTree::~BSTree(){
    delete root;
}

void BSTree::insert(int data){
    if(root == NULL){
        root = new TreeNode(data);
    }
    else{
        insert(root, data);
    }
}

void BSTree::insert(TreeNode* node, int data){
    if(data < node->data){
        if(node->left == NULL){
            node->left = new TreeNode(data);
        }
        else{
            insert(node->left, data);
        }
    }
    else{
        if(node->right == NULL){
            node->right = new TreeNode(data);
        }
        else{
            insert(node->right, data);
        }
    }
}

pair<int, pair<TreeNode*, TreeNode*>> BSTree::maxDistance(){
    return maxDistance(root);
}

pair<int, pair<TreeNode*, TreeNode*>> BSTree::maxDistance(TreeNode* node){
    if(node == NULL){
        return {0, {NULL, NULL}};
    }
    pair<int, pair<TreeNode*, TreeNode*>> left = maxDistance(node->left);
    pair<int, pair<TreeNode*, TreeNode*>> right = maxDistance(node->right);
    int max = left.first;
    pair<TreeNode*, TreeNode*> maxPair = left.second;
    if(right.first > max){
        max = right.first;
        maxPair = right.second;
    }
    if(left.first + right.first + 1 > max){
        max = left.first + right.first + 1;
        maxPair = make_pair(node, node);
    }
    return make_pair(max, maxPair);
}

void BSTree::printTree(){
    printTree(root);
}

void BSTree::printTree(TreeNode* node){
    if(node == NULL){
        return;
    }
    printTree(node->left);
    cout << node->data << " ";
    printTree(node->right);
}

int main(){
    BSTree tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(2);
    tree.insert(4);
    tree.insert(6);
    tree.insert(8);
    tree.insert(1);
    tree.insert(9);

    pair<int, pair<TreeNode*, TreeNode*>> result = tree.maxDistance();

    tree.printTree();

    cout << "max distance: " << result.first << endl;
    cout << "max distance pair: " << result.second.first->data << " " << result.second.second->data << endl;

    return 0;
}
