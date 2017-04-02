#include "CellBlock.h"
#include <iostream>

CellBlock::CellBlock()
{
	InitCells();
}

CellBlock::~CellBlock()
{

}

void CellBlock::InitCells()
{
	for (int i = 0; i < 9; ++i)
	{
		cells[i] = NULL;
	}
}
void CellBlock::SetCell(int index, Cell *cell)
{
	cells[index] = cell;
}

int CellBlock::GetValue(int index) const 
{
	return cells[index]->GetValue();
}

Cell* CellBlock::GetCell(int index) const
{
	return cells[index];
}
