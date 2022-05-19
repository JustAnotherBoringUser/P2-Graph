#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "graph.hpp"

using namespace std;

class Matrix : public Graph {

protected:

int** adj_m;

    public:
    virtual void init(int V, int E, int** data,bool rn);
    virtual void print();
    virtual void BF(int start, bool measure);
    Matrix() { adj_m=nullptr; }
    ~Matrix() {
        if (adj_m!=nullptr)
        {
        for(int j = 0; j < V; ++j)
        {
        delete [] adj_m[j];
        }
        delete [] adj_m;
        }
    }

};

void Matrix::print()
{
     cout<< "\nMacierz sasiedztwa odczytanego grafu:\n";

    for(int i = 0; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            cout << adj_m[i][j] <<" ";
        }
        cout<<endl;
    }
}

void Matrix::init(int V, int E, int** data, bool rn) 
{
    
    if (adj_m!=nullptr)
        {
        for(int j = 0; j < this->V; ++j)
        {
        delete [] adj_m[j];
        }
        delete [] adj_m;
        }
    
    int v1, v2;
    this->V = V;
    this->E = E;

    adj_m = new int *[V];
    for(int i = 0; i < V; ++i)
    {
        adj_m[i] = new int [V];

        for(int j = 0; j < V; ++j)
        {
            adj_m[i][j] = 0; //this->adj_m
        }
    }

    for (int b = 0; b < E; ++b)
    {
        v1 = data[b][0];        //wczytujemy dane z reprezentacji grafu z pliku
        v2 = data[b][1];
        adj_m[v1][v2] = data[b][2];
        if(rn) adj_m[v2][v1] = data[b][2];  //nieskierowany //if(E==(V*(V - 1))/2)
    }
    
	//print();
}

void Matrix::BF(int start, bool measure)
{

    int const max_int =2147483647; 

    int* cost;         
    cost = new int [V];

    int* p;    
    p = new int [V];

    for(int i = 0; i < V; i++)
    {
        p[i] = -1;     
        cost[i] = max_int;     ///koszty dojscia ustawiamy na nieskonczonosc, tutaj na maksymalna wartosc inta
    }

    cost[start] = 0;           ///zerujemy koszt dojscia do V start

    for(int i = 1; i < V; i++)
    {
        for(int j = 0; j < V; j++)
        {
            for(int k = 0; k < V; k++)   
            {
                if(cost[j] != max_int && adj_m[j][k] != 0 && cost[k] > cost[j] + adj_m[j][k])
                {
                    cost[k] = cost [j] +  adj_m[j][k];
                    p[k] = j;
                }
            }
        }
    }

    if(measure) path(p, cost, V, start);

    delete [] p; 
    delete [] cost;  
}


#endif