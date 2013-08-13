#include "fc.h"


void MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<vector<Umpire> > &Refs, vector<vector<int> > &Games, int NumUmpire, vector<Umpire> &Sol)
{
	int NFalses = 0, NSol = 0;
	bool Sum = true, back = false;
	while(InitWeek < NWeeks)
	{
		cout << "\nWeek: " << InitWeek << "" << endl;
		while(NumUmpire < NLocals)
		{
			cout << "- NumUmpire: " << NumUmpire << " " << endl;
			if ( InitWeek != 0)
			{
				Refs[InitWeek][NumUmpire].ActualCity = Refs[InitWeek - 1][NumUmpire].ActualCity; // Asigno!
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
        				Refs[InitWeek][NumUmpire].Trip.push_back(Games[InitWeek][InitLocal]);
					ShiftAssign(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek);
       	 				ShiftRest(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek);
        				Games[InitWeek][InitLocal] *= -1;
					cout << " --> Game[" << InitWeek << "][" << InitLocal << "]: " << Games[InitWeek][InitLocal] << "\n" << endl;
					NFalses = 0;
					InitLocal = 0;
					break;
				}

				if ((back == true) && (Games[InitWeek][InitLocal] == Refs[InitWeek][NumUmpire].Assign[NLocals - 1]))
				{
					ShiftAssignR(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek);
					back = false;
				}
				
				NFalses++;
				cout << "XXX -- Week: " << InitWeek << " Umpire: " << NumUmpire << " N Falsos: " << NFalses << " Game: " << Games[InitWeek][InitLocal]  << "\n" << endl;
				if ( (NFalses == NLocals))
				{
					cout << " --- Backtrack --- \n" << endl;
					//cout << "NumUmpire: " << NumUmpire << " Week: " << InitWeek << endl;

					if ( NumUmpire == 0)
					{
						cout << " *** Salto Week Anterior *** --> NumUmpire = 0 --> Week: " << InitWeek - 1 << "\n" <<endl;
					/*	for (int Init = 0;Init < NLocals;Init++)
                                                  {
                                                    cout << "Check Assignado Game[" << InitWeek - 1 << "][" << Init << "]: " << Games[InitWeek - 1][Init] << "\n" << endl;
                                                    if ((Games[InitWeek - 1][Init] < 0))
                                                        for(int x = 0; x < NLocals - 1; x++)
                                                        {
                                                                if (!IsIn(Refs[InitWeek - 1][x].Assign, (Games[InitWeek - 1][Init] * -1)))
                                                                {
                                                                //      cout << "Antes Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
                                                                        cout << "Cambiando Asignado" << endl;
                                                                        Games[InitWeek - 1][Init] *= -1;
                                                                //      cout << "Despues Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
                                                                }
                                                        }
                                                  }
					/*	for (int Init = 0;Init < NLocals;Init++)
                                                {       //cout << "Antes Game[" << InitWeek - 1 << "][" << Init << "]: " << Games[InitWeek - 1][Init] << "\n" << endl;
							Games[InitWeek - 1][Init] *= -1;
                                                        for(int x = 0; x < NumUmpire - 1; x++)
                                                                if (!IsIn(Refs[InitWeek - 1][x].Assign, Games[InitWeek - 1][Init]))
                                                                        Games[InitWeek - 1][Init] *= -1;
                                                        //cout << "Despues Game[" << InitWeek - 1 << "][" << Init << "]: " << Games[InitWeek - 1][Init] << "\n" << endl; 
                                                }
					*/
					//	ShiftAssignR(Refs, NLocals - 1, Games[InitWeek][InitLocal], InitWeek - 1);	
						InitWeek -= 1;
						NumUmpire = NLocals - 1;
						InitLocal = 0;
						NFalses = 0;
						Sum = false;
						break;
					}
					else
					{
						cout << "*** Salto a Umpire Anterior ***" << endl;
						//cout << "Tamaño: " << Refs[InitWeek][NumUmpire].Assign.size() << " Shift R " << endl;
					//	cout << "Sacando Derecha --> Game: " << Games[InitWeek][InitLocal] << " de "<< endl; 						
					//	ShiftAssignR(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek);
							
						if (NumUmpire <= 1)
						{
						  for (int Init = 0;Init < NLocals;Init++)
						    if ((Games[InitWeek][Init] < 0))
							{
                                                       //      cout << "Antes Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
                                                         cout << "Cambiando Asignado" << endl;
                                                         Games[InitWeek][Init] *= -1;
                                                                //      cout << "Despues Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
                                                        }
						}
						else
						{
						  for (int Init = 0;Init < NLocals;Init++)
                                                  {       
						    cout << "Check Assignado Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
						    if ((Games[InitWeek][Init] < 0))
							for(int x = 0; x < NumUmpire - 1; x++)
							{
								if (!IsIn(Refs[InitWeek][x].Assign, (Games[InitWeek][Init] * -1)))
								{
								//	cout << "Antes Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
									cout << "Cambiando Asignado" << endl;
									Games[InitWeek][Init] *= -1;
								//	cout << "Despues Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
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
                        	cout << "\n Solucion: " << InitWeek << " <> " << NumUmpire << "\n" << endl;
                                CalcSol(Refs, InitWeek, (NLocals - 1));
                        }
			if (!(Sum == false))
				NumUmpire++;
			Sum = true;
		}
		NumUmpire = 0;
		InitWeek++;
	}

}
void CalcSol( vector<vector<Umpire> > Refs, int InitWeek, int NLocals)
{
  for (int x = 0; x <= NLocals; x++)
  {
	for (int z = 0; z < Refs[InitWeek][NLocals].Trip.size(); z++)
	{
		cout << Refs[InitWeek][x].Trip[z] << " ";
	}
  	cout << "\n" << endl;
  }
}


int ShowVector(vector<int> v)
{
	for (int x = 0; x < v.size(); x++)
		cout << v[x] << " " << endl;
}

bool CanAssign(int Game, vector<vector<Umpire> > &Ref, int NumUmpire, int InitWeek)
{
	//cout << "CanAssign" << endl;
	if((IsIn(Ref[InitWeek][NumUmpire].Rest_d1, Game) || IsIn(Ref[InitWeek][NumUmpire].Rest_d2, Game)) || Game < 0 || IsIn(Ref[InitWeek][NumUmpire].Assign, Game))
        {
		//cout << "Restriccion <> Week: " << InitWeek << " Umpire: " << NumUmpire << " Local: " << Game << endl;
                return false;
        }
	else
	{
		return true;
	}
}

bool IsIn(vector<int> v, int x)
{
	//cout << "IS-IN" << endl;
        if(find(v.begin(), v.end(), x) != v.end())
        {
                return true;
        }
        else
        {
                return false;
        }
}

void ShiftRest(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek)
{
	//cout << "Shift Restricciones" << endl;
        Refs[InitWeek][NumUmpire].Rest_d1.erase(Refs[InitWeek][NumUmpire].Rest_d1.begin(), Refs[InitWeek][NumUmpire].Rest_d1.begin() + 1);
        Refs[InitWeek][NumUmpire].Rest_d1.push_back(Game);

        Refs[InitWeek][NumUmpire].Rest_d2.erase(Refs[InitWeek][NumUmpire].Rest_d2.begin(), Refs[InitWeek][NumUmpire].Rest_d2.begin() + 1);
        Refs[InitWeek][NumUmpire].Rest_d2.push_back(Game);
}

void ShiftAssign(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek)
{
        Refs[InitWeek][NumUmpire].Assign.erase(Refs[InitWeek][NumUmpire].Assign.begin(), Refs[InitWeek][NumUmpire].Assign.begin() + 1);
        Refs[InitWeek][NumUmpire].Assign.push_back(Game);
}

void ShiftAssignR(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek)
{
        Refs[InitWeek][NumUmpire].Assign.pop_back();
        Refs[InitWeek][NumUmpire].Assign.insert(Refs[InitWeek][NumUmpire].Assign.begin(),0);
}




