#ifndef PP3_H
#define PP3_H
#include "graph.h"

using namespace std;
template<class T>
class PP_3:public graph<T>{
    public:
        void add_edges(size_t source,size_t target,T label);
        void remove_edges(size_t source,size_t target,T label);
        void display();
    private:
        T edge_label[graph<T>::MAXIMUM][graph<T>::MAXIMUM];
};

template<class T>
void PP_3<T>::add_edges(size_t source, size_t target, T label){
    assert(source < graph<T>::size());
    assert(target < graph<T>::size());
    
    // set edge to true
    graph<T>::update_edges(source,target,true);

    //set label of the edge
    edge_label[source][target] = label;
}

template<class T>
void PP_3<T>::remove_edges(size_t source, size_t target, T label){
    assert(source < graph<T>::size());
    assert(target < graph<T>::size());
    
    //set edge to false
    graph<T>::update_edges(source,target,false);

    //remove the label
    edge_label[source][target] = -1;
}

template<class T>
void PP_3<T>::display(){
    for(int i = 0; i < graph<T>::size();i++){
        //print the index
        cout<<graph<T>::get_labels(i)<<"->";
        for(int j = 0; j< graph<T>::size();j++){
            //check whether there is edges and print it in order
            if(graph<T>::get_edges(i,j)){
                cout<<graph<T>::get_labels(j)<<"("<<edge_label[i][j]<<") ";
                
            }
            
        }
        cout<<endl;
    }
}

#endif // PP3_H