#include "chopper.h"

registerInFactory<Vehicle, Chooper> rch("chooper");
Chooper* Chooper::createInstance(){
    
    return new Chooper();
}

void Chooper::update(){
    if(getStat()=="Off road"){return;}
    Polar_vector pv;
    static int countOfViset = 0;
    pv.theta = to_radians(getAngle());
    pv.r = static_cast<double>(getSpeed())/100;
        
    Cartesian_vector cv(pv);
    Point oldLocation = getLocation();
    
    setLocation(Point(oldLocation.x+cv.delta_x,oldLocation.y+cv.delta_y));
    findTruckToSteal();
    

}
void Chooper::findTruckToSteal(){
        int size = allT->size();
        for(int i=0;i<size;i++){
            if(longScanner>=getDistance(getLocation() , (*allT)[i]->getLocation()) ){
                (*allT)[i]->stelIt();
                increase_Dic_LongScanner(1);
                setStat("Stopped");
                return;
            }

        }
    }
void Chooper::Print(){
        if(getStat()=="Off road"){return;}
         
        double num = getSpeed();
        stringstream stream;  
        // Set precision level to 3
        stream.precision(2);
        stream << fixed;
    
        // Convert double to string
        stream<<num;  
        cout<<"Chopper "<<getName()<<" at ";
        getLocation().print();
         
        cout<<" , Heading on course "<<getAngle() <<" deg, "<< "speed "<<stream.str()<<"km/h"<<"\n";
        
    }