/*
Problem

tl;dr: Given a string of digits S, insert a minimum number of opening and closing parentheses into it such that the resulting string is balanced and each digit d is inside exactly d pairs of matching parentheses.

Let the nesting of two parentheses within a string be the substring that occurs strictly between them. An opening parenthesis and a closing parenthesis that is further to its right are said to match if their nesting is empty, or if every parenthesis in their nesting matches with another parenthesis in their nesting. The nesting depth of a position p is the number of pairs of matching parentheses m such that p is included in the nesting of m.

For example, in the following strings, all digits match their nesting depth: 0((2)1), (((3))1(2)), ((((4)))), ((2))((2))(1). The first three strings have minimum length among those that have the same digits in the same order, but the last one does not since ((22)1) also has the digits 221 and is shorter.

Given a string of digits S, find another string S', comprised of parentheses and digits, such that:

    all parentheses in S' match some other parenthesis,
    removing any and all parentheses from S' results in S,
    each digit in S' is equal to its nesting depth, and
    S' is of minimum length.

Input

The first line of the input gives the number of test cases, T. T lines follow. Each line represents a test case and contains only the string S.
Output

For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is the string S' defined above.
Limits

Time limit: 20 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
1 ≤ length of S ≤ 100.
Test set 1 (Visible Verdict)

Each character in S is either 0 or 1.
Test set 2 (Visible Verdict)

Each character in S is a decimal digit between 0 and 9, inclusive.
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char prev_ch, ch;
	int flag, count, newline;
	int no_test_cases, tests, i;

	scanf("%d", &no_test_cases);
	scanf("%c",&ch);
	for(tests = 0; tests < no_test_cases ; tests++)
	{
		prev_ch = '0';
		newline = 0;
		printf("Case #%d: ", tests + 1);
		while(!newline)
		{
			scanf("%c",&ch);
			if(ch == '\n')
			{
				newline = 1;
				ch = '0';
			}
			flag = (ch > prev_ch) ? 1 : 0;
			count = flag ? (ch - prev_ch) : (prev_ch - ch);
			for(i = 0; i < count; i++)
			{
				if(flag)	
					printf("(");
				else
					printf(")");
			}
			if(!newline)
				printf("%c", ch);
			prev_ch = ch;
		}
		printf("\n");
	}
}
