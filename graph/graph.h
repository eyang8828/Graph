#ifndef GRAPH_H
#define GRAPH_H
#include <cassert>
#include <set>
#include <cstdlib>
#include <iostream>

using namespace std;
template<class T>
class graph{
public:
        static const size_t MAXIMUM = 20;

        graph(){many_vertices = 0;};
        void add_vertex(const T& label);
        void add_edges(size_t source, size_t target);
        void remove_edges(size_t source, size_t target);

        void update_edges(size_t source,size_t target,bool val);
        T get_labels(int index);
        bool get_edges(int index1, int index2);

        T& operator[](size_t vertex){
            assert(vertex < size());
            return labels[vertex];
        };
        T operator[](size_t vertex)const{
            assert(vertex < size());
            return labels[vertex];
        };
        bool is_edge(size_t source, size_t target){
            assert(target < size());
            assert(source < size());
            return edges[source][target];
        };
        size_t size() const{
            return many_vertices;
        };
        set<size_t> neighbors(size_t vertex)const;
    private:
        bool edges[MAXIMUM][MAXIMUM];
        T labels[MAXIMUM];
        size_t many_vertices;
};

template<class T> void graph<T>::add_edges(size_t source, size_t target){
    assert(source < size( ));
    assert(target < size( ));
    edges[source][target] = true;
}

template<class T>
void graph<T>::add_vertex(const T& label){
    std::size_t new_vertex_number;
    std::size_t other_number;
    assert(size( ) < MAXIMUM);
    new_vertex_number = many_vertices;
    many_vertices++;
    for (other_number = 0; other_number < many_vertices; ++other_number){
        edges[other_number][new_vertex_number] = false;
        edges[new_vertex_number][other_number] = false;
    }
    labels[new_vertex_number] = label;
}


template <class Item>
set<size_t> graph<Item>::neighbors(std::size_t vertex) const{
    set<size_t> answer;
    size_t i;
    assert(vertex < size( ));
    for (i = 0; i < size( ); ++i){
        if (edges[vertex][i])
            answer.insert(i);
    }
    return answer;
}


template<class T>
void graph<T>::remove_edges(size_t source, size_t target){
    assert(source < size( ));
    assert(target < size( ));
    edges[source][target] = false;
}


template<class T> 
void graph<T>::update_edges(size_t source, size_t target, bool val){
    edges[source][target] = val;
}

template<class T> 
T graph<T>::get_labels(int index){
    return labels[index];
}

template<class T>
bool graph<T>::get_edges(int index1, int index2){
    return edges[index1][index2];
}


#endif //GRAPH_H