#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;
#ifndef Omicron_
#define Omicron_
 
 
//
// Created by bhaa on 15/4/2022.
//

 
class Omicron: virtual public Covid{

public:
     
     
    Omicron(const Sstring& a,int ll):Covid(a,ll){
        double d = ll;
        d=2/d;
        this->typ = 'o';
        this->setP(d);
        
    }
    Omicron(const string& aa,const Sstring& a,int ll):Covid(a,ll){
        double d = ll;
        d=2/d;
        this->typ = 'o';
        this->setP(d);
        this->setmys(aa);
    }
     
    ~Omicron(){}
     
    virtual char getType()const{
        return 'o';
    }
    virtual void makeChange();
private:

};

 
#endif //Omicron_