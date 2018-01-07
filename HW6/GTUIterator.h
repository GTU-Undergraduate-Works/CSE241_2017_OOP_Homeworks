/*
 * File:   GTUIterator.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on December 13, 2017, 11:00 A.M
 * This file is interface file of GTUIterator class
 */

#ifndef GTUITERATOR_H
#define GTUITERATOR_H

#include "Node.h"

namespace DurakliEfkanSetAndMap {

	template<class T>
	class GTUIterator
	{
	public:
		GTUIterator() :current(NULL) {}
		GTUIterator(const shared_ptr<Node<T> > & initial) :current(initial) {}

		const T& operator*() const { return current->getData();}

		GTUIterator& operator ++() // prefix ++ opeartor
		{
			current = current->getNext();
			return *this;
		}

		GTUIterator operator ++(int ignore) // postfix ++ operator
		{
			GTUIterator start(current);
			current = current->getNext();
			return start;
		}

		GTUIterator& operator --()  // prefix -- operator
		{
	
			current = current->getPrev();
			return *this;

		}
		GTUIterator operator --(int ignore) // postfix ++ opearator
		{	
			
			GTUIterator start(current);
			current = current->getPrev();
			return start;
		}

		bool operator == (const GTUIterator & rightSide) const
		{ return (current == rightSide.current); }

		bool operator != (const GTUIterator & rightSide) const
		{ return (current != rightSide.current); }

		GTUIterator & operator=(const GTUIterator & rightSide) 
		{
			current = rightSide.current;
			return *this;
		}
		T* operator->()
		{
			T* temp;
			temp = &(*current);
			return temp;
		}

	private:
		shared_ptr<Node<T> > current;
	
	};
}


#endif // GTUITERATOR_H