#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>

using namespace std;
#ifndef COV_19
#define COV_19
#include <vector>
 #include "Sstring.h"
//
// Created by bhaa on 15/4/2022.
//

 
class Covid{

public:
     
    Covid(const string& a,int ll):dadstring(new string(a)),mys(a),l(ll),P(0){

    }
    Covid(const Sstring& a,int ll):dadstring(a),mys(*a),l(ll),P(0){

    }
    Covid( Covid &c):dadstring(c.getString()),mys(c.getCopyOfMys()),l(c.getL()),P(0),typ(c.getType()){

    }
    virtual~Covid(){}
    virtual double getH(const Covid &other);
    virtual double getF(const Covid &other);
    virtual double getP()const;
    virtual Sstring& getString();
    virtual Sstring getSstringNonRef(){
        return dadstring;
    }
    virtual Sstring* getStringpointer(){return &dadstring;}
    int getL()const;
    string& getmys();
    string getCopyOfMys(){return mys;}
    int RefCountOfMyDadString()const;
    void setP(double pp){P=pp;}
    virtual char getType()const{
        return typ;
    }
    virtual void makeChange(){   
    }
     
    const string getmysconst()const{
        const string s1 = mys;
        return s1;}
    friend ostream& operator<<(ostream& os, const Covid& n){
        char type = n.getType();
        int lenn = n.getmysconst().length();
        os<<type<<" ";
        for(int i=0;i<lenn;i++){
            os<<n.getmysconst()[i]<<" ";
        }
         
        return os;
    }
    void setmys(const string &t){
        mys = t;
    }
    
private:
    Sstring dadstring;
    string mys;
    int l;
    double P;

protected:
    char typ;   

       


};









#endif //COV_19