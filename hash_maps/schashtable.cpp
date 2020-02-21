/**
 * @file schashtable.cpp
 * Implementation of the SCHashTable class.
 */

#include "schashtable.h"

template <class K, class V>
SCHashTable<K, V>::SCHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::list<std::pair<K, V>>[size];
    elems = 0;
}

template <class K, class V>
SCHashTable<K, V>::~SCHashTable()
{
    delete[] table;
}

template <class K, class V>
SCHashTable<K, V> const& SCHashTable<K, V>::
operator=(SCHashTable<K, V> const& rhs)
{
    if (this != &rhs) {
        delete[] table;
        table = new std::list<std::pair<K, V>>[rhs.size];
        for (size_t i = 0; i < rhs.size; i++)
            table[i] = rhs.table[i];
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
SCHashTable<K, V>::SCHashTable(SCHashTable<K, V> const& other)
{
    table = new std::list<std::pair<K, V>>[other.size];
    for (size_t i = 0; i < other.size; i++)
        table[i] = other.table[i];
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void SCHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     */
    //increment number of elements so we can see if we will have to resize
    ++elems;
    //resizes table 
    if (shouldResize())
        resizeTable();
    //calculates hash index to insert at
    unsigned idx = hashes::hash(key, size);
    //creates new pair to insert
    std::pair<K, V> p(key, value);
    //inserts pair
    table[idx].push_front(p);
}

template <class K, class V>
void SCHashTable<K, V>::remove(K const& key)
{
    typename std::list<std::pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the lab spec about list iterators and the
     * erase() function on std::list!
     */
    //finds key
    // V val = find(key);
    //gets hash index of key
    unsigned idx = hashes::hash(key, size);
    //checks empty
    if(table[idx].empty())      return;
    //loops through idx
    for (it = table[idx].begin(); it != table[idx].end(); it++)
    {
        if (it->first == key)
        {
            table[idx].erase(it);
            --elems;
            break;    
        }
    }
}

template <class K, class V>
V SCHashTable<K, V>::find(K const& key) const
{

    /**
     * @todo: Implement this function.
     */
    //calculates index key would be at
    unsigned idx = hashes::hash(key, size);
    //searches LL at index for key
    for (std::pair<K,V> p : table[idx])
    {
        //if we find the key, we return the value
        if(p.first == key)  return p.second;
    }
    //returns default if not found
    return V();
}

template <class K, class V>
V& SCHashTable<K, V>::operator[](K const& key)
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return it->second;
    }

    // was not found, insert a default-constructed version and return it
    ++elems;
    if (shouldResize())
        resizeTable();

    idx = hashes::hash(key, size);
    std::pair<K, V> p(key, V());
    table[idx].push_front(p);
    return table[idx].front().second;
}

template <class K, class V>
bool SCHashTable<K, V>::keyExists(K const& key) const
{
    size_t idx = hashes::hash(key, size);
    typename std::list<std::pair<K, V>>::iterator it;
    for (it = table[idx].begin(); it != table[idx].end(); it++) {
        if (it->first == key)
            return true;
    }
    return false;
}

template <class K, class V>
void SCHashTable<K, V>::clear()
{
    delete[] table;
    table = new std::list<std::pair<K, V>>[17];
    size = 17;
    elems = 0;
}

template <class K, class V>
void SCHashTable<K, V>::resizeTable()
{
    typename std::list<std::pair<K, V>>::iterator it;
    /**
     * @todo Implement this function.
     *
     * Please read the note in the spec about list iterators!
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    //finds prime nearest to 2*size 
    size_t new_size = findPrime(size*2);
    //gets old size
    size_t old_size = size;
    //sets size
    size = new_size;

    //allocates new table
    std::list<std::pair<K, V>>* new_table =  new std::list<std::pair<K, V>>[new_size];
    
    //loops through rows of old hash table
    for(unsigned i = 0; i < old_size; i++)
    {
        //loops through pairs of each row
        for(std::pair<K,V> p : table[i])
        {
            //inserts from old hash table into new
            unsigned new_hash_idx = hashes::hash(p.first, size);
            std::pair<K,V> ins_pair = std::pair<K,V>(p.first, p.second);
            new_table[new_hash_idx].push_front(p);
        }
    }
    //reassigns
    delete[] table;
    table = new_table;
}
