/*
 * File:   GTUSet.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on December 13, 2017, 11:00 A.M
 * This file is interface file of GTUSet class
 */

#ifndef HW6_GTUSET_H
#define HW6_GTUSET_H

#include "GTUSetBase.h"

namespace DurakliEfkanSetAndMap {

	template <class T>
	class GTUSet : public GTUSetBase<T>
	{
	public:
		typedef GTUIterator<T> Iterator;

		GTUSet();
		GTUSet(const shared_ptr<GTUSet<T> > x) {}
		virtual bool empty() const;
		virtual int size() const; 
		virtual int max_size() const;
		virtual void insert(const T & val) throw (exception);
		virtual void erase(const T & val);
		virtual void clear() noexcept;
		virtual Iterator find(const T & val) const;
		virtual int count(const T & val) const ;
		virtual Iterator begin() const noexcept { return Iterator(this->head); }
		virtual Iterator end() const noexcept { return Iterator(); }
	};
}


#endif // HW6_GTUSET_H