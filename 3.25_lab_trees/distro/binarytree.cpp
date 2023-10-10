/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);
    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;
    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);

//pre-order  根左右   in-order 左根右   post-order 左右根
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    mirror(root);
}

//Private helper function for the public mirror function.
template <typename T>
void BinaryTree<T>::mirror(Node* subRoot)
{
    //your code here
    if(subRoot==NULL||(subRoot->left==NULL&&subRoot->right==NULL)){
        return;
    }
    Node* temp=subRoot->left;
    subRoot->left=subRoot->right;
    subRoot->right=temp;
    mirror(subRoot->left);
    mirror(subRoot->right);
}
/**
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
    vector<T>array;
    isOrdered(root,array);
    for(unsigned int i=0;i<array.size()-1;i++){
        if(array[i+1]<array[i]){
            return false;
        }
    }
    return true;
}

//Private helper function for the public isOrdered function.
template <typename T>
void BinaryTree<T>::isOrdered(Node* subRoot,vector<T>& a) const
{
    if (subRoot == NULL)
        return;
    isOrdered(subRoot->left,a);

    a.push_back(subRoot->elem);

    isOrdered(subRoot->right,a);
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    vector<T> NowPaths;
    printPaths(root,paths,NowPaths);
    // your code here
}

//Private helper function for the public printPaths function.
template <typename T>
void BinaryTree<T>::printPaths(Node* subRoot,vector<vector<T> > &paths,vector<T> &NowPaths) const
{
    if(subRoot==NULL){
        //NowPaths.push_back(0);
        return;
    }
    NowPaths.push_back(subRoot->elem);
    if(subRoot->left==NULL&&subRoot->right==NULL){
        //
        paths.push_back(NowPaths);
        return;
    }
    printPaths(subRoot->left,paths,NowPaths);
    if(subRoot->left!=NULL){
        NowPaths.pop_back();
    }
    printPaths(subRoot->right,paths,NowPaths);
    if(subRoot->right!=NULL){
        NowPaths.pop_back();
    }
    // your code here
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return subDistances(root, 0);
}


//Private helper function for the public sumDistances function.
template <typename T>
int BinaryTree<T>::subDistances(Node* subRoot,int nowdistance) const
{
    if (subRoot==NULL){
        return 0;
    }
    if(!subRoot->left&&!subRoot->right){
        return nowdistance;
    }

    return nowdistance+subDistances(subRoot->left,nowdistance+1)+subDistances(subRoot->right,nowdistance+1);
}
