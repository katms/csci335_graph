//Katherine Sullivan
//CSCI 335 Graph Assignment

//modifications from last project: removed hash table, remove, find, increaseKey, decreaseKey, items now percolate until < instead of <=
//I don't need any of them this time and it was either this or figure out how to hash Edge<T>

#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector> //std::vector
//#include <functional> //std::function
//#include "HashTable.h"

template <class T>
class BinaryHeap
{
    public:
        //constructor
        explicit BinaryHeap(int capacity = 10);
                
        //returns the number of items in the heap
        unsigned size() const;
        
        //returns true if the heap is empty
        bool empty() const;
        
        //inserts item into heap
        //ignores to duplicates to prevent issues with the hash table
        void insert(const T& item);
        
        //bool contains(const T& item) const;
        
        //removes minimum item in the heap and returns it
        T delete_min();
        
        //if item is found, decreases key by change and percolates up
        //void decreaseKey(const T& item, const int change); //uses T-=(int)
        
        //if item is found, increases key by change and percolates down
        //void increaseKey(const T& item, const int change);  //uses T+=(int)
        
        //removes item from heap (if found)
        //void remove(const T& item);
        
        //clears heap
        void clear();
        
        //calls T-=(change) on every item in the heap without percolating
        //void decrease_all(const int change);
        
        //typedef std::function<bool(const T&)> Test;
        
        //searches heap starting from a random index until it finds an item that returns true for test(item)
        //if the entire heap is searched without finding anything, returns nullptr
        //T* get_random(Test& test);
        
    private:
        //MEMBER VARIABLES
        
        int current_size; //signed int that tracks array.size()
        std::vector<T> array; //holds items
        //HashTable<T, int> table; //tracks the index of every item in the heap
        
        
        //PERCOLATE FUNCTIONS
        //index percolates as far up or down as possible (past equivalent items)
        
        void percolateUp(int index);
        
        void percolateDown(int index);

        
        //INDEXING FUNCTIONS
        //if index not found returns -1
        
        //int index_of(const T& item) const;
        
        int parent_of(const int child_index) const;
        int left_child(int parent) const;
        int right_child(int parent) const;
        
        int smaller_child(int parent) const;
};

#endif // BINARYHEAP_H
