#include "Cov.h"
//
// Created by bhaa on 15/4/2022.
//

 
double Covid::getH(const Covid &other){
    double egu = 0.0;
    string s1 = this->mys;
    string s2 = other.getmysconst();
    int lenth = s1.length();
    for(int i=0 ;i<lenth;i++){
        if(s1[i]==s2[i]){
            egu++;
        }
    }
    return egu;
     
}
double Covid::getF(const Covid& other){
    double f = getH(other)/l;
     
    return f;
}
double Covid::getP()const{
    return this->P;
}
Sstring& Covid::getString(){
    return dadstring;
}
int Covid::getL()const{return l;}
string& Covid::getmys(){
    return mys;
}
int Covid::RefCountOfMyDadString()const{
    return dadstring.getCountOfREf();
}