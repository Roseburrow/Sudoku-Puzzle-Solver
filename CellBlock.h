#pragma once

#include "Cell.h"

class CellBlock
{
public:
	CellBlock(void);
	~CellBlock(void);

	void SetCell(int index, Cell *cell);
	Cell* GetCell(const int index) const throw();
	int GetValue(const int index) const;
	void InitCells();

private:
	Cell* cells[9];
};

