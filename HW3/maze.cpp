//
//  maze.cpp
//  HW3
//
//  Created by August Greer on 2/11/18.
//  Copyright © 2018 CS32. All rights reserved.
//
//#include <string>
//#include <iostream>

bool pathExists(std::string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr < 0  ||  sr >= nRows  ||  sc < 0  || sc >= nCols  ||
        er < 0  ||  er >= nRows  ||  ec < 0  || ec >= nCols  ||
        maze[sr][sc] != '.'  ||  maze[er][ec] != '.')
        return false;
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = '#';
    if (maze[sr][sc + 1] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
            return true;
    }
    if (maze[sr + 1][sc] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
            return true;
    }
    if (maze[sr][sc - 1] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
            return true;
    }
    if (maze[sr - 1][sc] == '.')
    {
        if(pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
            return true;
    }
    return false;
}


//int main()
//{
//    std::string maze[10] = {
//        "XXXXXXXXXX",
//        "X...X..X.X",
//        "X..XX....X",
//        "X.X.XXXX.X",
//        "XXX......X",
//        "X...X.XX.X",
//        "X.X.X..X.X",
//        "X.XXXX.X.X",
//        "X..X...X.X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10,10, 4,3, 1,8))
//        std::cout << "Solvable!" << std::endl;
//    else
//        std::cout << "Out of luck!" << std::endl;
//}
//
//
