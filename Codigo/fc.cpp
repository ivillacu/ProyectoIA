#include "fc.h"


void MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<vector<Umpire> > &Refs, vector<vector<int> > &Games, int NumUmpire, vector<Umpire> &Sol)
{
	int NFalses = 0, NSol = 0;
	for (InitWeek = 0; InitWeek < NWeeks;InitWeek++)
	{
		//cout << "Weeks" << endl;
		for (NumUmpire;NumUmpire < NLocals;NumUmpire++)
		{
			//cout << "Umpire" << endl;
			if ( InitWeek != 0)
			{
				Refs[InitWeek][NumUmpire].ActualCity = Refs[InitWeek - 1][NumUmpire].ActualCity; // Asigno!
                                Refs[InitWeek][NumUmpire].Trip = Refs[InitWeek - 1][NumUmpire].Trip;
				Refs[InitWeek][NumUmpire].Rest_d1 = Refs[InitWeek - 1][NumUmpire].Rest_d1;
				Refs[InitWeek][NumUmpire].Rest_d2 = Refs[InitWeek - 1][NumUmpire].Rest_d2;
			}
			for(InitLocal;InitLocal < NLocals;InitLocal++)
			{
				if ( CanAssign(Games[InitWeek][InitLocal], Refs, NumUmpire, InitWeek) )
				{
					cout << "\n-- En Week: " << InitWeek << " Umpire: " << NumUmpire << " Local: " << InitLocal << " Asigno: " << Games[InitWeek][InitLocal] << "\n" << endl;
        				Refs[InitWeek][NumUmpire].ActualCity = Games[InitWeek][InitLocal]; // Asigno!
        				Refs[InitWeek][NumUmpire].Trip.push_back(Games[InitWeek][InitLocal]);
					ShiftAssign(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek);
       	 				ShiftRest(Refs, NumUmpire, Games[InitWeek][InitLocal], InitWeek);
        				Games[InitWeek][InitLocal] *= -1;
					cout << "Game[" << InitWeek << "][" << InitLocal << "]: " << Games[InitWeek][InitLocal] << "\n" << endl;
					NFalses = 0;
					InitLocal = 0;
					break;
				}
				
				NFalses++;
				cout << "Week: " << InitWeek << " Umpire: " << NumUmpire << " N Falsos: " << NFalses << " Game: " << Games[InitWeek][InitLocal]  << endl;
				if ( (NFalses == NLocals))
				{
					cout << "Entre a Falsos" << endl;
					//cout << "NumUmpire: " << NumUmpire << " Week: " << InitWeek << endl;

					if ( NumUmpire == 0)
					{
						cout << "NumUmpire = 0, Cambiando Week Anterior: " << InitWeek - 1 << endl;
						for (int Init = 0;Init < NLocals;Init++)
                                                {       //cout << "Antes Game[" << InitWeek - 1 << "][" << Init << "]: " << Games[InitWeek - 1][Init] << "\n" << endl;
							if ( Games[InitWeek - 1][Init] < 0)
                                                        	Games[InitWeek - 1][Init] *= -1;
                                                        //cout << "Despues Game[" << InitWeek - 1 << "][" << Init << "]: " << Games[InitWeek - 1][Init] << "\n" << endl; 
                                                }
						
						InitWeek -= 1;
						NumUmpire = NLocals - 1;
						InitLocal = 0;
						NFalses = 0;
					}
					else
					{
						cout << "NumUmpire > 0" << endl;
						if (Refs[InitWeek][NumUmpire].Assign.size() == 1)
						{
							Refs[InitWeek][NumUmpire].Assign[0] = 0;
						}
						else
						{
							 Refs[InitWeek][NumUmpire].Assign.pop_back();
						}

						for (int Init = 0;Init < NLocals;Init++)
                                                {       //cout << "Antes Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
							if ( Games[InitWeek][Init] < 0)
                                                        	Games[InitWeek][Init] *= -1;
                                                        //cout << "Despues Game[" << InitWeek << "][" << Init << "]: " << Games[InitWeek][Init] << "\n" << endl;
                                                }
						NumUmpire -= 1;
						InitLocal = 0;
						NFalses = 0;
						
					}
				}
			}
			if (((InitWeek == NWeeks - 1) && (NumUmpire == NLocals - 1)))
                                {
                                        cout << "\n Solucion \n" << endl;
                                        CalcSol(Refs, InitWeek, (NLocals - 1));
                                }
		}
		
		NumUmpire = 0;
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

/*
bool MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<Umpire> &Refs, vector<vector<int> > &Games, int NumUmpire)
{
 int NFalses = 0;
 cout << "\n Week: " << InitWeek << "\n" <<endl;
 
 for (NumUmpire; NumUmpire < NLocals; NumUmpire++)
 {
	cout << "Umpire: " << NumUmpire << endl;

	for (InitLocal; InitLocal < NLocals; InitLocal++)
        {
		cout << "Arr y Local: " << InitLocal << " <> " << Games[InitWeek][InitLocal] << endl;

		if(CheckandAssign(Games[InitWeek][InitLocal], Refs, NumUmpire))
		{	
			if ((InitWeek == (NWeeks - 1)) && (InitLocal == (NLocals - 1))) // Condicion de termino
        		{
                		cout << "Termine Recursion" << endl;
                		return true;
			}
			if (InitLocal <= (NLocals - 1) && NumUmpire == (NLocals - 1))
			{
				MainFC(NWeeks, NLocals, InitWeek + 1, 0, Refs, Games, 0);
			}
			else
                        {
                                MainFC(NWeeks, NLocals, InitWeek, 0, Refs, Games, NumUmpire + 1);

                        }        
		}
		else
		{
			NFalses++;
			cout << "Cant Falses: "<< NFalses << endl;
		}
		
 	}	
 }
}

bool CheckandAssign(int &Game, vector<Umpire> &Ref, int NumUmpire)
{
	if((IsIn(Ref[NumUmpire].Rest_d1, Game) || IsIn(Ref[NumUmpire].Rest_d2, Game)) || Game < 0)
	{
		cout << "Existe restriccion" << endl;
		return false;
	}
	cout << "No existe restriccion, Asigno: " << Game << endl;
	Ref[NumUmpire].ActualCity = Game; // Asigno!
	Ref[NumUmpire].Trip.push_back(Game);
	ShiftRest(Ref, NumUmpire, Game);
	Game = (Game * -1);	
	return true;
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

void ShiftRest(vector<Umpire> &Refs, int NumUmpire, int Game)
{
	Refs[NumUmpire].Rest_d1.erase(Refs[NumUmpire].Rest_d1.begin(), Refs[NumUmpire].Rest_d1.begin() + 1);
	Refs[NumUmpire].Rest_d1.push_back(Game);

	Refs[NumUmpire].Rest_d2.erase(Refs[NumUmpire].Rest_d2.begin(), Refs[NumUmpire].Rest_d2.begin() + 1);
	Refs[NumUmpire].Rest_d2.push_back(Game);
}


/*
bool MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<Umpire> &Refs, vector<vector<int> > &Games)
{
	if ((InitWeek == (NWeeks - 1)) && (InitLocal == (NLocals - 1))) // Condicion de termino
        {
        	cout << "Termine Recursion" << endl;
                return true;
        }	

        for (int NumUmpire = 0; NumUmpire < NLocals; NumUmpire++)
        {
                for (InitLocal; InitLocal < NLocals; InitLocal++)
                {
                        cout << "Fecha: " << InitWeek << " Local: " << InitLocal << endl;

                        if (CheckFC(Refs, NumUmpire, Games))
                        {
				//Refs[NumUmpire].ActualCity = Games[InitWeek][InitLocal]; // Asigno!
                                //Refs[NumUmpire].Trip.push_back(Games[InitWeek][InitLocal]);
for (InitLocal; InitLocal < NLocals; InitLocal++)
                                if ((InitWeek == (NWeeks - 1)) && (InitLocal == (NLocals - 1)))
                                {
                                        cout << "Termine Recursion" << endl;
                                        return true;
                                }
                                
                                if (InitLocal == (NLocals - 1))
                                {       
                                        MainFC(NWeeks, NLocals, InitWeek + 1, 0, Refs, Games);
                                }
                        }
                }
        }
}

bool CheckFC(vector<Umpire> Ref, int NumRef, vector<vector<int> > &Games)
{
        if(IsInRest(Ref[NumRef]))
	return true;
}

bool IsInRest()
{
	
}




bool MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<Umpire> &Refs, vector<vector<int> > &Games, int NumUmpire)
{
	for (InitWeek; InitWeek < NWeeks; InitWeek++)
	{
		for (InitLocal; InitLocal < NLocals; InitLocal++)
		{
			cout << "Fecha: " << InitWeek << " Local: " << InitLocal << endl;

			if (CheckFC(Refs, NumUmpire, Games[InitWeek][InitLocal]))
			{
				if ((InitWeek == (NWeeks - 1)) && (InitLocal == (NLocals - 1)))
                                {
                                        cout << "Termine Recursion" << endl;
                                        return true;
                                }

				Refs[NumUmpire].ActualCity = Games[InitWeek][InitLocal]; // Asigno!
				Refs[NumUmpire].Trip.push_back(Games[InitWeek][InitLocal]);
        			
				if (InitLocal == (NLocals - 1))
        			{       
                			MainFC(NWeeks, NLocals, InitWeek + 1, 0, Refs, Games, 0);
        			}
        			else
        			{
               			 	MainFC(NWeeks, NLocals, InitWeek, InitLocal + 1, Refs, Games, NumUmpire + 1);

				}
			}
		}
	}
}
*/

/*
void MainFC(int NWeeks, int NLocals, vector<Umpire>* Refs, vector<vector<int> > Games)
{
	int CheckLocal = NLocals;

	for(int week = 0; week < NWeeks; week++)
	{
		for(int local = 0; local < NLocals; local++)
		{
			Refs[local].ActualCity = Games[week][local];
			cout << Refs[local].ActualCity << endl;
			if((local - 1) == 0 && week == (NWeeks - 1))
			{
				cout << "Termine EL FC" << endl;
			}
			else
			{
				if (CheckFC)
				{
					
				{
			}
		}
	}
}
*/

