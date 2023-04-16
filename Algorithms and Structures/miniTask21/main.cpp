#include <iostream>
#include <sstream>
#include <string>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void serialize_recursive(TreeNode* root, std::stringstream& ss){
    if(root == nullptr){
        ss << "null" << " ";
        return;
    } else {
        ss << root->val << " ";
    }

    serialize_recursive(root->left, ss);
    serialize_recursive(root->right, ss);
}

std::string serialize(TreeNode* root) {
    std::stringstream ss;
    serialize_recursive(root, ss);

    return ss.str();
}

void deserialize_recursive(TreeNode*& root, std::stringstream& ss){

    std::string token;
    ss >> token;


    if (token == "null" || ss.tellp() == std::streampos(0)){
        return;
    }


    int val = std::stoi(token);
    root = new TreeNode(val);

    deserialize_recursive(root->left, ss);
    deserialize_recursive(root->right, ss);

}

TreeNode* deserialize(std::string data) {
    std::stringstream ss;
    ss << data;

    std::string token;
    ss >> token;

    if (token == "null"){
        return nullptr;
    }

    int val = std::stoi(token);
    auto root = new TreeNode(val);

    deserialize_recursive(root->left, ss);
    deserialize_recursive(root->right, ss);

    return root;
}
