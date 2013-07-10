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
                if(col > colHome)
                {
                        row++;
                        col = 0;
                }
        }

        return Mat;
}


vector<vector<int> > matWeeks(int numWeek, int numHome, string strMat)
{

	int row = 0, col = 0, team = 0;
	string temp;
	vector<int> numWeeks(numWeek);
	vector<vector<int> > Mat(numHome, numWeeks);
	istringstream iss(strMat);
	
	while ( getline(iss,temp, ' ') )
	{
		if ( isNumeric(temp) && StrToInt(temp) > 0)
		{
			Mat[row][col] = (team + 1);
			cout <<"Fecha: " << (row + 1) << "Pos. Local " << col << "Local: " << (team + 1)  << endl;
			col++;
		}

		team ++;

		if(col > numHome)
                {
                        row++;
                        col = 0;
			team = 0;
                }

	}
}	
