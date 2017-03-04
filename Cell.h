#pragma once

#include <vector>

class Cell
{
public:
	Cell();
	Cell(int num);
	~Cell(void);

	//Methods
	void SetValue(int num);
	void WasSetByFile(bool set);

private:
	std::vector<int> candidateList;
	int value;
	bool setByFile;
};

