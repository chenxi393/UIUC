/* Your code here! */

// path compression  路径压缩

// union-by-size   按秩归并

#ifndef _DESTS_
#define _DESTS_
#include<vector>
using namespace std;
class DisjointSets {
private:
    vector<int> data;

public:
    void addelements(int num);
    // Creates n unconnected root nodes at the end of the vector.

    int find(int elem);
    // This function should compress paths and works as described in lecture.

    void setunion(int a, int b);
    // This function should be implemented as union- by - size.

   // int size(int elem);
};

#endif