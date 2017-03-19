#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

class Cell
{
public:
	Cell(int num);
	~Cell(void);

	//Methods
	void SetValue(int num);
	int GetValue();

	bool GetWasSetByFile();
	void WasSetByFile(const bool set);

	void InitCandidates();
	int GetCandidateValue(const int index);
	void RemoveCandidate(const int value);
	void EmptyCandidates();
	bool Contains(const int value);
	int GetCandidatesLength();

private:
	std::vector<int> candidateList;
	int value;
	bool setByFile;
};

