//
// Created by bhaa on 15/1/2022.
//
#include "Container.h"
template <typename AnyType>
Container<AnyType>::Container(int mew){
    this->size = mew;
}
template <typename AnyType>
Container<AnyType>::~Container(){} 

template <typename AnyType>
int* Container<AnyType>::ParetoRanking(vector<vector<AnyType> > listF){
    int *ranks = new int[listF.size()];
    int iii = listF.size();
    for(int d=0;d <iii;d++){
        ranks[d]=0;
    }
    for(int i =0 ; i< iii ; i++){
        for(int j =0 ; j< iii ; j++){
            if(i!=j){
                if(isControl(listF[i],listF[j])){
                    ranks[i]++;
                }
            }
            
        }

    }
    return ranks;
}
template <typename AnyType>
bool Container<AnyType>::isControl(vector<AnyType> f1,vector<AnyType> f2){
    int k = f1.size();
    bool thereisLess = false;
    for(int i=0; i<k;i++){
        if(f1[i]>f2[i]){                 
            return false;
        }
        if(f1[i]<f2[i]){thereisLess = true;}
    }
    return thereisLess;
    
}
template <typename AnyType>
void Container<AnyType>::ElementsReordering(vector<Element<AnyType> >& elements){
    int iii = elements.size();
    for(int i=0;i<iii;i++){
        for(int j=0;j<iii;j++){
            if(elements[i] > elements[j]){
                Element<AnyType> temp = elements[i];
                elements[i] = elements[j];
                elements[j] = temp;
            }
        }
    }
}
template <typename AnyType>
void Container<AnyType>::ParetoSorting(vector<Element<AnyType> >& elements){
    vector<vector<AnyType> > listF;
    int jjj = elements.size();
    for(int i =0; i< jjj;i++){
        listF.push_back(elements[i].getF());
        
    }
    
    int *ranks = ParetoRanking(listF);
    for(int i =0; i< jjj;i++){
        elements[i].setRank(ranks[i]);

    }
    ElementsReordering(elements);

}

