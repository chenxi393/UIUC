/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Summer 2012
 * @modified by Dustin, 2018
 */
#include "lphashtable.h"

using hashes::hash;
using std::pair;

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new pair<K, V>*[size];
    should_probe = new bool[size];
    for (size_t i = 0; i < size; i++) {
        table[i] = NULL;
        should_probe[i] = false;
    }
    elems = 0;
}

template <class K, class V>
LPHashTable<K, V>::~LPHashTable()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
}

template <class K, class V>
LPHashTable<K, V> const& LPHashTable<K, V>::operator=(LPHashTable const& rhs)
{
    if (this != &rhs) {
        for (size_t i = 0; i < size; i++)
            delete table[i];
        delete[] table;
        delete[] should_probe;

        table = new pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{
    int vv=findIndex(key);
    if(vv!=-1){
        //std::cout<<key<<"    "<<vv<<"   "<<value<<std::endl;
        if(table[vv]->second<value)
            table[vv]->second=value;
        return;
        //problem2
    }
    ++elems;
    if (shouldResize())
        resizeTable();
    size_t idx = hash(key, size);
    int i=1;
    int flag=1;
    size_t temp=idx;
    while(table[idx]) {
        idx = (temp + i*i*flag) % size;
        if(flag==-1){
            i++;
        }
        flag*=-1;
    }
    
    should_probe[idx] = true;   
    table[idx] = new pair<K, V>(key, value);

}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    int idx = findIndex(key);
    if (idx != -1) {
        delete table[idx];
        table[idx] = NULL;
        --elems;
    }
}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{
    size_t idx = hash(key, size);
    size_t start = idx;
    int i=1;
    int flag=1;
    size_t temp=idx;
    while (should_probe[idx]) {
        if (table[idx] != NULL && table[idx]->first == key)
            return idx;
        idx = (temp + i*i*flag) % size;
        if(flag==-1){
            i++;
        }
        flag*=-1;
        // if we've looped all the way around, the key has not been found
        if (idx == start)
            break;
    }
    return -1;
}

template <class K, class V>
V LPHashTable<K, V>::find(K const& key) const
{
    int idx = findIndex(key);
    if (idx != -1)
        return table[idx]->second;
    return V();
}

template <class K, class V>
V& LPHashTable<K, V>::operator[](K const& key)
{
    // First, attempt to find the key and return its value by reference
    int idx = findIndex(key);
    if (idx == -1) {
        // otherwise, insert the default value and return it
        insert(key, V());
        idx = findIndex(key);
    }
    return table[idx]->second;
}

template <class K, class V>
bool LPHashTable<K, V>::keyExists(K const& key) const
{
    return findIndex(key) != -1;
}

template <class K, class V>
void LPHashTable<K, V>::clear()
{
    for (size_t i = 0; i < size; i++)
        delete table[i];
    delete[] table;
    delete[] should_probe;
    table = new pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{
    size_t newSize = findPrime(size * 2);
    pair<K, V>** temp = new pair<K, V>*[newSize];
    delete[] should_probe;
    should_probe = new bool[newSize];
    for (size_t i = 0; i < newSize; i++) {
        temp[i] = NULL;
        should_probe[i] = false;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (table[i] != NULL) {
            size_t idx = hash(table[i]->first, newSize);
            int k=1;//i重名了刚刚 找了半天
            int flag=1;
            size_t temp1=idx;
            while (temp[idx] != NULL){
                idx = (temp1 + k*k*flag) % newSize;
                if(flag==-1){
                  k++;
                }
                flag*=-1;
            }
            temp[idx] = table[i];
            should_probe[idx] = true;
        }
    }
    delete[] table;
    // don't delete elements since we just moved their pointers around
    table = temp;
    size = newSize;
}