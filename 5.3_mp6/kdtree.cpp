/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if(first[curDim]==second[curDim]){
        return first<second;
    }

    return first[curDim]<second[curDim];
    
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */

    double dis1=0;//cur
    double dis2=0;//potential
    for(int i=0;i<Dim;i++){
        dis1+=(currentBest[i]-target[i])*(currentBest[i]-target[i]);
        dis2+=(potential[i]-target[i])*(potential[i]-target[i]);
    }
    if(dis1==dis2){//dis1==dis2
        return potential<currentBest;
    }

    return dis2<dis1;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    if(newPoints.size()==0){
        root=NULL;
        size=0;
        return;
    }

    vector<Point<Dim>> curPoints(newPoints);
    size=curPoints.size();
    Build(0,size-1,curPoints,0,root);
}
template <int Dim>
void KDTree<Dim>::Build(int start,int end,vector<Point<Dim>>& curPoints,int dimension,KDTreeNode*& R)
{
    if(start>end){
        R=NULL;
        return;
    }

    // if(start==end){
    //     R=new KDTreeNode(curPoints[start]);
    //     return;
    // }
    int mid=(start+end)/2;
 
    quick_select(start,end,mid,curPoints,dimension);

    R=new KDTreeNode(curPoints[mid]);
    Build(start,mid-1,curPoints,(dimension+1)%Dim,R->left);
    Build(mid+1,end,curPoints,(dimension+1)%Dim,R->right);
}
template <int Dim>
void KDTree<Dim>::quick_select(int start,int end,int mid,vector<Point<Dim>>& curPoints,int dimension)const{

    int i=start,j=end;
    Point<Dim> pirror=curPoints[i];
    while(j>i){
        while(j>i&&smallerDimVal(curPoints[j],pirror,dimension)==false){
            j--;
        }
        swap(curPoints[j],curPoints[i]);
        while(j>i&&smallerDimVal(pirror,curPoints[i],dimension)==false){
            i++;
        }
        swap(curPoints[j],curPoints[i]);
    }
    
    if(i==mid){
        return;
    }else if(i<mid){
        quick_select(i+1,end,mid,curPoints,dimension);
    }else{
        quick_select(start,i-1,mid,curPoints,dimension);
    }
}



template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
   copy(other.root,root);
   size=other.size;
}

template <int Dim>
void KDTree<Dim>::copy(const KDTreeNode* other,KDTreeNode*& R) {
  /**
   * @todo Implement this function!
   */
   if(!other){
    R=NULL;
    return;
   }

   R=new KDTreeNode(other->point);
   copy(other->left,R->left);
   copy(other->right,R->right);
    
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */
    delete_(root);
    copy(rhs.root,root);
    size=rhs.size;
    return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   delete_(root);
}
//helper_function  for destructor
template <int Dim>
void KDTree<Dim>::delete_ (KDTreeNode* &R){
  if(R==NULL){
    return;
  }
  if(R->left){
    delete_(R->left);
  }

  if(R->right){
    delete_(R->right);
  }
  delete R;
  R=NULL;
}
template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */

    return findNearest(root,query,0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearest(const KDTreeNode* R, const Point<Dim>& query, int dimension) const {
    if(!R->left&&!R->right){
        return R->point;
    }

    bool left_flag=false;
    Point<Dim> curPoints=R->point;
    Point<Dim> nextPoints;
   
    if((smallerDimVal(query,curPoints,dimension)==true&&R->left)||!R->right){
        nextPoints=findNearest(R->left,query,(dimension+1)%Dim);
        left_flag=true;
    }else{ 
        nextPoints=findNearest(R->right,query,(dimension+1)%Dim);
        left_flag=false;
    }

    if(shouldReplace(query,curPoints,nextPoints)){
        curPoints=nextPoints;
    }

    double dis=0;
    for(int i=0;i<Dim;i++){
        dis+=(curPoints[i]-query[i])*(curPoints[i]-query[i]);
    }

    double splitting=(R->point[dimension]-query[dimension])*(R->point[dimension]-query[dimension]);
    if(splitting<=dis){
        if(left_flag&&R->right){
            nextPoints=findNearest(R->right,query,(dimension+1)%Dim);
        }else if(!left_flag&&R->left){
            nextPoints=findNearest(R->left,query,(dimension+1)%Dim);
        }
        if(shouldReplace(query,curPoints,nextPoints)){
            curPoints=nextPoints;
        }
    }
    return curPoints;
}