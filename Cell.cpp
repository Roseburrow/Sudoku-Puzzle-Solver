#include "Cell.h"
#include "vector"

Cell::Cell(int num) : value(num)
{
	setByFile = false;
}

Cell::~Cell()
{
}

int Cell::GetValue()
{
	return value;
}

void Cell::SetValue(int num) 
{
	value = num;
}

bool Cell::GetWasSetByFile()
{
	return setByFile;
}

void Cell::WasSetByFile(bool set)
{
	setByFile = set;
}

void Cell::InitCandidates()
{
	for (int i = 1; i < 10; ++i)
	{
		candidateList.push_back(i);
	}
}

void Cell::RemoveCandidate(const int value)
{
	//Removing from a vector by value from user:Georg Fritzsche.
	//http://stackoverflow.com/questions/3385229/c-erase-vector-element-by-value-rather-than-by-position#3385251
	candidateList.erase(std::remove(candidateList.begin(), candidateList.end(), value), 
						candidateList.end());
}

int Cell::GetCandidatesLength()
{
	return candidateList.size();
}

int Cell::GetCandidateValue(int index)
{
	return candidateList[index];
}

bool Cell::Contains(int value)
{
	return std::find(candidateList.begin(), 
					 candidateList.end(), 
					 value) != candidateList.end();
}

void Cell::EmptyCandidates()
{
	candidateList.clear();
}

