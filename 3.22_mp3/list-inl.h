/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  clear();
  /// @todo Graded in MP3.1
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  while(head_!= NULL){
      ListNode* temp = head_;
      head_ = head_->next;
      delete temp;
      temp = NULL;
    }
  head_ = NULL;
  tail_ = NULL;
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  if(head_ == NULL){
    ListNode* pointer = new ListNode(ndata);
    head_ = pointer;
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
  }
  else{
    ListNode* pointer = new ListNode(ndata);
    head_->prev = pointer;
    pointer->next = head_;
    pointer->prev = NULL;
    head_ = pointer;
  }
  length_ = length_ + 1;
  /// @todo Graded in MP3.1
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  if(head_ == NULL){
    ListNode* pointer = new ListNode(ndata);
    head_ = pointer;
    head_->next = NULL;
    head_->prev = NULL;
    tail_ = head_;
  }
  else{
    ListNode* pointer = new ListNode(ndata);
    tail_->next = pointer;
    pointer->next = NULL;
    pointer->prev = tail_;
    tail_ = pointer;
  }
  length_ = length_ + 1;
  /// @todo Graded in MP3.1
}

/**
 * Reverses the current List.
 */
template <class T>
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
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
  if (startPoint == endPoint || startPoint == NULL || endPoint == NULL){return;}
  ListNode* start = startPoint;
  ListNode* end = endPoint;
  ListNode* curr = startPoint;
  ListNode* temp = NULL;
  ListNode* leftside = startPoint->prev;
  ListNode* rightside = endPoint->next;
  while (curr != endPoint){
    temp = curr->prev;
    curr->prev = curr->next;
    curr->next = temp;
    curr = curr->prev;
  }
  curr->next = curr->prev;
  curr->prev = leftside;///
  start->next = rightside;///
  if (leftside == NULL){
    head_ = endPoint;
  }else{
    leftside->next = endPoint;
  }
  if (rightside == NULL){
    tail_ = startPoint;
  }else{
    rightside->prev = startPoint;///
  }
  startPoint = end;
  endPoint = start;
    /// @todo Graded in MP3.1
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  int m=length_;
  ListNode* cur1=head_;
  ListNode* cur2=head_;
  for(int i=1;i<=m;i=i+n){
    cur2=cur1;
    for(int j=0;j<n-1;j++){
      if(cur2->next==NULL){
        break;
      }
      cur2=cur2->next;
    }
    reverse(cur1,cur2);
    cur1=cur2->next;
  }
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
template <class T>
void List<T>::waterfall() {
  if(head_ == NULL){
    return;
  }
  ListNode* curr = head_;
  ListNode* second = curr->next;
  while (second != tail_ && second != NULL){
    curr->next = second->next;
    second->next->prev = curr;
    tail_->next = second;
    second->prev = tail_;
    second->next = NULL;
    tail_ = second;
    curr = curr->next;
    second = curr->next;
  }
  /// @todo Graded in MP3.1
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    ListNode *cur=start;
    for(int i=0;i<splitPoint-1;i++){
      cur=cur->next;
    }
    ListNode *temp=cur->next;
    temp->prev=NULL;
    cur->next=NULL;
    return temp;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
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
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
        if (first == NULL) {
            return second;
        }
        else if (second == NULL) {
            return first;
        }
        ListNode* head;
        ListNode* temp;
        if (first->data < second->data) {
            head = first;
            first = first->next;
        }
        else {
            head = second;
            second = second->next;
        }
        temp = head;
        while (first && second) {
            if (first->data < second->data) {
                temp->next = first;
                first->prev = temp;
                first = first->next;
            }
            else {
                temp->next = second;
                second->prev = temp;
                second = second->next;
            }
            temp = temp->next;
        }
        while (first) {
            temp->next = first;
            first->prev = temp;
            first = first->next;
            temp = temp->next;
        }

        while (second) {
            temp->next = second;
            second->prev = temp;
            second = second->next;
            temp = temp->next;
        }

        return head;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if(chainLength==1){
      return start;
    }
    ListNode* mid=split(start,chainLength/2);
    start=mergesort(start, chainLength / 2);
    mid=mergesort(mid, chainLength - chainLength / 2);
    
    return merge(start,mid);
}

