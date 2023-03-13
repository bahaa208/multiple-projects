//
// Created by bhaa on 21/6/2022.
//
#include <bits/stdc++.h>
#include "object.h"
#include "warehouse.h"
#include "Geometry.h"
#include <cmath>
using namespace std;
#ifndef VEHICLE_H_
#define VEHICLE_H_
class Truck;
class Vehicle : public Object{

public:
     
    Vehicle(){
        
        AllWarehouse = nullptr;
    }
    ~Vehicle(){

    }
    string getStat()const{
        return status;
    }
    
    void setStat(string a){
        status= a;
    }
    virtual void setCountBox(int i){}
    double getSpeed()const{
        return speed;
    }
    
    void setSpeed(double a){
        speed= a;
    }
    double getAngle()const{
        return angle;
    }
    
    void setAngle(double a){
        angle= a;
    }
    virtual void putAllInformation(string na,Point l,string sta,std::vector<string> places,double curs,int countb,double speed){
         

    }
    virtual void update(){

    }
    virtual void setAllTruck(std::shared_ptr<vector<Truck*> > al){
       
    }
    void setNextLocation(Warehouse a){
        nextLocation = a;
    }
    Warehouse getNextLocation(){
        return nextLocation;
    }
     
     
    void setTarget(Point p){
        target = p;
    }
    Point getTarget( ){
        return target ;
    }
    static double getDistance(const Point &p1,const Point &p2){
        return sqrt( ((p2.x-p1.x)*(p2.x-p1.x)) + ((p2.y-p1.y)*(p2.y-p1.y)) );
    }
    double farFrom(Vehicle v){
        return getDistance(getLocation(),v.getLocation());
    }
    static bool compareP(Point me ,Warehouse i1, Warehouse i2){
        return (getDistance(me,i1.getLocation()) < getDistance(me,i2.getLocation() ));
    }
    void allTheWarehouse(shared_ptr<vector<Warehouse> > v1){
        AllWarehouse = std::make_shared<vector<Warehouse> >(*v1);
        Point me = getLocation();
        sort((*AllWarehouse).begin(), (*AllWarehouse).end(),[me]( Warehouse lhs, Warehouse rhs ){return Vehicle::compareP(me,lhs,rhs);});
        moveNext();


    }

    virtual void moveNext(){
        if(AllWarehouse==nullptr || AllWarehouse->size()==0){return;}
        static int ind = 0;
        const double pi = 2. * atan2(1., 0.);
        setNextLocation((*AllWarehouse)[ind]);
    
        double ang =( atan2(getNextLocation().getLocation().y-getLocation().y,getNextLocation().getLocation().x-getLocation().x)*180)/pi;
        setAngle(ang);
        
        ind = (++ind)%AllWarehouse->size();

    }
    std::shared_ptr<vector<Warehouse> > getAllW(){
        return AllWarehouse;
    }
    virtual void Print(){}
    Warehouse& getWarebyName(string name){
        int size = AllWarehouse->size();
        for(int i=0;i<size;i++){
            if((*AllWarehouse)[i].getName()==name){
                return (*AllWarehouse)[i];
            }
        }
        return NoneFound;

    }
    
private:
    string status;
    double angle;
    double speed;
    std::shared_ptr<vector<Warehouse> > AllWarehouse;
    Warehouse nextLocation;
    Warehouse NoneFound;
    Point target;
};









#endif //VEHICLE_H_