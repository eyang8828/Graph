#ifndef PP5_H
#define PP5_H
#include "graph.h"
#include <cassert>
#include <set>
#include <cstdlib>
#include <iostream>
#include "../!include/vector/vector.h"

using namespace std;

template<class T>
class weighted_graph:public graph<T>{
    public:
        weighted_graph():graph<T>(){};
        void add_vertex(const T&label);
        void add_edges(size_t source,size_t target,int weight);
        void remove_edge(size_t source, size_t target);
        int get_weight(size_t source, size_t target)const;
        vector<size_t> shortest_distance(int start,int end);
        vector<size_t> shortest_path(int start,int end);
        int getMin(int* arr, bool* b_arr,int size);
    private:
        int weights[graph<T>::MAXIMUM][graph<T>::MAXIMUM];


};
template<class T> 
void weighted_graph<T>::add_vertex(const T &label){
    //call parent function
    size_t temp = graph<T>::size();
    graph<T>::add_vertex(label);

    // fill the new vertex with -1 
    for(size_t i = 0; i < graph<T>::size();i++){ 
        weights[i][temp]= -1;
        weights[temp][i]= -1;

    }
}
template<class T> 
void weighted_graph<T>::add_edges(size_t source, size_t target, int weight){
    graph<T>::add_edges(source,target);
    weights[source][target] = weight;
}
template<class T> 
void weighted_graph<T>::remove_edge(size_t source, size_t target){
    graph<T>::remove_edge(source,target);
    weights[source][target]=-1;
}
template<class T> 
int weighted_graph<T>::get_weight(size_t source, size_t target) const{
    return weights[source][target];
}

template<class T>
vector<size_t> weighted_graph<T>::shortest_distance(int start,int end){
    int distance[end];
    bool visited[end];

    //set distance default to -1 cause distance can never be negative
    for(int i = 0; i < end ; i++){
        distance[i] = -1;
        visited[end] = false;
    }

    distance[start] = 0;
    set<size_t> vertices;
    int next;
    set<size_t> neighbour;
    int point = 0, sum = 0;

    for (int i = 1;i<=end;i++){
        //call get Min to find the next index to work on
        next = getMin(distance,visited,end);
        //set it to visited and insert to vertices
        visited[next] = true;
        vertices.insert(next);
        neighbour = graph<T>::neighbors(next);

        //run through whole list
        for(point = 0; point<end;point ++){

            // updating the distance array
            if(vertices.count(point)&&(neighbour.count(point)>0)){
                sum = distance[next] + get_weight(next,point);
                if(distance[point] != -1 && sum<distance[point])
                    distance[point] = sum;
                else if(distance[point]==-1)
                    distance[point] = sum;
            }
        }
    }
    vector<size_t> distances;
    for(int i = 0; i < end; i ++){
        distances.push_back(distance[i]);
    }
    return distances;
}

template<class T> 
vector<size_t> weighted_graph<T>::shortest_path(int start, int end){
    int distance[end];
    int predecessor[end];
    bool visited[end];

    //initialize
    for(int i =0;i<end;i++){
        distance[i]= -1;
        visited[i] = false;
    }
    distance[start] = 0;
    set<size_t> vertices;
    int next;
    set<size_t> neightbour;
    int point, sum=0;
    for(int i =1;i<=end;i++){
        next = getMin(distance,visited,end);
        visited[next]=true;
        vertices.insert(next);
        neightbour = graph<T>::neighbors(next);
        for(point = 0; point<end;point++){

            //updating the distance array and predecessor
            if(!vertices.count(point)&&(neightbour.count(point)>0)){
                    sum = distance[next]+get_weight(next,point);
                if(distance[point]!=-1&&sum<distance[point]){
                    distance[point] = sum;
                    predecessor[point]=next;
                }else if(distance[point]==-1){
                    distance[point] = sum;
                    predecessor[point] =next;
                }
            }
        }
    }
    vector<size_t>output;
    for(int i =0; i < end;i++){
        output.push_back(predecessor[i]);
    }
    return output;
}

template<class T>
int weighted_graph<T>::getMin(int* arr, bool* b_arr, int size){
    int index = 0;
    int minimum = INT_MAX;

    //loop through to get the minimum and its index
    for(int i = 0; i < size; i++){
        if(!b_arr[i] && arr[i] > 0 && minimum>arr[i]){
            index = i;
            minimum = arr[i];
        }
    }
    return index;
}



#endif // PP5_H