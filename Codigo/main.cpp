#include "funciones.h"
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
        int N_Teams, Team, Fila = 0, Col = 0, Weeks;
        vector<vector<int> > MatDist, MatGames;
        vector<int> domLocales;

        ifstream infile;
        infile.open("Instancias/umps4.dat.txt");// Abro el archivo

        getline(infile,Basura,'='); //Saca lo que esta antes de =
        getline(infile,Num_Teams,';');//Saca lo que esta antes de ;

        N_Teams = StrToInt(Num_Teams);//Cambio str y guerdo la cantidad de equipos
        Weeks = 2*N_Teams - 2;

        getline(infile,strMat,';');//Obtengo Distancias
        MatDist =  matDistances(N_Teams,N_Teams, strMat);

        getline(infile,strMat,';');//Obtengo oponentes
	matWeeks(Weeks, N_Teams/2, strMat);
        /*
	for(int Dia = 0; Dia < Fechas; Dia++)
        {
                domLocales = CheckLocales(MatGames, Dia);
                for_each(domLocales.begin(), domLocales.end(), FC_Main);
        }
	*/
        infile.close();
        return 0;
}

