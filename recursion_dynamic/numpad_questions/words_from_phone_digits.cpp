#include <iostream>
#include <algorithm>

using namespace std;

//2d array to store phone numberpad digits to alphabets
const string hashTable[10] = {"", "wsx", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
//							  0		1	   2	  3		 4		5	   6	   7	  8		  9

void  printWordsUtil(int number[], int curr_digit, char output[], int n, int &count)
{
	// Base case, if current output word is prepared
	if (curr_digit == n)
	{
		cout << output << endl;
		count++;
		return;
	}

	//Try all 3 possible characters for current digir in number[]
	// and recur for remaining digits
	for (int i = 0; i < (hashTable[number[curr_digit]]).length(); i++)
	{
		output[curr_digit] = hashTable[number[curr_digit]][i];
		printWordsUtil(number, curr_digit+1, output, n, count);
		if (number[curr_digit] == 0 || number[curr_digit] == 1)
			return;
	}
}

void printWords(int number[], int n)
{
	char result[n+1];
	result[n] ='\0';
	int count = 0;
	printWordsUtil(number, 0, result, n, count);
	cout << count << endl;
}

int main()
{
	int number[] = {2, 3, 4};
	int size = sizeof(number)/sizeof(number[0]);
	printWords(number, size);
	return 0;
}
