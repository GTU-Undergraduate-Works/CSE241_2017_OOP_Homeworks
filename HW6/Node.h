/*
 * File:   Node.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on December 13, 2017, 11:00 A.M
 * This file is interface file of Node class
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <memory>
using namespace std;

namespace DurakliEfkanSetAndMap {

	template<class T>
	class Node
	{
	public:	
		Node() :next(NULL), prev(NULL) { }
		Node(const T & theData) :data(theData), next(NULL), prev(NULL) {}
		Node(const T& theData, shared_ptr<Node<T> >  thePrev, shared_ptr<Node<T> >  theNext) : data(theData), prev(thePrev), next(theNext) {}
		shared_ptr<Node<T> > getNext( ) const { return next; }
		shared_ptr<Node<T> > getPrev( ) const { return prev; }
		void setData(const T & theData) { data = theData;}
		void setNext(shared_ptr<Node<T> >  theNext) { next = theNext; }
		void setPrev(shared_ptr<Node<T> >  thePrev) { prev = thePrev; }
		const T& getData() const { return data;}

	private:
		shared_ptr<Node<T> >  next;
		shared_ptr<Node<T> >  prev;
		T data;
	};
}

#endif // NODET_H