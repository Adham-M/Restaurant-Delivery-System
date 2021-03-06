
#ifndef __NODE_H_
#define __NODE_H_

template < typename T>
class Node
{
private:
	T item; // A data item
	Node<T>* next; // Pointer to next node
	int priorityIndicator;    //for Vip motorcycles.
	int ID;      //For order purposes.
public:
	Node();
	Node(const T & r_Item);	//passing by const ref.
	Node(const T & r_Item, const int& id);
	Node(const T & r_Item, Node<T>* nextNodePtr);
	Node(const T & r_Item, Node<T>* nextNodePtr, const int & PI);
	void setItem(const T & r_Item);
	void setID(int id);
	int GetID() const;
	void setNext(Node<T>* nextNodePtr);
	void setPriority(const int& PI);
	T getItem() const;
	Node<T>* getNext() const;
	int getPriorityIndicator() const;
}; // end Node


template < typename T>
Node<T>::Node()
{
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T& r_Item)
{
	item = r_Item;
	next = nullptr;
}

template < typename T>
Node<T>::Node(const T & r_Item, const int& id)
{
	item = r_Item;
	next = nullptr;
	setID(id);
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr)
{
	item = r_Item;
	next = nextNodePtr;
}

template < typename T>
Node<T>::Node(const T& r_Item, Node<T>* nextNodePtr, const int& PI)
{
	item = r_Item;
	next = nextNodePtr;
	priorityIndicator = PI;
}

template < typename T>
void Node<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void Node<T>::setNext(Node<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
int Node<T>::getPriorityIndicator() const
{
	return priorityIndicator;
}

template< typename T>
void Node<T>::setPriority(const int& PI)
{
	priorityIndicator = PI;
}

template < typename T>
T Node<T>::getItem() const
{
	return item;
}

template < typename T>
Node<T>* Node<T>::getNext() const
{
	return next;
}

template<class T>
int Node<T>::GetID() const
{
	return ID;
}

template<class T>
void Node<T>::setID(int id)
{
	ID = id;
}

#endif