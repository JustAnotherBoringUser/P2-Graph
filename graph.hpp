#ifndef GRAF_HPP
#define GRAF_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <time.h>
#include <string> 

using namespace std;

class Graph{

protected:
    int V, E;

    public:
    virtual void print() = 0;
    virtual void init(int V, int E, int** data, bool rn) = 0; 
    //inicjalizacja z ktorej korzystaja losowe i z pliku 
    //czyli from file ktory nie byl czytaniem z pliku stricte
   virtual void BF(int start, bool measure) = 0; //
   void path(int* prev, int* cost, int V, int start); // = 0
    void random(int V, int E);
    Graph() {}
    virtual ~Graph() {}
};

void Graph::path(int* prev, int* cost, int V, int start) //tab poprzednikow, koszt, V
{
    std::fstream file;
    file.open("path.txt", std::ios::out);
    int* show = new int [V];  
    //tablica dynamiczna do wyswietlania po kolei V w sciezce

    int n = 0; //indeks tablicy show
    int vm; //V przez ktory "minelismy", przechowywany w tablicy poprzednikow
    file <<"Najkrotsze sciezki dla wierzcholka: " << start <<"\n";

    for(int i = 0; i < V; i++)    
    {
        file << i <<": "; //Vkoncowy 
        for(vm = i; vm != -1 && n < V; vm = prev[vm])show [n++] = vm;

        while(n)file << "->" << show[--n]; 
        //wyswietla przez jakie V przeszlismy by dojsc do Vkoncowego

        file<< ", koszt: " << cost[i] << std::endl;
    } 
    
    delete [] show;  
    file.close();
}

void Graph::random(int V, int E) {

    int** data = new int*[E];
    for(int i =0; i<E; ++i) { data[i] = new int[3]; }

    bool was_edge[V][V]; //tablica sasiedztwa mowiaca czy juz wylosowalismy dana krawedz

    for(int i=0; i<V; i++){
        for(int j=0; j<V; j++){
            was_edge[i][j]=false;
        }
    }

    int v1, v2, weight;

     for(int i = 0; i < E;)  // E=(g*V*(V - 1))/2, g - gestosc
    {
        v1 = rand() % V;   
        v2 = rand() % V; 
        
        if (v1 == v2 || was_edge[v1][v2]) { continue;} //sprawdzanie czy nie istnieje juz takie E
        was_edge[v1][v2] = true;
        weight = rand() % 30; 
		while (weight == 0) { //jezeli wylosuje 0 to losujemy znowu

			weight = rand() % 30;
		}
        data[i][0] = v1; data[i][1] = v2; data[i][2] = weight;
        ++i;
    }

    init(V,E,data,true);
   
        delete [] data;
}

#endif