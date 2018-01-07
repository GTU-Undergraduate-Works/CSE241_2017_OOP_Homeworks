/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Efkan Duraklı
 */

import javafx.util.Pair;
import java.security.InvalidParameterException;

public class GTUMap<K,V> extends GTUSet<Pair<K,V> >{
    
    /**
     * no parameter constructor
     * initialize capacity to 10
     */
    public GTUMap() {
        super();
    }
    
    /**
     * Insert element
     * throws exception InvalidParameterException if the key of element is already in the container
     * @param element 
     */
    @Override
    public void insert(Pair<K,V> element) {
        
        if (MAXSIZE > size) {
            if (this.search(element.getKey()))
                throw new InvalidParameterException(element.getKey() + " is exist");
            if (size >= capacity)
                resize();
            setVal(element, size);
            size++;
        }
    }
    
    /**
     * if k matches the key of an element in the set, the method returns a reference to its mapped value,
     * if not return null.
     * @param k
     * @return 
     */
    public V at(K k) {
        
        for (int i = 0; i < size; i++) {
            if (getVal(i).getKey() == k)
                return getVal(i).getValue();
        }
        return null;
    }
    
    /**
     * search key in caontainer
     * if key is exist,return true, if not return false
     * @param key
     * @return 
     */
    private boolean search(K key) {
        
        for (int i = 0; i < size; i++) {
            if (getVal(i).getKey() == key)
                return true;
        }
        return false;
    }
    
    /**
     * get intersection container of this and other
     * @param other
     * @return 
     */
    @Override
   public GTUSetInt<Pair<K,V> > intersection(GTUSetInt<Pair<K,V> > other) {
        
        GTUMap<K, V> temp = new GTUMap<K,V>();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < other.size(); j++)
                if (getVal(i).equals(other.getVal(j)))
                    temp.insert(other.getVal(j));
        }
        return temp;
        
    }
    /**
     * deletes key from cantainer, if key is exist
     * @param key
     * @return 
     */
   @Override
    public boolean erase(Object key) {
        
        for (int i = 0; i < size; i++) {
            if (getVal(i).getKey() == key) {
                for (int j = i; j < size-1; j++)
                    setVal(getVal(j+1), j);
                size--;
                return true;
            }
        }
        return false;
    }
    /**
     * if element is not exist in container, return iterator to end
     * @param element
     * @return 
     */
    @Override
    public GTUIterator find(Object element) {
        int i;
        for (i = 0; i < size; i++) {
            if (getVal(i).getKey().equals(element))
                return new GTUIterator(i);
        }
        return new GTUIterator(size);
    }
}


