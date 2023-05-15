/*** Maximum distance between two nodes in a binary tree

Given a binary search tree, find the maximum distance between two nodes in the tree.
The distance between two nodes is the number of edges on the path from one node to the other.
Also return the two nodes that are the farthest apart.
***/

#include <iostream>
#include <queue>

using namespace std;

class TreeNode
{
public:
    TreeNode(int data);
    ~TreeNode();
    int data;
    TreeNode *left;
    TreeNode *right;
};

TreeNode::TreeNode(int data)
{
    this->data = data;
    left = NULL;
    right = NULL;
}

TreeNode::~TreeNode()
{
    delete left;
    delete right;
}

class BSTree
{
public:
    BSTree();
    ~BSTree();
    void insert(int data);
    pair<int, pair<TreeNode *, TreeNode *>> maxDistance();
    void printTree();

private:
    TreeNode *root;
    void insert(TreeNode *node, int data);
    pair<int, pair<TreeNode *, TreeNode *>> maxDistance(TreeNode *node);
    void printTree(TreeNode *node);
};

BSTree::BSTree()
{
    root = NULL;
}

BSTree::~BSTree()
{
    delete root;
}

void BSTree::insert(int data)
{
    if (root == NULL)
    {
        root = new TreeNode(data);
    }
    else
    {
        insert(root, data);
    }
}

void BSTree::insert(TreeNode *node, int data)
{
    if (data < node->data)
    {
        if (node->left == NULL)
        {
            node->left = new TreeNode(data);
            return;
        }
        else
        {
            insert(node->left, data);
        }
    }
    else
    {
        if (node->right == NULL)
        {
            node->right = new TreeNode(data);
            return;
        }
        else
        {
            insert(node->right, data);
        }
    }
}

pair<int, pair<TreeNode *, TreeNode *>> BSTree::maxDistance()
{
    return maxDistance(root);
}

pair<int, pair<TreeNode *, TreeNode *>> BSTree::maxDistance(TreeNode *node)
{
    if (!node)
        return {0, {NULL, NULL}};
    auto left = maxDistance(node->left);
    auto right = maxDistance(node->right);
    int height = 1 + max(left.first, right.first);
    int distance = left.first + right.first;
    pair<TreeNode *, TreeNode *> farthest = {node, node};
    if (left.second.first)
    {
        farthest = {left.second.first, left.second.second};
        distance = max(distance, left.first);
    }
    if (right.second.first)
    {
        farthest = {farthest.first, right.second.second};
        distance = max(distance, right.first);
    }
    distance = max(distance, height);
    return {distance, farthest};
}

void BSTree::printTree()
{
    printTree(root);
}

void BSTree::printTree(TreeNode *node)
{
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        for (int i = 0; i < n; i++)
        {
            TreeNode *curr = q.front();
            q.pop();
            if (curr->left)
                q.push(curr->left);
            if (curr->right)
                q.push(curr->right);
            cout << curr->data << " ";
        }
        cout << endl;
    }
}

int main()
{
    int n;
    BSTree tree;
    cout << "Enter the number of nodes in the tree: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        tree.insert(rand()/1e4);
    }

    pair<int, pair<TreeNode *, TreeNode *>> maxDisWithNodes = tree.maxDistance();
    cout << "The maximum distance is between "
         << maxDisWithNodes.second.first->data
         << " & "
         << maxDisWithNodes.second.second->data << " nodes with distance: "
         << maxDisWithNodes.first << endl;
    tree.printTree();
    return 0;
}
