/**
 * @file avltree.h
 * Declaraction of the AVLTree class. You will probably need to modify this
 * file to add helper functions.
 */

#pragma once

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

/**
 * The AVLTree class represents a linked-memory AVL Tree.
 * @tparam K the type of key stored in the tree
 * @tparam V the type of value stored in the tree
 */
template <class K, class V>
class AVLTree
{
  private:
    /**
     * Node represents a tree node; that is, an element in a AVLTree.
     * It stores a key, value, and pointers to its left and right children.
     */
    struct Node {
        K key;
        V value;
        Node* left;
        Node* right;
        int height;

        /**
         * Node constructor; sets children to point to `NULL`.
         * @param newKey The object to use as a key
         * @param newValue The templated data element that the constructed
         *  node will hold.
         */
        Node(const K& newKey, const V& newValue)
            : key(newKey), value(newValue), left(NULL), right(NULL), height(0)
        {
        }
    };

  public:
    /**
     * Constructor to create an empty tree.
     */
    AVLTree();

    /**
     * Copy constructor.
     * @param other The tree to copy
     */
    AVLTree(const AVLTree& other);

    /**
     * Destructor; frees all nodes associated with this tree.
     */
    ~AVLTree();

    /**
     * Assignment operator.
     * @param rhs The tree to copy
     * @return A reference to the current tree
     */
    const AVLTree& operator=(const AVLTree& rhs);

    /**
     * Frees all nodes associated with this tree and sets it to be empty.
     */
    void clear();

    /**
     * Inserts a key and value into the AVLTree.
     * @param key The key to insert
     * @param value The value associated with the key
     */
    void insert(const K& key, const V& value);

    /**
     * Removes a key from the AVLTree. The key is assumed to exist in the tree.
     * @param key The key to remove
     */
    void remove(const K& key);

    /**
     * Finds an element in the AVL tree.
     * @param key The element to search for
     * @return The value stored for that key
     */
    V find(const K& key) const;

    /**
     * Prints the function calls to a stream.
     * @param out The stream to print to (default is stdout)
     */
    void printFunctionOrder(std::ostream& out = std::cout) const;

    /**
     * Prints the AVLTree to a stream.
     * @param out The stream to print to (default is stdout)
     */
    void print(std::ostream& out = std::cout, bool order = true) const;

    /**
     * This function is used for grading.
     * @param newOut The stream to print to
     */
    void setOutput(std::ostream& newOut);

    /**
     * Gets the in-order traversal of an AVL tree's keys.
     */
    std::vector<K> getInorderTraversal() const;

    /**
     * Gets the pre-order traversal of an AVL tree's keys.
     */
    std::vector<K> getPreorderTraversal() const;

    /*
    * Gets vector of function calls.
    */
    std::vector<std::string> getFunctionOrder() const;

  private:
    /**
     * The root of the tree.
     */
    Node* root;

    /**
     * Private helper function for the public #insert function.
     * @param node The current node in the recursion
     * @param key The key to insert
     * @param value The value associated with the key
     */
    void insert(Node*& node, const K& key, const V& value);

    /**
     * Private helper function for the public #remove function.
     * @param node The current node in the recursion
     * @param key The key to remove
     */
    void remove(Node*& node, const K& key);

    /**
     * Finds a value (by key) in the AVL tree.
     * @param node The node to search from (current subroot)
     * @param key The key to search for
     * @return The value stored for that key
     */
    V find(Node* node, const K& key) const;

    /**
     * Rotate the tree right (there is an imbalance on the left side).
     * @param node The node to rotate
     */
    void rotateRight(Node*& node);

    /**
     * Rotates the tree left (there is an imbalance on the right side).
     * @param node The node to rotate
     */
    void rotateLeft(Node*& node);

    /**
     * A right-left rotation.
     * This function should simply call rotateRight and rotateLeft.
     * @param node The node to rotate
     */
    void rotateRightLeft(Node*& node);

    /**
     * A left-right rotation.
     * This function should simply call rotateLeft and rotateRight.
     * @param node The node to rotate
     */
    void rotateLeftRight(Node*& node);

    /**
     * Rebalance a node by performing rotations. You can assume that node->left
     * and node->right are both balanced. Even if no rotations are required,
     * you should update the node's height.
     * @param node The node to balance.
     */
    void rebalance(Node*& node);

    /**
     * Return the node->height if the node is not NULL. Otherwise return -1.
     * Note: this function does not calculate the **actual** height of a node.
     * @param node The node's height to check
     * @return The height of the node if it's non-`NULL` or -1 if it is `NULL`
     */
    int heightOrNeg1(const Node* node) const;

    /**
     * Swap the keys and values of two nodes.
     * @param first The first node to swap
     * @param second The node to swap with
     */
    void swap(Node*& first, Node*& second);

    /**
     * Helper function for #operator= and AVLTree(const AVLTree &).
     * @param subRoot The current node in the recursion
     */
    Node* copy(const Node* subRoot);

    /**
     * Private helper function for clear that clears beneath the parameter node.
     * @param subRoot The current node in the recursion
     */
    void clear(Node* subRoot);

    /**
     * Gets the in-order traversal of an AVL tree's keys.
     * @param subRoot The current node in the recursion
     */
    void getInorderTraversal(const Node* subRoot, std::vector<K>& traversal) const;

    /**
     * Gets the pre-order traversal of an AVL tree's keys.
     * @param subRoot The current node in the recursion
     */
    void getPreorderTraversal(const Node* subRoot, std::vector<K>& traversal) const;

    /** This variable is used for grading. */
    std::ostream* _out;

    /** This variable tests the order of function calls **/
    std::vector<std::string> functionCalls;
};

#include "avltree_given.hpp"
#include "avltree.hpp"
