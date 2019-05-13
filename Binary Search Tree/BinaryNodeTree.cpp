/**
This templated class provides methods for creating and performing
operations with a binary tree.

@author		Solomon Colley
@file		BinaryNodeTree.cpp
@since		04/22/2019
*/

#include "BinaryNodeTree.h" 

// -------------------------------------------------------------------------------------
// Protected Utility Methods Section.
// Recursive helper methods for the public methods.
// -------------------------------------------------------------------------------------

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + std::max(getHeightHelper(subTreePtr->getLeftChildPtr()),
			getHeightHelper(subTreePtr->getRightChildPtr())); // end if-else
} // end getHeightHelper

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + getNumberOfNodesHelper(subTreePtr->getLeftChildPtr())
		+ getNumberOfNodesHelper(subTreePtr->getRightChildPtr()); // end if-else
} // end getNumberOfNodesHelper

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		BinaryNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
		BinaryNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();

		if (getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->setRightChildPtr(rightPtr);
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->setLeftChildPtr(leftPtr);
		}  // end if-else

		return subTreePtr;
	}  // end if-else
} // end balancedAdd

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::moveValuesUpTree(BinaryNode<ItemType>* subTreePtr)
{
	BinaryNode<ItemType>* leftPtr = subTreePtr->getLeftChildPtr();
	BinaryNode<ItemType>* rightPtr = subTreePtr->getRightChildPtr();
	int leftHeight = getHeightHelper(leftPtr);
	int rightHeight = getHeightHelper(rightPtr);

	if (leftHeight > rightHeight)
	{
		subTreePtr->setItem(leftPtr->getItem());
		leftPtr = moveValuesUpTree(leftPtr);
		subTreePtr->setLeftChildPtr(leftPtr);
		return subTreePtr;
	}
	else
	{
		if (rightPtr != nullptr)
		{
			subTreePtr->setItem(rightPtr->getItem());
			rightPtr = moveValuesUpTree(rightPtr);
			subTreePtr->setRightChildPtr(rightPtr);
			return subTreePtr;
		}
		else
		{
			delete subTreePtr;	// This item was a leaf and is not important.
			return nullptr;
		}  // end if-else
	}  // end if-else
} // end moveValuesUpTree

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,
	const ItemType target,
	bool& success)
{
	if (subTreePtr == nullptr) // The item was not found here.
		return nullptr;

	if (subTreePtr->getItem() == target)	// Found the item.
	{
		subTreePtr = moveValuesUpTree(subTreePtr);
		success = true;
		return subTreePtr;
	}
	else
	{
		BinaryNode<ItemType>* targetNodePtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(targetNodePtr);
		if (!success) // The right subTree does not need to be searched.
		{
			targetNodePtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
			subTreePtr->setRightChildPtr(targetNodePtr);
		}  // end if-else

		return subTreePtr;
	} // end if-else
} // end removeValue

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr,
	const ItemType& target,
	bool& success) const
{
	if (treePtr == nullptr)	// The node was not found here.
		return nullptr;

	if (treePtr->getItem() == target)	// Found the node.
	{
		success = true;
		return treePtr;
	}
	else
	{
		BinaryNode<ItemType>* targetNodePtr = findNode(treePtr->getLeftChildPtr(), target, success);
		if (!success)	// The right subTree does not need to be searched.
		{
			targetNodePtr = findNode(treePtr->getRightChildPtr(), target, success);
		} // end if-else

		return targetNodePtr;
	} // end if-else
} // end findNode

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
	BinaryNode<ItemType>* newTreePtr = nullptr;

	// Copy all the tree nodes during a preorder traversal.
	if (treePtr != nullptr)
	{
		// Copy the current node.
		newTreePtr = new BinaryNode<ItemType>(treePtr->getItem(), nullptr, nullptr);
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
	} // end if-else

	return newTreePtr;
} // end copyTree

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
	}  // end if-else
} // end destroyTree

// -------------------------------------------------------------------------------------
// Protected Tree Traversal Sub-Section.
// -------------------------------------------------------------------------------------

template<class ItemType>
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	}  // end if-else
} // end preorder

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
		inorder(visit, treePtr->getRightChildPtr());
	}  // end if-else
} // end inorder

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		ItemType theItem = treePtr->getItem();
		visit(theItem);
	} // end if-else
} // end postorder

// -------------------------------------------------------------------------------------
// Constructor and Destructor Section.
// -------------------------------------------------------------------------------------

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
} // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
} // end parameterized constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
	const BinaryNodeTree<ItemType>* leftTreePtr,
	const BinaryNodeTree<ItemType>* rightTreePtr)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr),
		copyTree(rightTreePtr->rootPtr));
} // end parameterized constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& treePtr)
{
	rootPtr = copyTree(treePtr.rootPtr);
} // end parameterized copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
} // end destructor

// -------------------------------------------------------------------------------------
// Public BinaryTreeInterface Methods Section.
// See @file BinaryTreeInterface.h for documentation.
// -------------------------------------------------------------------------------------

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return rootPtr == nullptr;
} // end isEmpty

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
} // end getHeight

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
} // end getNumberOfNodes

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
	destroyTree(rootPtr);
	rootPtr = nullptr;
} // end clear

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PreconditionException)
{
	if (isEmpty())
		throw PreconditionException("Function getRootData() was called with an empty tree."); // end if-else

	return rootPtr->getItem();
} // end getRootData

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newItem)
{
	if (isEmpty())
		rootPtr = new BinaryNode<ItemType>(newItem, nullptr, nullptr);
	else
		rootPtr->setItem(newItem); // end if-else
} // end setRootData

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = balancedAdd(rootPtr, newNodePtr);
	return true;
} // end add

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& target)
{
	bool isSuccessful = false;
	rootPtr = removeValue(rootPtr, target, isSuccessful);
	return isSuccessful;
} // end remove

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool isSuccessful = false;
	BinaryNode<ItemType>* binaryNodePtr = findNode(rootPtr, anEntry, isSuccessful);

	if (isSuccessful)
		return binaryNodePtr->getItem();
	else
		throw NotFoundException("The entry does not exist within the binary search tree."); // end if-else
} // end getEntry

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool isSuccessful = false;
	findNode(rootPtr, anEntry, isSuccessful);
	return isSuccessful;
} // end contains

// -------------------------------------------------------------------------------------
// Public Traversals Section.
// See @file BinaryTreeInterface.h for documentation.
// -------------------------------------------------------------------------------------

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	preorder(visit, rootPtr);
} // end preorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
} // end inorderTraverse

template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	postorder(visit, rootPtr);
} // end postorderTraverse

// -------------------------------------------------------------------------------------
// Overloaded Operator Section.
// -------------------------------------------------------------------------------------

template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(
	const BinaryNodeTree<ItemType>& rightHandSide)
{
	if (!isEmpty())
		clear();
	this = copyTree(&rightHandSide);
	return *this;
} // end operator=
