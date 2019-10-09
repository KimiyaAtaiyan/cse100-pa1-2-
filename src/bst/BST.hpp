/*
 * Author: Kimiya Ataiyan
 * Date: 10/4/19
 * UserID: kataiyan
 * Filename: BST.hpp
 * Source of help: tutors in lab, piazza
 */

#ifndef BST_HPP
#define BST_HPP
#include <iostream>
#include <vector>
#include "BSTIterator.hpp"
#include "BSTNode.hpp"
using namespace std;

template <typename Data>
class BST {
  protected:
    // pointer to the root of this BST, or 0 if the BST is empty
    BSTNode<Data>* root;

    // number of Data items stored in this BST.
    unsigned int isize;

    // height of this BST.
    int iheight;

  public:
    /** Define iterator as an aliased typename for BSTIterator<Data>. */
    typedef BSTIterator<Data> iterator;

    /** Default constructor.
     *  Initialize an empty BST.
     */
    BST() : root(0), isize(0), iheight(-1) {}

    virtual ~BST() { deleteAll(root); }

    /*
     * Function name: insert(const Data&item)
     * Function prototype: virtual bool insert(const Data&item)
     * Defintion: insert a copy of item into BST tree if not duplicate
     * Return: return true if inserted, false otherwise
     */

    virtual bool insert(const Data& item) {
        // start at root node and iterate through RHS or LHS of tree

        if (root != 0) {
            BSTNode<Data>* temp = root;
            int height = 0;

            while (height <= iheight) {
                // iterate through LHS
                if (item < temp->data) {
                    if (temp->left == 0) {
                        temp->left = new BSTNode<Data>(item);
                        temp->left->parent = temp;
                        isize++;
                        if (height == iheight) {
                            iheight++;
                        }
                        return true;
                    } else {
                        temp = temp->left;
                    }
                } else if (temp->data < item) {  // iterate through RHS

                    if (temp->right == 0) {
                        temp->right = new BSTNode<Data>(item);
                        temp->right->parent = temp;
                        isize++;

                        // if new row started, increment height
                        if (height == iheight) {
                            iheight++;
                        }
                        return true;
                    } else {
                        temp = temp->right;
                    }
                } else {  // if duplicate then return false

                    return false;
                }
                height++;
            }
        } else {  // seit height to 0 if its first elemtn to be inserted

            root = new BSTNode<Data>(item);
            isize++;
            iheight = 0;
            return true;
        }
    }

    /*
     * Function name: find(const Data & item)
     * Function prototype: virtual iterator find(const Data&item) const
     * Description: looks for an item in a BST tree and returns iterator to
     * pointing to that item, if found Return: iterator pointing to found node ,
     * or nullptr if not found
     */

    virtual iterator find(const Data& item) const {
        // compare to root to decide whether ot iterate through LHS or RHS

        BSTNode<Data>* temp = root;
        int height = 0;
        bool found = false;
	
	if(temp != 0){
        while (height <= iheight) {
            if (item < temp->data) {  // iterate through LHS

                temp = temp->left;
                height++;
                if(temp != nullptr) {
                    if(temp->data == item) {
                        found = true;
                        return BSTIterator<Data>(temp);
                    }
                }
            } else if (temp->data < item) {  // iterate through RHS

                temp = temp->right;
                height++;
                if (temp != nullptr) {
                    if (temp->data == item) {
                        found = true;
                        return BSTIterator<Data>(temp);
                    }
                }
            } else {  // check if equal to root
                    found = true;
                    return BSTIterator<Data>(temp);
            }
        }

        if (found == false) {
            return BSTIterator<Data>(nullptr);
        }
	}
    }

    /*
     * Function name: size
     * Function prototype: unsigned int size() const
     * Description: returns size of BST which is # of nodes
     * Return: unsigned int
     */

    unsigned int size() const { return isize; }

    /*
     * Function name: height
     * Function prototype: int height() const
     * Description: returns height of the tree
     * Return: int
     */
    int height() const { return iheight; }

    /*
     * Function name: empty
     * Function prototype: bool empty() const
     * Description: check if BST is empty
     * Return: true if no nodes in tree, false otherwise
     */
    bool empty() const {
        if (isize == 0) {
            return true;
        } else {
            return false;
        }
    }

    iterator begin() const { return BST::iterator(first(root)); }

    /** Return an iterator pointing past the last item in the BST.
     */
    iterator end() const { return typename BST<Data>::iterator(0); }

    /* Function name: inorder
     * Function Prototype: vector<Data> inorder() const
     * Description: uses the helper method inorderHelper to return a vector list
     * 			of the values in the BST in in-order traversal
     * Return: vector with data of each node
     */
    vector<Data> inorder() const {
        vector<Data> list;
        vector<Data> retList;
        BSTNode<Data>* temp = root;

        retList = inorderHelper(temp, list);

        return retList;
    }

    vector<Data> inorderHelper(BSTNode<Data>* node, vector<Data> list) const {

	if(node == nullptr){
		return list;
	}

        if (node->left != 0) {
            list = inorderHelper(node->left, list);
        }

        	list.push_back(node->data);

        if (node->right != 0) {
            list = inorderHelper(node->right, list);
        }

        return list;
    }

  private:
    /*
     * Function name: first
     * Function prototype: static BSTNode<Data>*first (BSTNode<Dta> * root)
     * Description: finds the node with the smallest data
     * Return: Node with smallest data
     */

    static BSTNode<Data>* first(BSTNode<Data>* root) {
        BSTNode<Data>* temp = root;

        if (root == 0) {
            return nullptr;
        }

        while (temp->left != 0) {
            temp = temp->left;
        }

        return temp;
    }

    /*
     * Function name: deleteAll
     * Function Prototype: static void deleteAll(BSTNode<Data> * n)
     * Description: deletes all dynamically allocated nodes
     * Return: none
     */
    static void deleteAll(BSTNode<Data>* n) {
        /* Pseudocode:
           if current node is null: return;
           recursively delete left sub-tree
           recursively delete right sub-tree
           delete current node
           */

        if (n == nullptr) {
            return;
        }
       
	deleteAll(n->left);
	deleteAll(n->right);
	delete n;

    }
};

#endif  // BST_HPP
