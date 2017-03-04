#include "Cell.h"

Cell::Cell()
{
}

Cell::Cell(int num)
{
	value = num;
}

Cell::~Cell()
{
}

void Cell::SetValue(int num) 
{
	value = num;
}

void Cell::WasSetByFile(bool set)
{
	setByFile = set;
}
