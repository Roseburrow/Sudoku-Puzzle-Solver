#pragma once

#include <iostream>
#include <fstream>
#include "CellBlock.h"
#include "Statistics.h"

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle();
	~SudokuPuzzle();

	void Solve(char filenameIn[]);

private:
	void Output() const;
	void ReadInGrid(char filenameIn[]);
	bool NarrowCandidates(Cell* checkCell, int row, int col, int checkBlock);
	bool CheckNakedSingle(Cell* checkCell, int block, int row, int col);
	bool CheckHiddenSingle(Cell* checkCell, int row, int col, int block, int index);
	bool IsIn(const CellBlock &cellGroup, int currentCell, int value);
	void InitSolve();

	Statistics stats;
	CellBlock gridBlocks[9];
	CellBlock gridRows[9];
	CellBlock gridColumns[9];
};

