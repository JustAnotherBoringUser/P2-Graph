#include <iostream>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <time.h>
#include <string>

#include "matrix.hpp"
#include "list.hpp"

using namespace std;

double result(int V, int E, int Vstart, Graph* randG)
{
    randG->random(V, E);
  
    auto start = std::chrono::high_resolution_clock::now();    

    randG->BF(Vstart, false);   
  
    auto stop = std::chrono::high_resolution_clock::now();   

    return std::chrono::duration<double, std::milli>(stop - start).count();  
}

void test(fstream& file)
{
    Matrix Mg;   
    List Lg;
    
    file.open("Wyniki.txt", ios_base::app);
    int Vstart, E;
    int vert[5] = {5, 10, 50, 75, 100}; 
	double dens[4] = {0.25, 0.5, 0.75, 1};

        file << "\nDla macierzy:\n";
        cout << "\nDla macierzy:\n";
        for (double g : dens) {
	    file <<"\ngestosc "<< g*100 <<"%\n ";
        //cout <<"\ngestosc "<< g*100 <<"%\n ";

		for (int V : vert) {
			file<<V<<" wierzcholkow: ";
            //cout <<V<<" wierzcholkow: ";
             E =(g*V*(V - 1))/2;
			double sr = 0;

			for (int i = 0; i < 100; ++i) { 

                Vstart = rand() % V;
				sr += result(V, E, Vstart, &Mg);

			}
			file << sr / 100 << "\n"; //sredni czas
            //cout << sr / 100 << "\n";
		}
		cout << "\nAlgorytm wykonal sie dla gestosci:" << 100*g << endl;
	}

        file << "\nDla listy:\n";
        cout << "\nDla listy:\n";
        for (double g : dens) {
	    file <<"\ngestosc "<< g*100 <<"%\n ";
        //cout <<"\ngestosc "<< g*100 <<"%\n ";

		for (int V : vert) {
			file<<V<<" wierzcholkow: ";
            //cout <<V<<" wierzcholkow: ";
            E =(g*V*(V - 1))/2;
			double sr = 0;

			for (int i = 0; i < 100; ++i) { 

                Vstart = rand() % V;
				sr += result(V, E, Vstart, &Lg);
			}
			file << sr / 100 << "\n"; //sredni czas
            //cout << sr / 100 << "\n"; 
		}
		cout << "\nAlgorytm wykonal sie dla gestosci:" << 100*g << endl;
	}

    file.close();                        ///zamykamy strumien danych

    cout << "Pomyslnie zapisano do pliku\n";
}

void shortest() {

    ifstream wejscie;     

    Matrix Mg;   
    List Lg;

    wejscie.open("Graf.txt", ios_base::in);
    fstream wyjscie;
    int V, E, start;
    int** graf;

    //try{

        wejscie >> E >> V >> start; //wczytujemy V, E i start

        graf = new int* [E];    ///alokowanie pamieci dla tablicy dynamicznej dwuwymiarowej

        for(int i = 0; i < E; i++)
        {
            graf[i] = new int [3];
        }
		
		 for(int j = 0; j < E; j++)    ///wczytujemy graf z pliku do tablicy dynamicznej 2-wymiarowej
		{
			wejscie >> graf[j][0] >> graf[j][1] >> graf[j][2];
            //file >> v1 >> v2 >> weight;
		}     

        int wybor;

            cout << "Wybierz opcje: \n1.Lista 2.Macierz \n";
            cin >> wybor;
          
        switch(wybor)
        {
            case 1: { Lg.init(V,E,graf,false); Lg.print(); Lg.BF(start,true); break;}
            case 2: { Mg.init(V,E,graf,false); Mg.print(); Mg.BF(start,true); break;}
            //case 3: break;
        }

        cout<<"Sciezki i koszty drogi zapisano w pliku wynikowym Path.txt\n";

        for(int z = 0; z < E; ++z) //usuwanie
        {
            delete [] graf[z];
        }
        delete [] graf;
    //}

    wejscie.close();    

    cout << "Pomyslnie zapisano do pliku\n";

    /*
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Allocation failed: " << e.what() << '\n';
    }
*/
}

void view_random(){ //odkomentować PRINT
	
	Matrix M;   
    List L;
	int V, E;
	
	V = rand() % 40;
	E = rand() % 40;
	
	        int wybor;

        ///*******************************|->menu wczytywania danych
            cout << "Wybierz opcje: \n1.Macierz 2.Lista \n";
            cin >> wybor;
          
        switch(wybor)
        {
            case 1: { M.random(V, E); M.print(); break;}
            case 2: { L.random(V, E); L.print(); break;}
            //case 3: break;
        }
    
}

int main()
{   

    srand(time(NULL));  
    fstream setka;
    
	
    int ch;    

    while(ch!=3)
    {
        
            cout << "Wybierz opcje: \n1. 100 instancji 2. problem najkrotszej sciezki 3.losowy graf 4.koniec\n";
            cin >> ch;
          
        switch(ch)
        {
            case 1: test(setka); break;
            case 2: shortest(); break;
            case 3: view_random(); break;
			case 4: break;
        }
    }
    

    return 0;
}