#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

bool isNumeric(string pszInput); //Check if STRING is a number
int StrToInt(string toInt); //Transform STRING to INT

vector<vector<int> > matDistances(int rowAway, int colHome, string strMat); // Initialize Matrix of distances
vector<vector<int> > matWeeks(int numWeek, int numHome, string strMat); // Initialize Matrix of domains


 
#endif
