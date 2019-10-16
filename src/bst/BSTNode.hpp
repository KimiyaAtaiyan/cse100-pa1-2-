/*
 * Author: Kimiya Ataiyan
 * UserID: kataiyan
 * Date: 5/10/19
 * Filename: BSTNode.hpp
 * Source of help: tutors in lab, piazza
 */

#ifndef BSTNODE_HPP
#define BSTNODE_HPP
#include <iomanip>
#include <iostream>
using namespace std;

template <typename Data>

class BSTNode {
  public:
    BSTNode<Data>* left;
    BSTNode<Data>* right;
    BSTNode<Data>* parent;
    Data const data;  // the const Data in this node.

    BSTNode(const Data& d) : data(d) {
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    /*
     * Function name: successor
     * Function Prototype: BSTNode<Data> * successor()
     * Description: find the successor of the node its called on, meaning the
     * smallest element that is larger than this node Return: BSTNode<Data> is
     * the successor, or nullptr if no successor
     */
    BSTNode<Data>* successor() {
        // if node has right subtree, find least value of node from that right
        // subtree

        if (this == nullptr) {
            return nullptr;
        }
        if (right != nullptr) {
            BSTNode<Data>* temp = right;

            // move until most left node of right tree
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            if (temp->data == data) {
                return nullptr;
            } else {
                return temp;
            }
        } else {  // if node has no right tree, iterate backwards

            BSTNode<Data>* temp = this;

            while (temp->parent != nullptr) {
                temp = temp->parent;

                if (data < temp->data) {
                    return temp;
                }
            }

            return nullptr;
        }
    }
};

/** DO NOT CHANGE THIS METHOD
 *  Overload operator<< to print a BSTNode's fields to an ostream.
 */
template <typename Data>
ostream& operator<<(ostream& stm, const BSTNode<Data>& n) {
    stm << '[';
    stm << setw(10) << &n;                  // address of the BSTNode
    stm << "; p:" << setw(10) << n.parent;  // address of its parent
    stm << "; l:" << setw(10) << n.left;    // address of its left child
    stm << "; r:" << setw(10) << n.right;   // address of its right child
    stm << "; d:" << n.data;                // its data field
    stm << ']';
    return stm;
}

#endif  // BSTNODE_HPP
