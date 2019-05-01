/**
This templated class provides methods for creating and performing
operations with a binary node.

@author		Solomon Colley
@file		BinaryNode.h
@since		04/22/2019
*/

#pragma once

template<class ItemType>
class BinaryNode
{
private:
	ItemType item;							// Data item.
	BinaryNode<ItemType>* leftChildPtr;		// Pointer to the left child.
	BinaryNode<ItemType>* rightChildPtr;	// Pointer to the right child.

public:
	// -------------------------------------------------------------------------------------
	// Constructor and Destructor Section.
	// -------------------------------------------------------------------------------------

	BinaryNode();
	BinaryNode(const ItemType& anItem);
	BinaryNode(const ItemType& anItem,
		BinaryNode<ItemType>* leftPtr,
		BinaryNode<ItemType>* rightPtr);

	// -------------------------------------------------------------------------------------
	// Public Methods Section.
	// -------------------------------------------------------------------------------------

	/**
	Sets the argument data item to this node's data item.
	@param		const ItemType& anItem
	@return		void
	*/
	void setItem(const ItemType& anItem);

	/**
	Returns the data item of this node.
	@return		A data item.
	*/
	ItemType getItem() const;

	/**
	Tests whether this node is a leaf or not.
	@return		True if this node is a leaf, or false if not.
	*/
	bool isLeaf() const;

	/**
	Returns the left child pointer of this node.
	@return		The left child pointer of this node.
	*/
	BinaryNode<ItemType>* getLeftChildPtr() const;

	/**
	Returns the right child pointer of this node.
	@return		The right child pointer of this node.
	*/
	BinaryNode<ItemType>* getRightChildPtr() const;

	/**
	Sets the argument leftPtr to this node's left child pointer.
	@param		BinaryNode<ItemType>* leftPtr
	@return		void
	*/
	void setLeftChildPtr(BinaryNode<ItemType>* leftPtr);

	/**
	Sets the argument rightPtr to this node's right child pointer.
	@param		BinaryNode<ItemType>* rightPtr
	@return		void
	*/
	void setRightChildPtr(BinaryNode<ItemType>* rightPtr);
}; // end BinaryNode

#include "BinaryNode.cpp"
