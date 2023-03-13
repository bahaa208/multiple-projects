//
// Created by bhaa on 15/1/2022.
//


#include "Element.h"

template <typename AnyType>
Element<AnyType> ::Element(){this->rank = 0;}
 
template <typename AnyType>
Element<AnyType> ::Element(const Element<AnyType> &other){
    this->setRank( other.getRank()) ;
    this->x.clear();
    this->f.clear();
    int ii = other.get_X().size();
    int jj = other.get_F().size();
    for(int i=0;i<ii;i++){
        this->x.push_back(other.get_X()[i]) ;
    }
    for(int i=0;i<jj;i++){
        this->f.push_back(other.get_F()[i]) ;
    }
     
     
     
}
template <typename AnyType>
int Element<AnyType> ::getRank()const{
    return this->rank;

}
template <typename AnyType>
vector<AnyType>& Element<AnyType> ::getX(){
    return this->x;
}
template <typename AnyType>
vector<AnyType>& Element<AnyType> ::getF(){
    return this->f;
}
template <typename AnyType>
void Element<AnyType> ::setX(vector<AnyType> xx){
    this->x.clear();
    for(int i=0;i<(int)xx.size();i++){
        this->x.push_back(xx[i]);
    }

}
template <typename AnyType>
void Element<AnyType> ::setF(vector<AnyType> ff){
    this->f.clear();
    for(int i=0;i<(int)ff.size();i++){
        this->f.push_back(ff[i]);
    }
}
template <typename AnyType>
void Element<AnyType> ::setRank(int r){
    this->rank = r;
}
 