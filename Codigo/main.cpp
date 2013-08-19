#include "funciones.h"
#include "fc.h"
#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char *argv[])
{
        string temp, Basura, strMat, Num_Teams, Dist, filename = "";
        int N_Teams, N_Umpires, Team, Fila = 0, Col = 0, Weeks = 0, Debug = 0, d1 = 0, d2 = 0;
        vector<vector<int> > MatDist, MatGames;
        vector<int> domLocales;

        if (!check_options(argc, argv, d1, d2, filename))
            return 1;

        ifstream infile;
        infile.open(filename.c_str());// Abro el archivo

        getline(infile,Basura,'='); //Saca lo que esta antes de =
        getline(infile,Num_Teams,';');//Saca lo que esta antes de ;

        N_Teams = StrToInt(Num_Teams);//Cambio str y guerdo la cantidad de equipos
	N_Umpires = N_Teams/2;
	cout << "Numero Teams: " << N_Teams << endl;
        Weeks = 2*N_Teams - 2;
        cout << "Numero Weeks: " << Weeks << endl;

	vector<Umpire> Umpires(N_Umpires), Sol;
	vector<vector<Umpire> > WeekUmpire(Weeks, Umpires), TUPSol;

	for (int wtmp = 0; wtmp < WeekUmpire.size(); wtmp++)
	  for (int tmp = 0; tmp < WeekUmpire[wtmp].size(); tmp++ )
          {
		WeekUmpire[wtmp][tmp].Assign.resize(N_Umpires,0);
                WeekUmpire[wtmp][tmp].Rest_d1.resize(d1,0);
                WeekUmpire[wtmp][tmp].Rest_d2.resize(d2,0);
          }
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

	TUPSol = MainFC(Weeks, N_Teams/2, 0, 0, WeekUmpire, MatGames,0, Sol, MatDist);
	cout << "Termine: " << endl;
        infile.close();
        return 0;
}

