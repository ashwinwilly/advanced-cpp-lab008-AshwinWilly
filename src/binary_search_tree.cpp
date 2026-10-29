#include "project/binary_search_tree.h"

#include <algorithm>
#include <stdexcept>

BinarySearchTree::BinarySearchTree() : root_(nullptr), size_(0) {}

BinarySearchTree::~BinarySearchTree() {
    deleteSubtree(root_);
}

void BinarySearchTree::deleteSubtree(TreeNode* node) {
    if (node == nullptr) {
        return;
    }

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

bool BinarySearchTree::insert(int value) {
    if(search(value)){
        return false;
    }
    root_=insertRecursive(root_,value);
    size_++;
    return true;
}

bool BinarySearchTree::remove(int value) {

    if(!search(value)) return false;
    root_=removeRecursive(root_,value);
    size_--;
    return true;
}

bool BinarySearchTree::search(int value) const {
    return searchRecursive(root_,value);
}

bool BinarySearchTree::contains(int value) const {
    return searchRecursive(root_,value);
}

bool BinarySearchTree::empty() const noexcept {
    return size_ == 0;
}

std::size_t BinarySearchTree::size() const noexcept {
    return size_;
}

int BinarySearchTree::height() const {
    if(empty()) return 0;
    return heightRecursive(root_);
}

std::vector<int> BinarySearchTree::inorderTraversal() const {
    std::vector<int> result;
    inorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::preorderTraversal() const {
    std::vector<int> result;
    preorderRecursive(root_, result);
    return result;
}

std::vector<int> BinarySearchTree::postorderTraversal() const {
    std::vector<int> result;
    postorderRecursive(root_, result);
    return result;
}

int BinarySearchTree::minimum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return minimumRecursive(root_);
}

int BinarySearchTree::maximum() const {
    if (empty()) {
        throw std::logic_error("BST is empty");
    }
    return maximumRecursive(root_);
}

TreeNode* BinarySearchTree::insertRecursive(TreeNode* node, int value) {
    if (node == nullptr) {
        TreeNode* insert=new TreeNode(value);
        return insert;
    }

    if (value < node->value) {
        node->left = insertRecursive(node->left,value);
    }
    else if (value > node->value) {
        node->right = insertRecursive(node->right,value);
    }
    else {
       return node;
    }

    return node;
}

TreeNode* BinarySearchTree::removeRecursive(TreeNode* node, int value) {
    if(node==nullptr){
        return nullptr;
    }
    if(node->value<value){
        node->right=removeRecursive(node->right,value);
    }else if(node->value >value){
        node->left=removeRecursive(node->left,value);
    }else{//found target
        if(node->right==nullptr && node->left==nullptr){//childless
            delete node;
            return nullptr;
        }else if(node->right==nullptr || node->left==nullptr){//1 child node
            TreeNode* child;
            if(node->right!=nullptr){
                child=node->right;
            }else{
                child=node->left;
            }
            delete node;
            return child;
        }else{//both children
            int min=minimumRecursive(node->right);
            node->value=min;
            node->right=removeRecursive(node->right,min);
        }
    }
    return node;
}

bool BinarySearchTree::searchRecursive(const TreeNode* node, int value) const {
    if(node==nullptr){
        return false;
    }else if(node->value==value){
        return true;
    }else if(node->value>value){
        return searchRecursive(node->left,value);
    }else{
        return searchRecursive(node->right,value);
    }
}

void BinarySearchTree::inorderRecursive(const TreeNode* node, std::vector<int>& result) const {
        if(node==nullptr){
            return;
        }
        
        inorderRecursive(node->left,result);
        result.push_back(node->value);//vist
        inorderRecursive(node->right,result);


}

void BinarySearchTree::preorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if(node==nullptr){
        return;
    }
    result.push_back(node->value);
    preorderRecursive(node->left,result);
    preorderRecursive(node->right,result);
}

void BinarySearchTree::postorderRecursive(const TreeNode* node, std::vector<int>& result) const {
    if(node==nullptr){
        return;
    }
    
    postorderRecursive(node->left,result);
    postorderRecursive(node->right,result);
    result.push_back(node->value);
}

int BinarySearchTree::heightRecursive(const TreeNode* node) const {
    if(node==nullptr){
        return 0;
    }
    return 1+ std::max(heightRecursive(node->left),heightRecursive(node->right));
}

int BinarySearchTree::minimumRecursive(const TreeNode* node) const {
    if(node->left==nullptr){
        return node->value;
    }
    return minimumRecursive(node->left);
}

int BinarySearchTree::maximumRecursive(const TreeNode* node) const {
    if(node->right==nullptr){
        return node->value;
    }
    return maximumRecursive(node->right);
}
