#pragma once
class Statistics
{
public:
	Statistics();
	~Statistics();

	int GetSolved();
	int GetPasses();
	int GetConsideredCands();

	void IncrementSolved();
	void IncrementPasses();
	void IncrementConsideredCands();

private:
	int solvedCells;
	int gridPasses;
	int candidatesConsidered;
};

