/* Your code here! */

#ifndef STACK_H
#define STACK_H
#include "dsets.h"

void DisjointSets::addelements(int num)
{
    for (int i = 0; i < num; i++) {
        data.push_back(-1);
    }
}

int DisjointSets::find(int elem)
{
    if (data[elem] < 0) {
        return elem;
    }
    return data[elem] = find(data[elem]); // path compression  路径压缩
}

void DisjointSets::setunion(int a, int b)
{
    int root1 = find(a);
    int root2 = find(b);
    int new_size = data[root1] + data[root2];

    if (data[root1] <= data[root2]) { // root1--size >= root2--size
        data[root2] = root1;
        data[root1] = new_size;
    } else {
        data[root1] = root2;
        data[root2] = new_size;
    }
    // union-by-size   按秩归并
}
#endif