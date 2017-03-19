#include "SudokuPuzzle.h"
#include <Windows.h>
#include <fstream>
#include <algorithm>

SudokuPuzzle::SudokuPuzzle(void)
{
}

SudokuPuzzle::~SudokuPuzzle(void)
{
}

void SudokuPuzzle::ReadInGrid(char filenameIn[])
{
	std::fstream fin(filenameIn);
	Cell *entireGrid[9][9];

	if (fin.is_open())
	{
		for (int row = 0; row < 9; ++row)
		{
			for (int col = 0; col < 9; ++col)
			{
				int c;
				Cell *cell;

				fin >> c;
				cell = new Cell(c);

				if (c != 0)
				{
					cell->WasSetByFile(true);
				}
				else
				{
					cell->InitCandidates();
				}

				entireGrid[row][col] = cell;
			}
		}
		fin.close();
	}

	int group = 0;
	int index = 0;

	for (int rows = 0; rows < 9; ++rows)
	{
		if (rows % 3 == 0 && rows != 0)
		{
			group = group + 3;
			index = 0;
		}

		for (int cols = 0; cols < 9; ++cols)
		{
			gridRows[rows].SetCell(cols, entireGrid[rows][cols]);
			gridColumns[cols].SetCell(rows, entireGrid[rows][cols]);
			gridBlocks[group].SetCell(index, entireGrid[rows][cols]);

			++index;

			if ((cols + 1) % 9 == 0)
			{
				group = group - 2;
			}
			else if ((cols + 1) % 3 == 0)
			{
				group = ++group;
				index -= 3;
			}
		}
	}
}

void SudokuPuzzle::Solve(char filenameIn[])
{
	//Keeps track of useful information like cells solved etc.
	Statistics* stats = new Statistics;

	// You will need to read the values of the Sudoku puzzle into your data structure
	ReadInGrid(filenameIn);

	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	bool loop = true;

	// Solve the puzzle
	while (loop)
	{
		int checkBlock = 0;
		loop = false;

		stats->IncrementPasses();

		//For every cell...
		for (int i = 0; i < 9; ++i)
		{
			if (i % 3 == 0 && i != 0)
			{
				checkBlock = checkBlock + 3;
			}

			for (int j = 0; j < 9; ++j)
			{
				//Get the cell...
				Cell* checkCell = gridRows[i].GetCell(j);

				//Run through the columns rows and block eliminating candidates
				if (NarrowCandidates(checkCell, i, j, checkBlock))
				{
					//changes have been made and the grid needs re-evaluating...
					loop = true;
				}

				//Check if the cell has only one candidate and if it does solve it and
				if (CheckNakedSingle(checkCell))
				{
					stats->IncrementSolved();
				}

				//Checks if the cell has a candidate that isnt in any other candidate list
				//of any cell on the same row or column or block.
				if (CheckHiddenSingle(checkCell, i, j, checkBlock))
				{
					stats->IncrementSolved();
				}

				if ((j + 1) % 9 == 0)
				{
					checkBlock = checkBlock - 2;
				}
				else if ((j + 1) % 3 == 0)
				{
					checkBlock = ++checkBlock;
				}
			}
		}
	}

	QueryPerformanceCounter(&end);

	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	int solved = stats->GetSolved();
	int passes = stats->GetPasses();
	int considered = stats->GetConsideredCands();

	std::cout << "TIME: " << time << std::endl;
	std::cout << "SOLVED: " << solved << std::endl;
	std::cout << "PASSES: " << passes << std::endl;
	std::cout << "CONSIDERED: " << considered << std::endl;

	Output();  // Output the solved puzzle
}

bool SudokuPuzzle::CheckNakedSingle(Cell* checkCell)
{
	if (checkCell->GetCandidatesLength() == 1)
	{
		int c = checkCell->GetCandidateValue(0);
		checkCell->SetValue(c);
		checkCell->RemoveCandidate(c);
		return true;
	}
	else
	{
		return false;
	}
}

bool SudokuPuzzle::CheckHiddenSingle(Cell* checkCell, int row, int col, int block)
{
	for (int x = 0; x < checkCell->GetCandidatesLength(); ++x)
	{
		int c = checkCell->GetCandidateValue(x);

		if (!gridRows[row].GetCell(col)->Contains(c) &&
			!gridColumns[col].GetCell(row)->Contains(c) &&
			!gridBlocks[block].GetCell(row)->Contains(c))
		{
			checkCell->SetValue(c);
			checkCell->EmptyCandidates();
			return true;
		}
	}
	return false;
}

bool SudokuPuzzle::NarrowCandidates(Cell* checkCell, int checkCellRow, int checkCellColumn, int checkBlock)
{
	Cell* comparisonCell;

	for (int j = 0; j < 9; ++j)
	{
		if (checkCell->GetCandidatesLength() == 0)
		{
			return false;
		}

		//Checks the row...
		if (j != checkCellColumn)
		{
			comparisonCell = gridRows[checkCellRow].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandidate(comparisonCell->GetValue());
			}

			//Check block...
			comparisonCell = gridBlocks[checkBlock].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandidate(comparisonCell->GetValue());
			}
		}

		//Check the column...
		if (j != checkCellRow)
		{
			comparisonCell = gridColumns[checkCellColumn].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandidate(comparisonCell->GetValue());
			}
		}
	}
	return true;
}

void SudokuPuzzle::Output()
{
	ofstream fout("sudoku_solution.txt");
	if (fout.is_open())
	{
		for (int y = 0; y < 9; ++y)
		{
			for (int x = 0; x < 9; ++x)
			{
				fout << gridRows[y].GetValue(x) << " ";
			}

			fout << endl;
		}
		fout.close();
	}
}
