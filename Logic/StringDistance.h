//@author A0122357L
#pragma once
#include <string.h>
#include <malloc.h>

class StringDistance
{
public:
	static int LD(char const *s, char const *t);
private:
	static int Minimum(int a, int b, int c);
	static int *GetCellPointer(int *pOrigin, int col, int row, int nCols);
	static int GetAt(int *pOrigin, int col, int row, int nCols);
	static void PutAt(int *pOrigin, int col, int row, int nCols, int x);
};

