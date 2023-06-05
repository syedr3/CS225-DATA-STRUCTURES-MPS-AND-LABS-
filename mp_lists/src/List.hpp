/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
   tail_ = NULL;
    head_ = tail_;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(tail_->next);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  ListNode* del_;
  while (head_ != NULL){
    del_ = head_;
    head_ = head_->next;
    delete del_;
  }
  
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  if (length_ > 1) {
    head_ -> prev = newNode;
    ListNode* p = head_;
    ListNode* x = newNode;
    newNode = p;
    head_ = x;
  }
  if (length_ == 0) {
    head_ = newNode;
    head_->next = NULL;
    head_->prev = NULL; 
    tail_ = head_;
    
  }
    if (length_ == 1){
    head_ = newNode;
    head_->prev = NULL;
    head_->next = tail_;
    tail_->prev = head_;
    tail_->next = NULL;
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
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;
  if (length_ > 1){
    tail_ -> next = newNode;
    // ListNode* p = tail_;
    // ListNode* x = newNode;
    // newNode = p;
    tail_ = newNode;
  }
  if (length_ == 0) {
    head_ = newNode;
    head_->next = NULL;
    head_->prev = NULL; 
    tail_ = head_;
    
  }
    if (length_ == 1){
    tail_ = newNode;
    tail_->next = NULL;
    head_->next = tail_;
    tail_->prev = head_;
    head_->prev = NULL;
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
  /// @todo Graded in mp_lists part 1

  // ListNode * curr = start;

  // for (int i = 0; i < splitPoint || curr != NULL; i++) {
  //   curr = curr->next;
  // }

  // if (curr != NULL) {
  //     curr->prev->next = NULL;
  //     curr->prev = NULL;
  // }

  // return NULL;
  ListNode * cur = start;
  if (splitPoint == 0){
    start = NULL;
    cur->prev = NULL;
    return cur;
  }
  while(splitPoint > 0){
    cur = cur->next;
    splitPoint--;
  }
  // ListNode *x = cur->next;
  // cur->next = NULL;
  // cur = x;
  cur->prev->next = NULL;
  cur->prev = NULL;
  return cur;
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
  /// @todo Graded in part 1
  int times = length_ - 2;
  ListNode* cur = head_;
  if (times > 0){
  while (times > 0){
    T val = cur->next->data;
    ListNode* del = cur->next;
    ListNode* oops = cur->next->next;
    cur->next = cur->next->next;
    oops->prev = cur;
    delete del;
    length_--;
    insertBack(val);
    cur = cur->next;
    times--;
  }
  }
  return;
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
  /// @todo Graded in mp_lists part 2
  ListNode *m = startPoint;
  ListNode *n = endPoint;
  int length = 0;
  while (m != n){
    length++;
    m = m->next;
  }
  length++;
  ListNode *x = startPoint;
  int asd = length;
  while (asd > 0){
    insertFront(x->data);
    length_ --;
    x = x->next;
    asd--;
  }
  int time = length;
  if (time > 0){
  while (time > 1){
    ListNode* p = endPoint;
    endPoint = endPoint->prev;
    delete p;
    p = NULL;
    time --;
  }
  ListNode* p = endPoint->prev;
  ListNode* del = endPoint;
  endPoint->prev->next = NULL;
  endPoint = p;
  delete del;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  int times = length_/n;
  if (times*n+1 != length_){
  if (times*n < length_){times++;}
  }
  for (int i = 0; i < times; i++){
  int qw = i*n;
  while (qw != 0 && head_->next != NULL){
    head_ = head_->next;
    qw--;
  }
  tail_ = head_;
  int x = n;
  ListNode* t;
  ListNode* we = head_->prev;
  while (x != 1 && tail_->next != NULL){
    tail_ = tail_->next;
    x--;
    t = tail_->next;
  }
  reverse();
  if (t != NULL){
  t->prev = tail_;
  tail_->next = t;
  }
  if (we != NULL){
    we->next = head_;
    head_->prev = we;
  }
  while (head_->prev != NULL){
    head_ = head_->prev;
  }
  while (tail_->next != NULL && tail_ != NULL){
    tail_ = tail_->next;
  }
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
  /// @todo Graded in mp_lists part 2
  if (first == NULL) {return NULL;}
  if (second == NULL) {return NULL;}
  ListNode* p;
  ListNode* x;
  if (first->data < second->data) {
    p = first;
    x = second;
  }
  else{
    p = second;
    x = first;
  }
ListNode* ret = p;
while (x!= NULL && p!=NULL){
  if ((p->data < x->data && (p->next == NULL || x->data < p->next->data)) || p->data == x->data){
    ListNode *xx = x->next;
    ListNode* qw = p->next;
    if (qw != NULL){
      qw->prev = x;
    }
    x->next = qw;
    p->next = x;
    x->prev = p;
    x = xx;
    p = p->next;
  }
  else { p = p->next;}
}
return ret;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
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
  /// @todo Graded in mp_lists part 2
  if (start->next == NULL) {
    return start;
    }
  ListNode *p = split (start, chainLength/2);
  ListNode *x = mergesort(start,chainLength/2);
  ListNode *y = mergesort(p,(chainLength-(chainLength/2)));
  return merge(x,y);
}
