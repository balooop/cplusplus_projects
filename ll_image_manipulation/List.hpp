/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
    length_ = 0;

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  //curr points to head
  if(length_ == 0)
    return;
  ListNode * curr = head_;
  //tmp listnode
  ListNode * tmp;
  //loops while the next element isnt NULL
  while(curr->next != NULL)
  {
    //tmp is the item after curr->next
    tmp = curr->next->next;
    //delete curr->next
    delete curr->next;
    //curr's next points to the item after the one deleted
    curr->next = tmp; 
  }
  //delets the first element
  delete head_;
  head_ = NULL;
  tail_ = NULL;

}
/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
    return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> prev = NULL;
  
  //inserting into an nonempty list
  if(length_ != 0)
  {
     //newNode is being placed before head, so its next pointer is the current head
    newNode->next = head_;
    //current head's previous pointer is the new head
    head_->prev = newNode;
    //assigns head to the newNode, since it's at the front
    head_ = newNode;
  }
  else
  {
    //newNode is both the head and tail
    head_ = newNode;
    tail_ = newNode;
    //there are no other items, so it points to NULL
    newNode->next = NULL;
  }
  
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  
  //tail always points to NULL
  ListNode * newTail = new ListNode(ndata);
  newTail->next = NULL;

  if(this->length_ != 0)
  {
    //previous tail will now point forward to the new node
    tail_->next = newTail;
    //the new tail points backward to the old tail
    newTail->prev = tail_;
    //tail_ is now th new node
    tail_ = newTail;
   
  }
  else
  {
    //head and tail point to the new node in an empty list
    head_ = newTail;
    tail_ = newTail;
    newTail->prev = NULL;
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  //creates a list node to iterate through the list
  ListNode* newFront = start;

  //makes sure start isn't null
  if(start == NULL)
    return NULL;
  //making sure we're making a valid split
  if(splitPoint == 0 || splitPoint >= length_)
    return start;

  //progresses the split list front node through the list until it reaches the split point
  for(int i = 0; i < splitPoint; i++)
  {
    newFront = newFront->next;
  }
  
  //detaches the list by disconnecting prev node from current node (in forward direction)
  newFront->prev->next = NULL;
  //detaches the list by disconnecting current node from prev node (in backward direction)
  newFront->prev = NULL;

  return newFront;

}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  if(length_ < 1)
    return;

  //creates two cursors 
  ListNode* cursor = head_->next;
  ListNode* prevCursor = head_;
  while(cursor->next != NULL && tail_ != NULL)
  {
      //remove node
      cursor->prev->next = cursor->next; //sets prev node to point forward to the next node
      cursor->next->prev = cursor->prev; //sets next node to point backward to the prev node

      //put node at back
      cursor->prev = tail_;             //node points backwards to old tail
      cursor->next = NULL;

      //adjust tail
      tail_->next = cursor;              //tail points forward to node
      tail_ = cursor;                   //node is now tail

      //increment
      cursor = prevCursor->next->next;  //skip one but move forward
      prevCursor = cursor->prev;        //adjust prevCursor
  }


  
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  
  //nodes for fixing start and end
  ListNode * farLeft = startPoint->prev;
  ListNode * farRight = endPoint->next;
  ListNode * endOrigPrev = endPoint->prev;
  ListNode * startOrigNext = startPoint->next;
  //i can't believe this is why my reverse Nth was failing 
  ListNode * origStart = startPoint;
  ListNode * origEnd = endPoint;
  
  ListNode * cursor = startPoint->next;
  //does reversing 
  while(cursor != endPoint)
  {
    //temp nodes used to adjust pointers
    ListNode * tempPrev = cursor->prev;
    ListNode * tempNext = cursor->next;

    //swap next and prev pointer
    cursor->next = tempPrev;
    cursor->prev = tempNext;

    //move through list
    cursor = tempNext;

  }    

  //fix startpoint
  startPoint->next = farRight;      //startpoints next will be pointing to farLeft, so we make it point to farRight (where it should)
  startPoint->prev = startOrigNext; //startpoint prev should point to what was originall y left

  //fix endpoint
  endPoint->next = endOrigPrev;     //swap next cursor as in loop
  endPoint->prev = farLeft;         //prev cursor should point one before orig start
  
  //fix head and tail if it starts at head or ends at tail
  //if farLeft is null, the endpoint is the head (b/c original head has been swapped with node @ endpoint), else, farLeft points to endPoint (since endpoint is now right after it)
  (farLeft == NULL) ?  head_ = endPoint : (farLeft->next = endPoint);
  //if farRight is null, the start is the tail (b/c original tail has been swapped with node @ startpoint), else farRight points backward to startPoint (since )
  (farRight == NULL) ?  tail_ = startPoint : (farRight->prev = startPoint);

  //need to flip start and end points for reverseNth, as they are incremented in the loop
  startPoint = origEnd;
  endPoint = origStart;
  //^^^^ a b s o l u t e nightmare to find this bug holey crappe
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  //needs to be a list to reverse
  if(n<0 || n == size() || size() == 0)
    return;

  //start ptr, end ptr
  ListNode * start = this->head_;
  ListNode * end = this->head_;
  
  while(start != NULL && start->next != NULL)
  {
    for(int i = 0; i < n - 1; i++)
    { 
      //guard for block smaller than remainder of list
      if(end->next) 
        end = end->next;
      else
        break;
    }
    
    //reverses portion of size N
    reverse(start, end);

    //updates start and end
    end = end->next;
    start = end;
  }

}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  
  //handles corner cases
  if(first == NULL)
    return second;
  if(second == NULL)
    return first;
  if(first == NULL && second == NULL)
    return NULL;

  //new head of merged list, and cursor to iterate through, and p/q pointers to iterate through first and second lists
  List<T>::ListNode * newHead;
  List<T>::ListNode * cursor;
  List<T>::ListNode * p = first;
  List<T>::ListNode * q = second;
  
  //sets first node of sorted list
  if(p->data < q->data)
  {
    //new sorted head is first --> used for returning
    newHead = p;
    //cursor points at new head --> used for iterating through lists
    cursor = p;
    //p is after new head, progresses through list
    p = cursor->next;
  }
  else
  {
    //new sorted head is second --> used for returning
    newHead = q;
    //cursor points at new head --> used for iterating through list
    cursor = q;
    //q is after new head, progresses through list
    q = cursor->next;
  }
  
  
  while(p != NULL && q != NULL)
  {
    //if current seconds list pointer < current first list pointer
    if(q->data < p->data)
    {
      //cursor should point to q, since it is smaller
      cursor->next = q;   
      //q prev pointer changes
      q->prev = cursor;
      //move cursor along
      cursor = q;
      //move q along
      q = cursor->next;
    }
    //else current second list pointer > current first list pointer
    else
    {
      //cursor should point to p, since it is smaller
      cursor->next = p;
      //p prev pointer changes
      p->prev = cursor;
      //move cursor along
      cursor = p;
      //move p along
      p = cursor->next;
    }
  }
  //handles case where first is longer than second
  if(p != NULL && q == NULL)
  {
    cursor->next = p;
    p->prev = cursor;
  }
  //handles case where second is longer than first
  if(q != NULL && p == NULL)
  {
    cursor->next = q;
    q->prev = cursor;
  }

  return newHead;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e.,s this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  //base case
  if(chainLength == 1)
    return start;
  //recursive case
  else
  {
    //sets first and second bounds
    int firstBound, secondBound;
    firstBound = chainLength/2;
    secondBound = chainLength - firstBound;

    ListNode * secondStart = split(start, firstBound);
    ListNode * firstSorted = mergesort(start, firstBound);
    ListNode * secondSorted = mergesort(secondStart, secondBound);
    ListNode * merged = merge(firstSorted, secondSorted);
    return merged;
  }
  
  return NULL;
}
