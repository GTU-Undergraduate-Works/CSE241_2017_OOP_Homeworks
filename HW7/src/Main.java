/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 * Tests GTUSet and GTUMap class
 * @author Efkan Duraklı
 */

import javafx.util.Pair;
import java.security.InvalidParameterException;

public class Main {
    
    public static void main(String args[]) {
        
        GTUSet<Integer> set1 = new GTUSet<Integer>();
        GTUSet<Integer> set2 = new GTUSet<Integer>();
        GTUSet<Integer> set3 = new GTUSet<Integer>();
        GTUMap<String,Integer> map1 = new GTUMap<String,Integer>();
        GTUMap<String,Integer> map2 = new GTUMap<String,Integer>();
        GTUMap<String,Integer> map3 = new GTUMap<String,Integer>();
        GTUSet<Integer>.GTUIterator setIter = set1.new GTUIterator();
        GTUMap<String,Integer>.GTUIterator mapIter = map1.new GTUIterator();
        int i;
        
        try {
            System.out.println("SET AND SET ITERATOR TESTS");
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("insert,erase,clear,begin,end,empty,max_size, count, find, intersection, hasNext, next, hasPrev, prev");
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("After inserting 78, 86, 55, 63 and 42 to set1");
            set1.insert(78);
            set1.insert(86);
            set1.insert(55);
            set1.insert(63);
            set1.insert(42);
            i = 1;
            setIter = set1.begin();
            while (setIter.hasNext()) {
                System.out.printf("Element %d = %d\n", i, setIter.next());
                i++;
            }
            System.out.printf("find(78) = %d\n", set1.find(78).next());
            if (!set1.empty())
                System.out.println("set1 is not empty");
            System.out.println("Size of set1 = " + set1.size());
            System.out.println("-----------------------------------------------------------------------------------");
            System.out.println("After erasing 86 from set1");
            set1.erase(86);
            setIter = set1.begin();
            i = 1;
            while (setIter.hasNext()) {
                System.out.printf("Element %d = %d\n", i, setIter.next());
                i++;
            }
            System.out.printf("Count of element 63 in set1 = %d\n", set1.count(63));
            System.out.printf("Count of element 73 in set1 = %d\n", set1.count(73));
            System.out.println("-------------------------------------------------------------------------------------");
            System.out.println("SET reverse Iterator Test");
            setIter = set1.end();
            i = set1.size();
            while (setIter.hasPrevious()) {
                System.out.printf("Element %d = %d\n", i, setIter.previous());
                i--;
            }
            System.out.println("Size of set1 = " + set1.size());
            System.out.println("Maxsize of set1 = " + set1.max_size());
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("After clearing all elements of set1");
            set1.clear();
            setIter = set1.begin();
            i = 1;
            while (setIter.hasNext()) {
                System.out.printf("Element %d = %d\n", i, setIter.next());
                i++;
            }
            System.out.println("Size of set1 = " + set1.size());
            if (set1.empty())
                System.out.println("set1 is empty\n");

            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("SET Intesection Test");
            System.out.println("------------------------------------------------------------------------------------");
            set1.insert(45);
            set1.insert(56);
            set1.insert(789);
            set1.insert(47);
            set2.insert(69);
            set2.insert(789);
            set2.insert(45);
            set2.insert(47);
            set3 = (GTUSet)set1.intersection(set2);
            System.out.println("Elements of set1:");
            setIter = set1.begin();
            i = 1;
            while (setIter.hasNext()) {
                System.out.printf("Element %d = %d\n", i, setIter.next());
                i++;
            }
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("Elements of set2:");
            setIter = set2.begin();
            i = 1;
            while (setIter.hasNext()) {
                System.out.printf("Element %d = %d\n", i, setIter.next());
                i++;
            }
            System.out.println("------------------------------------------------------------------------------------");
             System.out.println("Elements of Intersection of set1 and set2:");
            setIter = set3.begin();
            i = 1;
            while (setIter.hasNext()) {
                System.out.printf("Element %d = %d\n", i, setIter.next());
                i++;
            }
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("MAP AND MAP ITERATOR TESTS");
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("insert,erase,clear,begin,end,empty,max_size, count, find, intersection, hasNext, next, hasPrev, prev");
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("After inserting (elma=78), (armut=69), (kivi=69), (muz=87)");
            map1.insert(new Pair<String,Integer>("elma",78));
            map1.insert(new Pair<String,Integer>("armut",69));
            map1.insert(new Pair<String,Integer>("kivi",69));
            map1.insert(new Pair<String,Integer>("muz",87));
            mapIter = map1.begin();
            while (mapIter.hasNext())
                System.out.println(mapIter.next());

            System.out.println("find(kivi)---" + map1.find("kivi").next());
            if (!map1.empty())
                System.out.println("map1 is not empty");
            System.out.println("Size of map1 = " + map1.size());
            System.out.println("Maxsize of map1 = " + map1.max_size());
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("After erasing key armut from map1");
            map1.erase("armut");
            mapIter = map1.begin();
            while (mapIter.hasNext())
                System.out.println(mapIter.next());

            System.out.printf("Count of element (muz=87) in map1 = %d\n", map1.count(new Pair<String,Integer>("muz",87)));
            System.out.printf("Count of element (kamil=88) in map1 = %d\n", map1.count(new Pair<String,Integer>("kamil",88)));
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("MAP Reverse Iterator TEST");
            mapIter = map1.end();
            while(mapIter.hasPrevious())
                System.out.println(mapIter.previous());
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("After clearing all elements of map1");
            map1.clear();
            mapIter = map1.begin();

            while (mapIter.hasNext()) 
                System.out.println(mapIter.next());

            System.out.println("Size of set1 = " + map1.size());
            if (map1.empty())
                System.out.println("map1 is empty\n");

            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("MAP Intesection Test");
            System.out.println("------------------------------------------------------------------------------------");
            map1.insert(new Pair<String,Integer>("efkan",568));
            map1.insert(new Pair<String,Integer>("kamil",321));
            map1.insert(new Pair<String,Integer>("ahmet",654));
            map1.insert(new Pair<String,Integer>("zeynep",987));
            map2.insert(new Pair<String,Integer>("mustafa",729));
            map2.insert(new Pair<String,Integer>("kubra",785));
            map2.insert(new Pair<String,Integer>("efkan",568));
            map2.insert(new Pair<String,Integer>("kamil",321));

            map3 = (GTUMap)map1.intersection(map2);

            System.out.println("Elements of map1:");
            mapIter = map1.begin();

            while (mapIter.hasNext()) 
                System.out.println(mapIter.next());


            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("Elements of map2:");
            mapIter = map2.begin();

            while (mapIter.hasNext()) 
                System.out.println(mapIter.next());

            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("Elements of intersection of map1 and map2:");
            mapIter = map3.begin();
            while (mapIter.hasNext())
                System.out.println(mapIter.next());
            
            System.out.println("------------------------------------------------------------------------------------");
            System.out.println("EXEPTION TEST");
            map1.insert(new Pair<String,Integer>("efkan",5));
        }
        catch (InvalidParameterException exc) {
            System.out.println(exc.getMessage());
        }
        
    }
}
