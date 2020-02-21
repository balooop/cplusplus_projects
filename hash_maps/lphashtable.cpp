/**
 * @file lphashtable.cpp
 * Implementation of the LPHashTable class.
 */
#include "lphashtable.h"

template <class K, class V>
LPHashTable<K, V>::LPHashTable(size_t tsize)
{
    if (tsize <= 0)
        tsize = 17;
    size = findPrime(tsize);
    table = new std::pair<K, V>*[size];
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

        table = new std::pair<K, V>*[rhs.size];
        should_probe = new bool[rhs.size];
        for (size_t i = 0; i < rhs.size; i++) {
            should_probe[i] = rhs.should_probe[i];
            if (rhs.table[i] == NULL)
                table[i] = NULL;
            else
                table[i] = new std::pair<K, V>(*(rhs.table[i]));
        }
        size = rhs.size;
        elems = rhs.elems;
    }
    return *this;
}

template <class K, class V>
LPHashTable<K, V>::LPHashTable(LPHashTable<K, V> const& other)
{
    table = new std::pair<K, V>*[other.size];
    should_probe = new bool[other.size];
    for (size_t i = 0; i < other.size; i++) {
        should_probe[i] = other.should_probe[i];
        if (other.table[i] == NULL)
            table[i] = NULL;
        else
            table[i] = new std::pair<K, V>(*(other.table[i]));
    }
    size = other.size;
    elems = other.elems;
}

template <class K, class V>
void LPHashTable<K, V>::insert(K const& key, V const& value)
{

    /**
     * @todo Implement this function.
     *
     * @note Remember to resize the table when necessary (load factor >= 0.7).
     * **Do this check *after* increasing elems (but before inserting)!!**
     * Also, don't forget to mark the cell for probing with should_probe!
     */
    
    //increments elems
    ++elems;

    //checks resizing things
    if(shouldResize())  resizeTable();

    //gets hash_idx
    size_t hash_idx = hashes::hash(key, size);
    //keep probing while we should probe
    while(should_probe[hash_idx] == true)    hash_idx = (hash_idx+1) % this->size;
    
    //creates new pair
    std::pair<K,V> * insert_pair = new std::pair<K,V>(key, value);
    //inserts new pair into table
    table[hash_idx] = insert_pair;
    //marks spot as filled
    should_probe[hash_idx] = true;


}

template <class K, class V>
void LPHashTable<K, V>::remove(K const& key)
{
    /**
     * @todo: implement this function
     */
    //chekcks that key is in hash table
    int idx = findIndex(key);
    if(idx == -1) return;
    //deletes from table
    delete table[idx];
    table[idx] = NULL;
    //should probe is now false b/c the slot is empty
    should_probe[idx] = false;
    //decrements elements
    --elems;

}

template <class K, class V>
int LPHashTable<K, V>::findIndex(const K& key) const
{

    /**
     * @todo Implement this function
     *
     * Be careful in determining when the key is not in the table!
     */
    //gets hash index
    unsigned hash_idx = hashes::hash(key, size);
    unsigned start_idx = hash_idx;
    
    //loop while elements exist in the table
    while(should_probe[hash_idx])
    {
        //if there is an element in the table and that element has the key we are searching for, we return hash index
        if(table[hash_idx] != NULL && table[hash_idx]->first == key)  return hash_idx;
        //increments index
        hash_idx = (hash_idx + 1) % this->size;
        //don't want to infinitely loop table
        if(hash_idx == start_idx)   break;
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
    table = new std::pair<K, V>*[17];
    should_probe = new bool[17];
    for (size_t i = 0; i < 17; i++)
        should_probe[i] = false;
    size = 17;
    elems = 0;
}

template <class K, class V>
void LPHashTable<K, V>::resizeTable()
{

    /**
     * @todo Implement this function
     *
     * The size of the table should be the closest prime to size * 2.
     *
     * @hint Use findPrime()!
     */
    //calculates new size and reassigns it
    size_t new_size = findPrime(size * 2);
    size_t old_size = size;
    size = new_size;

    //creates new hash table
    std::pair<K, V>** new_table = new std::pair<K,V>*[size];
    delete[] should_probe;
    should_probe = new bool[size];

    for(int j = 0; j < 2; j++){
        switch(j)
        {
            //first time: 
            case 0:
                //initializes new table with NULL and should probe with false
                for(size_t i = 0; i < size; i++)
                {
                    new_table[i] = NULL;
                    should_probe[i] = false;
                }
                break;
            //second time:
            case 1:
                //loops through old table
                for(size_t i = 0; i < old_size; i++)
                {
                    if(table[i] != NULL)
                    {
                        //gets key
                        K cur_key = table[i]->first;
                        //calculates new hash
                        unsigned new_hash_idx = hashes::hash(cur_key, size);
                        //probe for open spot in new table
                        while(should_probe[new_hash_idx])    new_hash_idx = (new_hash_idx + 1) % size;
                        //inserts into new table
                        new_table[new_hash_idx] = table[i];
                        should_probe[new_hash_idx] = true;
                    }
                }
                break;
        }
    }
    //reassigns 
    delete[] table;
    table = new_table;
}
