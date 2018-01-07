/*
 * File:   GTUMap.cpp
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on December 13, 2017, 11:00 A.M
 * This file is implemetation file GTUMap class 
 */

#include "GTUMap.h"

namespace DurakliEfkanSetAndMap {

	template <class K, class V> 
	GTUMap<K,V>::GTUMap()
				:GTUSet<pair<K,V> >() 

	{ /* Intentioanlly empty */}


	template <class K, class V> 
	V GTUMap<K,V>::operator[] (const K& k)
	{
		shared_ptr<Node<pair<K,V> > > current = this->head;
		while (current) {

			if ((current->getData()).first == k) 
				return (current->getData()).second;
			
			current = current->getNext();
		}
	}

	template <class K, class V>
	int GTUMap<K,V>::count(const K & val) const 
	{
		shared_ptr<Node<pair<K,V> > > current = this->head;
		while (current) {
			if ((current->getData()).first == val)
				return 1;
			return 0;
		}
	}

	template <class K, class V>
	void GTUMap<K,V>::insert(const pair<K,V> & val) throw (exception)
	{
		shared_ptr<Node<pair<K, V> > > current = this->head;
		while(current) {
			if ((current->getData()).first == val.first)
				throw invalid_argument("Key is exist in map");
			current = current->getNext();
		}
		shared_ptr<Node<pair<K, V> > > newNode(make_shared<Node<pair<K, V> > >(val));
		if (this->head == NULL) {
			this->head = newNode;
		}
		else if ((this->head->getData()).first >= val.first) {
			newNode->setNext(this->head);
			(newNode->getNext())->setPrev(newNode);
			this->head = newNode;
		}
		else {
			current = this->head;
			while (current->getNext() != NULL && ((current->getNext())->getData()).first < val.first)
				current = current->getNext();
			newNode->setNext(current->getNext());

			if (current->getNext() != NULL)
				(newNode->getNext())->setPrev(newNode);

			current->setNext(newNode);
			newNode->setPrev(current); 
		}
		this->length++;
	}

	template <class K, class V> 
	void GTUMap<K,V>::erase(const K & val)
	{
		if (this->length > 0) {
			shared_ptr<Node<pair<K, V> > > current = this->head;
			bool flag = false;
			while (current) {
				if (current->getData().first == val) {
					flag = true;
					break;
				}
				current = current->getNext();
			}
			if (flag) {
				if (this->head == current)
					this->head = (this->head)->getNext();
				else {
					shared_ptr<Node<pair<K, V> > > tempprev(make_shared<Node<pair<K, V> > > ());	
					shared_ptr<Node<pair<K, V> > > tempnext(make_shared<Node<pair<K, V> > > ());
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
}

