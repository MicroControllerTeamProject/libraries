#include "LCDRowShift.h"


LCDRowShift::LCDRowShift()
{
	_currentRow = _totalItems;
}


LCDRowShift::~LCDRowShift()
{
}


int LCDRowShift::GetCurrentRow()
{
	int currentRow = --_currentRow;
	if (_currentRow < 0)
	{
		currentRow = _currentRow + _totalItems;
	}
	return currentRow;
}


void LCDRowShift::SetTotalItems(int totalItems)
{
	_totalItems = totalItems;
}
void LCDRowShift::SetTotalLcdRows(int numberOfLcdRows)
{
	_numberOfLcdRows = numberOfLcdRows;
}
