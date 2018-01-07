/*
 * File:   GTUSetBase.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on December 13, 2017, 11:00 A.M
 * This file is interface file of abstract GTUSetBase class
 */

#ifndef HW6_GTUSETBASE_H
#define HW6_GTUSETBASE_H

#include "GTUIterator.h"

namespace DurakliEfkanSetAndMap {

	#define MAXSIZE 1000  // maxsize for container
	
	template<class T>
	class GTUSetBase
	{
	public:
		// type definition for Iterator
		typedef GTUIterator<T> Iterator;

		GTUSetBase() :length(0) {} // no paramater constructor

		// PURE VIRTUAL FUNCTIONS
		virtual bool empty() const = 0;
		virtual int size() const = 0;
		virtual int max_size() const = 0;
		virtual void erase(const T & val) = 0;
		virtual void insert(const T & val) throw (exception) = 0;
		virtual void clear() noexcept = 0;
		virtual Iterator find(const T & val) const = 0;
		virtual int count(const T & val) const = 0;
		virtual Iterator begin() const noexcept = 0;
		virtual Iterator end() const noexcept = 0;
	protected:
		shared_ptr<Node<T> > head;
		int length;

	};
}


#endif // HW6_GTUSETBASE_H