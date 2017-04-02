#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Statistics.h"

class Cell
{
public:
	explicit Cell();
	explicit Cell(int num);
	~Cell();

	//Methods
	void SetValue(int num);
	int GetValue() const;

	bool GetWasSetByFile() const;

	void InitCandidates();
	int GetCandidateValue(const int index);
	void RemoveCandidate(const int value, Statistics* stats);
	void EmptyCandidates();
	bool Contains(const int value, Statistics* stats);
	int GetCandidatesLength() const;

private:
	std::vector<int> candidateList;
	int value;
	bool setByFile;
};

