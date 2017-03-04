#pragma once

#include "Cell.h"
class CellBlock
{
public:
	CellBlock(void);
	~CellBlock(void);

private:
	Cell* cells[9];
};

