//
// Created by bhaa on 21/6/2022.
//
#include "vehicle.h"
#include "factory.h"
#include <cmath>
#include "truck.h"

using namespace std;
#ifndef Chooper_H_
#define Chooper_H_

/*
shared_ptr<Shape> s1 = genericFactory<Shape>::instance().create("Chooper"); do this inside the modle ..

*/

 

class Chooper : public Vehicle{

public:
     
    
    Chooper(){done=false;setType("chooper");longScanner = 2;}
    ~Chooper(){

    }
    
    
  
    static Chooper *  createInstance();
    
    void increase_Dic_LongScanner(int i){
        if(i==1){
            if(longScanner<20){
                longScanner++;
            }
        }
        else{
            if(longScanner>0){
                longScanner--;
            }
        }
    }
    void setCameFrom(string s){
        cameFrom = s;
    }
    void setAllTruck(std::shared_ptr<vector<Truck*> > al){
        allT = al;
    }
    void findTruckToSteal();


    
    /* should use traget  */
    void update();
    void Print();
    
    
private:
    string cameFrom;
    bool done;
    int longScanner;
    std::shared_ptr<vector<Truck*> > allT;
    
    
    


     
};

#endif //Chooper_H_