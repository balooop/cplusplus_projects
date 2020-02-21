/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <cmath>

using namespace std;
using std::vector;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    return (first[curDim]<second[curDim]) ? true : (first[curDim]>second[curDim]) ? false : (first<second) ? true : false;

}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    double currDist = _calculateDistance(target, currentBest);
    double newDist = _calculateDistance(target, potential);
    
    return (newDist<currDist)? true : (currDist<newDist) ? false : (potential<currentBest)? true : false;
}

template <int Dim>
double KDTree<Dim>::_calculateDistance(const Point<Dim>& first, const Point<Dim>& second) const{
  double sum = 0;
  for (int i = 0; i<Dim; i++){
    sum = sum + pow(first[i]-second[i], 2);
  }
  return sqrt(sum);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = 0;
    points = newPoints;
 
    //otherwise we construct the tree recursively
    //final recursive return of the construct function will give us the root
    root = _construct(0, points.size() - 1, 0);
}

//recursive helper function for KDTree constructor
//@param l = start index of points
//@param r = end index of points
//@param d is the dimension we are constructing/splitting on
template <int Dim>
typename KDTree<Dim>::KDTreeNode * KDTree<Dim>::_construct(unsigned l, unsigned r, unsigned d)
{
    //base case
    if(r < l || points.empty() || r < 0 || r >= points.size() || l < 0 || l >= points.size())    return NULL;

    //recursive case
    //median is (l+r)/2
    unsigned median_idx = (l + r)/2;
    //gets median point
    Point<Dim> median_point = _quickselect(l, r, d, median_idx);
    //splits at median point
    KDTreeNode* node = new KDTreeNode(median_point);
    //constructs right subtree split recursively
    node->right = _construct(median_idx + 1, r, (d+1)%Dim);
    //constructs left subtree split recursively
    node->left = _construct(l, median_idx - 1, (d+1)%Dim);
    //increments size
    size++;
    //returns new internal or root node
    return node;
}

//quickselect median
//@param points is the array of points
//@param k indicates that we want the Kth smallest element (a+b)/2
//@param d is the current dimension we are looking at
//@param l is the leftmost index we are selecting from
//@param r is the rightmost index we are selecting from
//returns the index of the Kth smallest index
template <int Dim>
Point<Dim>& KDTree<Dim>::_quickselect(unsigned l, unsigned r, unsigned d, unsigned k)
{
  if(left != right)
  {
    //partitions about the middle of the array
    unsigned pivot_index = _partition(l, r, d, k);
    
    //if pivot index is the median index
    if(pivot_index == k)
    {
      //we can return the point
      return points[pivot_index];
    } else if(pivot_index < k)
    {
      //if pivot index is less than median point, we look at the right half of the vector
      return _quickselect(pivot_index + 1, r, d, k);
    } else
    {
      //if pivot index is greater than Kth smallest element, we look at the left half of the vector
      return _quickselect(l, pivot_index - 1, d, k);
    }
  }
  else{
    return points[r];
  }
}

//partition helper for quickselect
//@param points is array of points
//@param left is left point of partition
//@param right is right point of partition
//@param d is dimension of k-d tree
//@param k is the index to partition from (aka median index)
//returns the index at which all elements to the left are smaller, all elements to the right are larger, and element at the index returned is the Kth smallest element
template <int Dim>
unsigned KDTree<Dim>::_partition(unsigned left, unsigned right, unsigned d, unsigned k)
{
  //gets pivot point as the middle point
  Point<Dim> pivot = points[k];
  //moves pivot point to right
  swap(points[k], points[right]);
  
  //start swapping from the left
  unsigned swap_idx = left;

  //loops through points array
  for(unsigned i = left; i < right; i++)
  {
    //if the pivot point is larger than points[i], we want to swap points[i] with the point at our current swapping index
    if(!smallerDimVal(pivot, points[i], d))
    {
      swap(points[i], points[swap_idx]);
      ++swap_idx;
    }
  }
  //swaps the rightmost  point into place
  swap(points[right], points[swap_idx]);
  return swap_idx; 
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  _copy(root, other.root);
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  _destroy(root);
  _copy(root, rhs.root);
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  _destroy(root);
}

//copy helper function
template <int Dim>
void KDTree<Dim>::_copy(KDTreeNode *& curr, KDTreeNode * other){
    if(other != NULL)
    {
      //deep copies current node
      curr = new KDTreeNode(other->point);
      //deep copy recurse right and left
      _copy(curr->right, other->right);
      _copy(curr->left, curr->left);
    }
    return;
}


//destroy helper function
template <int Dim>
void KDTree<Dim>::_destroy(KDTreeNode *& root){
  if(root != NULL)
  {
    //recursively destroy
    _destroy(root->right);
    _destroy(root->left);
    delete root;
  }
  return;
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    //closest point
    Point<Dim> closest = root->point;
    //find closest neighbour using helper
    travelDown(closest, query, root, 0);



    return closest;
}

template <int Dim>
void KDTree<Dim>::travelDown(Point<Dim> &closest, const Point<Dim> &query, KDTreeNode* treeNode, int dim) const{
KDTreeNode * potential;
KDTreeNode * other;
  if (treeNode != NULL){
    //travel till we reach leaf node
    //sets the next node to traverse to. If query is smaller than
    //treeNode, we traverse left, else we traverse right
    if (smallerDimVal(query, treeNode->point, dim)){
      potential = treeNode ->left;
      other = treeNode ->right;
    }
    else{
      potential = treeNode->right;
      other = treeNode->left;
    }

    travelDown(closest, query, potential, (dim+1)%Dim); //recurses down the tree till we get to a leaf node closest to query

    closest = (shouldReplace(query, closest, treeNode->point)) ? treeNode->point : closest;
  
    //checking radius
    double r = 0; int i = 0; double d = 0;
    d = pow(treeNode->point[dim]-query[dim], 2);
    while (i < Dim){
      r = r + pow(closest[i] - query[i], 2);
      i++;
    }

    if (r>=d)
      travelDown(closest, query, other, (dim+1)%Dim);
  }
}