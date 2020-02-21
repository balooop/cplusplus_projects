
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cmath>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    //one indexed heap
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    //in one indexed heap, left child index = i*2
    return currentIdx * 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    //in one indexed heap, right child index = i*2 + 1
    return currentIdx * 2 + 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    //in one indexed heap, parent = floor (i/2)
    return std::floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    //if a node has a child, there will be an element at 2 * its index, since heaps are complete trees
    return ((currentIdx * 2) < _elems.size());
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    //gets left and right index
    size_t left = leftChild(currentIdx);
    size_t right = rightChild(currentIdx);
    //makes sure right child exists
    if(_elems.size() <= right)  return left;
    //compares left and right children using higher priority, returns the lower valued child
    return (higherPriority(_elems[left], _elems[right])) ? left : right;

}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    //makes sure we aren't at a leaf
    if(hasAChild(currentIdx))
    {
        //gets index of highest priority child
        unsigned childIdx = maxPriorityChild(currentIdx);
        //if the child index has a higher priority than the current one
        if(higherPriority(_elems[childIdx], _elems[currentIdx]))
        {
            //we swap them
            std::swap(_elems[currentIdx], _elems[childIdx]);
            //and heapify from the child
            heapifyDown(childIdx);
        }
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    //elems[0] is nothing
    _elems.push_back(T());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    //pushes back to 0th index
    _elems.push_back(T());
    
    //pushes all elems to _elems
    for(auto e : elems) _elems.push_back(e);

    //heapifies
    unsigned parentIdx = parent(_elems.size() - 1);
    for(unsigned i = parentIdx; i > 0; i--)
    {
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    //swap with last value
    T minValue = _elems[1];
    std::swap(_elems[1], _elems[(_elems.size() - 1)]);
    _elems.pop_back();

    //restore heap
    heapifyDown(1);

    //returns min value
    return minValue;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    
    //makes sure element is within size
    if(idx > _elems.size())   push(elem);
    
    //puts elem in array
    _elems[idx] = elem;
    T parentElem = _elems[parent(idx)];
    if (higherPriority(elem, parentElem))           heapifyUp(idx);
    else                                            heapifyDown(idx);

}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    return (1 == _elems.size());
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
