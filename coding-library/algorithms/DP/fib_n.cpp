#include<iostream>
#include<stdio.h>
using namespace std;
int dp[10000];
int nth_fib(int n)
{
	if (dp[n-1] >= 0)
		return dp[n-1];
	else
	{
		dp[n-1] = nth_fib(n - 1) + nth_fib(n - 2);
		return dp[n-1];
	}
}
int fibTest()
{
	memset(dp, -1, 10000);
	dp[0] = 1;
	dp[1] = 1;
	int index;
	scanf("%d", &index);
	printf("%d",nth_fib(index));
	return 0;
}