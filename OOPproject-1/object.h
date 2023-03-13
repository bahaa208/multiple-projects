#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <memory>
#include "Geometry.h"
using namespace std;
#ifndef OBJECT_H_
#define OBJECT_H_
#include <vector>
#define intercity  	    0
#define centraal     1
#define stad    2
//
// Created by bhaa on 21/6/2022.
//

 
class Object{

public:
     
    Object(){

    }
    ~Object(){

    }
    virtual string getName()const{
        return name;
    }
    virtual Point getLocation()const{
        return location;
    }
    virtual void setName(string a){
        name= a;
    }
    virtual void setLocation(Point a){
        location = a;
    }
    virtual void setType(string t){type = t;}
    string getType()const{
        return type;
    }
    virtual void Print(){}
    
private:
    string name;
    Point location;
    string type;
    

};









#endif //OBJECT_H_