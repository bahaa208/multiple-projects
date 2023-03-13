//
// Created by bhaa on 14/4/2022.
//

 
#include "FileRead.h"
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <limits>
#include <fstream>

FileRead::FileRead(const char* one,const char* two){
     
    
    
    try{
        int sizeOfString,lenn ;
        
         
        string myTexttt,s1 ;

         theStrongestStringEver =NULL;
          
         
        ifstream MyRead(one, ios::in);
        ifstream indata;
        indata.open(two); 
        if(!indata) { // file couldn't be opened
            cerr << "ERROR: Invalid input."<<endl;
            exit(1);
        }
        getline (MyRead, myTexttt);
        
        stringstream baha(myTexttt);
        baha>>sizeOfString;
         
        getline (MyRead, myTexttt);
        char* l1 = const_cast<char*>(myTexttt.c_str());
        char *token = strtok(l1, " ");
        
            
            
        
         
        stringstream  theS;
       
            
         
        while (token != NULL)
        {
                
            theS<<*token;
            
            token = strtok(NULL, " ");
        }
        
        string str;
        theS>>str;
        this->sizeOfString = sizeOfString;
        lenn = str.length();
        if(lenn!=sizeOfString){
            throw 404;
        }
        gool = new Covid(str,sizeOfString);
        
        getline (MyRead, myTexttt);
        stringstream baha1(myTexttt);
        baha1>>ourLoop;
        if(ourLoop>1000000){
            cerr << "ERROR: To much generations.";
            exit(1);
        }
        
        
         
        

        // Close the file
        MyRead.close();
        
    }
    catch(...){
        cerr << "ERROR1: Invalid input.";
         
    }
    
    
     




    try{
        
        int checkLine=0;
        ifstream indata;
        indata.open(two);  
        string myText2,txt;
        ifstream MyReadFile(two, ios::in );
        
        // Use a while loop together with the getline() function to read the file line by line
         
        getline (MyReadFile, txt);
        stringstream baha(txt);
        baha>>numberOfElement;

        while (getline (MyReadFile, myText2)) {
            char* l1 = const_cast<char*>(myText2.c_str());
            char *token = strtok(l1, " ");
            checkLine++;
             
             
            
            char type;
            stringstream baha11(token),theS;
            baha11>>type;
            int lenofstr = 0;
            token = strtok(NULL, " ");
            while (token != NULL)
            {
                 
                theS<<*token;
                if(*token != ' '){
                    lenofstr++;
                }
                
                token = strtok(NULL, " ");
            }
            string str;
            theS>>str;
            int lenn = str.length();
            if(this->sizeOfString!=lenn){
                throw 404;
            }
            
            
            string *stStr = new string(str);
            const Sstring sa(stStr);
            if(type=='a'){
                Covid *nnn= new Alpha(sa,this->sizeOfString);
                vectorOfCovid.push_back(nnn);
                vectorStr.push_back(sa);
            }
            else if(type=='o'){
                Covid *nnn = new Omicron(sa,this->sizeOfString);
                vectorOfCovid.push_back(nnn);
                vectorStr.push_back(sa);
            }
            else{
                Covid *nnn = new Delta(sa,this->sizeOfString);
                vectorOfCovid.push_back(nnn);
                vectorStr.push_back(sa);
            }
            
        }

        // Close the file
        MyReadFile.close();
        if(!(numberOfElement>=2&& numberOfElement<=200)){
            cerr << "ERROR: To much generations.";
            exit(1);
        }
        if(!indata) { // file couldn't be opened
            cerr << "ERROR : Invalid input."<<endl;
            exit(1);
        }
        else if(checkLine != numberOfElement){
            cerr << "ERROR : number of line !."<<endl;
            exit(1);
        }

    }
    catch(...){
        cerr << "ERROR22: Invalid input."<<endl;
        exit(1);
    }
    
     
}

void FileRead::makeChangerfomInside(){
    int size = vectorOfCovid.size();
    for(int i = 0 ; i<size;i++){
        vectorOfCovid[i]->makeChange();
    }
     
}

