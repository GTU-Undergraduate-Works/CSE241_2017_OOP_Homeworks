/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Efkan Duraklı
 */

import java.lang;
import java.security.InvalidParameterException;
import GTUSet.GTUIterator;
        
public interface GTUSetInt<T> {
    
    /**
     * test whether container is empty
     * if container is empty return true,if is not return false
     * @return boolean
     */
    public boolean empty();
    
    /**
     * return size of container
     * @return size of container
     */
    public int size();
    
    /**
     * Insert element
     * throws exception InvalidParameterException if the element is already in the container
     * @param element 
     */
    public void insert(T element);
    
    /**
     * return maxsize of container
     * @return maxsize of container
     */
    public int max_size();
    
    /**
     * deletes elemet from container
     * @param element
     * @return boolean
     */
    public boolean erase(Object element);
    
    /**
     * clear all content of container
     */
    public void clear();
    
    /**
     * get iterator to element
     * if element is not exist in container, return iterator to end
     * @param element
     * @return GTUUterator to element
     */
    public GTUIterator find(Object element);
    
    /**
     * count of element in container
     * @param element
     * @return cont of element in container
     */
    public int count(T element);
    
    /**
     * return iterator to beginnig of container
     * @return GTUIterator to first element
     */
    public GTUIterator begin();
    
    /**
     * return iterator to end of container
     * @return GTUIterator to end of container
     */
    public GTUIterator end();
    
    /**
     * get intersection container of this and other
     * @param index
     * @return 
     */
    public GTUSetInt<T> intersection(GTUSetInt<T> other);
    
    
    /**
     * get data to index
     * @param index
     * @return 
     */
    public T getVal(int index);
    
    
}
