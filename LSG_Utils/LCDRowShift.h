#pragma once
class LCDRowShift
{
public:
	LCDRowShift();
	~LCDRowShift();
	int _totalItems;
	int _numberOfLcdRows;
	int _currentRow;
	int _currentRowStored;
	int GetCurrentRow();
	void SetTotalItems(int totalItems);
	void SetTotalLcdRows(int numberOfLcdRows);

};