void FileRead::makeChangeFroGroup(){
    int i=0,j=0;
    while(i==j){
        i = (rand() % numberOfElement) %(numberOfElement);
        j = (rand() % numberOfElement) %(numberOfElement);

    }
    
    
    string string_for_i = vectorOfCovid[i]->getCopyOfMys();
    string string_for_j = vectorOfCovid[j]->getCopyOfMys();
    int s=0,t=0,size = string_for_i.length(),ft=size-4;
    stringstream ss1,ss2;

    while(s>=t){
         
        t = rand()%ft + 3 ;
        s = rand()%ft + 2 ;
        
    }
    
    for(int iii=0 ;iii<size;iii++){
        if(i>=s && i<=t){
        ss1<<string_for_j[iii];
        ss2<<string_for_i[iii]; 
        }
        else{
        ss1<<string_for_i[iii];
        ss2<<string_for_j[iii];
        }
        
        
    }
     
    string news1,news2;
    ss1>>news1;
    ss2>>news2;
    Covid* newfori;
    Covid* newforj;
    char ii = vectorOfCovid[i]->getType();
    char jj = vectorOfCovid[j]->getType();
    
    if(ii=='d'){
        newfori = new Delta(news1,vectorOfCovid[i]->getSstringNonRef(),sizeOfString);

    }
    if(ii == 'o'){
        newfori = new Omicron(news1,vectorOfCovid[i]->getSstringNonRef(),sizeOfString);
    }
    if(ii == 'a'){
        newfori = new Alpha(news1,vectorOfCovid[i]->getSstringNonRef(),sizeOfString);
    }
    /* for anther */

    if(jj=='d'){
        newforj = new Delta(news2,vectorOfCovid[j]->getSstringNonRef(),sizeOfString);

    }
    if(jj == 'o'){
        newforj = new Omicron(news2,vectorOfCovid[j]->getSstringNonRef(),sizeOfString);
    }
    if(jj == 'a'){
        newforj = new Alpha(news2,vectorOfCovid[j]->getSstringNonRef(),sizeOfString);
    }
    int firstWeak = FindTheMostWeak_Index(1);
    int secondWeak = FindTheMostWeak_Index(2);
     
    delete vectorOfCovid[firstWeak];
    vectorOfCovid[firstWeak] = newfori;
    delete vectorOfCovid[secondWeak];
    vectorOfCovid[secondWeak] = newforj;  


}
bool FileRead::CheckIfThereIStrong(){
    double dub = vectorOfCovid[FindTheMostStrongest_Index()]->getF(*gool);
    if(dub>0.9){
        return true;
    }
    return false;
}

 
int FileRead::FindTheMostStrongest_Index(){
    double strong=0 ;
    int  index1=0 ;

    for(int i =0;i<numberOfElement;i++){
        double dub = vectorOfCovid[i]->getF(*gool);
        if(dub>strong){
            strong = dub;
            index1 = i;
        }
    }
    return index1;
}
int FileRead::FindTheMostWeak_Index(int firstOrSecond){
    double weak1=1.0,weak2=1.0;
    int index1=0,index2=0;
    
    for(int i =0;i<numberOfElement;i++){
        double dub = vectorOfCovid[i]->getF(*gool);
         
        if(dub<weak1){
            weak1 = dub;
            index1 = i;
        }
    }
    if(firstOrSecond==1){
        return index1;
    }
    for(int i =0;i<numberOfElement;i++){
        double dub = vectorOfCovid[i]->getF(*gool);
        if(dub<weak2 && weak1!=dub){
            weak2 = dub;
            index2 = i;
        }
    }
    
    return index2;
}
void FileRead::Do(){
    int i=0,hight;
    theStrongestStringEver = &vectorOfCovid[FindTheMostStrongest_Index()];
    while((i++)< ourLoop){
        hight = FindTheMostStrongest_Index();
        makeChangerfomInside();  
        makeChangeFroGroup();
         
        if( (*theStrongestStringEver)->getF(*gool) < vectorOfCovid[hight]->getF(*gool)){
            theStrongestStringEver = &vectorOfCovid[hight ];
        }
        
        if(CheckIfThereIStrong()){
           
            return;
        }
       
    }
    
     
     
}
FileRead::~FileRead(){
    delete gool;
    delete theStrongestStringEver;
    int size = vectorOfCovid.size();
    for(int i = 0 ; i<size;i++){
        delete vectorOfCovid[i] ;
    }
     
}