#include <vector>
#include "pebble.h"

using namespace std;



int pebble::recursive_free_pebble(int nodenr,int source){
    
    nodelist[nodenr].visited=1;
    
    
    if(nodelist[nodenr].NB0index==-1){  //if -1 there is a free pebble
        nodelist[nodenr].NB0index=source;
        return 1;
    }
    if(nodelist[nodenr].NB1index==-1){
        nodelist[nodenr].NB1index=source;
        return 1;
    }
    
    if((nodelist[nodelist[nodenr].NB0index].visited==0)   && recursive_free_pebble(nodelist[nodenr].NB0index,nodenr)){
        nodelist[nodenr].NB0index=source;
        return 1;
    }
    
    if((nodelist[nodelist[nodenr].NB1index].visited==0)   && recursive_free_pebble(nodelist[nodenr].NB1index,nodenr)){
        nodelist[nodenr].NB1index=source;
        return 1;
    }
    
    return 0;
    
}

int pebble::free_pebble(int nodenr,int source,int exclude){
    for(int i=0;i<nodelist.size();i++){
        nodelist[i].visited=0;        
    }
    nodelist[exclude].visited=1;
    nodelist[source].visited=1;
    recursive_free_pebble(nodenr,source);
}

int pebble::draw_bond(int nodenr1, int nodenr2){ 
    
    
    int res1;
    int result=1;
    
    
    if(nodelist[nodenr1].NB0index!=-1){
        res1=free_pebble(nodelist[nodenr1].NB0index,nodenr1,nodenr2);
        if (res1) {
            nodelist[nodenr1].NB0index=-1;
        }
        result*=res1;
    }
    if(nodelist[nodenr1].NB1index!=-1 && result==1){
        res1=free_pebble(nodelist[nodenr1].NB1index,nodenr1,nodenr2);
        if(res1){
         nodelist[nodenr1].NB1index=-1;
        }
        result*=res1;
        
    }
    if(nodelist[nodenr2].NB0index!=-1 && result==1){
        res1=free_pebble(nodelist[nodenr2].NB0index,nodenr2,nodenr1);
        if(res1){
            nodelist[nodenr2].NB0index=-1;
        }
        result*=res1;
    }
    if(nodelist[nodenr2].NB1index!=-1 && result==1){
        res1=free_pebble(nodelist[nodenr2].NB1index,nodenr2,nodenr1);
        if(res1){
            nodelist[nodenr2].NB1index=-1;
        }
        result*=res1;
    }
    
    if(result==1){
        nodelist[nodenr1].nrNBs++;
        nodelist[nodenr2].nrNBs++;
        nodelist[nodenr1].neighbours.push_back(nodenr2);
        nodelist[nodenr2].neighbours.push_back(nodenr1);
        nodelist[nodenr1].NB0index=nodenr2;
       
        return 1; //succes
    }
    
    return 0;
}

pebble::pebble(int nrnodes,vector<double> &xpos,vector<double> &ypos)
  : nodelist(nrnodes)
{
    for(int i=0;i<nrnodes;i++){
        nodelist[i].nodex=xpos[i];
        nodelist[i].nodey=ypos[i];
    }
}



pebble::pebble(int nrnodes)
  :nodelist(nrnodes)
  {
   
  }

