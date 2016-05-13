#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "pebble.h"

using namespace std;




int main(int argc, char **argv) {

    vector<node> nodelist1(0);
    vector<vector<int> > springlist;

    node node0, node1;
    vector<double> X,Y;
  
    int mikado=1; 
    
    // load a mikadofile from .txt file
    if(mikado==1){
        //this section load an existing network from a txt file
        ifstream springf("springs2.txt",std::ifstream::in);
        //vector<vector<int> > springl;
        vector<int> sspring(2);
        string line;
        int springnode[2];
        while (getline(springf,line) ){
            stringstream ss(line);
            ss >>springnode[0] >> springnode[1];
            sspring[0]=springnode[0];
            sspring[1]=springnode[1];
            springlist.push_back(sspring);
        }
        //uncomment for extra springs (SSS)
//         sspring[0]=77;
//         sspring[1]=78;
//         springlist.push_back(sspring);
//         sspring[0]=18;
//         sspring[1]=19;
//         springlist.push_back(sspring);
//         sspring[0]=78;
//         sspring[1]=19;
//         springlist.push_back(sspring);
//         sspring[0]=18;
//         sspring[1]=77;
//         springlist.push_back(sspring);
//         
//         sspring[0]=289;
//         sspring[1]=77;
//         springlist.push_back(sspring);
//         sspring[0]=289;
//         sspring[1]=78;
//         springlist.push_back(sspring);
//         sspring[0]=289;
//         sspring[1]=18;
//         springlist.push_back(sspring);
//         sspring[0]=19;
//         sspring[1]=289;
//         springlist.push_back(sspring);
// 
//         sspring[0]=0;
//         sspring[1]=71;
//         springlist.push_back(sspring);
//         sspring[0]=4;
//         sspring[1]=71;
//         springlist.push_back(sspring);
//         sspring[0]=32;
//         sspring[1]=71;
//         springlist.push_back(sspring);
//         sspring[0]=77;
//         sspring[1]=71;
//         springlist.push_back(sspring);
//         
//         sspring[0]=0;
//         sspring[1]=4;
//         springlist.push_back(sspring);
//         sspring[0]=0;
//         sspring[1]=32;
//         springlist.push_back(sspring);
//         sspring[0]=32;
//         sspring[1]=77;
//         springlist.push_back(sspring);
//         sspring[0]=77;
//         sspring[1]=4;
//         springlist.push_back(sspring);
        
        ifstream coords("nodes.txt",std::ifstream::in);
        vector<double> coordxy(2);
        vector<vector<double > > XY;
        double pos1[3];
        while(getline(coords,line)){
            stringstream ss(line);
            ss >> pos1[0] >> pos1[1] >> pos1[2];
            coordxy[0]=pos1[1];
            coordxy[1]=pos1[2];
            X.push_back(pos1[1]);
            Y.push_back(pos1[2]);
            XY.push_back(coordxy);
        }
    }

    

    if(mikado!=1){ // regular nodes and springs. Not sure this will work w. the new class. Check monday
        node1.visited=0;
        node1.NB0index=-1;
        node1.NB1index=-1;
        node1.nrNBs=0;

        node1.nodex=0.0;
        node1.nodey=0.0;
        nodelist1.push_back(node1);
        node1.nodex=1.0;
        node1.nodey=0.0;
        nodelist1.push_back(node1);
        node1.nodex=0.5;
        node1.nodey=0.5;
        nodelist1.push_back(node1);
        node1.nodex=0.0;
        node1.nodey=1.0;
        nodelist1.push_back(node1);    
        node1.nodex=1.0;
        node1.nodey=1.0;
        nodelist1.push_back(node1);

        vector<int> spring;
        spring.push_back(0);
        spring.push_back(1);
        springlist.push_back(spring);
        
        spring[0]=0;
        spring[1]=2;
        springlist.push_back(spring);
        
        spring[0]=0;
        spring[1]=3;
        springlist.push_back(spring);
        
        spring[0]=1;
        spring[1]=2; 
        springlist.push_back(spring);
        
        spring[0]=1;
        spring[1]=4;
        springlist.push_back(spring);
        
        spring[0]=2;
        spring[1]=3;
        springlist.push_back(spring);
        
        spring[0]=2;
        spring[1]=4;
        springlist.push_back(spring);
        
        spring[0]=3;
        spring[1]=4;
        springlist.push_back(spring);
    }
     vector<int> nopebblesprings; //This vector stores the index of springs that don't get a pebble
    
    //make an instance of a pebble
     pebble pebbletest(X.size(),X,Y);

     //This loop plays the pebblegame. It changes the coord list inside pebbletest 
     //if springs != pebbled -> it is stored in nopebblesprings.
     for(int i=0;i<springlist.size();i++){
         if(!pebbletest.draw_bond(springlist[i][0],springlist[i][1]))
             nopebblesprings.push_back(i);
     }
     
    //Some post processing. Counting free pebbles etc etc
     int freepebbles=0;
     for(int i=0;i<pebbletest.nodelist.size();i++){
        if(pebbletest.nodelist[i].NB0index==-1){
           freepebbles++;
        }
        if(pebbletest.nodelist[i].NB1index==-1){
            freepebbles++;
        }
    }
 
     cout<<"The number of free pebbles = "<<freepebbles<<endl;
     cout<<"Number of nodes="<<pebbletest.nodelist.size()<<endl;
     cout<<"Number of springs="<<springlist.size()<<endl;
     cout<<"2*# nodes - #springs="<<2*pebbletest.nodelist.size()-springlist.size()<<endl;
     
     
     //And for now an ofstream of nodes w. # pebbles and springs w. nr pebbles 
     ofstream nodes("nodes1.txt");
     for(int i=0; i<pebbletest.nodelist.size();i++){
         int freepebs=0;
         if(pebbletest.nodelist[i].NB0index==-1){
         
             freepebs++;
         }
         if(pebbletest.nodelist[i].NB1index==-1){
             freepebs++;
         }
         nodes<<pebbletest.nodelist[i].nodex<<"\t"<<pebbletest.nodelist[i].nodey<<"\t"<<freepebs<<endl;;
     }
     
    ofstream springs("springs1.txt");
    int nodes1, nodes2;
    for(int i=0;i<pebbletest.nodelist.size();i++){
        nodes1=i;
        if(pebbletest.nodelist[i].NB0index!=-1){
            nodes2=pebbletest.nodelist[i].NB0index;
            springs<<nodes1<<"\t"<<nodes2<<"\t"<<nodes1<<endl;
        }
        if(pebbletest.nodelist[i].NB1index!=-1){
            nodes2=pebbletest.nodelist[i].NB1index;
            springs<<nodes1<<"\t"<<nodes2<<"\t"<<nodes1<<endl;
        }
    }
    
    ofstream springs0peb("springs0peb1.txt");
    for(int i=0;i<nopebblesprings.size();i++){
        nodes1=springlist[nopebblesprings[i]][0];
        nodes2=springlist[nopebblesprings[i]][1];
        springs0peb<<nodes1<<"\t"<<nodes2<<endl;
    }
    
    return 0;
}
