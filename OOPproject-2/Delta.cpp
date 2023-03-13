#include "Cov.h"
#include "Delta.h"
#include <stdio.h>
#include <stdlib.h>




void Delta::makeChange(){
    int k = rand() % 100 +1;
    int kk = this->getP()*100;
    int lenn = this->getmys().length();
    if(k<=kk){
            
        stringstream ss;
        for(int i=0 ;i< lenn;i++){
            if( this->getmys()[i]=='C'){
                 
                ss<<"G";
            }
            else{
                if(this->getmys()[i]=='G'){
                    ss<<"C";
                }
                else{
                    if(this->getmys()[i]=='A'){
                        ss<<"T";
                    }
                    else{
                        ss<<this->getmys()[i];
                    }
                }
            
            }
             
            
        }
         
        string s1;
        ss>>s1;
        this->setmys(s1);
    }
}