#include <iostream>
using namespace std;
#define Not_Taken 0
#define Red_player 1
#define Blue_player 2
#define Table_size 11
#ifndef HEX_H
#include "Hex.h"
class Table {
private:
    Hex **GameTable;
public:
    Table();/*Game initialization,matrix set to default(empty value).*/
    ~Table(){
        for(int i=0;i<Table_size;i++){
            delete [] GameTable[i];
        }
    }
    bool getInBefore(const int i,const int j);
    void SetgetInBefore(const int i,const int j);
    void SetAllGetInFalse();
    bool search_WithRec(const int i,const int j,int player);
     
    bool Add_point(const int i,const int j,int player);/*value setter, 0,1 or 2 to each given vertex.*/
    int get_point(const int i,const int j);/*value getter.*/
    void Print();/*A function to print the Table.*/
    bool ifWon(int player);
    int play(); /* the function that manage the game */
};


#endif //HEX_H