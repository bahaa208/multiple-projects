//
// Created by bhaa on 21/6/2022.
//
#include "model.h"
#include "view.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <exception>
 
#include <limits>
#include <fstream>
using namespace std;
#ifndef COTROOLER_H_
#define COTROOLER_H_
 
struct MyException : public exception {
   string name;
   int i;
    MyException(string s1,int ii):name(s1),i(ii){};
   const char * what () const throw () {
        if(i){
            string sa =  " is inside the network.\n";
            sa = name+sa;
            return sa.c_str() ;

        }
       string sa =  " is not inside the network.\n";
       sa = name+sa;
      return sa.c_str() ;
   }
};
/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/

class Controller {
public:	
	Controller():view_ptr(std::make_shared<View>()),time(0){
        
    }
	~Controller(){}

	// creates View object, runs the program by accepting user commands, then destroys View object
	void run(int argc, char* argv[]);
    int readFile(int argc, char* argv[]);
    string SplitString(string s){
        int i;
        string news;
        for(i=0;i<s.length();i++){
            if(s[i]!=')'&&s[i]!='('&&s[i]!=','){
                news+=s[i];
            }

        }
        return news;
    }
    string stringUntulsomthing(string s){
        int i;
        string news;
        for(i=0;i<s.length();i++){
            if(s[i]!=')'&&s[i]!='('&&s[i]!=','){
                news+=s[i];
            }
            else {return news;}

        }
        return news;
    }
    int addWarehosee(const char* f){
        try{
         
            string myTexttt,s1 ;
    
            ifstream MyRead(f, ios::in);
            ifstream indata;
            indata.open(f); 
            if(!indata) { // file couldn't be opened
                cerr << "ERROR opening the specified file."<<endl;
                return 0;
            }
            
             
             
            string Tt;
            //    string name, int x,int y,int Inventory
            while(getline (indata, myTexttt)){
                stringstream Xx(myTexttt);
                string name;
                int x,y,Inventory;


               
             
                 
                 
                string word;
                int num = 0;
                while (Xx >> word) {
                    
                    if(num==0){
                        stringstream ccc(word);
                        ccc>>name;
                        name = SplitString(name);
                    }
                    if(num == 1){
                        stringstream ccc(SplitString(word));
                        ccc>>x;
                    }
                    if(num == 2){
                        stringstream ccc(SplitString(word));
                        ccc>>y;
                    }
                    if(num == 3){
                        stringstream ccc(SplitString(word));
                        ccc>>Inventory;
                    }
                    num++;
                    
                    
                    
                     
                }
                Model::GetInstance()->addWarehose(name,x,y,Inventory);
                 
               
            }
            // Close the file
            MyRead.close();
            indata.close();
        }
        catch(...){
            cerr << "ERROR1: Invalid input.";
            return 0;
            
        }
        return 1;



    }
    int addTruckk(const char* f){
        try{
         
            string myTexttt,s1 ;
            stringstream Name(f);
            ifstream MyRead(f, ios::in);
            ifstream indata;
            indata.open(f); 
            if(!indata) { // file couldn't be opened
                cerr << "ERROR opening the specified file."<<endl;
                return 0;
            }
            
             
             
            string Tt;
            string name;
            Name>>name;
            string nameWare;
            int c=0;
            std::vector<string> places;
            //    string name, int x,int y,int Inventory
            while(getline (indata, myTexttt)){
                stringstream Xx(myTexttt);
                
                if(!c){nameWare = stringUntulsomthing(myTexttt);}
                c++;


               
             
                 
                 
                places.push_back(myTexttt);
                
                 
               
            }
            Model::GetInstance()->addTruck(name,nameWare,Point(0,0),"null", places,0,0,100);
            // Close the file
            MyRead.close();
            indata.close();
        }
        catch(...){
            cerr << "ERROR1: Invalid input.";
            return 0;
            
        }
        return 1;
    }
private:
	shared_ptr<View> view_ptr;
    int time;
};









#endif //COTROOLER_H_