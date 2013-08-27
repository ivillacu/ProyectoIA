#include "fc.h"


vector<vector<Umpire> > MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<vector<Umpire> > &Refs, vector<vector<int> > &Games, int NumUmpire, vector<Umpire> &Sol, vector<vector<int> > MatDist)
{
	int chequeos = 0, optimo = 0;;ssigno
	int NFalses = 0, NSol = 0;
	bool Sum = true, back = false;
	while(InitWeek < NWeeks)
	{
		cout << "\nWeek: " << InitWeek << "" << endl;
		while(NumUmpire < NLocals)
		{
			cout << "- NumUmpire: " << NumUmpire << " " << endl;
			if ( InitWeek != 0) // Copia las asignaciones del umpire de la semana anterior, menos las assignaciones en assign
			{
				Refs[InitWeek][NumUmpire].ActualCity = Refs[InitWeek - 1][NumUmpire].ActualCity;
                                Refs[InitWeek][NumUmpire].Trip = Refs[InitWeek - 1][NumUmpire].Trip; 
				Refs[InitWeek][NumUmpire].Rest_d1 = Refs[InitWeek - 1][NumUmpire].Rest_d1;
				Refs[InitWeek][NumUmpire].Rest_d2 = Refs[InitWeek - 1][NumUmpire].Rest_d2;
			}
			while(InitLocal < NLocals)
			{
				cout << "-- InitLocal: " << InitLocal << "\n" << endl;
				if ( CanAssign(Games[InitWeek][InitLocal], Refs, NumUmpire, InitWeek) )
				{	
					cout << "--- En Week: " << InitWeek << " Umpire: " << NumUmpire << " Local: " << InitLocal << " Asigno: " << Games[InitWeek][InitLocal];
        				Refs[InitWeek][NumUmpire].ActualCity = Games[InitWeek][InitLocal]; // Asigno!
        				Refs[InitWeek][NumUmpire].Trip.push_back(Games[InitWeek][InitLocal]); // agrego a Trip
					ShiftAssign(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek); // Añado a Assign, sin aumentar el tamaño
       	 				ShiftRest(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek);// Añado las Rest, sin aumentar el tamaño
        				Games[InitWeek][InitLocal] *= -1;
					cout << " --> Game[" << InitWeek << "][" << InitLocal << "]: " << Games[InitWeek][InitLocal] << "\n" << endl;
					NFalses = 0;
					InitLocal = 0;
					chequeos++;
					break;
				}

				if ((back == true) && (Games[InitWeek][InitLocal] == Refs[InitWeek][NumUmpire].Assign[NLocals - 1]))
				{
					ShiftAssignR(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek); // Saca una asignacion si viene de un bactrack
					back = false;
				}
				
				NFalses++; // Cuando no se puede asignar
				chequeos++;
				cout << "XXX -- Week: " << InitWeek << " Umpire: " << NumUmpire << " N Falsos: " << NFalses << " Game: " << Games[InitWeek][InitLocal]  << "\n" << endl;
				if ( (NFalses == NLocals))
				{
					cout << " --- Backtrack --- \n" << endl;

					if ( NumUmpire == 0) // Para pasar a una week anterior
					{
						cout << " *** Salto Week Anterior *** --> NumUmpire = 0 --> Week: " << InitWeek - 1 << "\n" <<endl;
					
						if (InitWeek == 0)
						{
							NumUmpire = 0;
							InitWeek = 0;
						}
						else
						{
							InitWeek -= 1;
							NumUmpire = NLocals - 1;
						}

						InitLocal = 0;
						NFalses = 0;
						Sum = false;
						break;
					}
					else // Cuando se pasa solo a una arbitro anterior
					{
						cout << "*** Salto a Umpire Anterior ***" << endl;
						if (NumUmpire <= 1)
						{
						  for (int Init = 0;Init < NLocals;Init++) // Chequeo cada local para ver si esta asignado a un arbotro anterior, sino lo transformo a no asignado.
						    if ((Games[InitWeek][Init] < 0))
							{
                                                         cout << "Cambiando Asignado" << endl; 
                                                         Games[InitWeek][Init] *= -1;
                                                        }
						}
						else
						{
						  for (int Init = 0;Init < NLocals;Init++)
                                                  {       
						    cout << "Check Assignado Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
						    if ((Games[InitWeek][Init] < 0))
						    {
							cout << "Menor \n" << endl;
							for(int x = 0; x < NumUmpire - 1; x++)
							{
								 cout << "X: "<< x << endl;
								if (!IsIn(Refs[InitWeek][x].Assign, (Games[InitWeek][Init] * -1)))
								{
									cout << "Cambiando Asignado" << endl;
									Games[InitWeek][Init] *= -1;
								}
							}
						    }
                                                  }
						}
						NumUmpire -= 1;
						InitLocal = 0;
						NFalses = 0;
						Sum = false;
						back = true;
						break;
					}
				}
				InitLocal++;
			}
			if (((InitWeek == NWeeks - 1) && (NumUmpire == NLocals - 1)))
                        {
                        	cout << "\n Solucion: " << InitWeek << " <> " << NumUmpire << " Chequeos: " << chequeos << "\n" << endl;
                                CalcSol(Refs, InitWeek, (NLocals - 1), MatDist); // Manda a calcular la solucion
				return Refs;
                        }
			if (!(Sum == false))
				NumUmpire++;
			Sum = true;
		}
		NumUmpire = 0;
		InitWeek++;
	}

}
void CalcSol( vector<vector<Umpire> > Refs, int InitWeek, int NLocals, vector<vector<int> > MatDist)
{

int suma = 0, x, z, optimo = 0;

  for (x = 0; x <= NLocals; x++)
  {
	for (z = 0; z < Refs[InitWeek][NLocals].Trip.size() - 1; z++)
	{
		optimo += MatDist[Refs[InitWeek][x].Trip[z] - 1][Refs[InitWeek][x].Trip[z + 1] - 1];
		suma += MatDist[Refs[InitWeek][x].Trip[z] - 1][Refs[InitWeek][x].Trip[z + 1] - 1];
		
	}
	for (z = 0; z < Refs[InitWeek][NLocals].Trip.size(); z++)
        {
                cout << Refs[InitWeek][x].Trip[z] << " ";

        }
  	cout << " --> Suma: "<< suma << "\n" << endl;
	suma = 0;
  }
cout << "OPTIMO: " << optimo << endl;
}


