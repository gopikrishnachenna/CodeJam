/*
Problem

Cameron and Jamie's kid is almost 3 years old! However, even though the child is more independent now, scheduling kid activities and domestic necessities is still a challenge for the couple.

Cameron and Jamie have a list of N activities to take care of during the day. Each activity happens during a specified interval during the day. They need to assign each activity to one of them, so that neither of them is responsible for two activities that overlap. An activity that ends at time t is not considered to overlap with another activity that starts at time t.

For example, suppose that Jamie and Cameron need to cover 3 activities: one running from 18:00 to 20:00, another from 19:00 to 21:00 and another from 22:00 to 23:00. One possibility would be for Jamie to cover the activity running from 19:00 to 21:00, with Cameron covering the other two. Another valid schedule would be for Cameron to cover the activity from 18:00 to 20:00 and Jamie to cover the other two. Notice that the first two activities overlap in the time between 19:00 and 20:00, so it is impossible to assign both of those activities to the same partner.

Given the starting and ending times of each activity, find any schedule that does not require the same person to cover overlapping activities, or say that it is impossible.
Input

The first line of the input gives the number of test cases, T. T test cases follow. Each test case starts with a line containing a single integer N, the number of activities to assign. Then, N more lines follow. The i-th of these lines (counting starting from 1) contains two integers Si and Ei. The i-th activity starts exactly Si minutes after midnight and ends exactly Ei minutes after midnight.
Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is IMPOSSIBLE if there is no valid schedule according to the above rules, or a string of exactly N characters otherwise. The i-th character in y must be C if the i-th activity is assigned to Cameron in your proposed schedule, and J if it is assigned to Jamie.

If there are multiple solutions, you may output any one of them. (See "What if a test case has multiple correct solutions?" in the Competing section of the FAQ. This information about multiple solutions will not be explicitly stated in the remainder of the 2020 contest.)
Limits

Time limit: 20 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
0 ≤ Si < Ei ≤ 24 × 60.
Test set 1 (Visible Verdict)

2 ≤ N ≤ 10.
Test set 2 (Visible Verdict)

2 ≤ N ≤ 1000.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 1010
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


int james[MAX_N * 2];
int cameron[MAX_N * 2];
int input[MAX_N * 2];
int id[MAX_N];
char result_string[MAX_N];
int len;
int flag = 0;

void clean_arrays()
{
	int i;
	len = 0;
	flag = 0;
	for(i = 0; i < (2 * MAX_N); i++)
	{
		james[i] = -1;
		james[i] = -1;
		cameron[i] = -1;
		cameron[i] = -1;
		if(i < MAX_N)
			id[i] = 0;
	}
}

int check_array(int arr[], int st, int et)
{
	int i;

	for(i = 0; arr[i] != -1; i++)	
	{
		if(MAX(arr[i], st) < MIN(arr[i + MAX_N], et))
			return 0;
	}

	arr[i] = st;
	arr[i + MAX_N] = et;	
	return 1;
}

int func_cmp(const void* x, const void* y) {
	return input[*(int*)x] - input[*(int*)y];
}


int main()
{
	int tests, no_of_tests, N, i;
	int st, et;

	scanf("%d", &no_of_tests);

	for(tests = 1; tests <= no_of_tests; tests++)
	{
		scanf("%d", &N);
		clean_arrays();	
		for(i = 1; i <= N; i++)
		{
			scanf("%d", &input[i]);
			scanf("%d", &input[i + MAX_N]);
			id[i] = i;
		}

		qsort(id + 1, N, sizeof(int), func_cmp);
		
		for(i = 1; i <= N; i++)
		{
			int ii = id[i];
			st = input[ii];
			et = input[ii + MAX_N];
			if(check_array(james, st, et))
				result_string[ii] = 'J';	
			else if(check_array(cameron, st, et))	
				result_string[ii] = 'C';
			else
				flag = 1;
		}
		if(!flag)
			printf("Case #%d: %.*s\n", tests, N, result_string + 1);
		else
			printf("Case #%d: IMPOSSIBLE\n", tests);
	}
	return 0;
}
