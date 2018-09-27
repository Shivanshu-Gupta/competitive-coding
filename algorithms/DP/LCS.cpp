#include<iostream>
#include<stdio.h>
#include<string>
using namespace std;
string s1, s2;
int dp[200][200];
int LCS_length_bottomup(int i, int j)
{
	for (int m = 0; m < i; m++)
		dp[0][0] = s1[0] == s2[0] ? 1 : 0;
	for (int m = 0; m < i; m++)
	{
		for (int n = 0; n < j; n++)
		{
			if (s1[m] == s2[n])
				dp[m][n] = dp[m - 1][n - 1] + 1;
			else
				dp[m][n] = dp[m - 1][n]>dp[m][n - 1] ? dp[m - 1][n] : dp[m][n - 1];
		}
	}
	return dp[i-1][j-1];
}
int LCS_length_topdown(int i, int j)
{
	int length;
	if (i == 0 || j == 0)
		return 0;
	if (dp[i][j] > 1) return dp[i][j];
	if (s1[i] == s2[j])
		length = LCS_length_topdown(i - 1, j - 1) + 1;
	else
	{
		int l1 = LCS_length_topdown(i, j - 1);
		int l2 = LCS_length_topdown(i - 1, j);
		if (l1 > l2)
			length = l1;
		else
			length = l2;
	}
	dp[i][j] = length;
	return length;
}
int main()
{
	memset(dp, -1, 100);
	//scanf_s("%s", &s1);
	//scanf_s("%s", &s2);
	cin >> s1;
	cin >> s2;
	string subseq;
	int LCSlength=LCS_length_bottomup(s1.length(), s2.length());
	int i = s1.length() - 1, j = s2.length() - 1,k=0;
	/*for (int i = 0; i < s1.length(); i++)
	{
		for (int j = 0; j < s2.length(); j++)
			cout << dp[i][j]<<'	';
		cout << '\n';
	}*/
	printf("%d\n", LCSlength);
	while (i >= 0 && j >= 0)
	{
		if (dp[i][j] == dp[i - 1][j])
			i--;
		else if (dp[i][j] == dp[i][j - 1])
			j--;
		else
		{
			subseq.push_back(s1[i]);
			k++;
			i--;
			j--;
		}
	}
	for (int k = subseq.length()-1; k >=0;k--)
	{
		cout << subseq[k];
	}
}
