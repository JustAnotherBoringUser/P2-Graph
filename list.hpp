#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "graph.hpp"

using namespace std;

class List : public Graph {

protected:

struct  List_neighbours  //struktura reprezentujaca pojedyncza liste sasiedztwa 
{
    int v2, w;    //v - wierzcholek z ktorym sie laczymy, w - waga
    List_neighbours* next;
};

List_neighbours **Atab;

    public:
    virtual void init(int V, int E, int** data, bool rn);
    virtual void print();
    virtual void BF(int start, bool measure);
    List() {Atab=nullptr;} 
    ~List() {
    if (Atab!=nullptr)
        {
    List_neighbours* list, *tmp; 
      for(int i = 0; i < V; i++) 
      {
        list = Atab[i];
        while(list)
        {
          tmp = list;
          list = list->next;
          delete tmp;
        }
      }
        delete [] Atab;  
    }
  }
};

void List::print() {
    List_neighbours* list;
    cout<< "\nLista sasiedztwa odczytanego grafu:\n";
    for(int i = 0; i < V; i++)
      {
        cout << i;
        list = Atab[i];
        while(list)
        {
          cout << ": [" << list->v2 << ";"<< list->w <<"] ";
          list = list->next;
        }
        cout << endl;
    }
    delete [] list; 
}

void List::init(int V, int E, int** data, bool rn) {

    if (Atab!=nullptr)
        {
    List_neighbours* list, *tmp; 
      for(int i = 0; i < this->V; i++) 
      {
        list = Atab[i];
        while(list)
        {
          tmp = list;
          list = list->next;
          delete tmp;
        }
      }
        delete [] Atab;  
    }
    this->V = V;
    this->E = E;

    Atab = new List_neighbours * [V]; 

    int v1, v2, weight;
    List_neighbours* lst;

    for(int i = 0; i < V; i++)   ///wypelniamy tablice list NULL'ami
    {
        Atab[i] = nullptr;
    }

    for(int i = 0; i < E; i++)   //tworzymy listy dla grafu skierowanego
    {
        v1 = data[i][0];    //wczytujemy dane z reprezentaiji grafu z pliku
        v2 = data[i][1];
        weight = data[i][2];

        lst = new List_neighbours;

        lst->v2 = v2;
        lst->w = weight;
        lst->next = Atab[v1];
        Atab[v1] = lst;
    }

//dodatkowe instrukcje gdy graf nieskierowany:

if(rn){ 
    for(int i = 0; i < E; i++)  
    {
        v2 = data[i][0];    //wczytujemy dane z reprezentaiji grafu z pliku
        v1 = data[i][1];
        weight = data[i][2];

        lst = new List_neighbours;

        lst->v2 = v2;
        lst->w = weight;
        lst->next = Atab[v1];
        Atab[v1] = lst;
    }
  }
    //print();  
}

void List::BF(int start, bool measure) 
{ 
    List_neighbours* l_adj; //lista sasiedztwa

    int* p;     //wskaznik na tablice dynamiczna poprzednikow
    p = new int [V];

    int const max_int=2147483647;   //maksymalna wartosc int w 32bit

    int* cost;    //wskaznik na tab kosztow
    cost = new int [V];

    for(int i = 0; i < V; i++)
    {
        p[i] = -1;
        cost[i] = max_int; //koszty dojscia ustawiamy na maxa
    }

    cost[start] = 0;  //zerujemy koszt dojscia do Vstart

    for(int i = 1; i < V; i++)
    { 
        for(int j = 0; j < V; j++)  //przeszukujemy liste sasiedztwa
        {
            for(l_adj = Atab[j]; l_adj; l_adj = l_adj -> next)
            {
                if(cost[j] != max_int && cost[l_adj -> v2] > cost[j] + l_adj -> w /*&& cost[l_adj -> v2]>0*/)
                {
                    cost[l_adj -> v2] = cost [j] + l_adj -> w;
                    p[l_adj -> v2] = j;
                }
            }
        }
    }

    if(measure)  path(p, cost, V, start); //zapis sciezki do pliku 
    delete [] p; 
    delete [] cost;          
}

#endif