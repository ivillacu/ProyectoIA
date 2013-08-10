#include "funciones.h"
#include "fc.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main ()
{
        string temp, Basura, strMat, Num_Teams, Dist;
        int N_Teams, N_Umpires, Team, Fila = 0, Col = 0, Weeks = 0, Debug = 0;
        vector<vector<int> > MatDist, MatGames;
        vector<int> domLocales;

        ifstream infile;
        infile.open("Instancias/umps4.dat.txt");// Abro el archivo

        getline(infile,Basura,'='); //Saca lo que esta antes de =
        getline(infile,Num_Teams,';');//Saca lo que esta antes de ;

        N_Teams = StrToInt(Num_Teams);//Cambio str y guerdo la cantidad de equipos
	N_Umpires = N_Teams/2;	
	
	vector<Umpire> Umpires(N_Umpires);
	
	cout << "Numero Teams: " << N_Teams << endl; 
        Weeks = 2*N_Teams - 2;
	cout << "Numero Weeks: " << Weeks << endl;

        getline(infile,strMat,';');//Obtengo Distancias
        MatDist =  matDistances(N_Teams,N_Teams, strMat);

        getline(infile,strMat,';');//Obtengo oponentes
	MatGames =  matWeeks(Weeks, N_Teams/2, strMat);
	//Muestra MatDist
	if (Debug == 1)
	{
		for(int i=0;i<MatDist.size(); i++) 
		{
      			for (int j=0;j<MatDist[i].size(); j++)
        			cout << MatDist[i][j] << " ";
			cout << endl;
   		}
		//Muestra MatFames
        	for(int i=0;i<MatGames.size(); i++) 
        	{
                	for (int j=0;j<MatGames[i].size(); j++)
                        	cout << MatGames[i][j] << " ";
			cout << endl;
        	}
	}
	//MainFC(Weeks,  N_Teams/2, Umpires, MatGames);
	bool tempo = MainFC(Weeks, N_Teams/2, 0, 0, Umpires, MatGames);
        /*
	for(int Dia = 0; Dia < Fechas; Dia++)
        {
                domLocales = CheckLocales(MatGames, Dia);
                for_each(domLocales.begin(), domLocales.end(), FC_Main);
        }
	*/
	cout << Umpires[1].ActualCity << endl;
	for (int x = 0; x < Umpires[0].Trip.size(); x++)
	{
		cout << "Ump: " << Umpires[0].Trip[x] << endl;
	}
	cout << MatGames[1][0] << endl;
	cout << "Termine: " << tempo << endl;
        infile.close();
        return 0;
}

