#include <iostream>
#include <algorithm>
#include <vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

//void left_rotation(TreeNode* root){
//    TreeNode* tmp = root->left;
//
//    root->left->left = new TreeNode(tmp->val, tmp->left, tmp->right);
//    root->left->right = root->right->left;
//
//    root->left->val = root->val;
//
//    root = root->right;
//    root->left = tmp;
//}
//
//void right_rotation(TreeNode* root){
//    TreeNode* tmp = root->right;
//
//    root->right->right = new TreeNode(tmp->val, tmp->left, tmp->right);
//    root->right->left = root->left->right;
//
//    root->right->val = root->val;
//
//    root = root->left;
//    root->right = tmp;
//}
//
//int get_height(TreeNode* root){
//    if (root == nullptr){
//        return 0;
//    }
//
//    return 1 + std::max(get_height(root->left), get_height(root->right));
//}
//
//int height_dif(TreeNode* root){
//    return get_height(root->right) - get_height(root->left);
//}
//
//TreeNode* balanceBST(TreeNode* root) {
//    TreeNode* cur_root = root;
//
//    // dif < 0 -> left part is higher
//    // dif > 0 -> right part
//    int root_height_dif = height_dif(cur_root);
//
//
//    if (root_height_dif == 2){
//        int right_height_dif = height_dif(cur_root->right);
//        if (right_height_dif == 0 || right_height_dif == 1){
//            left_rotation(cur_root);
//        } else if (right_height_dif == -1){
//            right_rotation(cur_root->right);
//            left_rotation(cur_root);
//        }
//    } else if (root_height_dif == -2) {
//        int left_height_dif = height_dif(cur_root->left);
//        if (left_height_dif == 0 || left_height_dif == 1){
//            right_rotation(cur_root);
//        } else if (left_height_dif == -1){
//            left_rotation(cur_root->left);
//            right_rotation(cur_root);
//        }
//    }
//}

void traversal(TreeNode* root, std::vector<int>& view){
    if (root == nullptr){
        return;
    }

    traversal(root->left, view);
    view.push_back(root->val);
    traversal(root->right, view);
}

TreeNode* inorder_to_BST(int s , int e , std::vector<int> &view){
    if(s > e)
        return nullptr;

    int mid = (s+e)/2;

    TreeNode* temp = new TreeNode(view[mid]);
    temp->left = inorder_to_BST(s , mid-1 , view);
    temp->right = inorder_to_BST(mid+1 , e , view);

    return temp;
}

TreeNode* balanceBST(TreeNode* root) {
    auto view = new std::vector<int>();
    traversal(root, *view);

    return inorder_to_BST(0, view->size() - 1, *view);
}