#include <iostream>

using namespace std; 

void gauss(float** a, int n, int m) 
{
	int flag;
	for(int i = 0; i < n; i++)
	{
		flag = 0;
		if(a[i][i] == 0)
		{
			for(int j = i + 1; j < n; j++)
			{
				if(a[j][i] != 0)
				{
					flag = 1;
					for(int k = 0; k <= m; k++) 
					{
						swap(a[j][k], a[i][k]);	
					}
					cout << "SWAP" << endl;
					print(a, n, m);
					break; 
				}
			}
			if(flag == 0)
			{
				cout << "BAD" << endl;
				continue;
			}
		}
		for(int j = i + 1; j <= m; j++)
		{
			for(int k = 0; k < n; k++)
			{
				if(k == i)
				{
					continue;
				}
				a[k][j] = ((a[k][j] * a[i][i]) - (a[i][j] * a[k][i])) / a[i][i]; 	
			}
		}				
		print(a, n, m);
		for(int j = 0; j < n; j++)
		{
			if(i == j)
			{
				continue;
			}
			a[j][i] = 0;
		}
		print(a, n, m);
	}
	for(int i = 0; i < n; i++)
	{
		float raz = a[i][i];
		for(int j = 0; j <= m; j++)
		{
			if(raz == 0)
			{
				continue;
			}
			else
			{
				a[i][j] /= raz;	
			}
		}
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			if(a[i][j] == -0)
			{
				a[i][j] = 0;
			}
		}
	}
	print(a, n, m);
}

void answer(float** a, int n, int m)
{
	int flag = 0, bas = n;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			if(j == m)
			{
				cout << "=" << a[i][j] << endl;
			}
			else if(a[i][j] != 0)
			{
				if(a[i][j] > 0 && j != 0)
				{
					cout << "+" << a[i][j] << "*X" << j;
				}
				else
				{
					cout << a[i][j] << "*X" << j;	
				}					
			}	
		}	
	}
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			if(j == m && a[i][j] != 0)
			{
				cout << "Система не имеет решений!" << endl;
				exit(0);
			}
			if(a[i][j] == 0)
			{
				continue;	
			}
			else
			{
				flag = 1;
				break;	
			}	
		}
		if(flag == 0)
		{
			bas--;		
		}
		flag = 0;
	}
	cout << "Решение имеет " << bas << " базисных переменных" << endl;		
}

int main()
{                     
    int n = 3, m = 3;
    //cin >> n >> m;

    float** a = new float*[n];
    for(int i = 0; i < n; i++)
    {
    	a[i] = new float[m + 1];
	}
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j <= m; j++)
		{
			cin >> a[i][j];
		}
	}

	cout << endl;
	gauss(a, n, m);
	answer(a, n, m);
	
	return 0;
}
