/**
This is a program that demonstrates the use of the binary search tree (BST)
data structure and its underlying algorithms. The BinarySearchTree class
and its dependencies provide users with a full implementation of BSTs.

@author		Solomon
@file		Main.cpp
@since		04/22/2019
*/

#include <iostream>
#include <random>
#include "BinarySearchTree.h"	// BST ADT

/* index and parameter are used for traversing and performing
operations with the data in the BST. */
int index = 1, parameter = 0;

/**
Displays the current entry being visited in the BST.
@param		int& anEntry
@return		void
*/
void display(int& anEntry);

/**
Finds and displays a specific node's value in the BST given
its position by traversing the BST and visiting each node.
@param		int& anEntry
@return		void
*/
void searchByPosUtility(int& anEntry);

/**
Finds and displays a specific node's value in the BST given
its value by traversing the BST and visiting each node.
@param		int& anEntry
@return		void
*/
void searchByValUtility(int& anEntry);

int main()
{
	BinarySearchTree<int>* bstPtr = new BinarySearchTree<int>();

	cout << "Testing the exceptions of the binary search tree (BST) ~"
		<< "\n\nTest 1 - Attempting to get the root data of an empty BST."
		<< "\nThis will throw a Precondition Exception.\n";
	try
	{
		bstPtr->getRootData();
		throw bstPtr;	// Throw exception on empty tree.
	}
	catch (const exception& e)
	{
		cout << e.what();
	} // end try-catch

	cout << "\n\nTest 2 - Attempting to set the root data of the BST."
		<< "\nThis will throw a Precondition Exception.\n";
	try
	{
		bstPtr->setRootData(-1);
		throw bstPtr;	// Throw exception. Cannot set a BST's root data.
	}
	catch (const exception& e)
	{
		cout << e.what();
	} // end try-catch

	cout << "\n\nTest 3 - Attempting to get a value that is not in the BST."
		<< "\nThis will throw a Not Found Exception.\n";
	try
	{
		bstPtr->getEntry(-1);
		throw bstPtr;	// Throw an exception. Cannot get a value from an empty BST.
	}
	catch (const exception& e)
	{
		cout << e.what();
	} // end try-catch

	cout << "\n\nCreating a BST consisting of 100 random integers -100 <= x <= 100 ~\n\n";
	int* randInts = new int[100];
	random_device seeder;
	mt19937 engine(seeder());
	uniform_int_distribution<int> distribution(-100, 100);
	for (int i = 0; i < 100; ++i)
	{
		randInts[i] = distribution(engine);
		bstPtr->add(randInts[i]);
	} // end for

	cout << "The BST now contains " << bstPtr->getNumberOfNodes() << " entries.\n"
		<< "The height of the BST is " << bstPtr->getHeight() << ".\n"
		<< "The root data of the BST is " << bstPtr->getRootData() << ".\n\n";

	cout << "Traversing and displaying the BST preorder ~\n\n";
	bstPtr->preorderTraverse(display);
	index = 1;

	cout << "\nRemoving the first 50 entries that were added to the BST ~\n\n";
	try
	{
		for (int i = 0; i < 50; ++i)
		{
			if (!bstPtr->remove(randInts[i]))	// If a removal fails, throw an exception.
				throw bstPtr;
		} // end for
		cout << "The entries were removed successfully.";
	}
	catch (const exception& e)
	{
		cout << e.what();
	} // end try-catch

	cout << "\n\nThe BST now contains " << bstPtr->getNumberOfNodes() << " entries."
		<< "\nThe height of the BST is " << bstPtr->getHeight() << "."
		<< "\nThe root data of the BST is " << bstPtr->getRootData() << ".";

	cout << "\n\nTraversing and displaying the BST postorder ~\n\n";
	bstPtr->postorderTraverse(display);
	index = 1;

	cout << "\nSearching for the 100th entry (" << randInts[99] << ") that was added to the BST ~"
		<< "\nNote: There could be more than one entry with this value.\n\n";
	parameter = randInts[99];
	bstPtr->preorderTraverse(searchByValUtility);
	index = 1;

	cout << "\nSearching for the entry at position " << 13 << " in the BST ~\n\n";
	parameter = 13;
	bstPtr->preorderTraverse(searchByPosUtility);
	index = 1;

	cout << "\nTraversing and displaying the BST inorder ~\n\n";
	bstPtr->inorderTraverse(display);
	index = 1;

	cout << "\nFreeing allocated memory and destroying the BST ~\n";
	delete[] randInts;
	bstPtr->clear();
	bstPtr->~BinarySearchTree();
	delete bstPtr;
	bstPtr = nullptr;

	cout << "Enter any character to exit: ";
	cin.get();

	return 0;
} // end main

void display(int& anEntry)
{
	cout << anEntry << ", ";

	if (index++ % 10 == 0)	// Display 10 entries per line.
		cout << "\n";
} // end display

void searchByPosUtility(int& anEntry)
{
	if (parameter == index)
		cout << "Entry " << anEntry << " is at position " << index << ".\n";
	++index;
} // end searchByPosUtility

void searchByValUtility(int& anEntry)
{
	if (parameter == anEntry)
		cout << "Entry " << anEntry << " is at position " << index << ".\n";
	++index;
} // end searchByValUtility
