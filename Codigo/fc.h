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

struct Umpire
{
        int ActualCity;
        int PastCity;
        vector<int> Trip;
        vector<int> Rest_d1;
	vector<int> Rest_d2;
};


bool MainFC(int NWeeks, int NLocals, int InitWeek, int InitLocal, vector<Umpire> &Refs, vector<vector<int> > &Games);
bool CheckFC(vector<Umpire> Ref, int NumRef, int Game);

#endif

