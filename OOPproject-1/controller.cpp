#include "controller.h"



void Controller::run(int argc, char* argv[]){
        int work = readFile(argc,argv);
        if(!work){
            cout<< "you have to put at least Truck file and WareHouse file.. \n";
            return;
        }
        cout<<"press exit or Exit to Exit\n\n";
        string Quit="";
        
        while(Quit!="EXIT" && Quit!="exit"){
            cout<<"\nTime "<<time<<": Enter command:";
            string in;
            int input=12;
            getline(cin, in);
            Quit= in;
            stringstream ss(in);
            string word,word1;
            ss>>word;
            
            if(word=="default"){input=0;}
            if(word=="size"){input=1;}
            if(word=="zoom"){input=2;}
            if(word=="pan"){input=3;}
            if(word=="show"){input=4;}
            if(word=="go"){input=5;}
            if(word=="status"){input=6;}
            if(word=="create"){input=7;}
            
            if(word=="attack"){input=8;}
            if(word=="stop"){input=9;}
            
            try{

                 
                if(input==0){view_ptr->defult();}

                else if(input==1){
                        int s;
                    ss>>s;
                    if(!view_ptr->setsize(s)){
                        cout<<"Error size .\n";
                    }
                }
                        
                else if(input==2){
                    int s;
                    ss>>s;
                    
                    if(!view_ptr->setSc(s)){
                        cout<<"Error zoom"<<s<<" .\n";
                    }
                }
                        
                else if(input==3){
                    int xx,yy;
                    ss>>xx;
                    ss>>yy;
                    view_ptr->pan(xx,yy);
                }
                    
                    
                else if(input==4){
                      view_ptr->show();

                }
                    
                else if(input==5){
                    Model::GetInstance()->update();
                    time++;
                }
                
                else if(input==6){
                        view_ptr->Status();
                }
                    
                else if(input==7) {
                    string name;
                    ss>>name;
                    string type;
                    ss>>type;
                    if(Model::GetInstance()->existingIn(name)){
                        throw MyException(name,1);
                    }

                    if(type=="Chopper"){
                         
                        string sx,sy;
                        ss>>sx;
                        ss>>sy;
                        sx = SplitString(sx);
                        sy = SplitString(sy);
                        Model::GetInstance()->addChooper(name,stoi(sx),stoi(sy),0,0);
                    }
                    if(type=="State_trooper"){
                        string nameOfWarehouse ;
                        ss>>nameOfWarehouse;
                        Model::GetInstance()->addTrooper( name,0,0 ,0, 0,  nameOfWarehouse);
                    }
                    //should check if he is in the system before add ;
                }
                    
                else if(input==8) {
                    string name;
                    ss>>name;
                    if(!Model::GetInstance()->existingIn(name)){
                        throw MyException(name,0);
                    }
                    Model::GetInstance()->attack(name);
                }
                
                else if(input==9){
                    Model::GetInstance()->stop();}
                    
                
                else{
                    if((word!= "exit" && word!="EXIT") && !Model::GetInstance()->existingIn(word)){
                        throw MyException(word,0);
                    }
                    string whatToDo;
                    ss>>whatToDo;
                    if(whatToDo=="course"){
                        double an,sp;
                        ss>>an;
                        ss>>sp;
                        Model::GetInstance()->course(word,an,sp);
                    }// ------
                    if(whatToDo=="position"){ 
                        double ax,ay,sp;
                        string axx,ayy,spp;

                        ss>>axx;
                        ss>>ayy;
                        ax = stoi(stringUntulsomthing(axx));
                        ay = stoi(stringUntulsomthing(ayy));
                        ss>>spp;
                        sp = stoi(spp);
                        Model::GetInstance()->position(word,ax ,ay ,sp);
                    }// ------
                    if(whatToDo=="destination"){ 
                        string nameW;
                        ss>>nameW;
                            
                        Model::GetInstance()->destination(word,nameW);
                    }// ------
                     
                    
                }

                 

            }
            catch(MyException& e){std::cout << e.what() ;}




        } 

 



}

int Controller::readFile(int argc, char* argv[]){
        bool go = true;
        bool go2 = false;
        const char* conWareHouse;
        std:: vector<const char*> vectorTruc;

        for(int ndx=1 ; ndx < argc; ++ndx) {
            try{
                if(go && argv[ndx][0]=='-' &&argv[ndx][1]=='w'){
                    ndx++;
                    conWareHouse = argv[ndx] ;
                    go = false;
                }
                if(go2 || (argv[ndx][0]=='-' &&argv[ndx][1]=='t')){
                    if(!go2)ndx++;
                    vectorTruc.push_back(argv[ndx]);
                    go2 = true;
                }
                 
            }
            catch(...){cout<<"Error with file .\n";return 0;}

            
            
        }
        addWarehosee(conWareHouse);
        for(auto a: vectorTruc){
            addTruckk(a);
        }
        if(go || !go2){
            return 0;
        }
        return 1;
    
}