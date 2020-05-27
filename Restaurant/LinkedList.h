#pragma once
#include "Generic_DS/Node.h"
#include "Rest/Order.h"

template<class T>
class LinkedList
{
private:
	Node<T>* Head;
	int Count;
public:
	LinkedList();
	bool Add(const T& it);
	bool Remove(const T& it);
	void Clear();
	int GetCurrentSize() const;
	bool IsEmpty() const;
	bool Contains(const T& it);
	int GetFrequencyOf(const T& it);
	void Print();
	bool InsertEnd(const T& it, int id);
	Node<T>* SearchID(const int& id);
	bool Delete(Node<T>* n);
	bool GetTop(T& it);
	bool RemoveFirst(T&);
	virtual ~LinkedList();
};

template<class T>
LinkedList<T>::LinkedList()
{
	Count = 0;
	Head = nullptr;
}

template<class T>
bool LinkedList<T>::Add(const T& it)
{
	Node<T>* Temp = new Node<T>(it, Head);
	if (Temp == nullptr)
		return false;

	Head = Temp;
	Count++;
	return true;
}

template<class T>
bool LinkedList<T>::RemoveFirst(T& it)
{
	if (Head == nullptr)
		return false;
	it = Head->getItem();
	Head = Head->getNext();
	Count--;
	return true;
}

template<class T>
bool LinkedList<T>::Remove(const T& it)
{
	Node<T>* Temp = Head;
	if (Head == nullptr)
		return false;

	if (Head->getItem() == it)
	{
		Temp = Head;
		Head = Head->getNext();
		delete Temp;
		Temp = nullptr;
		Count--;
		return true;
	}

	Node<T>* Prev = Temp;
	while (Temp != nullptr)
	{
		if (Temp->getItem() == it)
		{
			Prev->setNext(Temp->getNext());
			delete Temp;
			Temp = nullptr;
			Count--;
			return true;
		}
		Prev = Temp;
		Temp = Temp->getNext();
	}
	return false;
}

template<class T>
void LinkedList<T>::Clear()
{
	Count = 0;
	Node<T>* Temp = Head;
	while (Temp != nullptr)
	{
		Head = Temp;
		Temp = Temp->getNext();
		delete Head;;
		Head = nullptr;
	}
}

template<class T>
int LinkedList<T>::GetCurrentSize() const
{
	return Count;
}

template<class T>
bool LinkedList<T>::IsEmpty() const
{
	if (Count == 0)
		return true;
	return false;
}

template<class T>
bool LinkedList<T>::Contains(const T& it)
{
	Node<T>* Temp = Head;
	while (Temp != nullptr)
	{
		if (Temp->getItem() == it)
			return true;
		Temp = Temp->getNext();
	}
	return false;
}

template<class T>
int LinkedList<T>::GetFrequencyOf(const T& it)
{
	int Freq = 0;
	Node<T>* Temp = Head;
	while (Temp != nullptr)
	{
		if (Temp->getItem() == it)
			Freq++;
		Temp = Temp->getNext();
	}
	return Freq;
}

template<class T>
bool LinkedList<T>::InsertEnd(const T& it, int id)
{
	Node<T>* Temp = Head;
	Node<T>* NewNode = new Node<T>(it, nullptr);
	NewNode->setID(id);
	if (NewNode == nullptr)
		return false;
	if (Temp == nullptr)
		Head = NewNode;
	else
	{
		while (Temp->getNext() != nullptr)
			Temp = Temp->getNext();
		Temp->setNext(NewNode);
	}
	Count++;
	return true;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	Clear();
}

template<class T>
void LinkedList<T>::Print()
{
	Node<T>* Temp = Head;
	while (Temp != nullptr)
	{
		cout << "[ " << Temp->getItem() << " ]-->" << " ";
		Temp = Temp->getNext();
	}
	cout << "#" << endl;
}


template<class T>
Node<T>* LinkedList<T>::SearchID(const int& id)
{
	Node<T>* Temp = Head;
	while (Temp != nullptr)
	{
		if (Temp->GetID() == id)
			return Temp;
		Temp = Temp->getNext();
	}
	return Temp;
}

template < typename T>
bool LinkedList<T>::Delete(Node<T>* n)
{
	Node<T>* ptr = Head;

	if (Head == n)
	{
		Node<T>* d = Head;
		Head = Head->getNext();
		delete d;
		Count--;
		return true;
	}

	while (ptr != nullptr && ptr->getNext() != nullptr)
	{
		if (ptr->getNext() == n)
		{
			Node<T>* d = ptr->getNext();
			ptr->setNext(d->getNext());
			delete d;
			Count--;
			return true;
		}
		ptr = ptr->getNext();
		if (ptr == nullptr)
			return false;
	}
	return false;
}

template< typename T>
bool LinkedList<T>::GetTop(T &it)
{
	if (Head != nullptr)
	{
		it = Head->getItem();
		return true;
	}
	return false;
}