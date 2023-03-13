#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;
#ifndef ALPHA
#define ALPHA
 
 
//
// Created by bhaa on 15/4/2022.
//

 
class Alpha: virtual public Covid{

public:
     
    Alpha(const Sstring& a,int ll):Covid(a,ll){
        this->setP(0.37);
        this->typ = 'a';
    }
    Alpha(const string& aa,const Sstring& a,int ll):Covid(a,ll){
        this->setP(0.37);
        this->typ = 'a';
        this->setmys(aa);
    }
     
    ~Alpha(){}
    virtual char getType()const{
        return 'a';
    }
     
    
    virtual void makeChange();
private:

};

 
#endif //ALPHA