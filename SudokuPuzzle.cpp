#include "SudokuPuzzle.h"
#include <Windows.h>
#include <fstream>
#include <algorithm>

SudokuPuzzle::SudokuPuzzle()
{
}

SudokuPuzzle::~SudokuPuzzle()
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			delete gridRows[i].GetCell(j);
		}
	}
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

				if (c == 0)
				{
					cell = new Cell();
				}
				else
				{
					cell = new Cell(c);
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
	ReadInGrid(filenameIn);

	LARGE_INTEGER start, end, frequency;
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&start);

	bool hiddenStop;
	bool nakedStop;
	Cell* checkCell;

	//Does one pass through the grid and narrows down the candidate lists
	//This is to ensure that a naked single can be solved at the start.
	InitSolve();

	//Overall solve loop...
	do
	{
		int checkBlock = 0;
		int index = 0;
		hiddenStop = false;
		nakedStop = false;
		stats.IncrementPasses();

		//For every cell...
		for (int i = 0; i < 9; ++i)
		{
			//Used to check for blocks.
			if (i % 3 == 0 && i != 0)
			{
				checkBlock = checkBlock + 3;
				index = 0;
			}

			for (int j = 0; j < 9; ++j)
			{
				checkCell = gridRows[i].GetCell(j);

				//Checks for changes via the solving of a cell.
				//If a pass is made and no changes are made then we have
				//solved all that we can else we continue.
				if (CheckNakedSingle(checkCell, checkBlock, i, j))
				{
					nakedStop = true;
				}
				if (CheckHiddenSingle(checkCell, i, j, checkBlock, index))
				{
					hiddenStop = true;
				}
				
				++index;

				//Used to check for blocks.
				if ((j + 1) % 9 == 0)
				{
					checkBlock = checkBlock - 2;
				}
				else if ((j + 1) % 3 == 0)
				{
					checkBlock = ++checkBlock;
					index -= 3;
				}
			}
		}
	} while (nakedStop || hiddenStop);

	QueryPerformanceCounter(&end);

	float time = (end.QuadPart - start.QuadPart) / (static_cast<float> (frequency.QuadPart));
	int solved = stats.GetSolved();
	int passes = stats.GetPasses();
	int considered = stats.GetConsideredCands();
	int hiddenSolved = stats.GetHidden();
	int nakedSolved = stats.GetNaked();

	std::cout << "TIME: " << time << std::endl;
	std::cout << "TOTAL SOLVED: " << solved << std::endl;
	std::cout << "HIDDEN SOLVED: " << hiddenSolved << std::endl;
	std::cout << "NAKED SOLVED: " << nakedSolved << std::endl;
	std::cout << "PASSES: " << passes << std::endl;
	std::cout << "CONSIDERED: " << considered << std::endl;

	Output();
}

bool SudokuPuzzle::CheckNakedSingle(Cell* checkCell, int block, int row, int col)
{
	//If a cell only has 1 candidate then... 
	if (checkCell->GetCandidatesLength() == 1)
	{
		//...get the candidate and set the cell to it. Then remove it from the cells
		//candidate list.
		int c = checkCell->GetCandidateValue(0);
		checkCell->SetValue(c);
		checkCell->RemoveCandidate(c, &stats);

		//Remove the newly set value from other candidate lists on the row, col and block.
		for (int i = 0; i < 9; ++i)
		{
			gridBlocks[block].GetCell(i)->RemoveCandidate(c, &stats);
			gridRows[row].GetCell(i)->RemoveCandidate(c, &stats);
			gridColumns[col].GetCell(i)->RemoveCandidate(c, &stats);
		}

		stats.IncrementNaked();
		stats.IncrementSolved();

		return true;
	}
	return false;
}

bool SudokuPuzzle::CheckHiddenSingle(Cell* checkCell, int row, int col, int block, int index)
{
	if (checkCell->GetValue() == 0)
	{
		int candSize = checkCell->GetCandidatesLength();

		//for every candidate in the candidate list...
		for (int x = 0; x < candSize; ++x)
		{
			//Get the candidate...
			int c = checkCell->GetCandidateValue(x);

			//Check if it is in the row, column and block...
			if (!IsIn(gridRows[row], col, c) &&
				!IsIn(gridColumns[col], row, c) &&
				!IsIn(gridBlocks[block], index, c))
			{
				//If not then it is unique to that cell so solve it...
				checkCell->SetValue(c);
				checkCell->EmptyCandidates();

				stats.IncrementHidden();
				stats.IncrementSolved();
				return true;
			}
		}
	}
	return false;
}

bool SudokuPuzzle::NarrowCandidates(Cell* checkCell, int checkCellRow, int checkCellColumn, int checkBlock)
{
	Cell* comparisonCell;

	for (int j = 0; j < 9; ++j)
	{
		//If the cell has no candidates it has been solved or set by the file.
		//We therefore cannot remove anything from their list so return.
		if (checkCell->GetCandidatesLength() == 0)
		{
			return false;
		}

		//Checks the row...
		if (j != checkCellColumn)
		{
			//Sets comparison cell to the next cell along.
			comparisonCell = gridRows[checkCellRow].GetCell(j);

			//If the value of the comparison cell isnt 0 then we can remove its value
			//from the current cell's candidate list.
			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandidate(comparisonCell->GetValue(), &stats);
			}

			//Check block...
			comparisonCell = gridBlocks[checkBlock].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{				
				checkCell->RemoveCandidate(comparisonCell->GetValue(), &stats);
			}
		}

		//Check the column...
		if (j != checkCellRow)
		{
			comparisonCell = gridColumns[checkCellColumn].GetCell(j);

			if (comparisonCell->GetValue() != 0)
			{
				checkCell->RemoveCandidate(comparisonCell->GetValue(), &stats);
			}
		}
	}
	return true;
}

void SudokuPuzzle::InitSolve()
{
	int checkBlock = 0;
	int index = 0;
	Cell* checkCell;

	stats.IncrementPasses();

	//For every cell...
	for (int i = 0; i < 9; ++i)
	{
		if (i % 3 == 0 && i != 0)
		{
			checkBlock = checkBlock + 3;
			index = 0;
		}

		for (int j = 0; j < 9; ++j)
		{
			checkCell = gridRows[i].GetCell(j);

			NarrowCandidates(checkCell, i, j, checkBlock);
			++index;

			if ((j + 1) % 9 == 0)
			{
				checkBlock = checkBlock - 2;
			}
			else if ((j + 1) % 3 == 0)
			{
				checkBlock = ++checkBlock;
				index -= 3;
			}
		}
	}
}

bool SudokuPuzzle::IsIn(const CellBlock &cellGroup, int currentCell, int value)
{
	//For each cell in the cellgroup...
	for (int cell = 0; cell < 9; ++cell)
	{
		//If not the cell we are inspecting...
		if (currentCell != cell)
		{
			//...then check if the cell contains the candidate we are looking for.
			if (cellGroup.GetCell(cell)->Contains(value, &stats))
			{
				//If it does then return true which means the candidate is not unique.
				return true;
			}
		}
		else
		{
			//Go around the loop again.
			continue;
		}
	}
	return false;
}

void SudokuPuzzle::Output() const
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
