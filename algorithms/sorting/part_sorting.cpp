#include<iostream>
#include<stdio.h>
#include<list>
using namespace std;
int main()
{
	list<int> numbers;
	int T,size, temp, nswap;
	int pos=0;
	scanf("%d", &T);
	for (int i=0; i < T; i++)
	{
		scanf("%d", &size);
		numbers.clear();
		for (int j = 0; j < size; j++)
		{
			scanf("%d", &temp);
			numbers.push_back(temp);
		}
		scanf("%d", &nswap);
		while (nswap>0)
		{

			list<int>::iterator it1 = numbers.begin();
			list<int>::iterator it2 = numbers.begin();
			pos = 0;
			for (int k = 1; k <= nswap; k++)
			{
				it1++;
				if (*it1 > *it2)
				{
					pos = k;
					it2 = it1;
				}
			}
			temp = *it2;
			nswap -= pos;
			numbers.erase(it2);
			printf("%d ", temp);
		}
		list<int>::iterator it = numbers.begin();
		for (; it!=(--numbers.end()); it++)
		{
			printf("%d ", *it);
		}
		printf("%d", *it);
		printf("\n");
	}

}
