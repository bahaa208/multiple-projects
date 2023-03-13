#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include "factory.h"
#include "truck.h"
#include "chopper.h"
#include "trooper.h"
using namespace std;
#ifndef MODEL_H_
#define MODEL_H_



class Model
{

    /**
     * The Model's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */

private:
    Model( ): w_Vector_of_wareHouse(new vector<Warehouse>()) ,
     t_Vector_of_Truck(new vector<shared_ptr<Truck> >()) ,
      r_Vector_of_Trooper(new vector<shared_ptr<Vehicle> >())  ,
       c_Vector_of_Chooper (new vector<shared_ptr<Vehicle> >()) 
    {
        addWarehose("Frankfurt", 40,10,100000);
    }
    shared_ptr<vector<Warehouse> > w_Vector_of_wareHouse;
    shared_ptr<vector<shared_ptr<Truck> > > t_Vector_of_Truck;
    shared_ptr<vector<shared_ptr<Vehicle> > > r_Vector_of_Trooper;
    shared_ptr<vector<shared_ptr<Vehicle> > > c_Vector_of_Chooper;
    
    

     

public:
    static Model* Model_;
    /**
     * Models should not be cloneable.
     */
    Model(Model &other) = delete;
    /**
     * Models should not be assignable.
     */
    
    void operator=(const Model &) = delete;
    /**
     * This is the static method that controls the access to the Model
     * instance. On the first run, it creates a Model object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static Model *GetInstance();
    /**
     * Finally, any Model should define some business logic, which can be
     * executed on its instance.
     */
    void update(){
         
        for(auto a:  *c_Vector_of_Chooper.get()){
            a->update();
        }
        for(auto a: *t_Vector_of_Truck.get()){
            a->update();
        }
        for(auto a: *r_Vector_of_Trooper.get()){
            a->update();
        }
    }
    void addChooper(string name, int x,int y ,double ang, double spee){
        shared_ptr<Vehicle> s2 = genericFactory<Vehicle>::instance()->create("chooper");
        s2->setName(name);
        s2->setLocation(Point(x,y));
        s2->setSpeed(spee);
        s2->setAngle(ang);
        c_Vector_of_Chooper->push_back(s2);
    }
    void addWarehose(string name, int x,int y,int Inventory){
        Warehouse s1;
        s1.setName(name);
        s1.setLocation(Point(x,y));
        s1.setInventory(Inventory);
        w_Vector_of_wareHouse->push_back(s1);
        
        someoneNew();


    }
    void printStatus(){
        
         
        for(auto a:  *c_Vector_of_Chooper.get()){
            if(a->getStat()!="Off road"){
                a->Print();
            }
            
        }
        for(auto a: *t_Vector_of_Truck.get()){
            if(a->getStat()!="Off road"){
                a->Print();
            }
        }
        for(auto a: *r_Vector_of_Trooper.get()){
            if(a->getStat()!="Off road"){
                a->Print();
            }
        }
        for(auto a: *w_Vector_of_wareHouse){
            a.Print();
        }
    
    }
    shared_ptr<Vehicle> getTrooper(string name){
        for(auto a: *r_Vector_of_Trooper.get()){
            if(a->getName()==name){
                return a;
            }

        }
        return nullptr;
    }
    Warehouse getWare(string name){
        Warehouse aa;
        for(auto a: *w_Vector_of_wareHouse){
            if(a.getName()==name){
                return  a;
            }

        }
        return aa;
    }
     
    
    double Far(Point p1, Point p2){
        
        double d = 999;
        try{
                d = sqrt( ((p2.x-p1.x)*(p2.x-p1.x)) + ((p2.y-p1.y)*(p2.y-p1.y)) );
        }
        catch(...){}
        return d;
    }
    string findInThisArea(double x,double y,double scaal){
        Point p1(x,y);
        stringstream ss;
        int j;
        int size = w_Vector_of_wareHouse->size();
        for(auto a:  *c_Vector_of_Chooper.get()){
            Point p2 = a->getLocation();
            if(Far(p1,p2)<=scaal){
                string name = a->getName();
                ss<<name[0];
                ss<<name[1];
                string s3;
                ss>>s3;
                return s3;
            }
        }
        
        for(auto a: *t_Vector_of_Truck.get()){
            Point p2 = a->getLocation();
            if(Far(p1,p2)<=scaal){
                string name = a->getName();
                ss<<name[0];
                ss<<name[1];
                string s3;
                ss>>s3;
                return s3;
            }
        }
        for(auto a: *r_Vector_of_Trooper.get()){
             Point p2 = a->getLocation();
            if(Far(p1,p2)<=scaal){
                string name = a->getName();
                ss<<name[0];
                ss<<name[1];
                string s3;
                ss>>s3;
                return s3;
            }
        }
         
        for(j=0 ;j<size;j++){
            Point p2 = (*w_Vector_of_wareHouse)[j].getLocation();
             
             if(Far(p1,p2)<=scaal){
                 
                string name = (*w_Vector_of_wareHouse)[j].getName();
                ss<<name[0];
                ss<<name[1];
                string s3;
                ss>>s3;
                return s3;
            }
        }
        return ".";


    }
    void attack(string name){
        for(auto a: *t_Vector_of_Truck.get()){
            if(a->getName()==name){
                ((Truck*)a.get())->stelIt();
            }
        }
    }
    void position(string name ,int x,int y, double speed);
    void destination(string namePolic ,string nameWare);
    void course(string name ,int ang, double speed);
    void someoneNew();
    void stop(){
    }
    void addTruck(string na,string nameW ,Point l,string sta,std::vector<string> places,double curs,int countb,double speed){
        shared_ptr<Vehicle> s1 = genericFactory<Vehicle>::instance()->create("truck");
        Point p1 = getWare(nameW).getLocation();
         
        s1->putAllInformation(na,p1,sta,places,curs,countb,speed);
     
        t_Vector_of_Truck->push_back(std::dynamic_pointer_cast<Truck>(s1));
        
        someoneNew();


    }
    void addTrooper(string name, int x,int y ,double ang, double spee,string nameOfWarehouse){
        shared_ptr<Vehicle> s2 = genericFactory<Vehicle>::instance()->create("trooper");
        s2->setName(name);
        s2->setLocation(Point(x,y));
        s2->setSpeed(spee);
        s2->setAngle(ang);
        r_Vector_of_Trooper->push_back(s2);
        someoneNew();
        ((Trooper*)s2.get())->currentware(nameOfWarehouse);
        
        
    }
    bool existingIn(string name){
        for(auto a:  *c_Vector_of_Chooper.get()){
            if(a->getName()==name){
                return true;
            }
            
        }
        for(auto a: *t_Vector_of_Truck.get()){
            if(a->getName()==name){
                return true;
            }
        }
        for(auto a: *r_Vector_of_Trooper.get()){
            if(a->getName()==name){
                return true;
            }
        }
        for(auto a: *w_Vector_of_wareHouse){
            if(a.getName()==name){
                return true;
            }
        }
        return false;
    }
      
};


#endif //MODEL_H_