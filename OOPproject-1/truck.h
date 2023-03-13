//
// Created by bhaa on 21/6/2022.
//
#include "vehicle.h"
#include "factory.h"
using namespace std;
#ifndef TRUCK_H_
#define TRUCK_H_

/*
 
*/

 

class Truck : public Vehicle{

public:
    typedef struct cllock1
    {
        string hour;
        string min;
        string to_h;
        string to_m;
        
    } cllock; 
    Truck(string na,Point l,string sta,std::vector<string> places,double curs,int countb,double speed){
        this->setName(na);
        this->setLocation(l);
        this->setStat(sta);
        takeInformtion(places);
        this->setAngle(curs);
        this->count_of_all_box = countb;
        this->setSpeed(speed);

    }
    Truck(){gotTo=false;setType("truck");}
    Truck(const Truck & t):get_from(t.get_from),places_toGo(t.places_toGo),count_of_box_in_place(t.count_of_box_in_place){
        count_of_all_box = t.count_of_all_box;
        setType(t.getType());
        gotTo = t.gotTo;


     }
    ~Truck(){

    }
    void putAllInformation(string na,Point l,string sta,std::vector<string> places,double curs,int countb,double speed);
    void takeInformtion(std::vector<string> places);
    int how_much_box_to_put(string name_Of_Place);
    static Truck *  createInstance();
    void stelIt(){
        setStat("Off road");
        count_of_all_box = 0;
    }
     
    void update();
    /* warehouse : getname ,takeBox ,getlocation , */
    void Print(){
        if(getStat()=="Off road"){return;}
        cout<<"Truck "<<getName()<<" at ";
        getLocation().print();
        cout<<" , Heading to "<<getNextLocation().getName()<<", Crates: "<<count_of_all_box<<"\n";
    }
    void setCountBox(int i){
        count_of_all_box = i;
    }
    void NumberBox(){
        int sum=0;
        for(auto a: count_of_box_in_place){
            sum+=a.second;
        }
        setCountBox(sum);
    }
    
private:

    pair<string,string> get_from;
    std::vector<pair<string,cllock> > places_toGo;
    std::vector<pair<string,int> > count_of_box_in_place;
    int count_of_all_box;
    bool gotTo;
     

     
};

#endif //TRUCK_H_