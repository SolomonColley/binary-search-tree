/**
This templated class provides methods for creating and performing
operations on a binary search tree (BST).

@author		Solomon Colley
@file		BinarySearchTree.h
@since		04/22/2019
*/
 
#pragma once

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PreconditionException.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
private:
   BinaryNode<ItemType>* rootPtr;	// Pointer to the root of a tree.
   
protected:
	// ---------------------------------------------------------------------------
	// Protected Utility Methods Section.
	// ---------------------------------------------------------------------------

	/**
	Recursively finds where the argument as a given node should be
	placed in the tree and inserts it in a leaf node at that position.
	@post		The new node was inserted at the correct position in
					the tree.
	@param		BinaryNode<ItemType>* subTreePtr
	@param		BinaryNode<ItemType>* newNode
	@return		A pointer to the revised subtree, or nullptr if
					subTreePtr was nullptr.
	*/
	BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr,
                                       BinaryNode<ItemType>* newNode);
   
	/**
	Recursive function for removing the argument as a given target
	from the tree while maintaining a binary search tree structure.
	@post		The given target is removed from the tree.
	@param		BinaryNode<ItemType>* subTreePtr
	@param		const ItemType target
	@param		bool& success
	@return		A pointer to the revised subtree, or nullptr if
					subTreePtr was nullptr.
	*/
	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
                                     const ItemType target,
                                     bool& success);

	/**
	Recursive function for removing the argument as a given node
	pointer from the tree while maintaining a binary search tree
	structure.
	@post		The given node is removed from the tree.
	@param		BinaryNode<ItemType>* nodePtr
	@return		A pointer to the node.
	*/
	BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);

	/**
	Recursive function for removing the leftmost node in the left
	subtree of the node pointed to by nodePtr. Sets inorderSuccessor
	to the value in this node and returns a pointer to the revised
	subtree.
	@post		The leftmost node has been removed.
	@param		BinaryNode<ItemType>* nodePtr
	@param		ItemType& inorderSuccessor
	@return		A pointer to the revised subtree.
	*/
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                            ItemType& inorderSuccessor);

	/**
	Recursive function for returning a pointer to the node containing
	the given target value, or nullptr if the target value was
	not found in the tree.
	@param		BinaryNode<ItemType>* treePtr
	@param		const ItemType& target
	@return		A pointer to the node containing the target, or
					nullptr if it was not found.
	*/
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr,
                                  const ItemType& target) const;
   
public:
	// ---------------------------------------------------------------------------
	// Constructor and Destructor Section.
	// ---------------------------------------------------------------------------

	BinarySearchTree();
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& tree);
	virtual ~BinarySearchTree();
   
	// ---------------------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	// See @file BinaryTreeInterface.h for documentation.
	// ---------------------------------------------------------------------------

	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PreconditionException);
	void setRootData(const ItemType& newData) const throw(PreconditionException);
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	// ---------------------------------------------------------------------------
	// Public Traversals Section.
	// See @file BinaryTreeInterface.h for documentation.
	// ---------------------------------------------------------------------------

	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

	// ---------------------------------------------------------------------------
	// Overloaded Operator Section.
	// ---------------------------------------------------------------------------

	/**
	Overloads the assignment operator = for clearing the tree and copying the
	tree pointed to by rightHandSide to this tree. A pointer to this tree
	is returned.
	@post		rightHandSide is copied and a pointer to it is returned.
	@param		const BinaryNodeTree& rightHandSide
	@return		A pointer to this tree.
	*/
	BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);   
}; // end BinarySearchTree

#include "BinarySearchTree.cpp"
