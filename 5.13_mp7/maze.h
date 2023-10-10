/* Your code here! */
#ifndef _MAZE_
#define _MAZE_

// bitset
// bitset<2> a; a[0]=1;a[1]=0;

#include "./cs225/PNG.h"
#include <bitset>
#include <vector>
using namespace std;
using namespace cs225;
class SquareMaze {
private:
    /* data */
    vector<bitset<2>> data;

    int width_;
    int height_;

public:
    SquareMaze();
    // No- parameter constructor.More...

    void makeMaze(int width, int height);
    // Makes a new SquareMaze of the given height and width.More...

    bool canTravel(int x, int y, int dir) const;
    // This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates(x, y)           .More...

    void setWall(int x, int y, int dir, bool exists);
    // Sets whether or not the specified wall exists.More...

    vector<int> solveMaze();
    // Solves this SquareMaze.More...

    PNG* drawMaze() const;
    // Draws the maze without the solution.More...

    PNG* drawMazeWithSolution();
    // This function calls drawMaze, then solveMaze;
    // it modifies the PNG from drawMaze to show the solution vector and the exit.More...
};

#endif