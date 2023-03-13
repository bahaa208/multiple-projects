#include <iostream>

#include <cstdlib>


#ifndef FILEREADER_H
#define FILEREADER_H
#include <vector>
#include "Container.cpp"

//
// Created by bhaa on 15/1/2022.
//
/* this class is the main class the have container that have Element inside and make the born opration and sort like he should do */
 
class FileReader
{
public:
     
    FileReader(const char* one,const char* two);
    ~FileReader(){delete [] conta;}
    vector<int> e(int n,int i);
    double f1x(vector<double> x, int numE);
    vector<double> fx(vector<double> x );
    int sizeString(string str);
    void sumVector(vector<double> &x,double* z);
    void setEveryE_F(vector<Element<double> >& ele);
    const char* getNameOfFileToSend(){
        return toFile;
    }
    void Children();
    void writeToFile(const char* to);
    void untilTheTimeIsDone();
    Container<double> * getContainer(){
        return conta;
    }
    friend ostream& operator<<(ostream& os, FileReader& n){

        vector<Element<double> > ele = n.getContainer()->getElements();
        
        int iii = ele.size();
        for(int i=0;i<iii;i++){
            int jjj = ele[i].get_F().size();
            
            for(int j=0;j<jjj;j++){
                os<<ele[i].get_F()[j]<<" ";
            }
            os<<endl;
        }

        return os;
    }


private:
    Container<double> *conta;
    int m,n,mew,time;
    const char* toFile;


};









#endif //FILEREADER_H