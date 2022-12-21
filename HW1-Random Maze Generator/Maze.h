
#ifndef Maze_h
#define Maze_h
#include "DynTemplatedStack.h"
#include "DynTemplatedStack.cpp"
struct cell{
    int l_wall, r_wall, u_wall, d_wall, coord_x, coord_y;
    bool isVisited, isVisitedPath;
    
    /*cell::*/cell(){
        l_wall = 1;
        r_wall = 1;
        u_wall = 1;
        d_wall = 1;
        isVisited = false;
        isVisitedPath = false;
        
    }
};

class Maze{
public:
    Maze(){};
    Maze(const int &r, const int &c, int numID); //Default constructor
    ~Maze(); //Destructor
    void setID(int intID);
    bool isValid(const int &row, const int &col, const int &totalRow, const int &totalCol) const;
    bool isValidDirection(const int &row, const int &col, const int &totalRow, const int &totalCol) const;
    char randWall(const int &row, const int &col, const int &totalRow, const int &totalCol) const;
    char randDirection(const int &row, const int &col, const int &totalRow, const int &totalCol) const;
    void wallBreaker(int &row, int &col, const char &wall);
    void mazeGenerator(const int &totalRow, const int &totalCol);
    cell returnCell(const int &row, const int &col) const;
    int returnMazeID();
    const Maze & operator=(const Maze & rhs);
    void pathFinder(const int &entry_x, const int &entry_y, const int &exit_x, const int &exit_y, const int &totalRow, const int &totalCol, Stack<cell> &mazeStach);
    
private:
    int row, col, mazeID;
    cell ** matrix;
};



#endif /* Maze_h */
