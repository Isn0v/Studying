#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


bool valid_traversal(TreeNode* cur_node, long min, long max){
    if (cur_node == nullptr){
        return true;
    }

    if (cur_node->val <= min || cur_node->val >= max){
        return false;
    }

    bool left_check = valid_traversal(cur_node->left, min, cur_node->val);
    bool right_check = valid_traversal(cur_node->right, cur_node->val, max);
    return left_check && right_check;
}

bool isValidBST(TreeNode* root) {
    return valid_traversal(root, std::numeric_limits<long>::min(), std::numeric_limits<long>::max());
}