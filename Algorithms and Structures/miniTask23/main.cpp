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


void traversal(TreeNode* cur_node, std::vector<int>& vals, bool& is_bst){
    if(cur_node == nullptr){
        return;
    }

    traversal(cur_node->left, vals, is_bst);
    if(vals.empty()){
        vals.push_back(cur_node->val);
    } else {
        if(vals[vals.size() - 1] >= cur_node->val){
            is_bst = false;
        }

        vals.push_back(cur_node->val);
    }

    traversal(cur_node->right, vals, is_bst);
}

bool isValidBST(TreeNode* root) {
    std::vector<int> vals;
    bool is_bst = true;

    traversal(root, vals, is_bst);

    return is_bst;
}