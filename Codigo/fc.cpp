//Foward Cheking
#include "fc.h"

/*
	int ActualCity
        int PastCity
        vector<int> Trip
        vector<int> Rest_d1 
        vector<int> Rest_d2
*/

bool MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<Umpire> &Refs, vector<vector<int> > &Games)
{
	
        for (int NumUmpire = 0; NumUmpire < NLocals; NumUmpire++)
        {
                for (InitLocal; InitLocal < NLocals; InitLocal++)
                {
                        cout << "Fecha: " << InitWeek << " Local: " << InitLocal << endl;

                        if (CheckFC(Refs, NumUmpire, Games[InitWeek][InitLocal]))
                        {
				Refs[NumUmpire].ActualCity = Games[InitWeek][InitLocal]; // Asigno!
                                Refs[NumUmpire].Trip.push_back(Games[InitWeek][InitLocal]);

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





/*
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
bool CheckFC(vector<Umpire> Ref, int NumRef,int Game)
{
	return true;
}

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

