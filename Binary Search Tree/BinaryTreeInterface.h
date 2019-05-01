/**
This templated class provides a public interface that enables
polymorphism. Its functions are used for performing operations
on and with binary trees.

@author		Solomon Colley
@file		BinaryTreeInterface.h
@since		04/22/2019
*/

#pragma once

#pragma warning(disable:4290)

#include "NotFoundException.h"

template<class ItemType>
class BinaryTreeInterface
{
public:
	/**
	Tests whether this binary tree is empty or not.
	@return		True if this binary tree is empty,
					or false if not.
	*/
	virtual bool isEmpty() const = 0;

	/**
	Gets the height of this binary tree.
	@return		The height of the binary tree.
	*/
	virtual int getHeight() const = 0;

	/**
	Gets the number of nodes in this binary tree.
	@return		The number of nodes in this binary tree.
	*/
	virtual int getNumberOfNodes() const = 0;

	/**
	Gets the data item that is in the root of this
	binary tree.
	@pre		The binary tree is not empty.
	@post		The root’s data has been returned and the binary
					tree is unchanged.
	@return		The data in the root of the binary tree.
	*/
	virtual ItemType getRootData() const = 0;

	/**
	Replaces the data item in the root of this binary tree
	with the given data item if the tree is not empty. However,
	if the tree is empty, inserts a new root node containing the
	given data item into the binary tree.
	@post		The entry in the root of the binary tree is
					set as the argument's value.
	@param		const ItemType& newEntry
	@return		void
	*/
	virtual void setRootData(const ItemType& newData) = 0;

	/**
	Adds a new node containing the given data item to this
	binary tree.
	@post		The binary tree contains a new node with the
					given data item.
	@param		const ItemType& newData
	@return		True if the addition was successful, or false not.
	*/
	virtual bool add(const ItemType& newData) = 0;

	/**
	Removes the node containing the given data item from this binary tree.
	@post		The appropriate node was removed if a match was found.
	@param		const ItemType& data
	@return		True if the removal was successful, or false not.
	*/
	virtual bool remove(const ItemType& data) = 0;

	/**
	Removes all nodes from this binary tree.
	@post		The binary tree is empty.
	@return		void
	*/
	virtual void clear() = 0;

	/**
	Gets the specified entry from this binary tree.
	@post		The desired entry has been returned, and the binary tree
					is unchanged. If no such entry was found, a Not Found
					Exception is thrown.
	@param		const ItemType& anEntry
	@return		The entry in the binary tree that matches the given entry.
	@throws		NotFoundException if the given entry is not in the tree.
	*/
	virtual ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException) = 0;

	/**
	Tests whether a given entry occurs in this binary tree or not.
	@post		The binary tree is unchanged.
	@param		const ItemType& anEntry
	@return		True if the entry occurs in the tree, or false if not.
	*/
	virtual bool contains(const ItemType& anEntry) const = 0;

	/**
	Traverses this binary tree in preorder and calls the user-defined
	function 'visit' once for each node. 'visit' may perform an operation
	on or with the data in each visited node.
	@post		The tree may change or remain unchanged depending on
					the functionality of the user-defined function
					'visit'.
	@param		void visit(ItemType&)
	@return		void
	*/
	virtual void preorderTraverse(void visit(ItemType&)) const = 0;

	/**
	Traverses this binary tree in inorder and calls the user-defined
	function 'visit' once for each node. 'visit' may perform an operation
	on or with the data in each visited node.
	@post		The tree may change or remain unchanged depending on
					the functionality of the user-defined function
					'visit'.
	@param		void visit(ItemType&)
	@return		void
	*/
	virtual void inorderTraverse(void visit(ItemType&)) const = 0;

	/**
	Traverses this binary tree in postorder and calls the user-defined
	function 'visit' once for each node. 'visit' may perform an operation
	on or with the data in each visited node.
	@post		The tree may change or remain unchanged depending on
					the functionality of the user-defined function
					'visit'.
	@param		void visit(ItemType&)
	@return		void
	*/
	virtual void postorderTraverse(void visit(ItemType&)) const = 0;
}; // end BinaryTreeInterface
