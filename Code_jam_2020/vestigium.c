/*

Problem

Vestigium means "trace" in Latin. In this problem we work with Latin squares and matrix traces.

The trace of a square matrix is the sum of the values on the main diagonal (which runs from the upper left to the lower right).

An N-by-N square matrix is a Latin square if each cell contains one of N different values, and no value is repeated within a row or a column. In this problem, we will deal only with "natural Latin squares" in which the N values are the integers between 1 and N.

Given a matrix that contains only integers between 1 and N, we want to compute its trace and check whether it is a natural Latin square. To give some additional information, instead of simply telling us whether the matrix is a natural Latin square or not, please compute the number of rows and the number of columns that contain repeated values.
Input

The first line of the input gives the number of test cases, T. T test cases follow. Each starts with a line containing a single integer N: the size of the matrix to explore. Then, N lines follow. The i-th of these lines contains N integers Mi,1, Mi,2 ..., Mi,N. Mi,j is the integer in the i-th row and j-th column of the matrix.
Output

For each test case, output one line containing Case #x: k r c, where x is the test case number (starting from 1), k is the trace of the matrix, r is the number of rows of the matrix that contain repeated elements, and c is the number of columns of the matrix that contain repeated elements.
Limits
Test set 1 (Visible Verdict)

Time limit: 20 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
2 ≤ N ≤ 100.
1 ≤ Mi,j ≤ N, for all i, j.

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_N_VALUE 100
#define COUNT_VALUE_COL(_v, _col) count[(_v * 2) - 1][_col]
#define COUNT_VALUE_ROW(_v, _row) count[(_v * 2) - 2][_row]
#define INC_RESULT_ROW(_row) results[_row][0]++
#define INC_RESULT_COL(_col) results[_col][1]++

int no_test_cases;
int N;
int results[MAX_N_VALUE][2];
int count[MAX_N_VALUE * 2][MAX_N_VALUE];

void clean_count_results()
{
	int i, j;

	for(i = 0; i < (MAX_N_VALUE * 2); i++)
	{
		for(j = 0; j < MAX_N_VALUE; j++)
		{
			count[i][j] = -1;
			if(i < MAX_N_VALUE && j < 2)
				results[i][j] = 0;
		}
	}
}

char return_result(char N, char row_or_col)
{
	int i, result = 0;

	for(i = 0; i < N; i++)
	{
		if(results[i][row_or_col])
			result++;
	}
	
	return result;
}

int main()
{
	int row, col, tests, value;
	scanf("%d", &no_test_cases);

	for(tests = 0; tests < no_test_cases; tests++)
	{
		int trace = 0;

		scanf("%d", &N);
		clean_count_results();
		for(row = 0; row < N; row++)
		{
			for(col = 0; col < N; col++)
			{
				scanf("%d", &value);
				if(++COUNT_VALUE_ROW(value, row))
					INC_RESULT_ROW(row);
				if(++COUNT_VALUE_COL(value, col))
					INC_RESULT_COL(col);
				if(row == col)
					trace += value;
			}
		}
		printf("Case #%d: %d %d %d\n", tests + 1, trace, return_result(N, 0), return_result(N, 1));	
	}
}

