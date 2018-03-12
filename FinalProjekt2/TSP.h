#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <ctime>
#include <iomanip> 
#include "Timer.h"
#undef max//////
using namespace std;

static const double MAX = numeric_limits<double>::infinity();

class TSP
{
private:
	int Size = 0;
	int *order = nullptr;
	double** distances = nullptr;
	double** coordinates = nullptr;

public:
	TSP(int);
	TSP() {}
	~TSP();
	int  GetSize() const;
	void RandomData(int, int);
	void ReadFromFileM(string filename, int count);
	void ReadFromFileK(string filename, int count);
	void computeDistances();

	static void CopyTable(int*, int*, int);
	void Swap2(int*, int*) const;

	void decrementTabu(int**) const;
	static void TabuCopyLength(int, int, int, int**);

	void TabuZero(int **) const;
	int* nearNeighbour() const;

	int* TabuSearch(int, int, int) const;
	double GetRouteLen(int*) const;
	void Print(int*, int) const;
};