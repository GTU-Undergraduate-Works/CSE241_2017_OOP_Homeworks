#include <iostream>
#include <string>
#include "GTUSetBase.h"
#include "GTUSet.h"
#include "GTUSet.cpp"
#include "GTUMap.h"
#include "GTUMap.cpp"
#include "Node.h"
using namespace std;
using namespace DurakliEfkanSetAndMap;

template<class T>
shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>&, const GTUSetBase<T>&);


int main() {

	try {

		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "SET FUNCTIONS TESTS" << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		GTUSet<int> set1;
		GTUSet<int> set2;
		GTUSet<int>::Iterator p;

		if (set1.empty())
			cout << "set1 is empty" << endl;

		cout << "After Inserting 5,78,65,56,42,98,55,1, elements of set1 :" << endl;
		set1.insert(5);
		set1.insert(78);
		set1.insert(65);
		set1.insert(56);
		set1.insert(42);
		set1.insert(98);
		set1.insert(55);
		set1.insert(1);
		set2.insert(1);
		set2.insert(77);
		set2.insert(42);
		set2.insert(951);

		auto set3 = setIntersection(set1, set2);

		for (p = set1.begin(); p != set1.end(); p++)
			cout << *p << "  ";
		cout << "\nSize of set1 = " << set1.size() << endl;
		if (!set1.empty())
			cout << "set1 is not empty" << endl;

		cout << "Test for find(55) function" << endl;
		p = set1.find(55);
		cout <<"find(55) = "<< *p << endl;

		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "SET INTERSECTION TEST " << endl;

		cout << "Elements of set1: " ;
		for (p = set1.begin(); p != set1.end(); p++)
			cout << *p << "  ";
		cout << "\nElements of set2: " ;
		for (p = set2.begin(); p != set2.end(); p++)
			cout << *p << "  ";
		cout << "\nIntersection of set1 and set2: ";
		for (p = set3->begin(); p != set3->end(); p++)
			cout << *p << "  ";
		cout << "\n-----------------------------------------------------------------------------" << endl;

		set1.erase(56);
		set1.erase(98);
		cout << "\nAfter deleting 56 and 98, elements of set1" << endl;
		for (p = set1.begin(); p != set1.end(); p++)
			cout << *p << "  ";
		cout << "\nSize of set1 = " << set1.size() << endl;
		cout << "Count of 78 in set1 = " << set1.count(78) << endl;

		cout << "After clearing of all elements of set1" << endl;
		set1.clear();
		for (p = set1.begin(); p != set1.end(); p++)
			cout << *p << "  ";
		cout << "\nSize of set1 = " << set1.size() << endl;
		cout << "Max size of set1 = " << set1.max_size() << endl;

		cout << "-----------------------------------------------------------------------------" << endl;
		cout << "MAP FUNCTIONS TESTS" << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		
		GTUMap<string, int> map;
		GTUMap<string, int>::Iterator mapIter;

		if (map.empty())
			cout << "map is empty" << endl;

		cout << "After inserting elements to map" << endl;
		map.insert(pair<string, int>("elma", 1));
		map.insert(pair<string, int>("armut", 7));
		map.insert(pair<string, int>("ayva", 89));
		map.insert(pair<string, int>("muz", 56));
		map.insert(pair<string, int>("kiraz", 56));
		map.insert(pair<string, int>("seftali", 53));


		for (mapIter = map.begin(); mapIter != map.end(); mapIter++)
			cout << "Key: " << (*mapIter).first << "--Value: " << (*mapIter).second << endl;

		cout << "Size of map = " << map.size() << endl;
		if (!map.empty())
			cout << "map is not empty" << endl;

		cout << "After deleting 'elma' and 'armut' " << endl;
		map.erase("elma");
		map.erase("armut");
		for (mapIter = map.begin(); mapIter != map.end(); mapIter++)
			cout << "Key: " << (*mapIter).first << "--Value: " << (*mapIter).second << endl;
		cout << "Size of map = " << map.size() << endl;
		cout << "After clearing of all elements of map" << endl;
		map.clear();
		for (mapIter = map.begin(); mapIter != map.end(); mapIter++)
			cout << "Key: " << (*mapIter).first << "--Value: " << (*mapIter).second << endl;

		cout << "\nSize of map = " << map.size() << endl;
		cout << "Max size of map = " << map.max_size() << endl;
		cout << "-----------------------------------------------------------------------------" << endl;

		cout << "Index operator Test" << endl;
		map.insert(pair<string, int>("elma", 1));
		cout << "elma = " << map["elma"] << endl;
		cout << "EXEPTION TEST" << endl;
		map.insert(pair<string, int>("elma", 1));

	}
	catch (exception e) {
		cout << e.what() << endl;
	}
	return 0;
}

template<class T>
shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>& set1, const GTUSetBase<T>& set2)
{
	shared_ptr<GTUSet<T> > retVal(make_shared<GTUSet<T> >());
	typename GTUSet<T>::Iterator iter1;
	typename GTUSet<T>::Iterator iter2;
	for (iter1 = set1.begin(); iter1 != set1.end(); iter1++) {
		for (iter2 = set2.begin(); iter2 != set2.end(); iter2++) {
			if (*iter1 == *iter2) 
				retVal->insert(*iter2);
		}
	}
	return retVal;
}

