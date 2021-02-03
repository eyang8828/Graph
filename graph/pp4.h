#ifndef PP4_H
#define PP4_H
#include "graph.h"
#include "../queue/queue.h"
using namespace std;

template<class T>
bool find_path(graph<T> g,int source, int target){
    // check whether source is the target
    if(source == target){
        return true;
    }

    // the ones that we checked
    bool *visited = new bool[g.size()];
    for (int i = 0; i < g.size();i++)
        visited[i] = false;
    
    //using queue to search
    Queue<T> temp;
    
    //mark the current point as visited
    visited[source] = true;

    temp.push(source);
    while(!temp.empty()){
        source = temp.pop();
        for(int i =0; i < g.size();i++){
            //check for connection
            if(g.get_edges(source,i)){

                //if we find the target return true
                if(i==target){
                    return true;
                }

                //if it's not the target and not visited push in queue
                if(!visited[i]){
                    visited[i]= true;
                    temp.push(i);
                }
            }
            
        }

    }
    //search completed without visited target
    return false;


}


#endif