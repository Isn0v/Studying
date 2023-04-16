#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void traversal(std::vector<int>& view, TreeNode* cur_node, int level){
    if (cur_node == nullptr){
        return;
    }

    if (view.size() == level){
        view.push_back(cur_node->val);
    }

    traversal(view, cur_node->right, level + 1);
    traversal(view, cur_node->left, level + 1);
}

std::vector<int> rightSideView(TreeNode* root) {
    std::vector<int> vec = {};

    traversal(vec, root, 0);

    return vec;
}