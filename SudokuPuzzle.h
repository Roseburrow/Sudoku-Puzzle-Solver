#pragma once

#include <iostream>
#include <fstream>
#include "CellBlock.h"
using namespace std;

class SudokuPuzzle
{
public:
	SudokuPuzzle(void);
	~SudokuPuzzle(void);

	void Solve(char filenameIn[]);

private:
	void Output() const;
	void ReadInGrid(char filenameIn[]);
	//other methods here...

	CellBlock grid[9];
	//other variables here...
};

