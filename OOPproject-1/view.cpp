#include "view.h"



void View::show(){
        cout<<"Display size:"<< size<<", scale: "<<scale<<", origin: ("<<Xaxic<<", "<<Yaxic<<")\n";
        int county = (size)*scale;
        int countx = Yaxic+(size-1)*scale;
        int i,j;
        vector<int> vy = numbers_For_graph(1);
        vector<int> vx = numbers_For_graph(0);
        int mod3 = 3,ind_y=0;
        for(i=county;i>=scale;i-=scale){
            if(mod3%3==0){
                stringstream ss;
                ss<<vy[vy.size()-1-ind_y];
                string s;
                ss>>s;
                if(s.length()==1){
                    cout<<s<<"  ";
                }
                else if(s.length()==2){
                    cout<<s<<" ";
                }
                else{ cout<<s;

                }
                
               ind_y++;
            }
            else{cout<<"   ";}
            mod3++;
            for(j=Yaxic;j<countx;j+=scale){
                string str = Model::GetInstance()->findInThisArea(i,j,scale);
                string str1 = Model::GetInstance()->findInThisArea(i-scale,j,scale);
                string str2 = Model::GetInstance()->findInThisArea(i+scale,j-scale,scale);
                string str3 = Model::GetInstance()->findInThisArea(i-scale,j-scale,scale);
                string str4 = Model::GetInstance()->findInThisArea(i,j-scale,scale);
                 
                if(str=="." ){
                    cout<<str<<" ";
                }
                else{
                    if(str1!=str&&str2!=str&&str3!=str&&str4!=str){
                        cout<<str;
                    }
                    else{cout<<"."<<" ";

                    }
                }


            
            }
            cout<<"\n";



        }
        cout<<" ";
        int sizeV = vx.size();
        
         
        for(j=0;j<sizeV;j++){
            if(j!=sizeV-1){
            cout<<vx[j]<<"    ";}
            else{cout<<vx[j];}
            

        }
        cout<<"\n";
    }