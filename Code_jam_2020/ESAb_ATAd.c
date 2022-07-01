/*
 Last year, a research consortium had some trouble with a distributed database system that sometimes lost pieces of the data. You do not need to read or understand that problem in order to solve this one!

The consortium has decided that distributed systems are too complicated, so they are storing B bits of important information in a single array on one awesome machine. As an additional layer of security, they have made it difficult to obtain the information quickly; the user must query for a bit position between 1 and B, and then they receive that bit of the stored array as a response.

Unfortunately, this ultra-modern machine is subject to random quantum fluctuations! Specifically, after every 1st, 11th, 21st, 31st... etc. query is sent, but before the response is given, quantum fluctuation causes exactly one of the following four effects, with equal probability:

    25% of the time, the array is complemented: every 0 becomes a 1, and vice versa.
    25% of the time, the array is reversed: the first bit swaps with the last bit, the second bit swaps with the second-to-last bit, and so on.
    25% of the time, both of the things above (complementation and reversal) happen to the array. (Notice that the order in which they happen does not matter.)
    25% of the time, nothing happens to the array.

Moreover, there is no indication of what effect the quantum fluctuation has had each time. The consortium is now concerned, and it has hired you to get its precious data back, in whatever form it is in! Can you find the entire array, such that your answer is accurate as of the time that you give it? Answering does not count as a query, so if you answer after your 30th query, for example, the array will be the same as it was after your 21st through 30th queries.
Input and output

This is an interactive problem. You should make sure you have read the information in the Interactive Problems section of our FAQ.

Initially, your program should read a single line containing two integers T and B: the number of test cases and the number of bits in the array, respectively. Note that B is the same for every test case.

Then, you need to process T test cases. In each case, the judge begins with a predetermined B-bit array; note that this array can vary from test case to test case, and is not necessarily chosen at random. Then, you may make up to 150 queries of the following form:

    Your program outputs one line containing a single integer P between 1 and B, inclusive, indicating which position in the array you wish to look at.
    If the number of queries you have made so far ends with a 1, the judge chooses one of the four possibilities described above (complementation, reversal, complementation + reversal, or nothing), uniformly at random and independently of all other choices, and alters the stored array accordingly. (Notice that this will happen on the very first query you make.)
    The judge responds with one line containing a single character 0 or 1, the value it currently has stored at bit position P, or N if you provided a malformed line (e.g., an invalid position).

Then, after you have made as many of the 150 queries above as you want, you must make one more exchange of the following form:

    Your program outputs one line containing a string of B characters, each of which is 0 or 1, representing the bits currently stored in the array (which will not necessarily match the bits that were initially present!)
    The judge responds with one line containing a single letter: uppercase Y if your answer was correct, and uppercase N if it was not (or you provided a malformed line). If you receive Y, you should begin the next test case, or stop sending input if there are no more test cases.

After the judge sends N to your input stream, it will not send any other output. If your program continues to wait for the judge after receiving N, your program will time out, resulting in a Time Limit Exceeded error. Notice that it is your responsibility to have your program exit in time to receive a Wrong Answer judgment instead of a Time Limit Exceeded error. As usual, if the memory limit is exceeded, or your program gets a runtime error, you will receive the appropriate judgment.
Limits

Time limit: 40 seconds per test set.
Memory limit: 1GB.
1 ≤ T ≤ 100.
Test set 1 (Visible Verdict)

B = 10.
Test set 2 (Visible Verdict)

B = 20.
Test set 3 (Hidden Verdict)

B = 100.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_B 100

int tests, no_of_tests;
int B;
char input[MAX_B + 9];
int flag;
int found_same;
char value_same;
int found_diff;
char value_diff;
char reply[1];
int count;

void input_oper(int op);

void reset_input()
{
	int i;

	flag = 0;
	count = 0;
	found_same = found_diff = 0;
	for(i = 0; i < (MAX_B + 9); i++)
	{
		input[i] = 'X';
	}
}

char query(int p)
{
	char result[1];

	count++;

	printf("%d\n", p);
	fflush(stdout);
	scanf("%s", result);
		
	return *result;
}

void do_input_oper(void)
{
	if((flag & 0x03) == 0x03)
	{
		value_same = query(found_same);
		value_diff = query(found_diff);
		if((value_same == input[found_same]) && (value_diff == input[found_diff]))
			return;
		if((value_same != input[found_same]) && (value_diff == input[found_diff]))
			input_oper(3);
		if((value_same == input[found_same]) && (value_diff != input[found_diff]))
			input_oper(2);
		if((value_same != input[found_same]) && (value_diff != input[found_diff]))
			input_oper(1);
	}
	else if(flag & 0x02)
	{
		value_diff = query(found_diff);
		if(value_diff != input[found_diff])
			input_oper(1);
		if(value_diff == input[found_diff])
			return;
	}
	else
	{
		value_same = query(found_same);
		if(value_same == input[found_same])
			return;
		if(value_same != input[found_same])
			input_oper(1);	
	}
}

void input_oper(int op)
{
	int i;
	char temp;
	if(op == 1 || op == 3)
	{
		for(i = 1; i <= B; i++)
		{
			if(input[i] == 'X')
				continue;
			if(input[i] == '0')
				input[i] = '1';
			else
				input[i] = '0';
		}
		if(op == 1)
			return;
	}

	for(i = 1; (2 * i) <= (B + 1); i++)
	{
		temp = input[i];
		input[i] = input[B - i + 1];
		input[B - i + 1] = temp;
	}
}

int main()
{
	int i;
	
	scanf("%d", &no_of_tests);
	scanf("%d", &B);

	for(tests = 1; tests <= no_of_tests; tests++)
	{
		reset_input();
		for(i = 1; (2 * i) <= (B + 1); i++)
		{
			if((count != 0) && (((count % 10) == 9) || ((count % 10) == 0)))
			{
				if(count % 10 == 9)
					query(1);
				do_input_oper();
			}
			input[i] = query(i);
			input[B - i + 1] = query(B - i + 1);
			if(!found_same && (input[i] == input[B - i + 1]))
			{
				found_same = i;
				flag |= 0x01;
			}
			if(!found_diff && (input[i] != input[B - i + 1]))
			{
				found_diff = i;
				flag |= 0x02;
			}
		}
		printf("%.*s\n", B, input + 1);
		fflush(stdout);
		scanf("%s", reply);
		if(*reply == 'N')
			return -1;
	}

}

