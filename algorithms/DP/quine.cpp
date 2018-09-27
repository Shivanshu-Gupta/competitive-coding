#include<iostream>
#include<fstream>
#include<stdio.h>
#include<sstream>
#include<string>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;
vector<vector <string> > chart;
vector<int>	mins;
vector<int>dcmins;
vector<string>essentials;
void reduce_chart();
class N_ones{
public:
	vector<int> minterm;
	vector<short> prime;
	vector<vector<int>> dif;
	int minterm_count;
	N_ones(){
		minterm_count = 0;
	}
};
class step{
public:
	N_ones *sets;
	int no_of_sets;

};
int main()
{
	ios::sync_with_stdio(false);
	ifstream fin("k.txt");
	ofstream fout("output.txt");
	stringstream ss;
	int n_var, minterm,n_minterm;
	int no_of_ones = 0;
	int temp;
	bool tocareornottocare=1;
	string s;
	vector<string>buff;
	vector<string> prime_imp;
	vector<vector <int> > implicants;
	vector<int>implicant;
	vector<int> buffer;
	vector<int> dif;
	dif.push_back(0);
	bool present = 0;
	//cin>>minterm;
	//n_var = 4;
	fin.seekg(3);
	fin >> n_var;
	fout << ".i " << n_var << "\n";
	vector <step> steps(n_var+1);
	for (int i = 0; i < n_var + 1; i++)
	{
		steps[i].sets = new N_ones[n_var + 1 - i];
		steps[i].no_of_sets = n_var + 1 - i;
		for (int j = 0; j < steps[i].no_of_sets; j++)
		{
			steps[i].sets[j].minterm.reserve(100);
			steps[i].sets[j].prime.reserve(100);
			steps[i].sets[j].dif.reserve(200);
			//for (int k = 0; k < 40; k++)
				//steps[i].sets[j].dif[k].reserve(10);
		}
	}
	getline(fin,s, 'm');
	fout << ".m\n";
	//fin >> s;
	//cin>>n_minterm;
	//n_minterm = 2;
	//for (int i = 0; i < n_minterm; i++)
	getline(fin,s, '.');
	ss << s;
	while (ss>>minterm)
	{
		no_of_ones = 0;
		fout << minterm << ' ';
		mins.push_back(minterm);
		//cin>>minterm;
		//minterm = i;
		temp = minterm;
		while (temp)
		{
			no_of_ones += temp % 2;
			temp /= 2;
		}
		steps[0].sets[no_of_ones].minterm.push_back(minterm);
		steps[0].sets[no_of_ones].minterm_count++;
		steps[0].sets[no_of_ones].dif.push_back(dif);
		steps[0].sets[no_of_ones].prime.push_back(1);
	}
	fout << "\n.d\n";
	fin >> s;
	getline(fin,s, '\n');
	getline(fin, s, '\n');
	ss.clear();
	ss << s;
	while (ss>> minterm)
	{
		no_of_ones = 0;
		fout << minterm<<' ';
		dcmins.push_back(minterm);
		//cin>>minterm;
		//minterm = i;
		temp = minterm;
		while (temp)
		{
			no_of_ones += temp % 2;
			temp /= 2;
		}
		steps[0].sets[no_of_ones].minterm.push_back(minterm);
		steps[0].sets[no_of_ones].minterm_count++;
		steps[0].sets[no_of_ones].dif.push_back(dif);
		steps[0].sets[no_of_ones].prime.push_back(1);
	}
	fout << '\n';
	for (int i = 0; i < n_var; i++)
	{
		for (int j = 0; j < steps[i].no_of_sets - 1; j++)
		{
			for (int k = 0; k < steps[i].sets[j].minterm_count; k++)
			{
				minterm = steps[i].sets[j].minterm[k];
				for (int l=0; l<steps[i].sets[j+1].minterm_count; l++)
				{
					temp = steps[i].sets[j + 1].minterm[l] - minterm;
					if (temp>0 && (!(temp&(temp - 1))))
					{
						if (steps[i].sets[j].dif[k] == steps[i].sets[j + 1].dif[l])
						{
							buffer.assign(steps[i].sets[j].dif[k].begin(),steps[i].sets[j].dif[k].end());
							buffer.push_back(temp);
							sort(buffer.begin(), buffer.end());
							present = 0;
							for (unsigned int m = 0; m < steps[i + 1].sets[j].minterm.size(); m++)
							{
								if (steps[i + 1].sets[j].minterm[m] == minterm && steps[i + 1].sets[j].dif[m] == buffer)
									present = 1;
							}
							if (!present)
							{
								steps[i + 1].sets[j].minterm.push_back(minterm);
								steps[i + 1].sets[j].dif.push_back(buffer);
								steps[i + 1].sets[j].prime.push_back(1);
								steps[i + 1].sets[j].minterm_count++;
							}
							steps[i].sets[j].prime[k] = 0;
							steps[i].sets[j + 1].prime[l] = 0;
						}
					}
				}
			}
		}
	}
	/*for (int i = 0; i < n_var + 1; i++)
	{
		for (int j = 0; j < steps[i].no_of_sets; j++)
		{
			for (int k=0;k<steps[i].sets[j].minterm_count; k++)
			{
				if (steps[i].sets[j].prime[k])
				{
					cout<<steps[i].sets[j].minterm[k];
					cout<<"\t(";
					for (unsigned int l = 0; l < steps[i].sets[j].dif[k].size();l++)
					{
						cout<<steps[i].sets[j].dif[k][l];
					}
					cout<<" )\n";
				}
			}
		}
	}*/
	prime_imp.reserve(100);
	for (int i = 0; i < n_var + 1; i++)
	{
		for (int j = 0; j < steps[i].no_of_sets; j++)
		{
			for (int k=0; k<steps[i].sets[j].minterm_count; k++)
			{
				if (steps[i].sets[j].prime[k])
				{
					s.clear();
					temp = 0;
					minterm = steps[i].sets[j].minterm[k];
					implicant.clear();
					implicant.push_back(minterm);
					for (unsigned int l = 1; l < steps[i].sets[j].dif[k].size();l++)
					{
						temp = temp | steps[i].sets[j].dif[k][l];
						n_minterm = implicant.size();
						for (int m = 0; m < n_minterm; m++)
						{
							minterm = implicant[m] + steps[i].sets[j].dif[k][l];
							tocareornottocare = 1;
							for (unsigned int n = 0; n < dcmins.size(); n++)
							{
								if (dcmins[n] == minterm)
								{
									tocareornottocare = 0;
									break;
								}
							}
							if (tocareornottocare)
								implicant.push_back(minterm);
							
						}
					}

					minterm = steps[i].sets[j].minterm[k];
					for (unsigned int n = 0; n < dcmins.size(); n++)
					{
						if (dcmins[n] == minterm)
						{
							implicant.erase(implicant.begin());
						}
					}
					implicants.push_back(implicant);
					for (int k = 0; k < n_var; k++)
					{
						if (temp % 2)
							s.append(1,'-');
						else
							s.append(1,char(minterm % 2+48));
						minterm /= 2;
						temp /= 2;
					}

					prime_imp.push_back(s);
					/*for (int k = s.length(); k >= 0; k--)
					{
						cout << s[k];
					}
					cout << '\n';*/
				}
			}
		}
	}
	fout << ".p " << prime_imp.size()<<'\n';
	for (unsigned int i = 0; i < prime_imp.size(); i++)
	{
		s.clear();
		for (int k = prime_imp[i].length(); k >= 0; k--)
		{
			cout << prime_imp[i][k];
			fout << prime_imp[i][k];
			s.push_back(prime_imp[i][k]);
		}
		cout << '\n';
		fout << '\n';
		prime_imp[i] = s;
	}
	
	for (unsigned int i = 0; i < mins.size(); i++)
	{
		for (unsigned int j = 0; j < implicants.size(); j++)
		{
			//implicant.clear();
			implicant = implicants[j];
			for (unsigned int k = 0; k < implicant.size(); k++)
			{
				if (mins[i] == implicant.at(k))
				{
					buff.push_back(prime_imp.at(j));
				}
			}
		}
		chart.push_back(buff);
		buff.clear();
	}
	for (unsigned int i = 0; i < chart.size(); i++)
	{
		cout << mins[i]<<'	';
		for (unsigned int j = 0; j < chart[i].size(); j++)
		{
			cout << chart[i][j] << '	';
		}
		cout << '\n';
	}
	reduce_chart();
	cout << '\n';
	for (unsigned int i = 0; i < chart.size(); i++)
	{
		cout << mins[i]<<'	';
		for (unsigned int j = 0; j < chart[i].size(); j++)
		{
			cout << chart[i][j] << '	';
		}
		cout << '\n';
	}
}
void reduce_chart()
{
	string implicant;
	bool non_ess = 0;
	for (unsigned int i = 0; i < mins.size(); i++)
	{
		if (chart[i].size()==1)
		{
			implicant = chart[i][0];
			essentials.push_back(implicant);
			chart.erase(chart.begin() + i);
			mins.erase(mins.begin() + i--);
			for (unsigned int j = 0; j < mins.size(); j++)
			{
				non_ess = 0;
				for (unsigned int k = 0; k < chart[j].size(); k++)
				{
					if (chart[j][k] == implicant)
					{
						non_ess = 1;
						break;
					}
				}
				if (non_ess)
				{
					chart.erase(chart.begin() + j);
					mins.erase(mins.begin() + j--);
					i--;
				}
			}
		}
	}
}