#pragma once

#include <iostream>
#include <fstream>
#include "CellBlock.h"
#include "Statistics.h"

using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);

private:
	void Output();
	void ReadInGrid(char filenameIn[]);
	bool NarrowCandidates(Cell* checkCell, int row, int col, int checkBlock);
	bool CheckNakedSingle(Cell* checkCell);
	bool CheckHiddenSingle(Cell* checkCell, int row, int col, int block);

	CellBlock gridBlocks[9];
	CellBlock gridRows[9];
	CellBlock gridColumns[9];
	//other variables here...
};

