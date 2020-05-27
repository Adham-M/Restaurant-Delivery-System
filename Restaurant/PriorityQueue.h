#pragma once

#include"Generic_DS/Node.h"

template <typename T>
class PriorityQueue
{
private:

	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, const int& PI);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	~PriorityQueue();
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, const int& PI)
{
	// Insert the new node
	if (isEmpty())
	{
		Node<T>* newNodePtr = new Node<T>(newEntry, nullptr, PI);
		if (newNodePtr == nullptr)
			return false;
		frontPtr = newNodePtr; // The queue is empty
		backPtr = newNodePtr; // New node is at back
	}
	else if (PI>frontPtr->getPriorityIndicator())
	{
		Node<T>* temp = frontPtr;
		Node<T>* newNodePtr = new Node<T>(newEntry, frontPtr, PI);
		frontPtr = newNodePtr;
		if (newNodePtr == nullptr)
			return false;
	}
	else
	{
		Node<T>* Prev = frontPtr;
		Node<T>* Temp = frontPtr->getNext();
		while (Temp != nullptr)
		{
			if (PI > Temp->getPriorityIndicator())
			{
				Node<T>* newNodePtr = new Node<T>(newEntry, Temp, PI);
				if (newNodePtr == nullptr)
					return false;
				Prev->setNext(newNodePtr);
				return true;
			}
			Prev = Temp;
			Temp = Prev->getNext();
		}
		Node<T>* newNodePtr = new Node<T>(newEntry, nullptr, PI);
		if (newNodePtr == nullptr)
			return false;
		Prev->setNext(newNodePtr);
		backPtr = newNodePtr;
	}
	return true;
} // end enqueue

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;

}

template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}