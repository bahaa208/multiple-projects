#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;
#ifndef DELTA_
#define DELTA_
 
 
//
// Created by bhaa on 15/4/2022.
//

 
class Delta: virtual public Covid{

public:
     
     
    Delta(const string& aa,const Sstring& a,int ll):Covid(a,ll){
        double d = ll;
        d=1/d;
        this->setP(d);
        this->typ = 'd';
        setmys(aa);
    }
    Delta(const Sstring& a,int ll):Covid(a,ll){
        double d = ll;
        d=1/d;
        this->setP(d);
        this->typ = 'd';
    }
     
    ~Delta(){}
     
    virtual char getType()const{
        return 'd';
    }
     
    virtual void makeChange();
private:

};

 
#endif //DELTA_