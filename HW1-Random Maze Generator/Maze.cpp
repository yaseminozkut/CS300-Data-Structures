
#include "Maze.h"
#include "randgen.h"

using namespace std;

Maze::Maze(const int &r, const int &c, int numID){
    row = r;
    col = c;
    mazeID = numID;
    matrix = new cell * [row];

    for (int i = 0; i<row; i++)
        matrix[i] = new cell[col];
    
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            matrix[i][j].coord_x =j;
            matrix[i][j].coord_y =i;
        }
    }
}

Maze::~Maze()
{
    for (int i = 0; i < row; i++) {
        delete [] matrix[i];
        
    }
    delete [] matrix;
    mazeID =0;
}
void Maze::setID(int intID){
    mazeID = intID;
}
bool Maze::isValid(const int &row, const int &col, const int &totalRow, const int &totalCol) const{
    if(row < totalRow && row>=0 && col < totalCol && col >=0 && matrix[row][col].isVisited == false){
        return true;
    }
    else{
        return false;
    }
}
bool Maze::isValidDirection(const int &row, const int &col, const int &totalRow, const int &totalCol)const{
    if(row < totalRow && row>=0 && col < totalCol && col >=0 && matrix[row][col].isVisitedPath == false){
        return true;
    }
    else{
        return false;
    }
}

char Maze::randWall(int const &row, const int &col, const int &totalRow, const int &totalCol) const{
    char direction[4];
    int dirIdx = -1;
    for(int i=-1; i<=1; i++){
        if(i!=0){
            if(isValid(row, col+i, totalRow, totalCol)==true){
                dirIdx++;
                if(i==-1) direction[dirIdx]='l';
                else direction[dirIdx]='r';
            }
        }
        
        else{
            for(int k=-1; k<=1; k+=2){
                if(isValid(row+k, col, totalRow, totalCol)==true){
                    dirIdx++;
                    if(k==-1) direction[dirIdx]='d';
                    else direction[dirIdx]='u';
                }
            }
        }
    }
    if(dirIdx != -1){
        RandGen rand;
        int idx = rand.RandInt(dirIdx+1);
        return direction[idx];
    }
    else
        return '0';
}

char Maze::randDirection(int const &row, const int &col, const int &totalRow, const int &totalCol) const {
    char direction[4];
    int dirIdx = -1;
    for(int i=-1; i<=1; i++){
        if(i!=0){
            if(isValidDirection(row, col+i, totalRow, totalCol)==true){
                //dirIdx++;
                if(i==-1 && matrix[row][col].l_wall == 0){
                    dirIdx++;
                    direction[dirIdx]='l';
                }
                else if (i==1 && matrix[row][col].r_wall == 0){
                    dirIdx++;
                    direction[dirIdx]='r';
                }
            }
        }
        
        else{
            for(int k=-1; k<=1; k+=2){
                if(isValidDirection(row+k, col, totalRow, totalCol)==true){
                    //dirIdx++;
                    if(k==-1 && matrix[row][col].d_wall == 0){
                        dirIdx++;
                        direction[dirIdx]='d';
                    }
                    else if (k==1 && matrix[row][col].u_wall == 0){
                        dirIdx++;
                        direction[dirIdx]='u';
                    }
                }
            }
        }
    }
    if(dirIdx != -1){
        RandGen rand;
        int idx = rand.RandInt(dirIdx+1);
        return direction[idx];
    }
    else
        return '0';
}

void Maze::wallBreaker(int &row, int &col, const char &wall){
    if(wall == 'l'){
        matrix[row][col].l_wall = 0;
        matrix[row][col-1].r_wall = 0;
        col--;
    }
    else if(wall == 'r'){
        matrix[row][col].r_wall = 0;
        matrix[row][col+1].l_wall = 0;
        col++;
    }
    else if(wall == 'u'){
        matrix[row][col].u_wall = 0;
        matrix[row+1][col].d_wall = 0;
        row++;
    }
    else if(wall == 'd'){
        matrix[row][col].d_wall = 0;
        matrix[row-1][col].u_wall = 0;
        row--;
    }
}

void Maze::mazeGenerator(const int &totalRow, const int &totalCol){
    Stack<cell> mazeStack;
    int totalUnvisited =totalRow*totalCol;
    int x = 0;
    int y = 0;
    mazeStack.push(matrix[y][x]); //push 0,0 first
    matrix[y][x].isVisited = true;
    totalUnvisited--;
    while(totalUnvisited>0){
        char randomWall = randWall(y, x, totalRow, totalCol);
        if (randomWall != '0'){
            wallBreaker(y, x, randomWall);
            mazeStack.push(matrix[y][x]);
            matrix[y][x].isVisited = true;
            totalUnvisited--;
        }
        else{
            mazeStack.pop();
            x=mazeStack.top().coord_x;
            y=mazeStack.top().coord_y;
        }
    }
}

cell Maze::returnCell(const int &row, const int &col) const{
    return matrix[row][col];
}

int Maze::returnMazeID(){
    return mazeID;
}

void Maze::pathFinder(const int &entry_x, const int &entry_y, const int &exit_x, const int &exit_y, const int &totalRow, const int &totalCol, Stack<cell> &mazeStack){
    
    //Stack<cell> mazeStack;
    int x = entry_x;
    int y = entry_y;
    matrix[y][x].isVisitedPath = true;
    mazeStack.push(matrix[y][x]);
    while(mazeStack.top().coord_x != exit_x || mazeStack.top().coord_y != exit_y){
        char direction = randDirection(y, x, totalRow, totalCol);
        
        if (direction != '0'){
            if(direction == 'l')
                x--;
            else if(direction == 'r')
                x++;
            else if(direction == 'u')
                y++;
            else if(direction == 'd')
                y--;
            matrix[y][x].isVisitedPath = true;
            mazeStack.push(matrix[y][x]);
        }
        else{
            mazeStack.pop();
            x=mazeStack.top().coord_x;
            y=mazeStack.top().coord_y;
        }
    }
}


const Maze & Maze::operator=(const Maze &rhs){
    if(this==&rhs){
        return *this;
    }
    row = rhs.row;
    col = rhs.col;
    mazeID = rhs.mazeID;
    matrix = new cell * [row];

    for (int i = 0; i<row; i++)
        matrix[i] = new cell[col];
    
    for (int i=0; i<row; i++){
        for (int j=0; j<col; j++){
            matrix[i][j]=rhs.matrix[i][j];
        }
    }
    
    return *this;
}
