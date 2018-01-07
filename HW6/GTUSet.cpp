/*
 * File:   GTUSet.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on December 13, 2017, 11:00 A.M
 * This file is implemetation file GTUSet class 
 */

#include "GTUSet.h"

namespace DurakliEfkanSetAndMap {

	template<class T>
	GTUSet<T>::GTUSet()
				:GTUSetBase<T>()
	
	{ /* Intentionally empty */}

	// checks set is empty or not
	// if set is empty return true, if not retur false
	template<class T>
	bool GTUSet<T>::empty() const
	{
		if (this->length == 0)
			return true;
		return false;
	}
	
	// returns size of set
	template<class T>
	int GTUSet<T>::size() const 
	{
		return this->length;
	}

	// returns max size of set
	template<class T>
	int GTUSet<T>::max_size() const 
	{
		return MAXSIZE;
	}

	// insert element set ordered
	// comparision operators must be overloaded
	template<class T>
	void GTUSet<T>::insert(const T & val) throw (exception)
	{
		
		shared_ptr<Node<T> > current = this->head;
		while(current) {
			if (current->getData() == val)
				throw invalid_argument("Element is exist in set");
			current = current->getNext();
		}
		shared_ptr<Node<T> > newNode(make_shared<Node<T> >(val));
		if (this->head == NULL) {
			this->head = newNode;
		}
		else if (this->head->getData() >= val) {
			newNode->setNext(this->head);
			(newNode->getNext())->setPrev(newNode);
			this->head = newNode;
		}
		else {
			current = this->head;
			while (current->getNext() != NULL && (current->getNext())->getData() < val)
				current = current->getNext();
			newNode->setNext(current->getNext());

			if (current->getNext() != NULL)
				(newNode->getNext())->setPrev(newNode);

			current->setNext(newNode);
			newNode->setPrev(current); 
		}
		this->length++;
	}

	// deletes specific elemets from set
	template<class T>
	void GTUSet<T>::erase(const T & val)
	{	
		if (this->length > 0) {
			shared_ptr<Node<T> > current = this->head;
			bool flag = false;
			while (current) {

				if (current->getData() == val) {
					flag = true;
					break;
				}
				current = current->getNext();
			}
			if (flag) {
				if (this->head == current)
					this->head = (this->head)->getNext();
				else {
					shared_ptr<Node<T> > tempprev(make_shared<Node<T> >());	
					shared_ptr<Node<T> > tempnext(make_shared<Node<T> >());
					tempprev = current->getPrev();
					tempnext = current->getNext();
					tempprev->setNext(tempnext);
					if (tempnext != NULL)
						tempnext->setPrev(tempprev);
				}
			}
			(this->length)--;
		}
	}
	
	// clear all elements of set	
	template<class T>
	void GTUSet<T>::clear() noexcept
	{
		this->head = NULL;
		this->length = 0;
	}

	// return iterator for specific element
	template<class T>	
	GTUIterator<T> GTUSet<T>::find(const T & val) const
	{
		shared_ptr<Node<T> > current = this->head;

		while (current) {

			if (current->getData() == val)
				return GTUIterator<T>(current);

			current = current->getNext();
		}
		return GTUIterator<T>();
	}

	// return count of specific element in set
	template<class T>
	int GTUSet<T>::count(const T & val) const 
	{

		shared_ptr<Node<T> > current = this->head;
		while (current) {
			if (current->getData() == val)
				return 1;
			current = current->getNext();
		}
		return 0;
	}
}





