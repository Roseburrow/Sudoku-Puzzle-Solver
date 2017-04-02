#pragma once
class Statistics
{
public:
	Statistics();
	~Statistics();

	int GetSolved() const;
	int GetPasses() const;
	int GetHidden() const;
	int GetNaked() const;
	int GetConsideredCands() const;

	void IncrementSolved();
	void IncrementHidden();
	void IncrementNaked();
	void IncrementPasses();
	void IncrementConsideredCands();

private:
	int solvedCells;
	int gridPasses;
	int candidatesConsidered;
	int hiddenSolved;
	int nakedSolved;
};

