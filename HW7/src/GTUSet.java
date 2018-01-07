
import java.lang.reflect.Array;
import static javafx.scene.input.KeyCode.T;
import java.security.InvalidParameterException;


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Efkan Duraklı
 * @version 1.0
 * @since 2017-12-25
 */

public class GTUSet<T> implements GTUSetInt<T> {
    
    protected int size;
    protected int capacity;
    private T[] data;
    protected final int MAXSIZE = 1000;
    
    /**
     * no parameter constructor
     * initialize capacity to 10
     */
    public GTUSet() {
        
        size = 0;
        capacity = 10;
        data = (T[]) new Object[capacity];
    }
    
   
    
    /**
     * get data to index
     * @param index
     * @return 
     */
    public T getVal(int index) {
        return data[index];
    }
    
    /**
     * set dat to index
     * @param element
     * @param index 
     */
    protected void setVal(T element, int index) {
        data[index] = element;
    }
    
    /**
     * inner class to iterate container
     */
    public class GTUIterator {
        
        private int currentIndex;
        
        /**
         * no parameter constructor
         */
        public GTUIterator() {
            currentIndex = -1;
        }
        
        /**
         * one parameter constructor
         * @param index 
         */
        public GTUIterator(int index) {
            currentIndex = index;
        }
        /**
         * returns true if this list iterator has more elements when traversing the list in the forward direction.
         * @return 
         */
        public boolean hasNext() {
            if (currentIndex >= size)
                return false;
            
            return true;
        }
        
        /**
         * returns true if this list iterator has more elements when traversing the list in the reverse direction.
         * @return 
         */
        public boolean hasPrevious() {
            if (currentIndex <= 0)
                return false;
            
            return true;
        }
        
        /**
         * returns the next element in the list and advances the cursor position.
         * @return 
         */
        public T next() {
            T temp;
            temp = data[currentIndex]; 
            currentIndex++;
            return temp;
         
        }
        /**
         * returns the previous element in the list and moves the cursor position backwards.
         * @return 
         */
        public T previous() {
            T temp;
            temp = data[currentIndex-1];
            currentIndex--;
            return temp;
        }
    }
    
    /**
     * test whether container is empty
     * if container is empty return true,if is not return false
     * @return 
     */
    @Override
    public boolean empty() {
        
        if (size == 0)
            return true;
        
        return false;
        
    }
    
    /**
     * return size of container
     * @return 
     */
    @Override
    public int size() {
    
        return size;
    }

    /**
     * Insert element
     * throws exception InvalidParameterException if the element is already in the container
     * @param element 
     */
    @Override
    public void insert(T element) {
        
        if (MAXSIZE > size) {
            if (this.search(element))
                throw new InvalidParameterException(element + " is exist");
            if (size >= capacity)
                resize();
            data[size] = element;
            size++;
        }
    }
    
    /**
     * return maxsize of container
     * @return 
     */
    @Override
    public int max_size() {
        return MAXSIZE;
    }
    
    /**
     * deletes elemet from container
     * @param element
     * @return 
     */
    @Override
    public boolean erase(Object element) {

            for (int i = 0; i < size; i++) {
                if (data[i] == element) {
                    for (int j = i; j < size-1; j++)
                        data[j] = data[j+1];
                    size--;
                    return true;
                }
            }
        return false;
     }
    
    /**
     * resize container 2*capacity
     */
    protected void resize() {
        T temp[] = (T[]) new Object[capacity];
        for(int i = 0; i < size; i++)
           temp[i] = data[i];
        capacity *= 2;
        data = null;
        data = (T[]) new Object[capacity];
        for (int i = 0; i < size; i++)
        data[i] = temp[i];
    }
    
    /**
     * clear all content of container
     */
    @Override
    public void clear() {
        
        data = null;
        size = 0;
        capacity = 10;
        data = (T[]) new Object[capacity];
        
    }

    /**
     * get iterator to element
     * if element is not exist in container, return iterator to end
     * @param element
     * @return 
     */
    @Override
    public GTUIterator find(Object element) {
        
        int i;
        for (i = 0; i < size; i++) {
            if (data[i] == element)
                return new GTUIterator(i);
        }
        return new GTUIterator(size);
    }

    /**
     * count of element in container
     * @param element
     * @return 
     */
    @Override
    public int count(T element) {
        
        for (int i = 0; i < size; i++) {
            if (data[i].equals(element))
                return 1;
        }
        return 0;
    }

    /**
     * return iterator to beginnig of container
     * @return 
     */
    @Override
    public GTUIterator begin() {
        return new GTUIterator(0);
    }
    
    /**
     * return iterator to end of container
     * @return 
     */
    @Override
    public GTUIterator end() {
        
        return new GTUIterator(size);
    }
    
    /**
     * search element in caontainer
     * if element is exist,return true, if not return false
     * @param element
     * @return 
     */
    private boolean search(T element) {
        
        for (int i = 0; i < size; i++) {
            if (data[i].equals(element))
                return true;
        }
        return false;
    }
    
    /**
     * get intersection container of this and other
     * @param index
     * @return 
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other) {
        
        GTUSet<T> temp = new GTUSet<T>();
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < other.size(); j++)
                if (data[i].equals(other.getVal(j))) 
                    temp.insert(data[i]);
        }
        return temp;
    }
}
