////
////  mazequeue.cpp
////  HW2
////
////  Created by August Greer on 2/2/18.
////  Copyright © 2018 August Greer. All rights reserved.
////
//
#include <queue>
#include <iostream>

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};



bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    std::queue<Coord> coordQueue;
    Coord start(sr,sc);
    
    coordQueue.push(start);
    maze[sr][sc] = '#';
    while (coordQueue.empty() != true)
    {
        Coord current = coordQueue.front();
        int r = current.r();
        int c = current.c();
        
        coordQueue.pop();
        if (r == er && c == ec)
            return true;
        else
        {
            if (maze[r][c + 1] == '.') {
                coordQueue.push(Coord(r, c + 1));
                maze[r][c + 1] = '#';
            }
            if (maze[r + 1][c] == '.') {
                coordQueue.push(Coord(r + 1, c));
                maze[r + 1][c] = '#';
            }
            if (maze[r][c - 1] == '.') {
                coordQueue.push(Coord(r, c - 1));
                maze[r][c - 1] = '#';
            }
            if (maze[r - 1][c] == '.') {
                coordQueue.push(Coord(r - 1, c));
                maze[r - 1][c] = '#';
            }
        }
    }
    
    return false;
}



int main()
{
    std::string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X3XXXX.X",
        "XXX0147ADX",
        "X962X8XX.X",
        "XCX5XBEX.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,3, 1,8))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
}

