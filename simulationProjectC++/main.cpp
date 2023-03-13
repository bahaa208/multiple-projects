#include <string.h>
#include "FileReader.h"
int main(int argc,char *argv[]){
    FileReader *f = new FileReader(argv[1],argv[2]);
    f->untilTheTimeIsDone();
    f->writeToFile(f->getNameOfFileToSend());
    try{
        if(argc!=3){
            cerr << "error: invalid input."<<endl;
            return 0;
        }
        
        cout<<*f<<endl;
        srand(time(0));
         
        
    }
    catch(...){
         cerr << "error: invalid input."<<endl;
        return 0;
    }
    

    return 0;
}