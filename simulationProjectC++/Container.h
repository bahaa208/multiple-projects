#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;
#ifndef Container_H
#define Container_H
#include <vector>
#include "Element.cpp"
//
// Created by bhaa on 15/1/2022.
//
template <typename AnyType>
class Container
{
public:
     
    Container(int mew);
    ~Container();
    void addE(Element<AnyType> neww){list.push_back(neww);}
    int* ParetoRanking(vector<vector<AnyType> > listF); 
    bool isControl(vector<AnyType> f1,vector<AnyType> f2);
    void ElementsReordering(vector<Element<AnyType> >& elements);
    void ParetoSorting(vector<Element<AnyType> >& elements);
    vector<Element<AnyType> >& getElements(){
        return list;
    }
private:
    int size;
    vector<Element<AnyType> > list;


};









#endif //Container_H