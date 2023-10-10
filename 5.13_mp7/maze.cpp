/* Your code here! */
#include "maze.h"
#include "dsets.h"
#include <cstdlib>
#include <queue>
SquareMaze::SquareMaze()
{
    width_ = height_ = 0;
}

void SquareMaze::makeMaze(int width, int height)
{
    // clear all the existing data
    data.clear();
    width_ = width;
    height_ = height;

    DisjointSets set;

    set.addelements(width_ * height_);
    // 1----有墙  0表示没墙
    bitset<2> temp("11"); // usage of bitset
    for (int i = 0; i < width_ * height_; i++) {
        data.push_back(temp);
    }
    int cnt = 0;
    int x_, y_, dir;
    while (cnt < width_ * height_ - 1) {
        x_ = rand() % width_;
        y_ = rand() % height_;
        dir = rand() % 2; // 0 右墙 1 代表下墙
        if (x_ == width_ - 1 && dir == 0) {
            continue;
        }
        if (y_ == height_ - 1 && dir == 1) {
            continue;
        }
        if (data[x_ + y_ * width_][dir] == 1) {
            if (dir == 0) {
                if (set.find(x_ + y_ * width_) != set.find(x_ + 1 + y_ * width_)) {
                    set.setunion(x_ + y_ * width_, x_ + 1 + y_ * width_);
                    data[x_ + y_ * width_][dir] = 0;
                    cnt++;
                }
            } else {
                if (set.find(x_ + y_ * width_) != set.find(x_ + (y_ + 1) * width_)) {
                    set.setunion(x_ + y_ * width_, x_ + (y_ + 1) * width_);
                    // data[x_ + (y_ + 1) * width_][dir] = 0;
                    data[x_ + y_ * width_][dir] = 0;
                    cnt++;
                }
            }
        }
    }
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
    // You can not step off of the maze or through a wall.
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        return false;
    }

    switch (dir) {
    case 0:
        /* code */
        if (x == width_ - 1) {
            return false;
        }
        return !data[x + y * width_][0];
        break;
    case 1:
        if (y == height_ - 1) {
            return false;
        }
        return !data[x + y * width_][1];
        break;
    case 2:
        if (x == 0) {
            return false;
        }
        return !data[x - 1 + y * width_][0];
        break;
    case 3:
        if (y == 0) {
            return false;
        }
        return !data[x + (y - 1) * width_][1];
        break;
    default:
        return false;
        break;
    }
    return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
    if (x < 0 || y < 0 || x >= width_ || y >= height_) {
        return;
    }

    data[x + y * width_][dir] = exists;
}

vector<int> SquareMaze::solveMaze() // bfs
{
    queue<int> bfs;
    bool visited[width_ * height_];
    // bool dis[width_ * height_];
    // bool path[width_ * height_];
    int dis[width_ * height_];
    int path[width_ * height_];

    for (int i = 0; i < width_ * height_; i++) {
        visited[i] = 0;
        dis[i] = 0;
        path[i] = -1;
    }

    bfs.push(0);
    visited[0] = 1;
    while (!bfs.empty()) {
        int temp = bfs.front();
        int x_ = temp % width_;
        int y_ = temp / width_;
        bfs.pop();

        if (canTravel(x_, y_, 0) && !visited[temp + 1]) {
            visited[temp + 1] = 1;
            dis[temp + 1] = dis[temp] + 1;
            path[temp + 1] = temp;
            bfs.push(temp + 1);
        }
        if (canTravel(x_, y_, 1) && !visited[temp + width_]) {
            visited[temp + width_] = 1;
            dis[temp + width_] = dis[temp] + 1;
            path[temp + width_] = temp;
            bfs.push(temp + width_);
        }
        if (canTravel(x_, y_, 2) && !visited[temp - 1]) {
            visited[temp - 1] = 1;
            dis[temp - 1] = dis[temp] + 1;
            path[temp - 1] = temp;
            bfs.push(temp - 1);
        }
        if (canTravel(x_, y_, 3) && !visited[temp - width_]) {
            visited[temp - width_] = 1;
            dis[temp - width_] = dis[temp] + 1;
            path[temp - width_] = temp;
            bfs.push(temp - width_);
        }
    }

    int max_x = 0;
    for (int i = 1; i < width_; i++) {
        if (dis[width_ * (height_ - 1) + i] > dis[width_ * (height_ - 1) + max_x]) {
            max_x = i;
        }
    }

    vector<int> ans;
    int k = width_ * (height_ - 1) + max_x;
    while (path[k] != -1) {
        int t = k - path[k];
        if (t == 1) { // right
            ans.push_back(0);
        } else if (t == -1) {
            ans.push_back(2);
        } else if (t == width_) {
            ans.push_back(1);
        } else {
            ans.push_back(3);
        }
        k = path[k];
    }

    // reverse(ans.begin(),ans.end()) ;  return ans;
    return vector<int>(ans.rbegin(), ans.rend());
}

PNG* SquareMaze::drawMaze() const
{
    PNG* new_PNG = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    HSLAPixel black(0, 0, 0, 1);
    for (unsigned i = 0; i < width_ * 10 + 1; i++) {
        if (i < 1 || i > 9) {
            // except the entrance (1,0) through (9,0).
            *new_PNG->getPixel(i, 0) = black;
        }
    }
    for (unsigned i = 0; i < height_ * 10 + 1; i++) {
        *new_PNG->getPixel(0, i) = black;
    }
    int x_, y_;
    for (int i = 0; i < width_ * height_; i++) {
        x_ = i % width_;
        y_ = i / width_;

        if (data[i][0]) {
            for (int k = 0; k <= 10; k++) {
                *new_PNG->getPixel((x_ + 1) * 10, y_ * 10 + k) = black;
            }
        }
        if (data[i][1]) {
            for (int k = 0; k <= 10; k++) {
                *new_PNG->getPixel(x_ * 10 + k, (y_ + 1) * 10) = black;
            }
        }
    }
    return new_PNG;
}

PNG* SquareMaze::drawMazeWithSolution()
{
    PNG* maze = drawMaze();
    vector<int> solution = solveMaze();

    int x_ = 5;
    int y_ = 5;
    HSLAPixel red(0, 1, 0.5, 1);
    HSLAPixel white(0, 1, 1, 1);
    for (unsigned i = 0; i < solution.size(); i++) {
        switch (solution[i]) {
        case 0:
            for (int k = 0; k <= 10; k++) {
                *maze->getPixel(x_ + k, y_) = red;
            }
            x_ += 10;
            break;
        case 1:
            for (int k = 0; k <= 10; k++) {
                *maze->getPixel(x_, y_ + k) = red;
            }
            y_ += 10;
            break;
        case 2:
            for (int k = 0; k <= 10; k++) {
                *maze->getPixel(x_ - k, y_) = red;
            }
            x_ -= 10;
            break;
        case 3:
            for (int k = 0; k <= 10; k++) {
                *maze->getPixel(x_, y_ - k) = red;
            }
            y_ -= 10;
            break;
        }
    }
    x_ -= 5;
    y_ += 5;
    for (int i = 1; i <= 9; i++) {
        *maze->getPixel(x_ + i, y_) = white;
    }
    return maze;
}