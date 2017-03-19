#pragma once

#include "Cell.h"

class CellBlock
{
public:
	CellBlock(void);
	~CellBlock(void);

	void SetCell(int index, Cell *cell);
	Cell* GetCell(const int index);
	int GetValue(const int index);

private:
	Cell* cells[9];
};