int ShowVector(vector<int> v)
{
	for (int x = 0; x < v.size(); x++)
		cout << v[x] << " " << endl;
}

bool CanAssign(int Game, vector<vector<Umpire> > &Ref, int NumUmpire, int InitWeek)
{
	if((IsIn(Ref[InitWeek][NumUmpire].Rest_d1, Game) || IsIn(Ref[InitWeek][NumUmpire].Rest_d2, Game)) || Game < 0 || IsIn(Ref[InitWeek][NumUmpire].Assign, Game))
        {
                return false;
        }
	else
	{
		return true;
	}
}

bool IsIn(vector<int> v, int x)
{
        if(find(v.begin(), v.end(), x) != v.end())
        {
                return true;
        }
        else
        {
                return false;
        }
}

void ShiftRest(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek) // Añade las restricciones
{
        Refs[InitWeek][NumUmpire].Rest_d1.erase(Refs[InitWeek][NumUmpire].Rest_d1.begin(), Refs[InitWeek][NumUmpire].Rest_d1.begin() + 1);
        Refs[InitWeek][NumUmpire].Rest_d1.push_back(Game);

        Refs[InitWeek][NumUmpire].Rest_d2.erase(Refs[InitWeek][NumUmpire].Rest_d2.begin(), Refs[InitWeek][NumUmpire].Rest_d2.begin() + 1);
        Refs[InitWeek][NumUmpire].Rest_d2.push_back(Game);
}

void ShiftAssign(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek) // Añade las assinaciones
{
        Refs[InitWeek][NumUmpire].Assign.erase(Refs[InitWeek][NumUmpire].Assign.begin(), Refs[InitWeek][NumUmpire].Assign.begin() + 1);
        Refs[InitWeek][NumUmpire].Assign.push_back(Game);
}

void ShiftAssignR(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek) // quita asignaciones
{
        Refs[InitWeek][NumUmpire].Assign.pop_back();
        Refs[InitWeek][NumUmpire].Assign.insert(Refs[InitWeek][NumUmpire].Assign.begin(),0);
}




