//
// Created by bhaa on 21/6/2022.
//
#include "object.h"
#include "Geometry.h"

using namespace std;
#ifndef Warehouse_H_
#define Warehouse_H_
class Warehouse : public Object{

public:
     
    Warehouse(string name){
        setName(name);
         
    }
    Warehouse( ){
        setName("null");
         
    }
    Warehouse(const Warehouse& n ){
        setName(n.getName());
        setInventory(n.getInventory());
        setLocation(n.getLocation());
        setType(n.getType());
         
    }
    void setInventory(int c){
        Inventory= c;
    }
    int getInventory()const{
        return Inventory;
    }
    ~Warehouse(){}
    void takeBox(int y){
        setInventory(getInventory()-y);
    }
     void Print(){
        string inv = to_string(Inventory);
        cout<<"Warehouse "<<getName()<<" at position ";
        getLocation().print();
        cout<<", Inventory: "<<inv<<"\n";
    }
 
private:
     int Inventory;
};









#endif //Warehouse_H_