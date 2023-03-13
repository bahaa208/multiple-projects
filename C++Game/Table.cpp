//
// Created by bhaa on 03/12/2021.
//

#include <iostream>
#include "Table.h"
#define Not_Taken 0
#define Red_player 1
#define Blue_player 2
using namespace std;


Table::Table(){
    GameTable = new Hex*[Table_size];
    for(int i=0;i<Table_size;i++){
        GameTable[i] = new Hex[Table_size];
    }
    for(int i=0;i<Table_size;i++){
        for(int j=0;j<Table_size;j++){
            GameTable[i][j].val = Not_Taken;
            GameTable[i][j].getIn = false;
        }
    }
}
void Table::SetAllGetInFalse(){
    for(int i=0;i<Table_size;i++){
        for(int j=0;j<Table_size;j++){
            GameTable[i][j].getIn = false;
        }
    }
}
bool Table::Add_point(int i, int j, int player) {
    if(this->GameTable[j][i].val==0){
        this->GameTable[j][i].val= player;
        return true;
    }
    return false;
    
}

int Table::get_point(int i, int j) {
    return this->GameTable[i][j].val;
}
bool Table::getInBefore(const int i,const int j){
    return this->GameTable[i][j].getIn;
}
void Table::Print() {
    char player;
    for( int i=0; i< Table_size;i++){
        for(int k=0;k<i;k++){
            cout << " ";
        }
        for(int j=0;j<Table_size;j++){
            player = (this->GameTable[i][j].val == Not_Taken) ? 'O' : (this->GameTable[i][j].val == Red_player) ? 'R' : 'B';
            if(j < Table_size - 1)
                cout << player << " ";
            else
                cout << player << endl;
        }
    }
}
void Table::SetgetInBefore(const int i,const int j){
    this->GameTable[i][j].getIn = true;
}
bool Table::search_WithRec(const int i,const int j,int player){ /* this function check if the read player is wen the game */
    
    if(get_point(i,j)==player && !getInBefore(i,j)){
        if(player == Red_player && i==10){ /* if we got to the end  then we the red player won the game */
            return true;
        }
        if(player == Blue_player && j==10){ /* if we got to the end  then we the  blue player won the game */
            return true;
        }
        SetgetInBefore(i,j);
        if(i==0 && j>=0 && j<=10){   /* the first row */
            if(j<10 && j>0){ 
                return search_WithRec(i+1,j,player) || search_WithRec(i,j+1,player) || search_WithRec(i,j-1,player) || search_WithRec(i+1,j-1,player);
            }
            if(j==10){
                return search_WithRec(i+1,j,player) || search_WithRec(i,j-1,player) || search_WithRec(i+1,j-1,player);
            }
            if(j==0){
                return search_WithRec(i+1,j,player) || search_WithRec(i,j+1,player);

            }
        }
        if(i>0 && i<10 && j>=0 && j<=10){ /* if between the first and before the last */
            if(j<10 && j>0){
                return search_WithRec(i,j+1,player) || search_WithRec(i,j-1,player) ||search_WithRec(i-1,j,player) || search_WithRec(i-1,j+1,player) || search_WithRec(i+1,j,player) || search_WithRec(i+1,j-1,player);
            }
            if(j==0){
                return search_WithRec(i+1,j,player) || search_WithRec(i,j+1,player);
            }
            if(j==10){
                return search_WithRec(i,j-1,player) || search_WithRec(i+1,j-1,player) || search_WithRec(i+1,j,player) || search_WithRec(i-1,j,player);
            }
        }
        if(i==10 && j>=0 && j<=10){ /* if in the last row */
            if(j<10 && j>0){
                return search_WithRec(i,j-1,player) || search_WithRec(i-1,j,player) || search_WithRec(i-1,j+1,player) ||search_WithRec(i,j+1,player);
            }
            if(j==0){
                return search_WithRec(i-1,j,player) || search_WithRec(i-1,j+1,player) || search_WithRec(i,j+1,player);
            }
            if(j==10){
                return search_WithRec(i-1,j,player) || search_WithRec(i,j-1,player);
            }
            

        }

    }
    return false;

}
bool Table::ifWon(int player){
    if(player==Red_player){
        bool tf;
        for(int j=0;j<Table_size;j++){ /* check from the red side if red won the game */
            tf = search_WithRec(0,j,1);
            SetAllGetInFalse();
            if(tf){
                return true;
            }
        }
        return false;
    }
    bool tf;
    for(int i=0;i<Table_size;i++){  /* check from the blue side if the blue won */
        tf = search_WithRec(i,0,2);
        SetAllGetInFalse();
        if(tf){
            return true;
        }
    }
    return false;


}
int abcToi(char z){
    int i;
    switch(z){
        case 'A':
           i=0;
           break;
        case 'B':
           i=1;
           break;
        case 'C':
           i=2;
           break;
        case 'D':
           i=3;
           break;
        case 'E':
           i=4;
           break;
        case 'F':
           i=5;
           break;
        case 'G':
           i=6;
           break;
        case 'H':
           i=7;
           break;
        case 'I':
           i=8;
           break;
        case 'J':
           i=9;
           break;
        case 'K':
           i=10;
           break;
        default:
           i=-1;
    }
    return i;
}
int aToi(char x,char i2){
    int i;
    switch(x){
        
        case '1':
           i=0;
           break;
        case '2':
           i=1;
           break;
        case '3':
           i=2;
           break;
        case '4':
           i=3;
           break;
        case '5':
           i=4;
           break;
        case '6':
           i=5;
           break;
        case '7':
           i=6;
           break;
        case '8':
           i=7;
           break;
        case '9':
           i=8;
           break;
         
        default:
           i=-1;
    }
    if(i2 !='\0'){
        if(i2=='1'){
            i=10;
            return i;

        }
        i = 9;
    }
    return i;
}
int Table::play(){
    
    char in[4];
    int first = 2; /* first is the blue player */ 
    int i,j;
    in[0] = '\0';
    while(!ifWon(first)){
        if(in[0]=='Q'){ /* if someone Quit */
            
            if(first==Red_player){
                cout<<"R: QUIT"<<endl;
                Print();
                cout<<"B wins the game.\n";
                return 0;
            }
            cout<<"B: QUIT"<<endl;
            Print();
            cout<<"R wins the game.\n";
            return 0;
        }
        first = 2;
        Print();
        cout<<"B:"<<endl;
        cin>>in;
        i = abcToi(in[0]);
        j = aToi(in[1],in[2]);
        if(i!=-1 && j!=-1){
            Add_point(i,j,first);
             
        }
        
        if(in[0]=='Q'){ /* if someone Quit */
            
            if(first==Red_player){
                cout<<"R: QUIT"<<endl;
                Print();
                cout<<"B wins the game.\n";
                return 0;
            }
            cout<<"B: QUIT"<<endl;
            Print();
            cout<<"R wins the game.\n";
            return 0;
        }
        if(i==-1 || j== -1){
            cout<<"Invalid move; the game awaits a valid move.\n";
        }
        if(ifWon(first)){
            Print();
            cout<<"B wins the game.\n";
            return 0;
        }
        first = 1;
        Print();
        cout<<"R:"<<endl;
        cin>>in;
        i = abcToi(in[0]);
        j = aToi(in[1],in[2]);
        if(i!=-1 && j!=-1){
            Add_point(i,j,first);
             
        }



    }
    Print();
    cout<<"R win the game.\n";
    return 0;
    


}


 