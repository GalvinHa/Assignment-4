//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
	 @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <type_traits>

//   SORTING ----------------------------------------------------
template<class ItemType>
void LinkedBag<ItemType>::sort(int method) {
	if (itemCount <= 1)
		return;

	if (method == 0) {
		// update function call if you change the prototype. 
		mergeSort();
	} 
	else {
		// for EXTRA CREDIT, update function call if you change the prototype.
		// If you do NOT implement quickSort, NO action needed here
		quickSort();
	}
}
//mergesort ----------------------------------------------------------------------------------------------------------
// Merge two sorted linked lists
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::mergeSortedLists(Node<ItemType>* left, Node<ItemType>* right) {
	if (!left) return right;
	if (!right) return left;

	Node<ItemType>* result = nullptr;
	if (left->getItem() <= right->getItem()) {
		result = left;
		result->setNext(mergeSortedLists(left->getNext(), right));
	}
	else {
		result = right;
		result->setNext(mergeSortedLists(left, right->getNext()));
	}
	return result;
}

// Recursive merge sort on linked list nodes
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::mergeSortNodes(Node<ItemType>* head) {
	if (!head || !head->getNext()) return head;

	// Split list in half
	Node<ItemType>* slow = head;
	Node<ItemType>* fast = head->getNext();
	while (fast && fast->getNext()) {
		slow = slow->getNext();
		fast = fast->getNext()->getNext();
	}

	Node<ItemType>* mid = slow->getNext();
	slow->setNext(nullptr);

	// Recursive sort
	Node<ItemType>* left = mergeSortNodes(head);
	Node<ItemType>* right = mergeSortNodes(mid);

	// Merge sorted halves
	return mergeSortedLists(left, right);
}

// Merge sort public function
template<class ItemType>
void LinkedBag<ItemType>::mergeSort() {
	headPtr = mergeSortNodes(headPtr);
}
//mergesort ----------------------------------------------------------------------------------------------------------
//Extra Credit -- TO DO: implement quick sort and change its prototype 
//                       if you need to.
//quicksort ----------------------------------------------------------------------------------------------------------
template<class ItemType>
void LinkedBag<ItemType>::quickSort() {
	Node<ItemType>* tail = getTail(headPtr);
	headPtr = quickSortRec(headPtr, tail);
}

// Recursive QuickSort
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::quickSortRec(Node<ItemType>* head, Node<ItemType>* end) {
	if (!head || head == end)
		return head;

	Node<ItemType>* newHead = nullptr;
	Node<ItemType>* newEnd = nullptr;

	Node<ItemType>* pivot = partition(head, end, &newHead, &newEnd);

	// Sort the left part
	if (newHead != pivot) {
		Node<ItemType>* temp = newHead;
		while (temp->getNext() != pivot)
			temp = temp->getNext();
		temp->setNext(nullptr);

		newHead = quickSortRec(newHead, temp);

		// Connect sorted left with pivot
		Node<ItemType>* tailLeft = getTail(newHead);
		tailLeft->setNext(pivot);
	}

	// Sort the right part
	pivot->setNext(quickSortRec(pivot->getNext(), newEnd));

	return newHead;
}

// Partition function
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::partition(Node<ItemType>* head, Node<ItemType>* end,
	Node<ItemType>** newHead, Node<ItemType>** newEnd) {
	Node<ItemType>* pivot = end;
	Node<ItemType>* prev = nullptr;
	Node<ItemType>* curr = head;
	Node<ItemType>* tail = pivot;

	while (curr != pivot) {
		if (curr->getItem() < pivot->getItem()) {
			if (!*newHead)
				*newHead = curr;
			prev = curr;
			curr = curr->getNext();
		}
		else {
			if (prev)
				prev->setNext(curr->getNext());
			Node<ItemType>* temp = curr->getNext();
			curr->setNext(nullptr);
			tail->setNext(curr);
			tail = curr;
			curr = temp;
		}
	}

	if (!*newHead)
		*newHead = pivot;

	*newEnd = tail;
	return pivot;
}

// Get tail of list
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getTail(Node<ItemType>* current) {
	while (current && current->getNext())
		current = current->getNext();
	return current;
}
// --------------------------------------------------------------
//quicksort ----------------------------------------------------------------------------------------------------------
template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0) {
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag) {
	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty
	else
	{
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());

		Node<ItemType>* newChainPtr = headPtr;		// Points to last node in new chain
		origChainPtr = origChainPtr->getNext();	  // Advance original-chain pointer

		while (origChainPtr != nullptr)
		{
			ItemType nextItem = origChainPtr->getItem();
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag() {
	clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const {
	return itemCount == 0;
}

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const {
	return itemCount;
}

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry) {
	Node<ItemType>* nextNodePtr = new Node<ItemType>();
	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);
	headPtr = nextNodePtr;
	itemCount++;
	return true;
}

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const {
	std::vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}
	return bagContents;
}

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry) {
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem) {
		entryNodePtr->setItem(headPtr->getItem());
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		itemCount--;
	}
	return canRemoveItem;
}

template<class ItemType>
bool LinkedBag<ItemType>::removeAlt(const ItemType& anEntry) {
	Node<ItemType>* prev = headPtr;
	Node<ItemType>* cur = headPtr;
	bool found = false;

	while ((cur != nullptr) && !found) {
		found = (*(cur->getItem()) == *anEntry);
		if (!found) {
			prev = cur;
			cur = cur->getNext();
		}
	}

	if (found) {
		prev->setNext(cur->getNext());
		delete cur;
		cur = nullptr;
		itemCount--;
	}

	return found;
}

template<class ItemType>
void LinkedBag<ItemType>::clear() {
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr) {
		headPtr = headPtr->getNext();
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = headPtr;
	}
	itemCount = 0;
}

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const {
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem()) frequency++;
		counter++;
		curPtr = curPtr->getNext();
	}
	return frequency;
}

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const {
	return (getPointerTo(anEntry) != nullptr);
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const {
	bool found = false;
	Node<ItemType>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	}
	return curPtr;
}
