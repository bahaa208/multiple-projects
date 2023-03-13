//
// Created by bhaa on 21/6/2022.
//
#include "vehicle.h"
#include "factory.h"
#include <cmath>
using namespace std;
#ifndef TROOPER_H_
#define TROOPER_H_

/*
shared_ptr<Shape> s1 = genericFactory<Shape>::instance().create("Trooper"); do this inside the modle ..

*/

 

class Trooper : public Vehicle{

public:
     
    
    Trooper(){done=false;setType("trooper");}
    ~Trooper(){

    }
    
    
  
    static Trooper *  createInstance();
    
    int destination(string nameOfWarehouse){
        if(getWarebyName(nameOfWarehouse).getName()=="null"){return 0;}
        setNextLocation(getWarebyName(nameOfWarehouse));
        return 1;
    }
    void setCameFrom(string s){
        cameFrom = s;
    }
    int currentware(string nameOfWarehouse){
        if(getWarebyName(nameOfWarehouse).getName()=="null"){return 0;}
        setLocation(getWarebyName(nameOfWarehouse).getLocation());
        return 1;
    }
    
     
    void update();
    void Print();
    
private:
    string cameFrom;
    bool done;

    
    


     
};

#endif //TROOPER_H_