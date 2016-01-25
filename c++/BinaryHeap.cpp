//Katherine Sullivan
//CSCI 335 Graph Assignment
//modified from Hash Assignment

#include "BinaryHeap.h"

//constructor
template <class T>
BinaryHeap<T>::BinaryHeap(int capacity):
    current_size(0)//, table(T{}, -1, 2*capacity)
{
    if(capacity<=0) capacity=10; //make sure capacity is positive
    array.reserve(capacity);
}

//returns the number of items in the heap
template<class T>
unsigned BinaryHeap<T>::size() const
{
    return array.size();
}

//returns true if heap is empty
template<class T>
bool BinaryHeap<T>::empty() const
{
    return array.empty();
}

//inserts item into heap
template <class T>
void BinaryHeap<T>::insert(const T& item)
{
    /*if(table.contains(item)) //duplicate, do nothing
    {
        return;
    }*/
    
    ++current_size;
    
    //add item to the end of array (the newest heap)
    array.push_back(item);
    
    //update table
    //table.insert(item, current_size-1);
    //the heap allows duplicate items but the table does not, so hopefully this situation will never come up
        
    //find item's real place in the heap
    percolateUp(array.size()-1);
}
/*
template<class T>
bool BinaryHeap<T>::contains(const T& item) const
{
    return table.contains(item);
}*/

//removes minimum from heap and returns it
template <class T>
T BinaryHeap<T>::delete_min()
{
    if(array.empty())
    {
        throw "Called delete_min() on empty heap";
    }
    
    //get/remove minimum
    T minimum = std::move(array[0]);
    
    //update table
    //table.remove(minimum);
    
    //check if any additional work needs to be done
    if(array.size()==1) //min is the last item, just clear array
    {
        clear();
        return minimum;
    }
    
    //place last item in the heap in hole left by minimum
    array[0] = std::move(array.back());
    //table.set_value(array[0], 0);
    array.pop_back();
    --current_size;
    
    //the last item is unlikely to belong at index 0
    percolateDown(0);

    return minimum;
}

/*
template <class T>
void BinaryHeap<T>::decreaseKey(const T& item, const int change)
{
    int index=index_of(item); //find item
    if(index<0)
    {
        return;
    }
    else
    {
        array[index]-=change; //decrease key
        percolateUp(index); //update
    }
}

template <class T>
void BinaryHeap<T>::increaseKey(const T& item, const int change)
{
    int index=index_of(item); //find item
    if(index<0)
    {
        return;
    }
    else
    {
        array[index]+=change; //increase key
        percolateDown(index); //update
    }
}

//remove item by percolating it up to the top and calling delete_min()
template <class T>
void BinaryHeap<T>::remove(const T& item)
{
    int index=index_of(item);
    if(index<0) //item not in heap
    {
        return;
    }
    else if(0==index) //item is already min, no need to decreaseKey
    {
        delete_min();
    }
    else
    {
        int decrement = static_cast<int>(array[index]) - static_cast<int>(array[0]); 
        //the decrement needed so that item is equivalent to min
        
        //since items percolate as far up or down as possible (while <=) item becomes the new min
        decreaseKey(item, decrement);
        
        
        OR:
        while(array[0] < array[index])
            decreaseKey(array[index], some number, 1 would do but could go higher)
    
        
        delete_min();
    }
}*/

//make heap empty
template <class T>
void BinaryHeap<T>::clear()
{
    //table.clear(); //update table
    array.clear();
    current_size=0;
}
/*
//shortcut to call T-=(change) on every item in the heap
//since every item decreases by the same constant amount, no need to re-arrange the heap after calling it on each item
template <class T>
void BinaryHeap<T>::decrease_all(const int change)
{
    for(unsigned i=0; i<array.size(); ++i)
    {
        array[i]-=change;
    }
}*/
/*
//returns a randomly selected object in the heap that satisfies test
//returns nullptr if no qualifying item
template <class T>
T* BinaryHeap<T>::get_random(Test& test)
{
    if(array.empty())
    {
        return nullptr;
    }
    int searched=0, i=rand()%current_size; //start from a random index
    while(searched<current_size) //check every item
    {
        ++searched;
        if(test(array[i]))
        {
            return &(array[i]);
        }
        
        ++i;
        if(current_size==i) //wrap around
        {
            i=0;
        }
    }
    //no qualified item found
    return nullptr;
}
*/

//PERCOLATING

//repeatedly swap array[hole] with its parent as long as parent > array[hole]
//if item are equivalent, keeps going
template <class T>
void BinaryHeap<T>::percolateUp(int hole) //assume hole is valid index
{
    for(int parent=parent_of(hole); parent>-1 && array[hole] < array[parent]; hole=parent, parent=parent_of(parent))
    {
        std::swap(array[parent], array[hole]);
        //table.set_value(array[parent], parent);
        //table.set_value(array[hole], hole);
    }
}

//repeatedly swap array[hole] with its smaller child as long as array[hole] is larger
//if item are equivalent, keeps going
template <class T>
void BinaryHeap<T>::percolateDown(int hole) //assume hole is valid index
{
    for(int child=smaller_child(hole); child>-1 && array[child] < array[hole]; hole=child, child=smaller_child(child))
    {
        std::swap(array[hole], array[child]);
        //table.set_value(array[child], child);
        //table.set_value(array[hole], hole);

    }
}

//INDEXING FUNCTIONS
//in each case, returns -1 if not found

//returns the parent of child_index
//if child_index is the root or not in the heap, returns -1
//if it's a left child, parent=(i-1)/2
//else parent=(i-2)/2
template <class T>
int BinaryHeap<T>::parent_of(const int child_index) const
{
    if(child_index>0 && child_index<current_size)
    {
        int result;
        if(0==child_index%2)//right child
        {
            result=child_index-2;
        }
        
        else //left child
        {
            result=child_index-1;
        }
        return result/2;
    }
    else return -1;
}

//left child of p = 2*p+1
template <class T>
int BinaryHeap<T>::left_child(int parent) const
{
    int result = 2*parent + 1;
    if(result<current_size)
    {
        return result;
    }
    else return -1;
}

//right child of p = 2*p+2
template <class T>
int BinaryHeap<T>::right_child(int parent) const
{
    int result=2*parent + 2;
    if(result<current_size)
    {
        return result;
    }
    else return -1;
}

//given parent returns the index of its smaller child
template <class T>
int BinaryHeap<T>::smaller_child(int parent) const
{
    int left = left_child(parent);
    int right = right_child(parent);
    if(right<0 || left<0) //1 or 0 children, do not access or compare items
    {
        return left; //left is either -1 or the only child
    }
    else return (array[left] < array[right]) ? left : right;
}
/*
//uses table to find the index of item
//returns default value (-1) if item is not in table, and therefore not in the heap
template <class T>
int BinaryHeap<T>::index_of(const T& item) const
{
    return table.get_value(item);
}*/
