//Foward Cheking .h
#ifndef FC_H
#define FC_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

struct Umpire // Estructura de arbitro
{
        int ActualCity;
	vector<int> Assign;
        vector<int> Trip;
        vector<int> Rest_d1;
	vector<int> Rest_d2;
};


vector<vector<Umpire> > MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<vector<Umpire> > &Refs, vector<vector<int> > &Games, int NumUmpire, vector<Umpire> &Sol, vector<vector<int> > MatDist);
bool CanAssign(int Game, vector<vector<Umpire> > &Ref, int NumUmpire, int InitWeek);

bool CheckandAssign(int &Game, vector<Umpire> &Refs, int NumUmpire);

bool IsIn(vector<int> v, int x);

void ShiftRest(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek);

int ShowVector(vector<int> v);

void ShiftAssign(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek);

void CalcSol( vector<vector<Umpire> > Refs, int InitWeek, int NLocals, vector<vector<int> > MatDist);

void ShiftAssignR(vector<vector<Umpire> > &Refs, int NumUmpire, int Game, int InitWeek);
#endif

