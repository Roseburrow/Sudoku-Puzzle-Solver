#include "Statistics.h"

Statistics::Statistics() : solvedCells(0), gridPasses(0), candidatesConsidered(0), hiddenSolved(0), nakedSolved(0)
{
}

Statistics::~Statistics()
{
}

int Statistics::GetSolved() const
{
	return solvedCells;
}

int Statistics::GetPasses() const
{
	return gridPasses;
}

int Statistics::GetConsideredCands() const
{
	return candidatesConsidered;
}

int Statistics::GetNaked() const
{
	return nakedSolved;
}

int Statistics::GetHidden() const
{
	return hiddenSolved;
}

void Statistics::IncrementSolved()
{
	++solvedCells;
}

void Statistics::IncrementPasses()
{
	++gridPasses;
}

void Statistics::IncrementNaked()
{
	++nakedSolved;
}

void Statistics::IncrementHidden()
{
	++hiddenSolved;
}

void Statistics::IncrementConsideredCands()
{
	++candidatesConsidered;
}
