//
// Created by bhaa on 21/6/2022.
//
#include "model.h"
 
using namespace std;
#ifndef VIEW_H_
#define VIEW_H_
 

class View {

public:
     
    View(double x= -10,double y = -10 ,double sc=2,double si= 25):Xaxic(x),Yaxic(y),scale(sc),size(si){
         
    }
     
     
    vector<int> numbers_For_graph(int c){
        //c = 1 ~ ser y
        vector<int> vec;
        if(c){
            int time = size/3;
            
            int i;
            vec.push_back(Yaxic);
            int t = Yaxic;
            for(i=0;i<time;i++){
                t = t +3*scale;
                vec.push_back(t);
                
            }
            return vec;
            
        }
        else{
            int time = size/3;
            
            int i;
            vec.push_back(Xaxic);
            int t = Xaxic;
            for(i=0;i<time;i++){
                t = t +3*scale;
                vec.push_back(t);
                
            }
            return vec;
        }
    }
    void show();
    //defult 
    void defult(){
        setAx(-10);
        setAy(-10);
        setSc(2);
        setsize(25);
    }
    void setAx(double d){
        Xaxic = d;
    }
    void setAy(double d){
        Yaxic = d;
    }
    int pan(int x,int y){
        setAx(x);
        setAy(y);
        
    }
    int setSc(double d){ // zoom
        if(d<=0){
            return 0;
        }
        scale = d;
        return 1;
    }
    // size 
    int setsize(double d){
        if(d>30 || d<6){return 0;}
        size = d;
        return 1;
    }
    void Status(){
        Model::GetInstance()->printStatus();
    }
    ~View(){}
    
 
private:
    double Xaxic,Yaxic;
    double scale;
    int size;

};









#endif //VIEW_H_