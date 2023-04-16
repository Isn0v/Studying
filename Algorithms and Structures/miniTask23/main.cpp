#include <iostream>
#include <vector>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void traversal(TreeNode* cur_node, std::vector<int>& vals){
    if(cur_node == nullptr){
        return;
    }

    traversal(cur_node->left, vals);
    vals.push_back(cur_node->val);
    traversal(cur_node->right, vals);
}

bool isValidBST(TreeNode* root) {
    std::vector<int> vals;

    traversal(root, vals);

    for(int i = 1; i < vals.size(); i++){
           if (vals[i - 1] > vals[i] || std::count(vals.begin(), vals.end(), vals[i - 1]) > 1){
               return false;
           }
    }
    return true;
}