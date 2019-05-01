/**
This templated class provides methods for creating and performing
operations with a binary tree.

@author		Solomon Colley
@file		BinaryNodeTree.h
@since		04/22/2019
*/

#pragma once

#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "PreconditionException.h"
#include "NotFoundException.h"

template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
	BinaryNode<ItemType>* rootPtr;	// Pointer to the root node.

protected:
	//-------------------------------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//-------------------------------------------------------------------------------------

	/**
	Recursive utility function for getting the height of this subtree.
	@param		BinaryNode<ItemType>* subTreePtr
	@return		The height of this subtree.
	*/
	int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;

	/**
	Recursive utility function for getting the number of nodes of
	this subtree.
	@param		BinaryNode<ItemType>* subTreePtr
	@return		The number of nodes of this subtree.
	*/
	int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;

	/**
	Recursive utility function for deleting all the nodes from the subtree.
	@param		BinaryNode<ItemType>* subTreePtr
	@return		void
	*/
	void destroyTree(BinaryNode<ItemType>* subTreePtr);

	/**
	Recursive utility function that adds a new node to the tree in a left/right
	fashion to maintain the tree's balance.
	@post		The new node has been added to the tree and the tree
					is balanced.
	@param		BinaryNode<ItemType>* subTreePtr
	@param		BinaryNode<ItemType>* newNodePtr
	@return		A pointer to the subtree.
	*/
	BinaryNode<ItemType>* balancedAdd(BinaryNode<ItemType>* subTreePtr,
		BinaryNode<ItemType>* newNodePtr);

	/**
	Removes the target data item from the tree by calling moveValuesUpTree
	to overwrite the item with the item from a child node. Uses a depth-first
	search.
	@pre		The tree is not empty.
	@post		The target data item has been removed from the tree and
					any values have been moved up the tree, maintaining
					the tree's balance.
	@param		BinaryNode<ItemType>* subTreePtr
	@param		const ItemType target
	@param		bool& success
	@return		A pointer to the subtree, or nullptr if the tree is empty.
	*/
	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr,
		const ItemType target, bool& success);

	/**
	Copies the data items up the tree to overwrite a data item in the current
	node until a leaf is reached. The leaf is then removed because its item
	is stored in the parent node.
	@pre		The node is not a leaf.
	@post		The data items have been moved up the tree, maintaining
					the tree's balance.
	@param		BinaryNode<ItemType>* subTreePtr
	@return		A pointer to the subtree, or nullptr if the node was a leaf.
	*/
	BinaryNode<ItemType>* moveValuesUpTree(BinaryNode<ItemType>* subTreePtr);

	/**
	Recursive function for searching for the target data item in the tree
	by using a preorder traversal of the tree.
	@pre		The tree is not empty.
	@param		BinaryNode<ItemType>* treePtr
	@param		const ItemType& target
	@param		bool& success
	@return		A pointer to the target node, or nullptr if it was
					not found.
	*/
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr,
		const ItemType& target,
		bool& success) const;

	/**
	Copies the tree rooted at treePtr and returns a pointer to the copy.
	@post		The tree was copied.
	@param		const BinaryNode<ItemType>* treePtr
	@return		A pointer to the copy of the tree, or nullptr if the tree
					was empty.
	*/
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;

	/**
	Recursive utility method for performing a preorder traversal of the tree.
	@param		void visit(ItemType&)
	@param		BinaryNode<ItemType>* treePtr
	@return		void
	*/
	void preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;

	/**
	Recursive utility method for performing an inorder traversal of the tree.
	@param		void visit(ItemType&)
	@param		BinaryNode<ItemType>* treePtr
	@return		void
	*/
	void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;

	/**
	Recursive utility method for performing a postorder traversal of the tree.
	@param		void visit(ItemType&)
	@param		BinaryNode<ItemType>* treePtr
	@return		void
	*/
	void postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;

public:
	//-------------------------------------------------------------------------------------
	// Constructor and Destructor Section.
	//-------------------------------------------------------------------------------------

	BinaryNodeTree();
	BinaryNodeTree(const ItemType& rootItem);
	BinaryNodeTree(const ItemType& rootItem,
		const BinaryNodeTree<ItemType>* leftTreePtr,
		const BinaryNodeTree<ItemType>* rightTreePtr);
	BinaryNodeTree(const BinaryNodeTree<ItemType>& tree);
	virtual ~BinaryNodeTree();

	//-------------------------------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	// See @file BinaryTreeInterface.h for documentation.
	//-------------------------------------------------------------------------------------

	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PreconditionException);
	void setRootData(const ItemType& newData);
	bool add(const ItemType& newData);
	bool remove(const ItemType& data);
	void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;

	//-------------------------------------------------------------------------------------
	// Public Traversals Section.
	// See @file BinaryTreeInterface.h for documentation.
	//-------------------------------------------------------------------------------------

	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

	//-------------------------------------------------------------------------------------
	// Overloaded Operator Section.
	//-------------------------------------------------------------------------------------

	/**
	Overloads the assignment operator = for clearing the tree and copying the
	tree pointed to by rightHandSide to this tree. A pointer to this tree
	is returned.
	@post		rightHandSide is copied and a pointer to it is returned.
	@param		const BinaryNodeTree& rightHandSide
	@return		A pointer to this tree.
	*/
	BinaryNodeTree& operator=(const BinaryNodeTree& rightHandSide);
}; // end BinaryNodeTree

#include "BinaryNodeTree.cpp"
