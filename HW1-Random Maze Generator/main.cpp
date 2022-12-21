
#include <iostream>
#include "Maze.h"
#include <fstream>
#include <vector>
#include "strutils.h"
using namespace std;

int main() {
    int numMaze, row, col;
    cout << "Enter the number of mazes: ";
    cin >> numMaze;
    cout << "Enter the number of rows and columns (M and N): ";
    cin >> row >> col;
    
    Maze * mazes = new Maze[numMaze];
    Maze temp;

    for(int i = 0; i<numMaze; i++){
        Maze maze(row,col,i+1);
        maze.mazeGenerator(row, col);
        temp = maze;
        mazes[i] = temp;
        
        ofstream out;
        string fileName = "maze_";
        string temp = itoa(i+1);
        fileName += temp;
        fileName += ".txt";
        out.open(fileName.c_str());
        
        out<< row << " " << col <<"\n";
        for (int i= 0; i<row; i++){
            for(int j=0; j<col; j++){
                cell temp = maze.returnCell(i, j);
                out << "x=" << temp.coord_x << " y=" << temp.coord_y << " l=" << temp.l_wall << " r=" << temp.r_wall << " u=" << temp.u_wall << " d=" << temp.d_wall << "\n";
            }
        }
    }

    int mazeID, entry_x, entry_y, exit_x, exit_y;
    cout << "\nEnter a maze ID between 1 and " << numMaze << " inclusive to find a path: ";
    cin >> mazeID;
    cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): ";
    cin >> entry_x >> entry_y;
    cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): ";
    cin>> exit_x >> exit_y;
    Stack<cell> mazeStack;
    Stack<cell> reverseStack;
    mazes[mazeID-1].pathFinder(entry_x, entry_y, exit_x, exit_y, row, col, mazeStack);
    
    while (!mazeStack.isEmpty()){
        cell temp = mazeStack.topAndPop();
        reverseStack.push(temp);
    }
    
    ofstream outPath;
    string fileNamePath = "maze_";
    string pathID = itoa(mazeID);
    string x_enter = itoa(entry_x);
    string y_enter = itoa(entry_y);
    string x_exit = itoa(exit_x);
    string y_exit = itoa(exit_y);
    fileNamePath = fileNamePath + pathID + "_path_" + x_enter + "_" + y_enter + "_" + x_exit + "_" + y_exit + ".txt";
    outPath.open(fileNamePath.c_str());
    
    
    while(!reverseStack.isEmpty()){
        int x= reverseStack.top().coord_x;
        int y= reverseStack.top().coord_y;
        outPath << x << " " << y << endl;
        reverseStack.pop();
    }
    
    return 0;
}

