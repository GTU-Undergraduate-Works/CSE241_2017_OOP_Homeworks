/*
 * File:   GTUMap.h
 * Author: EFKAN DURAKLI - 161044086
 *
 * Created on December 13, 2017, 11:00 A.M
 * This file is interface file of GTUMap class
 */

#ifndef HW6_GTUMAP_H
#define HW6_GTUMAP_H

#include "GTUSet.h"

namespace DurakliEfkanSetAndMap {

	template <class K, class V> 
	class GTUMap : public GTUSet <pair<K,V> >
	{
	public:
		GTUMap();
		V operator[] (const K& k); // inex operator for map
		int count(const K & val) const; // redefinition 
		void insert(const pair<K,V> & val) throw (exception); // redefinition
		void erase(const K & val); // redefinition
 
	private:

	};
}

#endif // HW6_GTUMAP_H