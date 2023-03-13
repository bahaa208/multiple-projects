#include "Cov.h"
#include "Delta.h"
#include "Omicron.h"
#include "Alpha.h"
#include "FileRead.h"
#include <vector>
#include<algorithm>
 

int main(int argc,char *argv[]){
  srand(time(NULL));
  try{
    if(argc!=3){
      cerr << "error: invalid input."<<endl;
      return 0;
    }
     
    FileRead *f = new FileRead(argv[1],argv[2]);
    srand(time(0));
    f->Do();
    cout<<*f;
    
  }
  catch(...){
    cerr << "error: invalid input."<<endl;
    return 0;
  }
  

  return 0;
}