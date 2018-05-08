#include "History.h"
#include "globals.h"
using namespace std;



//History initializer//
//Goes through and creates a map of dots to represent the locations that will eventually show how many flatulans were attempted to be converted at that point

History::History(int nRows, int nCols)		
{
	m_rowz = nRows;
	m_colz = nCols;
	for (int i = 0; i < m_rowz; i++)
	{
		for (int j = 0; j < m_colz; j++)
		{
			notConverted[i][j] = '.';
		}
	}

}

//records the position of a flatulan that was unsuccessfully attempted to be converted
bool History::record(int r, int c)
{
	if (r > m_rowz || c > m_colz || r < 0 || c < 0)
		return false;
	if (notConverted[(r - 1)][(c - 1)] >= 'A' && notConverted[(r - 1)][(c - 1)] <= 'Z')
		notConverted[(r - 1)][(c - 1)] += 1;
	else
		notConverted[(r - 1)][(c - 1)] = 'A';
	return true;
}

//clears the screen and displays the current "notConverted" array that is holding all previously recored locations
void History::display() const
{
	clearScreen();
	for (int i = 0; i < m_rowz; i++)
	{
		for (int j = 0; j < m_colz; j++)
			cout << notConverted[i][j];
		cout << endl;
	}
	cout << endl;
}