#include <iostream>
#include <fstream>

using namespace std;

int min(int a, int b)
{
	return (a < b ? a : b);
}

void print(int **a, int **traffic, int *dop, bool issklad, bool iseat, int *sklad, int *eat, int n, int m)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cout << a[i][j] << "/" << traffic[i][j] << "\t";
		}
		if (issklad)
		{
			cout << dop[i] << "/0\t";
		}
		cout << sklad[i] << "\t";
		cout << endl;
	}
	if (iseat)
	{
		for (int i = 0; i < m; i++)
		{
			cout << dop[i] << "/0\t";
		}
		cout << dop[m] << "\t";
		cout << endl;
	}
	for (int i = 0; i < m; i++)
	{
		cout << eat[i] << "\t";
	}
	if (issklad)
	{
		cout << dop[n] << "\t";
	}
	cout << endl;
	cout << endl;
}

int main()
{
	ifstream fin("in.txt");

	int n; 
	int m;

	bool issklad = 0;
	bool iseat = 0;
	bool isvyr = 0;

	int x = 0;
	int y = 0;

	int obsklad = 0;
	int obeat = 0;

	int* dop;

	int sum = 0;
	int count = 0;

	fin >> n >> m;

	int* sklad = new int[n];

	for (int i = 0; i < n; i++)
	{
		fin >> sklad[i];
	}

	int* eat = new int[m];

	for (int i = 0; i < m; i++)
	{
		fin >> eat[i];
	}

	for (int i = 0; i < n; i++)
	{
		obsklad += sklad[i];
	}

	for (int i = 0; i < m; i++)
	{
		obeat += eat[i];
	}

	if (obsklad < obeat)
	{
		dop = new int[m + 1];
		for (int i = 0; i < m; i++)
		{
			dop[i] = 0;
		}
		dop[m] = obeat - obsklad;
		iseat = 1;
	}

	else if (obsklad > obeat)
	{
		dop = new int[n + 1];
		for (int i = 0; i < n; i++)
		{
			dop[i] = 0;
		}
		dop[n] = obsklad - obeat;
		issklad = 1;
	}

	int **traffic = new int*[n];
	for (int i = 0; i < n; i++)
	{
		traffic[i] = new int[m];
	}

	for(int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fin >> traffic[i][j];
		}
	};

	int **a = new int*[n];
	for (int i = 0; i < n; i++)
	{
		a[i] = new int[m];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			a[i][j] = 0;
		}
	}

	print(a, traffic, dop, issklad, iseat, sklad, eat, n, m);
	while (1)
	{
		if (iseat && x == n)
		{
			count = min(dop[m], eat[y]);

			dop[y] = count;

			dop[m] -= count;
			eat[y] -= count;

			if (eat[y] == 0 && dop[m] == 0)
			{
				break;
			}

			if (eat[y] == 0)
			{
				y++;
			}
		}
		else if (issklad && y == m)
		{
			count = min(sklad[x], dop[n]);

			dop[x] = count;

			sklad[x] -= count;
			dop[n] -= count;

			if (sklad[x] == 0 && dop[n] == 0)
			{
				break;
			}

			if (sklad[x] == 0)
			{
				x++;
			}
		}
		else
		{
			count = min(sklad[x], eat[y]);

			a[x][y] = count;

			sklad[x] -= count;
			eat[y] -= count;

			if (sklad[x] == 0 && eat[y] == 0)
			{
				isvyr = 1;
			}

			if (sklad[x] == 0)
			{
				x++;
				if (x == n && !iseat)
				{
					x--;
				}
			}

			if (eat[y] == 0)
			{
				y++;
				if (y == m && !issklad)
				{
					y--;
				}
			}

			if (sklad[x] == 0 && eat[y] == 0 && (x == n - 1 || y == m - 1))
			{
				break;
			}
		}
		print(a, traffic, dop, issklad, iseat, sklad, eat, n, m);
	}

	print(a, traffic, dop, issklad, iseat, sklad, eat, n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			sum += traffic[i][j] * a[i][j];
		}
	}

	if (isvyr)
	{
		cout << "plan vyrozdenny" << endl;
	}
	cout << sum << endl;
}