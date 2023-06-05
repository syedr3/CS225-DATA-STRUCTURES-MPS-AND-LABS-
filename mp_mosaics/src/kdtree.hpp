/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <deque>

using namespace std;

template <int Dim>
bool smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) //DONE
{
    /**
     * @todo Implement this function!
     */
     if (first[curDim] < second[curDim]) {return true;}
     else if(first[curDim] > second[curDim]) {return false;}
     else {return (first<second);}
    return false;
}

template <int Dim>
bool shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) //DONE
{
    /**
     * @todo Implement this function!
     */
     double currentBest_ = 0.0;
     double potential_ = 0.0;
     int Dim_ = 0;
     while (Dim_ != Dim){
      currentBest_ = currentBest_ + ((currentBest[Dim_]-target[Dim_])*(currentBest[Dim_]-target[Dim_]));
      potential_ = potential_ + ((potential[Dim_]-target[Dim_])*(potential[Dim_]-target[Dim_]));
      Dim_++;
     }
     if ((potential_) < (currentBest_)) {return true;}
     else if ((currentBest_) < (potential_)) {return false;}
     else {return (potential < currentBest);}
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints) //DONE
{
    /**
     * @todo Implement this function!
     */
    if (newPoints.size() == 0){ return;}
    vector<Point<Dim>> WORK;
    for (unsigned int i = 0; i < newPoints.size(); i++){
      WORK.push_back(newPoints[i]);
    }
    auto start = WORK.begin();
    auto end = WORK.end();
    size = newPoints.size();
    helper_function(start,end,0,root);
}

template <int Dim>
template <typename RandIter>
void KDTree<Dim>::helper_function(RandIter start, RandIter end, int Dimensions, KDTreeNode *&subroot) //DONE
{
if (end == start || end < start) {return;}
RandIter x = start;
int y = 0;
while (x != end){
  y++;
  x++;
}
if (y > 0){
y--;
y = y/2;
}
RandIter median = start+y;
auto cmp = [Dimensions](const Point<Dim>& first, const Point<Dim>& second){return smallerDimVal(first, second, Dimensions);};
select(start, end, median, cmp);
subroot = new KDTreeNode(Point<Dim> (*median));
helper_function(start, median, (Dimensions+1)%Dim, subroot->left);
helper_function(median+1, end, (Dimensions+1)%Dim, subroot->right);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) //DONE
{
  /**
   * @todo Implement this function!
   */
destroy(root);
if (other == NULL) {return;}
size = other.size;
auto other_ = other.root;
helper_(root, other_);
}

template <int Dim>
void KDTree<Dim>::helper_(KDTreeNode *&subroot, KDTreeNode *&other_) //DONE
{
  if (other_ == NULL) {return;}
  subroot = new KDTreeNode(other_->point);
  helper_(subroot->left, other_->left);
  helper_(subroot->right, other_->right);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) { //DONE
  /**
   * @todo Implement this function!
   */
   if (this != &rhs){
    delete *this;
    this = new KDTree(rhs);
   }
  return *this;
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode* r) //DONE
{
  if (!r) return;
  destroy(r->left);
  destroy(r->right);
  delete r;
}

template <int Dim>
KDTree<Dim>::~KDTree() { //DONE
  /**
   * @todo Implement this function!
   */
   destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */


    if (root == NULL) return Point<Dim>();
    return findNearestNeighbor_(root, query, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor_(KDTreeNode *subroot, const Point<Dim>& query, int Dimension) const{
Point<Dim> ChildResult;
bool left;
Point<Dim> current_best;
if (subroot->right == NULL && subroot->left == NULL) {return subroot->point;}
if (smallerDimVal(query, subroot->point, Dimension%Dim)){
  if (subroot->left == NULL)
    return subroot->point;
  ChildResult = findNearestNeighbor_(subroot->left, query, (Dimension+1)%Dim);
  left = true;
}
else{
  if (subroot->right == NULL)
    return subroot->point;
  ChildResult = findNearestNeighbor_(subroot->right, query, (Dimension+1)%Dim);
  left = false;
}
if (shouldReplace(query, ChildResult, subroot->point)){
  current_best = subroot->point;
}
else{
  current_best = ChildResult;
}
double radius_ = radius(query, current_best);
double split = ((subroot->point)[Dimension%Dim]-(query)[Dimension%Dim]) * ((subroot->point)[Dimension%Dim]-(query)[Dimension%Dim]);
if (split <= radius_){
  if (left == true){
    if (subroot->right != NULL){
      Point<Dim> current_best_contender = findNearestNeighbor_(subroot->right, query, (Dimension+1)%Dim);
      if (shouldReplace(query, current_best, current_best_contender))
      {current_best = current_best_contender;}
    }
  }
  else{
    if (subroot->left != NULL){
      Point<Dim> current_best_contender = findNearestNeighbor_(subroot->left, query, (Dimension+1)%Dim);
      if (shouldReplace(query, current_best, current_best_contender))
      {current_best = current_best_contender;}
    }
  }
}
return current_best;
}

template <int Dim>
double KDTree<Dim>::radius(Point<Dim> x, Point<Dim> y) const
{
  double sum = 0;
  for (int i = 0; i < Dim; i++){
    sum = sum + (x[i] - y[i])*(x[i] - y[i]);
  }
  return sum;
}


template <typename RandIter, typename Comparator>
void select(RandIter begin, RandIter end, RandIter k, Comparator cmp) //DONE
{
    /**
     * @todo Implement this function!
     */
     if (begin == end || end < begin) {return;}
     RandIter pivotIndex = k;
     pivotIndex = partition(begin,end,pivotIndex,cmp);
     if (k == pivotIndex) {return;}
     else if(k < pivotIndex) {return select(begin,pivotIndex,k,cmp);}
     else {return select(pivotIndex+1,end,k,cmp);}

}

template <typename RandIter, typename Comparator>
RandIter partition(RandIter begin, RandIter end, RandIter k, Comparator cmp) //DONE
{
  auto pivotValue = *k;
  *k = *(end-1);
  *(end-1) = pivotValue;
  RandIter storeIndex = begin;
  for (RandIter i = begin; i < end-1; i++){
    if (cmp(*i,pivotValue)){
      auto plz = *i;
      *i = *storeIndex;
      *storeIndex = plz;
      storeIndex++;
    }
  }
  if (storeIndex == end) storeIndex--;
  auto work = *storeIndex;
  *storeIndex = *(end-1);
  *(end-1) = work;
  return storeIndex;
}

