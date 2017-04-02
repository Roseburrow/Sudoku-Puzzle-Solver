#include "Cell.h"
#include "vector"

Cell::Cell() : value(0), setByFile(false) 
{
	InitCandidates();
}

Cell::Cell(int num) : value(num), setByFile(true)
{
}

Cell::~Cell()
{
}

int Cell::GetValue() const
{
	return value;
}

void Cell::SetValue(int num) 
{
	value = num;
}

bool Cell::GetWasSetByFile() const
{
	return setByFile;
}

void Cell::InitCandidates()
{
	for (int i = 1; i < 10; ++i)
	{
		candidateList.push_back(i);
	}
}

void Cell::RemoveCandidate(const int value, Statistics* stats)
{
	for (int i = 0; i < candidateList.size(); ++i)
	{
		stats->IncrementConsideredCands();
		if (value == candidateList[i])
		{
			candidateList.erase(candidateList.begin() + i);
			break;
		}
	}
}

int Cell::GetCandidatesLength() const
{
	return candidateList.size();
}

int Cell::GetCandidateValue(int index)
{
	return candidateList[index];
}

bool Cell::Contains(int value, Statistics* stats)
{
	for (int i = 0; i < candidateList.size(); ++i)
	{
		stats->IncrementConsideredCands();
		if (value == candidateList[i])
			return true;
	}
	return false;
}

void Cell::EmptyCandidates()
{
	candidateList.clear();
}