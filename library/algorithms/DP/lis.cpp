#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include<stdlib.h>
#include<time.h>
using namespace std;
int longest_inc_subseq(vector <int> A, int last_term);
int lengths[100];
int main()
{
	memset(lengths, -1, 100);
	vector <int> my_ints;
	int length;
	my_ints.reserve(100);
	for (int i = 0; i < 5; i++)
	{
		srand(time(NULL));
		my_ints.push_back(rand() % 400);
	}
	length = longest_inc_subseq(my_ints,my_ints.size());
	cout << length;

}
int longest_inc_subseq(vector <int> A,int last_term)
{
	if (last_term==1)
	{
		return 1;
	}
	int length = 0;
	for (int i = last_term-2; i >0; i--)
	{
		if (A[i] < A[last_term - 1])
		{
			if (lengths[i] < 0)
				lengths[i]=longest_inc_subseq(A, i+1);
			if (lengths[i] > length)
			{
				length = lengths[i];
			}
		}
	}
	return length + 1;
}