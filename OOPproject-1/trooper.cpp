#include "trooper.h"

registerInFactory<Vehicle, Trooper> rt("trooper");
Trooper* Trooper::createInstance(){
    
    return new Trooper();
}

void Trooper::update(){
        if(done|| getStat() == "stop"){return;}
        Polar_vector pv;
        static int countOfViset = 0;
        pv.theta = to_radians(getAngle());
        pv.r = static_cast<double>(getSpeed())/100;
         
        Cartesian_vector cv(pv);
        Point oldLocation = getLocation();
        
        setLocation(Point(oldLocation.x+cv.delta_x,oldLocation.y+cv.delta_y));
        
        if(getDistance(getLocation(),getNextLocation().getLocation())<=getSpeed()){
            countOfViset++;
            moveNext();
            if(countOfViset>=getAllW()->size()){
                currentware(cameFrom);
                setStat("Off road");
                done=true;
            }

        }
        else{countOfViset++; setStat("Moving to...");if(countOfViset>=getAllW()->size()){done=true;}}

}

void Trooper::Print(){//State_trooper Cooper at (39.19, 10.40), Heading to Hamburg, speed 90.00 km/h

        double num = getSpeed();
        stringstream stream;  
        // Set precision level to 3
        stream.precision(2);
        stream << fixed;
    
        // Convert double to string
        stream<<num; 
        cout<<"State_trooper "<<getName()<<" at ";
        getLocation().print();
        cout<<" , Heading to "<<getNextLocation().getName()<<", speed "<<stream.str()<<"km/h"<<"\n";
    }