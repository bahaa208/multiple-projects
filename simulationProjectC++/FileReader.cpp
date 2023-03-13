//
// Created by bhaa on 15/1/2022.
//
#include <stdlib.h>     /* srand, rand */
#include <ctime>
#include "FileReader.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <limits>
#include <fstream>
using namespace std;
int FileReader::sizeString(string str){
    int count =0;
    for (int i = 0; str[i] != '\0';i++)
    {
        if (str[i] == ' ')
            count++;    
    }
    return count+1;

}
FileReader::FileReader(const char* one,const char* two){
    int  checkN =0,checkMew=0,numcul=1 ;
    this->toFile = two;
    try{
        
        
        
        string myText;
        ifstream indata;
        indata.open(one);
        if(!indata) { // file couldn't be opened
            cerr << "ERROR: "<<one<<" does not exist or cannot be opened"<<endl;
            exit(1);
        }
        
        ifstream MyReadFile(one, ios::in);
        getline (MyReadFile, myText);
        if(sizeString(myText)!=4){
           cerr <<"ERROR: simulation definition in "<< myText<<" is invalid\n"<<endl;
            exit(1);
        }
        stringstream baha(myText);
        baha>>this->mew;
        baha>>this->n;
        baha>>this->m;
        conta = new Container<double>(this->m);
        baha>>this->time;
         
       
         
        while (getline (MyReadFile, myText)) {
            char* l2 = const_cast<char*>(myText.c_str());
            checkMew++;
             

            // Returns first token
            char *token = strtok(l2, " ");

            
            // delimiters present in str[].
             
            double x1=0.0;
            Element<double> el;
            while (token != NULL)
            {
                stringstream baha(token);
                baha>>x1;
                el.getX().push_back(x1);
                checkN++;
                 
                token = strtok(NULL, " ");
            }
            numcul++;
            if(this->m >= this->n){ /* as we know m should be less than n */
                cerr <<"ERROR: simulation definition in "<< one<<" is invalid\n";
                exit(1);
            }
            
            if(checkN!=this->n){
                throw 10;
            }
            checkN = 0;
            conta->addE(el);
           
        }

        // Close the file
        MyReadFile.close();
        
        if( checkMew != this->mew ){
            
            throw 404;
        }
    }
    catch(...){
        cerr << "ERROR: population definition in "<<one<<" at line "<< numcul <<" is invalid\n";
        exit(1); 
    }
    
}
/* function that return vector e(i)={i0,i1,i2,i,i,i,in}  */
vector<int> FileReader::e(int n,int i){
    vector<int> ee;
    for(int z = 0; z < n;z++){
        ee.push_back(i);
    }
    return ee;
}
/* one element in f(x)  */
double FileReader::f1x(vector<double> x, int numE){
    int siz = x.size();
    double sum= 0;
    vector<int> ve = e(siz,numE);
    for(int i=0 ;i<siz ;i++){
        sum += (x[i] - ve[i])*(x[i] - ve[i]) ;
    }
    return sum;

}
vector<double> FileReader::fx(vector<double> x){
    vector<double> newF;
    newF.clear();
    
    for(int i = 1 ; i <= this->m ; i++){
        newF.push_back(f1x(x,i));
    }
     
    return newF;
}
/* random vector btween (0..1)~N */
static double* z(int n){
    double *Z = new double[n];
     
    
    for(int i=0 ; i<n ; i++) {
        srand((unsigned) time(NULL));
        Z[i]=(float) rand() / RAND_MAX;
       
    }
    return Z;
}
/* make the eps = x+z */
void FileReader::sumVector(vector<double> &x,double* z){
     
    int ii = x.size();
    for(int i=0 ;i<ii;i++){
        x[i]= x[i]+z[i];
    }
     
}
/* this function is one time like mew ~ born a new mew ~ then we have two mew element we find rank for every one 
then make sort by rank then take 
the first mew element */
void FileReader::Children(){
    
     
   
    for(int i=0 ; i <this->mew ; i++) {
        vector<double> x = conta->getElements()[i].get_X(); 
        
        double *zz = z(this->n);
        sumVector(x,zz);
         
         
        Element<double> child;
        child.setX(x);
        conta->getElements().push_back(child); 
    }
     
    setEveryE_F(conta->getElements());
    
    conta->ParetoSorting(conta->getElements());
    
    for(int i=0 ; i <this->mew ; i++) {
        conta->getElements().pop_back();
    }
     
     



}
void FileReader::untilTheTimeIsDone(){
    for(int i=0;i<this->time;i++){
        
        Children();
    }
}
void FileReader::setEveryE_F(vector<Element<double> >& ele){
    int si = ele.size();
    for(int i=0;i<si;i++){
         
        ele[i].setF(fx(ele[i].get_X()));
        
    
    }
    
}

void FileReader::writeToFile(const char* to){
    ofstream outdata; // outdata is like cin
     

    outdata.open(this->toFile); // opens the file
    if( !outdata ) { // file couldn't be opened
        cerr << "Error: file could not be opened" << endl;
        exit(1);
    }
    vector<Element<double> > ele = conta->getElements();
    int iii = ele.size();
    for(int i=0;i<iii;i++){
        int jjj = ele[i].get_F().size();
        
        for(int j=0;j<jjj;j++){
            outdata <<ele[i].get_F()[j]<<" ";
        }
        outdata <<endl;
    }

         

     
    
    outdata.close();
}