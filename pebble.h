#ifndef PEBBLE_H
#define PEBBLE_H


#include <vector>

struct node{
    int visited;
    int NB0index;
    int NB1index;
    int nrNBs;
    std::vector<int> neighbours;
    double nodex;
    double nodey;

public:
    node(){
        visited=0;
        NB0index=-1;
        NB1index=-1;
        nrNBs=0;
        neighbours;
        nodex=0.0;
        nodey=0.0;
    }
};





// int recursive_free_pebble(std::vector<node> &nodelist,int nodenr,int source);
// int free_pebble(std::vector<node> &nodelist,int nodenr,int source,int exclude);
// int draw_bond(std::vector<node> &nodelist, int nodenr1, int nodenr2);


class pebble{
private:

    int recursive_free_pebble(int nodenr,int source);
    int free_pebble(int nodenr,int source,int exclude);
    
public:
    std::vector<node> nodelist;
    int draw_bond(int nodenr1, int nodenr2);
    
    pebble(int); //constructor
    pebble(int, std::vector<double> &xpos,std::vector<double> &ypos);
    ~pebble(){}; //destructor
    };


#endif