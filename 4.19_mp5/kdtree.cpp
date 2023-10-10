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
    double dis1=0.0;
    double dis2=0.0;
    for(int i=0;i<Dim;i++){
        dis1+=(target[i]-currentBest[i])*(target[i]-currentBest[i]);
        dis2+=(target[i]-potential[i])*(target[i]-potential[i]);
    }
    if(dis1==dis2){
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
    size=newPoints.size();
    vector<Point<Dim>> Points_(newPoints);
    Build(0,size-1,Points_,root,0);
}
//helper Function
template <int Dim>
void KDTree<Dim>::Build(int start,int end,vector<Point<Dim>> Points_,KDTreeNode* & R,int dimension)
{
    if(start>end){
        R=NULL;
        return;
    }
    // if(start==end){
    //     R=new KDTreeNode(Points_[start]);
    //     return;
    // }
   
    int mid=(start+end)/2;
    quick_select(start,end,mid,Points_,dimension);
    R=new KDTreeNode(Points_[mid]);
    Build(start,mid-1,Points_,R->left,(dimension+1)%Dim);
    Build(mid+1,end,Points_,R->right,(dimension+1)%Dim);

}

//quick_select-----O(N)
// 1.取一个点为基准
// 2.比这个点小的放左边 比这个点大的放右边

// -----quick_sort-------O(N*logN)(每次)

//helper Function 
template <int Dim>
void KDTree<Dim>::quick_select(int start,int end,int k,vector<Point<Dim>> &Points_,int dimension){
//漏了引用  must
    int i=start,j=end;
    Point<Dim> pirror=Points_[start];
    while(j>i){
        while(j>i&&smallerDimVal(Points_[j],pirror,dimension)==false){
            j--;
        }
        swap(Points_[i],Points_[j]);
        while(j>i&&smallerDimVal(Points_[i],pirror,dimension)==true){
            i++;
        }
        swap(Points_[i],Points_[j]);
    }

    if(i==k){
        return;
    }else if(i<k){
        quick_select(i+1,end,k,Points_,dimension);
    }else{
        quick_select(start,i-1,k,Points_,dimension);
    }

}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {//copy constructor
  /**
   * @todo Implement this function!
   */
    copy(other.root,root);
    size=other.size;
}
//copy constructor - helper function
template <int Dim>
void KDTree<Dim>::copy(const KDTreeNode* other,KDTreeNode* & R) {
    if(other==NULL){
        R=NULL;
        return;
    }
    R=new KDTreeNode(other->point);
    copy(other->left,R->left);
    copy(other->right,R->right);

}

// KDTree<2> r1;
// KDTree<2> r2=r1--------r2(r1);
// r1=r2;

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
void KDTree<Dim>::delete_(KDTreeNode* & R){
    if(R==NULL){
        return;
    }
    delete_(R->left);
    delete_(R->right);
    delete R;
    R=NULL;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
   delete_(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    
    return findNearest(query,root,0);
}

template <int Dim>//
Point<Dim> KDTree<Dim>::findNearest(const Point<Dim>& query,const KDTreeNode* R,int dimension) const
{
    /**
     * @todo Implement this function!
     */
    if(R->left==NULL&&R->right==NULL){
        return R->point;
    }
    Point<Dim> potential=R->point;
    Point<Dim> currentBest;
    bool left_flag;
    if((smallerDimVal(query,potential,dimension)==true&&R->left)||!R->right){
        left_flag=true;
        currentBest=findNearest(query,R->left,(dimension+1)%Dim);
    }else{
        left_flag=false;
        currentBest=findNearest(query,R->right,(dimension+1)%Dim);
    }

    if(shouldReplace(query,currentBest,potential)==true){
        currentBest=potential;
    }
    double dis1=0;
    for(int i=0;i<Dim;i++){
        dis1+=(currentBest[i]-query[i])*(currentBest[i]-query[i]);
    }
    double dis2=(query[dimension]-potential[dimension])*(query[dimension]-potential[dimension]);
    if(dis1>=dis2){
        if(left_flag&&R->right){
            potential=findNearest(query,R->right,(dimension+1)%Dim);
        }else if(!left_flag&&R->left){
            potential=findNearest(query,R->left,(dimension+1)%Dim);
        }
        if(shouldReplace(query,currentBest,potential)==true){
           currentBest=potential;
        }
    }

    return currentBest;
}

