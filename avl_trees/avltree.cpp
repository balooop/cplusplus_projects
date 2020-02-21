/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "avltree.h"

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * oldRoot = t;
    Node * newRoot = t->right;
    //t's right should be its right child's left child
    oldRoot->right = newRoot->left;
    //now the new root's (tmp) left child is the original root
    newRoot->left = oldRoot;
    //reassign/recalculate heights
    oldRoot->height = std::max(heightOrNeg1(oldRoot->left), heightOrNeg1(oldRoot->right)) + 1;
    newRoot->height = std::max(heightOrNeg1(newRoot->left), heightOrNeg1(newRoot->right)) + 1;
    t = newRoot; 

}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
     // your code here
    //right node is going to become root
    Node * oldRoot = t;
    Node * newRoot = t->left;
    //t's right should be its right child's left child
    oldRoot->left = newRoot->right;
    //now the new root's (tmp) left child is the original root
    newRoot->right = oldRoot;
    //reassign/recalculate heights
    oldRoot->height = std::max(heightOrNeg1(oldRoot->left), heightOrNeg1(oldRoot->right)) + 1;
    newRoot->height = std::max(heightOrNeg1(newRoot->left), heightOrNeg1(newRoot->right)) + 1;
    t = newRoot; 
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    //calculate balance
    int balance = heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);

    //check balance of node
    if(balance == -2)
    {
        //go left, figure out what to rotate
        int lbalance = heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
        if(lbalance == -1)
        {
            rotateRight(subtree);
        }
        else
        {
            rotateLeftRight(subtree);
        }
    }
    if(balance == 2)
    {
        //go right, figure out what to rotate
        int rbalance = heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->right->left);
        if(rbalance == 1)
        {
            rotateLeft(subtree);
        }
        else
        {
            rotateRightLeft(subtree);
        }        
    }

    subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    //if at a leaf, add node
    if(subtree == NULL)
    {
        subtree = new Node(key, value);
    }
    else if ( key < subtree->key)
    {
        //recurse left
        insert(subtree->left, key, value);
    }
    else if ( key > subtree->key)
    {
        //recurse right
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        //recurse left
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        //recurse right
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            //find IOP
            Node * iop = subtree->left;
            while(iop->right != NULL)
            {
                iop = iop->right;
            }
            //swap nodes with iop
            swap(subtree, iop);
            //remove iop from left subtree
            remove(subtree->left, iop->key);
        } else {
            /* one-child remove */
            // your code here
            Node * tmp = subtree;
            if(subtree->left != NULL)
            {
                subtree = subtree->left;
            }
            if(subtree->right != NULL)
            {
                subtree = subtree->right;
            }
            delete tmp;
            tmp = NULL;
        }
        // your code here
    }
    rebalance(subtree);
}