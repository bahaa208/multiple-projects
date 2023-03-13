#include "model.h"


Model *Model::GetInstance()
{
    /**
     * This is a safer way to create an instance. instance = new Model is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if(Model_==nullptr){
        Model_ = new Model( );
    }
    return Model_;
}

Model* Model::Model_= nullptr;







void Model::position(string name ,int x,int y, double speed){
        for(auto a:  *c_Vector_of_Chooper.get()){
            if(a->getName()==name){
                a->setLocation(Point(x,y));
                a->setSpeed(speed);
                return ;
            }
        }
        for(auto a: *t_Vector_of_Truck.get()){
            if(a->getName()==name){
                a->setLocation(Point(x,y));
                a->setSpeed(speed);
                return ;
            }
        }
        for(auto a: *r_Vector_of_Trooper.get()){
            if(a->getName()==name){
                a->setLocation(Point(x,y));
                a->setSpeed(speed);
                return ;
            }
        }
    }
void Model::destination(string namePolic ,string nameWare){
        
    Warehouse ware = getWare(nameWare);
    for(auto a: *r_Vector_of_Trooper.get()){
        if(a->getName()==namePolic){
            a->setNextLocation(ware);
                
            return ;
        }
    }
}
void Model::course(string name ,int ang, double speed){
    for(auto a:  *c_Vector_of_Chooper.get()){
        if(a->getName()==name){
            a->setAngle(ang);
            a->setSpeed(speed);
            return ;
        }
    }
    for(auto a: *t_Vector_of_Truck.get()){
        if(a->getName()==name){
            a->setAngle(ang);
            a->setSpeed(speed);
            return ;
        }
    }
    for(auto a: *r_Vector_of_Trooper.get()){
        if(a->getName()==name){
            a->setAngle(ang);
            a->setSpeed(speed);
            return ;
        }
    }
}
void Model::someoneNew(){
    
    std::shared_ptr<vector<Truck*> > al(new vector<Truck*>());
    
    for(auto a: *t_Vector_of_Truck.get()){
        al->push_back((Truck*)a.get());
        
    }
    for(auto a:  *c_Vector_of_Chooper.get()){
        a->setAllTruck(al);
    }
    for(auto a: *t_Vector_of_Truck.get()){
        a->allTheWarehouse(w_Vector_of_wareHouse);
    }
    for(auto a: *r_Vector_of_Trooper.get()){
        a->allTheWarehouse(w_Vector_of_wareHouse);
    }
}