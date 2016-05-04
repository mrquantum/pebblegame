#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

struct node{
    int visited;
    int NB0index;
    int NB1index;
    int nrNBs;
    vector<int> neighbours;
    double nodex;
    double nodey;
};







int recursive_free_pebble(vector<node> &nodelist,int nodenr,int source){
    
    nodelist[nodenr].visited=1;
    
    
    if(nodelist[nodenr].NB0index==-1){  //if -1 there is a free pebble
        nodelist[nodenr].NB0index=source;
        return 1;
    }
    if(nodelist[nodenr].NB1index==-1){
        nodelist[nodenr].NB1index=source;
        return 1;
    }
    
    if((nodelist[nodelist[nodenr].NB0index].visited==0)   && recursive_free_pebble(nodelist,nodelist[nodenr].NB0index,nodenr)){
        nodelist[nodenr].NB0index=source;
        return 1;
    }
    
    if((nodelist[nodelist[nodenr].NB1index].visited==0)   && recursive_free_pebble(nodelist,nodelist[nodenr].NB1index,nodenr)){
        nodelist[nodenr].NB1index=source;
        return 1;
    }
    
    return 0;
    
}



int free_pebble(vector<node> &nodelist,int nodenr,int source,int exclude){
    for(int i=0;i<nodelist.size();i++){
        nodelist[i].visited=0;        
    }
    nodelist[exclude].visited=1;
    nodelist[source].visited=1;
    recursive_free_pebble(nodelist,nodenr,source);
}



int draw_bond(vector<node> &nodelist, int nodenr1, int nodenr2){ // dont understand this!
    
    
    int res1;
    int result=1;
    
    
    if(nodelist[nodenr1].NB0index!=-1){
        res1=free_pebble(nodelist,nodelist[nodenr1].NB0index,nodenr1,nodenr2);
        if (res1) {
            nodelist[nodenr1].NB0index=-1;
        }
        result*=res1;
    }
    if(nodelist[nodenr1].NB1index!=-1 && result==1){
        res1=free_pebble(nodelist,nodelist[nodenr1].NB1index,nodenr1,nodenr2);
        if(res1){
         nodelist[nodenr1].NB1index=-1;
        }
        result*=res1;
        
    }
    if(nodelist[nodenr2].NB0index!=-1 && result==1){
        res1=free_pebble(nodelist,nodelist[nodenr2].NB0index,nodenr2,nodenr1);
        if(res1){
            nodelist[nodenr2].NB0index=-1;
        }
        result*=res1;
    }
    if(nodelist[nodenr2].NB1index!=-1 && result==1){
        res1=free_pebble(nodelist,nodelist[nodenr2].NB1index,nodenr2,nodenr1);
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










int main(int argc, char **argv) {

    vector<node> nodelist(0);
    node node0,node1,node2,node3;

    node1.visited=0;
    node1.NB0index=-1;
    node1.NB1index=-1;
    node1.nrNBs=0;

    node1.nodex=0.0;
    node1.nodey=0.0;
    nodelist.push_back(node1);
    node1.nodex=1.0;
    node1.nodey=0.0;
    nodelist.push_back(node1);
    node1.nodex=0.5;
    node1.nodey=0.5;
    nodelist.push_back(node1);
    node1.nodex=0.0;
    node1.nodey=1.0;
    nodelist.push_back(node1);    
    node1.nodex=1.0;
    node1.nodey=1.0;
    nodelist.push_back(node1);

    
    cout<<draw_bond(nodelist,0,1)<<endl;
    cout<<draw_bond(nodelist,0,2)<<endl;
    cout<<draw_bond(nodelist,0,3)<<endl;
    cout<<draw_bond(nodelist,1,2)<<endl;
    cout<<draw_bond(nodelist,1,4)<<endl;
    cout<<draw_bond(nodelist,2,3)<<endl;
    cout<<draw_bond(nodelist,3,4)<<endl;

    
    cout<<"After the bonds"<<endl;
    for(int i=0;i<nodelist.size();i++){
        cout<<i<<"\t"<<nodelist[i].NB0index<<"\t"<<nodelist[i].NB1index<<endl;
    }

    ofstream nodes("nodes.txt");
    for(int i=0; i<nodelist.size();i++){
        int freepebs=0;
        if(nodelist[i].NB0index==-1){
        
            freepebs++;
        }
        if(nodelist[i].NB1index==-1){
            freepebs++;
        }
        nodes<<nodelist[i].nodex<<"\t"<<nodelist[i].nodey<<"\t"<<freepebs<<endl;;
    }
    

    //monday make a list for springs that have pebbles and draw those pebbles
    for(int i=0;i<nodelist.size();i++){
        
        
    }
    
    
    
    return 0;
}
