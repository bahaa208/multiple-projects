#include "truck.h"

registerInFactory<Vehicle, Truck> rtt("truck");
Truck* Truck::createInstance(){
    
    return new Truck();
}

int Truck::how_much_box_to_put(string name_Of_Place){
        int size = count_of_box_in_place.size();
        for(int i=0;i<size;i++){
            if(count_of_box_in_place[i].first==name_Of_Place){
                return count_of_box_in_place[i].second;

            }
        }
        return 0;
    }
void Truck::putAllInformation(string na,Point l,string sta,std::vector<string> places,double curs,int countb,double speed){
        this->setName(na);
        this->setLocation(l);
        this->setStat(sta);
        takeInformtion(places);
        this->setAngle(curs);
        this->count_of_all_box = countb;
        this->setSpeed(speed);
        NumberBox();

    }
void Truck::update(){
        if(getStat()=="Off road"|| getStat() == "stop"){return;}
        Polar_vector pv;
        gotTo = false;
        pv.theta = to_radians(getAngle());
        pv.r = static_cast<double>(getSpeed())/100;
        
        Cartesian_vector cv(pv);
        Point oldLocation = getLocation();
         
        setLocation(Point(oldLocation.x+cv.delta_x,oldLocation.y+cv.delta_y));
        if(getDistance(getLocation(),getNextLocation().getLocation())<=getSpeed()){
            getNextLocation().takeBox(how_much_box_to_put(getNextLocation().getName()));
            count_of_all_box-=how_much_box_to_put(getNextLocation().getName());
            moveNext();
            setStat("Parked");
            gotTo = true;

        }
        else{setStat("Moving to...");}
    }

void Truck::takeInformtion(std::vector<string> places){
        
        int size = places.size();
        for(int i=0;i<size;i++){
            string S, T;  // declare string variables  
            stringstream X(places[i]); // X is an object of stringstream that references the S string  
            if(i==0){
                // use while loop to check the getline() function condition  
                short ss=-1;
                while (std::getline(X, T, ',')) {  
                    /* X represents to read the string from stringstream, T use for store the token string and, 
                    ' ' whitespace represents to split the string where whitespace is found. */  
                    ss++;
                    if(ss==0){get_from.first=T;}
                    else{get_from.second=T;}
                    
                }
            }
            else{
                short s=-1;

                string copname;
                // use while loop to check the getline() function condition  
                cllock c1;
                int countbox;
                while (std::getline(X, T, ',')) {  
                    /* X represents to read the string from stringstream, T use for store the token string and, 
                    ' ' whitespace represents to split the string where whitespace is found. */  
                    s++;
                    string nam;
                    if(s==0){
                        copname = T;
                    }
                    if(s==1){
                        stringstream cc(T)  ;
                        std::getline(cc, c1.hour, ':');
                        
                        std::getline(cc, c1.min, ':');
                         
                        
                        
                    }
                    if(s==2){
                        countbox = stoi(T);

                         
                    }
                    if(s==3){
                         
                        stringstream cc(T)  ;
                        std::getline(cc,c1.to_h, ':');
                       
                        std::getline(cc,c1.to_m, ':');
                         
                         
                        places_toGo.push_back(pair<string,cllock>(copname,c1));
                        count_of_box_in_place.push_back(pair<string,int>(copname,countbox));
                         
                    }
                     
                }
            }
            
        } 
    
          
    }