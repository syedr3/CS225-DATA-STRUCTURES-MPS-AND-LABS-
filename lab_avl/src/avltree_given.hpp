/**
 * @file avltree_given.cpp
 * Definitions of some standard binary tree functions.
 *
 * YOU WON'T NEED TO MODIFY THIS FILE.
 *
 * In fact, you shouldn't have to read below this line. To see what the given
 * functions do, read the header file.
 */

#include "binarytree/printtree.h"

template <class K, class V>
AVLTree<K, V>::AVLTree()
    : root(NULL), _out(&std::cout)
{
    
}

template <class K, class V>
AVLTree<K, V>::AVLTree(const AVLTree& other)
    : root(copy(other.root)), _out(&std::cout)
{

}

template <class K, class V>
AVLTree<K, V>::~AVLTree()
{
    clear(root);
}

template <class K, class V>
std::vector<K> AVLTree<K,V>::getInorderTraversal() const
{
    std::vector<K> traversal;
    getInorderTraversal(root, traversal);
    return traversal;
}

template <class K, class V>
void AVLTree<K,V>::getInorderTraversal(const Node* subRoot, std::vector<K>& traversal) const
{
    if (subRoot == NULL) {
        return;
    }
    getInorderTraversal(subRoot->left, traversal);
    traversal.push_back(subRoot->key);
    getInorderTraversal(subRoot->right, traversal);
}

template <class K, class V>
std::vector<K> AVLTree<K,V>::getPreorderTraversal() const
{
    std::vector<K> traversal;
    getPreorderTraversal(root, traversal);
    return traversal;
}

template <class K, class V>
void AVLTree<K,V>::getPreorderTraversal(const Node* subRoot, std::vector<K>& traversal) const
{
    if (subRoot == NULL) {
        return;
    }
    traversal.push_back(subRoot->key);
    getPreorderTraversal(subRoot->left, traversal);
    getPreorderTraversal(subRoot->right, traversal);
}

template <class K, class V>
std::vector<std::string> AVLTree<K,V>::getFunctionOrder() const {
    return functionCalls;
}

template <class K, class V>
const AVLTree<K, V>& AVLTree<K, V>::operator=(const AVLTree& rhs)
{
    if (this != &rhs) {
        clear(root);
        root = copy(rhs.root);
    }
    return *this;
}

template <class K, class V>
void AVLTree<K, V>::clear()
{
    clear(root);
    root = NULL;
    functionCalls.clear();
}

template <class K, class V>
typename AVLTree<K, V>::Node* AVLTree<K, V>::copy(const Node* subRoot)
{
    if (subRoot == NULL)
        return NULL;

    // Copy this node and its children
    Node* newNode = new Node(subRoot->key, subRoot->value);
    newNode->left = copy(subRoot->left);
    newNode->right = copy(subRoot->right);
    return newNode;
}

template <class K, class V>
void AVLTree<K, V>::clear(Node* subRoot)
{
    if (subRoot == NULL)
        return;

    clear(subRoot->left);
    clear(subRoot->right);
    delete subRoot;
}

template <class K, class V>
void AVLTree<K, V>::swap(Node*& first, Node*& second)
{
    K tempkey = first->key;
    V tempvalue = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = tempkey;
    second->value = tempvalue;
}

// class for generic printing

template <typename Node>
class AVLTreeNodeDescriptor
    : public GenericNodeDescriptor<AVLTreeNodeDescriptor<Node>>
{
  public:
    AVLTreeNodeDescriptor(const Node* root) : subRoot(root)
    {
    }
    bool isNull() const
    {
        return subRoot == NULL;
    }

    std::string key() const
    {
        std::stringstream ss;
        ss << subRoot->key;
        return ss.str();
    }

    AVLTreeNodeDescriptor left() const
    {
        return AVLTreeNodeDescriptor(subRoot->left);
    }
    AVLTreeNodeDescriptor right() const
    {
        return AVLTreeNodeDescriptor(subRoot->right);
    }

  private:
    const Node* subRoot;
};

template <class K, class V>
void AVLTree<K, V>::printFunctionOrder(std::ostream& out) const
{
    for (int i = 0; i < (int)functionCalls.size(); i++) {
        out << functionCalls[i] << std::endl;
    }
}

template <class K, class V>
void AVLTree<K, V>::print(std::ostream& out, bool order) const
{
    if(order)
        printFunctionOrder(out);
    printTree(AVLTreeNodeDescriptor<Node>(root), out);
}

template <class K, class V>
int AVLTree<K, V>::heightOrNeg1(const Node* node) const
{
    if (node == NULL)
        return -1;
    else
        return node->height;
}

template <class K, class V>
void AVLTree<K, V>::setOutput(std::ostream& newOut)
{
    _out = &newOut;
}
