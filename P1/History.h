#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include "globals.h"


////////  Interface for History Class  ////////

class History
{
public:								//Given Functions
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;
private:							//private member variables to support implementation
	int m_rowz;
	int m_colz;
	char notConverted[MAXROWS][MAXCOLS];
};
#endif