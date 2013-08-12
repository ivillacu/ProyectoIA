#include "funciones.h"

bool isNumeric( string pszInput )
{
        istringstream iss( pszInput );
        int dTestSink;
        iss >> dTestSink;
        // was any input successfully consumed/converted?
        if ( ! iss )
                return false;
        // was all the input successfully consumed/converted?
        return ( iss.rdbuf()->in_avail() == 0 );
}

int StrToInt(string toInt)
{
        int inInt;
        stringstream(toInt) >> inInt;
        return inInt;
}

vector<vector<int> > matDistances(int rowAway, int colHome, string strMat)
{
        int row = 0, col = 0;
        string temp;
        vector<int> Home(colHome);
        vector<vector<int> > Mat(rowAway, Home);
        istringstream iss(strMat);
 
        while ( getline(iss,temp, ' '))
        {
                if(isNumeric(temp))
                {
                        Mat[row][col] = StrToInt(temp);
                        //cout <<"Fila: " << Fila << "Columna: " << Col << "Dato: " << StrToInt(temp)  << endl;
                        col++;
                }
                if(col == colHome)
                {
                        row++;
                        col = 0;
                }
        }

        return Mat;
}


vector<vector<int> > matWeeks(int numWeek, int numHome, string strMat)
{
	int row = 0, col = 0, homeCheck = 0;
	string temp;
	vector<int> numHomes(numHome);
	vector<vector<int> > Mat(numWeek, numHomes);
	istringstream iss(strMat);
	
	while(getline(iss, temp, ' '))
	{
		if(isNumeric(temp))
		{
			if ( StrToInt(temp) > 0)
                        {
				Mat[row][homeCheck] = (col + 1);
				//cout << "Dentro Matrix -- Row: " << row << " Col: " << homeCheck << " Matriz: " << Mat[row][homeCheck] << endl;
				homeCheck++;
			}
		
		col++;
		}
		if(homeCheck == numHome)
		{
			//cout << "Fecha: " << row << ". Encontrado los Locales \n" << endl;
			homeCheck = 0;
			col = 0;
			row++;
			getline(iss, temp, '\n');
		}
	}
	return Mat;
}

