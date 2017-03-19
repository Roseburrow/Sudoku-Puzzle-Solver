#include "CellBlock.h"
#include <iostream>

CellBlock::CellBlock()
{
}

CellBlock::~CellBlock()
{
	/*for (int i = 0; i < 9; ++i)
	{
		delete cells[i];
	}*/
}

void CellBlock::SetCell(int index, Cell *cell)
{
	cells[index] = cell;
}

int CellBlock::GetValue(int index)
{
	return cells[index]->GetValue();
}

Cell* CellBlock::GetCell(int index)
{
	return cells[index];
}
