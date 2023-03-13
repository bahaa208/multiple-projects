#include "Cov.h"
#include "Alpha.h"
#include <stdio.h>
#include <stdlib.h>




void Alpha::makeChange(){
    int k = rand() % 100 +1;
    int kk = this->getP()*100;
    int lenn = this->getmys().length();
    
    if(k<=kk){
            
        stringstream ss;
        for(int i=0 ;i< lenn;i++){
            if( this->getmys()[i]=='A'){
                 
                ss<<"T";
            }
            else{
                if( this->getmys()[i]=='T'){
                    ss<<"A";
                }
                else{
                    ss<<this->getmys()[i];
                }
            }
            
        }
         
        string s1;
        ss>>s1;
        this->setmys(s1);
    }
}