#include <iostream>
using namespace std;
#include <cstdlib>
#include "Cov.h"
#include "Delta.h"
#include "Omicron.h"
#include "Alpha.h"
#include <vector>
#include<algorithm>
#include <fstream>
 
#ifndef FileRead_H

class FileRead {
private:
    vector<Covid*> vectorOfCovid;/* vector of  pointer of Delta ,Omicron,Alpha */
    vector<Sstring> vectorStr;/* the strings that evrey one of it we caunt the refre..*/
    int ourLoop;/* long of the loop */
    Covid *gool;/* the gool string that we search */
    int numberOfElement;/* how much of element we have */
    int sizeOfString;/* lenght of string*/
    Covid** theStrongestStringEver;/* we save the strongest string evrey loop */
public:
    FileRead(const char* one,const char* two); 
    /* this function replaced the charcter of the string by T~C ... 
    every one have his legall change.*/ 
    ~FileRead(); 
    /* the dectractor */
    void Do(); /* her we run inside the loop */
    void makeChangerfomInside();/* this function replaced the charcter of the string by T~C ... 
every one have his legall change.*/

    void makeChangeFroGroup();/* in this function we make new two element,for to string we build anew by take aport of them 
 and find the most to weak and we replace */
    bool CheckIfThereIStrong(); /* and the other function we can know what they doing by the name 
    
    
    
    
    
    */
    ostream&  pRint(ostream& os) {
        for(int j =0 ;j<numberOfElement;j++){
            os<<*vectorOfCovid[j]<<" "<<vectorStr[j].getCountOfREf()-1<<endl;
        }
         
        os<<endl;
        
        os<<**theStrongestStringEver;
        return os;


    }
    int FindTheMostWeak_Index(int firstOrSecond);
    int FindTheMostStrongest_Index();
    friend ostream& operator<<(ostream& os,FileRead& n){
        return n.pRint(os);

    }
         
        


     
};


#endif //FileRead_H