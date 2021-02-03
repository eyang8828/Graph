#ifndef PP1_H
#define PP1_H
#include <cassert>
#include <set>
#include <cstdlib>
#include <iostream>

using namespace std;

template< class T>
class graph{
    public:
        static const size_t MAXIMUM = 20;

        graph();
        graph(size_t vertices = MAXIMUM);
        void add_vertex(const T& label);
        void add_edges(size_t source, size_t target);
        void remove_edges(size_t source, size_t target);
        void resize(size_t new_size);



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
        set<size_t> neighbors(size_t vertex);
    private:
        bool **edges;
        T *labels;
        size_t many_vertices;
        size_t allocated;

};

template<class T>
graph<T>::graph(){
    many_vertices = 0;
}

template<class T>
graph<T>::graph(size_t vertices){
    allocated = vertices;
    many_vertices = 0;
    labels = new T[vertices];
    edges = new bool*[vertices];
    for(size_t i = 0; i < vertices; i ++){
        edges[i]= new bool[vertices];
    }
    for(int i = 0 ; i < vertices ; i++){
        for(int j = 0 ; j < vertices ; j++)
            edges[i][j]= false;
    }

}

template<class T>
void graph<T>::add_vertex(const T& label){
    if(allocated == many_vertices)
        resize(allocated+5);
    std::size_t new_size;
    std::size_t other_number;
    assert(size( ) < MAXIMUM);
    new_size = many_vertices;
    ++many_vertices;
    for (other_number = 0; other_number < many_vertices; ++other_number){
        edges[other_number][new_size] = false;
        edges[new_size][other_number] = false;
    }
    labels[new_size] = label;
};


template<class T>
void graph<T>::add_edges(size_t source, size_t target){
    assert(source < size());
    assert(target < size());
    edges[source][target] = true;
};

template<class T>
void graph<T>::resize(size_t new_size){
    if(new_size <= many_vertices){
        return;
    }
    allocated = new_size;

    //setting up new labels and edges
    T *temp = new T[allocated];
    for( int i = 0; i < many_vertices; i++){
        temp[i]= labels[i];
    }

    delete[] labels;
    labels = temp;

    bool **temp2 = new bool*[allocated];
    for(size_t i = 0;i<allocated;i++){
        temp2[i] = new bool[allocated];
    }

    for(int i = 0; i< allocated;i++){
        for(int j = 0; j<allocated;j++){
            temp2[i][j] = false;
        }
    }

    for(int i = 0; i < many_vertices; i++){
        for(int j = 0; j < many_vertices; j++){
            temp2[i][j]= edges[i][j];
        }
    }

    //delete old edges
    for(int i = 0; i < many_vertices; i++){
        delete[] edges[i];
    }

    delete[] edges;

    edges = temp2;
}

template<class T> set<size_t> graph<T>::neighbors(size_t vertex){
    set<size_t> answer;
    size_t i;
    assert(vertex < size( ));
    for (i = 0; i < size( ); ++i){
        if (edges[vertex][i])
            answer.insert(i);
    }
    return answer;
}

template<class T> void graph<T>::remove_edges(size_t source, size_t target){
    assert(source < size());
    assert(target < size());
    edges[source][target] = false;
}




#endif // PP1_H