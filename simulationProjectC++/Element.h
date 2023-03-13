#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;
#include <vector>
#ifndef ELEMENT_H
#define ELEMENT_H
 
//
// Created by bhaa on 15/1/2022.
//
template <typename AnyType>

                                         
class Element
{
public:
     
    Element();
    Element(const Element<AnyType> &other);  
    ~Element(){} 
    int getRank()const;
    vector<AnyType>& getX();
    vector<AnyType>& getF();
    vector<AnyType>  get_X()const{return x;};
    vector<AnyType>  get_F()const {return f;};
    
    void setX(vector<AnyType> xx);
    void setF(vector<AnyType> ff);
    void setRank(int r);

    Element<AnyType>& operator=( Element<AnyType> other){
    
        if (this == &other)
            return *this; 
        else{
            this->x.clear();
            this->f.clear();
            this->setRank( other.getRank()) ;
            int ii = other.getX().size();
            int jj = other.getF().size();
            for(int i=0;i<ii;i++){
                this->x.push_back(other.getX()[i]) ;
            }
            for(int i=0;i<jj;i++){
                this->f.push_back(other.getF()[i]) ;
            }
            return *this;
        }
         
    }
    friend bool operator<=(const Element<AnyType>& lhs, const Element<AnyType>& rhs){ return (lhs.getRank() <= rhs.getRank()); }
    friend bool operator<(const Element<AnyType>& lhs, const Element<AnyType>& rhs){ return (lhs.getRank() < rhs.getRank()); }
    friend bool operator>(const Element<AnyType>& lhs, const Element<AnyType>& rhs){ return (lhs.getRank() > rhs.getRank()); }
    friend ostream& operator<<(ostream& os, const Element<AnyType>& n){

        return os;
    }
    

private:
    int rank;
    vector<AnyType> x; // size of x == n  x =~ {v1,v2,v3..vn}
    vector<AnyType> f;// size of f == m  f =~ {v1,v2,v3..vn}


};
#endif //ELEMENT_H