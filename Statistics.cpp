#include "Statistics.h"

Statistics::Statistics()
{
	solvedCells = 0;
	gridPasses = 0;
	candidatesConsidered = 0;
}

Statistics::~Statistics()
{
}

int Statistics::GetSolved()
{
	return solvedCells;
}

int Statistics::GetPasses()
{
	return gridPasses;
}

int Statistics::GetConsideredCands()
{
	return candidatesConsidered;
}

void Statistics::IncrementSolved()
{
	++solvedCells;
}

void Statistics::IncrementPasses()
{
	++gridPasses;
}

void Statistics::IncrementConsideredCands()
{
	++candidatesConsidered;
}
