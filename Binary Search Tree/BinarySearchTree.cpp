/**
This templated class provides methods for creating and performing
operations on a binary search tree (BST).

@author		Solomon Colley
@file		BinarySearchTree.cpp
@since		04/22/2019
*/

#include "BinarySearchTree.h" 
// #include "BinaryNode.h" 

// ---------------------------------------------------------------------------
// Protected Utility Methods Section.
// ---------------------------------------------------------------------------

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr,
	BinaryNode<ItemType>* newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		if (subTreePtr->getItem() > newNodePtr->getItem())
			subTreePtr->setLeftChildPtr(insertInorder(subTreePtr->getLeftChildPtr(), newNodePtr));
		else
			subTreePtr->setRightChildPtr(insertInorder(subTreePtr->getRightChildPtr(), newNodePtr)); // end if-else

		return subTreePtr;
	} // end if-else
} // end insertInorder

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr,
	const ItemType target,
	bool& success)
{
	if (subTreePtr == nullptr) // The item was not found here.
	{
		success = false;
		return nullptr;
	} // end if-else
	if (subTreePtr->getItem() == target)
	{
		// The item is in the root of some subtree.
		subTreePtr = removeNode(subTreePtr);
		success = true;
		return subTreePtr;
	}
	else
	{
		if (subTreePtr->getItem() > target)
			// Search the left subtree.
			subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
		else
			// Search the right subtree.
			subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success)); // end if-else

		return subTreePtr;
	}  // end if-else
} // end removeValue

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr)
{
	// Case 1: The node is a leaf and it is deleted.
	// Case 2: The node has one child and the parent adopts it.
	// Case 3: The node has two children so find the successor node.
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = nullptr;
		return nodePtr;
	}
	else if (nodePtr->getLeftChildPtr() == nullptr)	// This node only has a rightChild.
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightChildPtr() == nullptr)	// This node only has a leftChild.
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftChildPtr();
		delete nodePtr;
		nodePtr = nullptr;
		return nodeToConnectPtr;
	}
	else	// This node has two children.
	{
		ItemType newNodeValue;
		nodePtr->setRightChildPtr(removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	} // end if-else
} // end removeNode

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
	ItemType& inorderSuccessor)
{
	if (nodePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessor = nodePtr->getItem();
		return removeNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftChildPtr(removeLeftmostNode(nodePtr->getLeftChildPtr(), inorderSuccessor));
		return nodePtr;
	} // end if-else   
} // end removeLeftmostNode

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr,
	const ItemType& target) const
{
	// Uses a binary search.
	if (subTreePtr == nullptr)	// The node was not found here.
		return nullptr;
	else if (subTreePtr->getItem() == target) // Found the node.
		return subTreePtr;
	else if (subTreePtr->getItem() > target)
		// Search the left subtree.
		return findNode(subTreePtr->getLeftChildPtr(), target);
	else
		// Search the right subtree.
		return findNode(subTreePtr->getRightChildPtr(), target);
} // end findNode

// ---------------------------------------------------------------------------
// Constructor and Destructor Section.
// ---------------------------------------------------------------------------

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
} // end default constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, nullptr, nullptr);
} // end parameterized constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& treePtr)
{
	rootPtr = this->copyTree(treePtr.rootPtr);
} // end parameterized copy constructor

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	this->destroyTree(rootPtr);
} // end destructor

// ---------------------------------------------------------------------------
// Public BinaryTreeInterface Methods Section.
// ---------------------------------------------------------------------------

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return rootPtr == nullptr;
} // end isEmpty

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
	return this->getHeightHelper(rootPtr);
} // end getHeight

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
	return this->getNumberOfNodesHelper(rootPtr);
} // end getNumberOfNodes

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
	this->destroyTree(rootPtr);
	rootPtr = nullptr;
} // end clear

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PreconditionException)
{
	if (isEmpty())
		throw PreconditionException("Function getRootData() was called with an empty tree."); // end if-else

	return rootPtr->getItem();
} // end getRootData

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newItem) const throw(PreconditionException)
{
	throw PreconditionException("The root data in a binary search tree cannot be changed.");
} // end setRootData

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newData)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = insertInorder(rootPtr, newNodePtr);
	return true;
} // end add

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
	bool isSuccessful = false;
	rootPtr = removeValue(rootPtr, target, isSuccessful);
	return isSuccessful;
} // end remove

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	BinaryNode<ItemType>* nodeWithEntry = findNode(rootPtr, anEntry);

	if (nodeWithEntry == nullptr)
		throw NotFoundException("The entry does not exist within the binary search tree.");
	else
		return nodeWithEntry->getItem(); // end if-else
} // end getEntry

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	return (findNode(rootPtr, anEntry) != nullptr) ? true : false;  // nullptr is the same as false.
} // end contains

// ---------------------------------------------------------------------------
// Public Traversals Section.
// See @file BinaryTreeInterface.h for documentation.
// ---------------------------------------------------------------------------

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
{
	this->preorder(visit, rootPtr);
} // end preorderTraverse

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	this->inorder(visit, rootPtr);
} // end inorderTraverse

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
{
	this->postorder(visit, rootPtr);
} // end postorderTraverse

// ---------------------------------------------------------------------------
// Overloaded Operator Section.
// ---------------------------------------------------------------------------

template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::
operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
	if (!isEmpty())
		clear();
	this = copyTree(&rightHandSide);

	return *this;
} // end operator=
