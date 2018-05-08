////
////  main.cpp
////  HW2
////
////  Created by August Greer on 2/2/18.
////  Copyright © 2018 August Greer. All rights reserved.
////
//
#include <iostream>
#include <stack>
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
    std::stack<Coord> coordStack;
    Coord start(sr,sc);
    
    coordStack.push(start);
    maze[sr][sc] = '#';
    while (coordStack.empty() != true)
    {
        Coord current = coordStack.top();
        int r = current.r();
        int c = current.c();
        
        coordStack.pop();
        if (r == er && c == ec)
            return true;
        else
        {
            if (maze[r][c + 1] == '.') {
                coordStack.push(Coord(r, c + 1));
                maze[r][c + 1] = '#';
            }
           if (maze[r + 1][c] == '.') {
                coordStack.push(Coord(r + 1, c));
                maze[r + 1][c] = '#';
            }
            if (maze[r][c - 1] == '.') {
                coordStack.push(Coord(r, c - 1));
                maze[r][c - 1] = '#';
            }
            if (maze[r - 1][c] == '.') {
                coordStack.push(Coord(r - 1, c));
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
        "XXX01BC..X",
        "X652XDXX.X",
        "X7X4X..X.X",
        "X8XXXX.X.X",
        "X9AX...X.X",
        "XXXXXXXXXX"
    };

    if (pathExists(maze, 10,10, 4,3, 1,8))
        std::cout << "Solvable!" << std::endl;
    else
        std::cout << "Out of luck!" << std::endl;
}

