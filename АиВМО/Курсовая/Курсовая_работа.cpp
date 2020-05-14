#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class prime//����� ������� ������
{
	private:
		int chisl;
		int znam;
		int gcd(int a, int b) 
		{
			while (a != b) 
			{
				if (a > b) 
				{
					a -= b;
				}
				else 
				{
					b -= a;
				}
			}
			return a;
		}
	public:
		void set(int a, int b)
		{
			chisl = a;
			znam = b;
		}
		int getchisl()
		{
			return chisl;
		}
		int getznam()
		{
			return znam;
		}
		prime()
		{
			set(0, 1);
		}
		prime(int a, int b)
		{
			if(b == 0)
			{
				cout << "ERROR 0 ZNAM" << endl;
				exit(1);
			}
			if(a == 0)
			{
				set(0, 1);
			}
			else
			{
				int sign = 1;
				if(a < 0)
				{
					sign *= -1;
					a *= -1;
				}
				if(b < 0)
				{
					sign *= -1;
					b *= -1;
				}
				
				int tmp = gcd(a, b);
				set(a / tmp * sign, b / tmp);
			}
		}

	prime operator*(const prime& b) 
	{
		return prime(this->getchisl() * b.chisl, this->getznam() * b.znam);
	}
	prime operator/(const prime& b) 
	{
		return prime(this->getchisl() * b.znam, this->getznam() * b.chisl);
	}
	prime& operator+=(const prime& b) 
	{
		prime c(this->getchisl() * b.znam + b.chisl * this->getznam(), this->getznam() * b.znam);
		*this = c;
		return *this;
	}
	prime& operator-=(const prime& b) 
	{
		prime c(this->getchisl() * b.znam - b.chisl * this->getznam(), this->getznam() * b.znam);
		*this = c;
		return *this; 
	}	
	prime& operator/=(const prime& b) 
	{
		prime c(this->getchisl() * b.znam, b.chisl * this->getznam());
		*this = c;
		return *this; 
	}	
	friend ostream& operator<<(ostream &out, const prime &a);	 
};

ostream& operator<<(ostream& strm, const prime& a) 
{
	if(a.znam == 1) 
	{
		strm << a.chisl;
	}
	else 
	{
		strm << a.chisl << "/" << a.znam;
	}
	return strm;
}

prime operator+(prime a, int b)
{
	return prime(b * a.getznam() + a.getchisl(), a.getznam());
}

prime operator*(int b, prime a)
{
	return prime(b * a.getchisl(), a.getznam());	
}

void print(prime  *a, int n, int m)//����� ����������� ������� 
{ 
	cout << "1\t";
	for (int i = 1; i < m; i++)
	{
		cout << "x" << i << "\t";
	}
	cout << endl;
	for(int i = 0; i < n; i++) 
	{ 
		for(int j = 0; j < m; j++)
		{
			cout << a[i * m + j] << "\t";
		}  
		cout << endl;
	} 
	cout << endl;
}

void print2(prime *a, prime *so, prime *z, int n, int m, int t)//����� ��������-������� 
{ 
	int nul = 0;
	int ed = 0;
	int bas_stolb = 0;
	int iswrite = 0;
	
	cout << "Table " << t << ":" << endl;
	cout << "B.P\t1\t";
	for (int i = 1; i < m; i++)
	{
		cout << "x" << i << "\t";
	}
	cout << "SO\t" << endl;

	for(int i = 0; i < n; i++)
	{
		for(int j = 1; j < m; j++)
		{	
			if(a[i * m + j].getchisl() == 1 && a[i * m + j].getznam() == 1 && iswrite == 0)//���� ����� �������
			{
				for(int k = 0; k < n; k++)//�������, �������� �� ������� ��������
				{
					if(a[k * m + j].getchisl() == 0)
					{
						nul++;	
					}
					if(a[k * m + j].getchisl() == 1)
					{
						ed++;
						bas_stolb = j;	
					}
				}
				if(nul == n - 1 && ed == 1)//���� ������� - ��������
				{
					cout << "x" << bas_stolb << "\t";
					iswrite = 1;
					bas_stolb = 0;
					nul = 0;
					ed = 0; 
				}	
			}
			if(iswrite == 1)//���� ���������� ��� ��������
			{
				for(int h = 0; h < m; h++)//������� ���������� ��������
				{
					cout << a[i * m + h] << "\t";	
				}
				cout << so[i] << endl;//����� ��������-���������
				iswrite = 0;	
			}
			nul = 0;
			ed = 0;
		}	
	}
		
	cout << endl << "Z\t";
	for(int i = 0; i < m; i++)//����� z-������
	{
		cout << z[i] << "\t";
	}
	cout << endl;
}

void gauss(prime *a, int n, int m, int* bas, int* svob)//�������������� ������� ������� �������-������
{
	m:int y = 0;//������� ������� 
	prime *res = new prime(0, 1);//����������� �������
	for (int i = 0; i < n; i++)//����������� �� ������������� ��������� � ������� ��������� ������
	{
		if (a[i * m].getchisl() < 0)//���� ������� ������ ����
		{
			for (int j = 0; j < m; j++)//�������� ��� ������ �� -1
			{
				a[i * m + j] = -1 * a[i * m + j];
			}
		}
	}
	print(a, n, m);
	for(int i = 0; i < n; i++)//�������������� �������(i - ����� ����������� ������)
	{
		y = bas[i];//���������� �� ����������� �������
		*res = a[i * m + y];//�������� ����������� �������
		if (res->getchisl() == 0)//���� ����������� ������� - 0
		{
			for (int j = i + 1; j < n; j++)//���� � ������� ��������� �������
			{
				if (a[j * m + y].getchisl() != 0)//���� �����
				{
					for (int k = 0; k < m; k++)//���������� ������
					{
						a[i * m + k] += a[j * m + k];
					}
					break;//����� �� �����
				}
			}
		}
		*res = a[i * m + y];//�������������� ������������ ��������
		if (res->getchisl() == 0)//���� ����������� ������� ����� 0
		{
			cout << "net reshenia" << endl;//�� ������� ���
			exit(1);
		}
		for(int j = 0; j < m; j++)//����� ������ �� ����������� �������
		{
			a[i * m + j] /= *res;	
		}
		*res /= *res;//����� ����� ����������� ������� ��� �� ����, ����� �� ���������		
		for(int j = 0; j < n; j++)//������ �� ������� ��� ������� ���������
		{
			if(i == j) //���� ������� �� ����������� ������ - ����������
			{
				continue;	
			}
			for(int k = 0; k < m; k++)
			{
				if(y == k)//���� ������� �� ����������� ������� - ����������
				{
					continue;
				}
				a[j * m + k] -= ((a[j * m + y] * a[i * m + k]) / *res);//�������������� �� ������� ��������������		
			}	
		}
		for(int j = 0; j < n; j++)//��������� ��������� �������
		{
			if(i == j) //���� �� ����������� ������ - ����������
			{
				continue;
			}
			a[j * m + y] = prime(0, 1); //�������� ��������
		}
		print(a, n, m);	
	}	

	int index = 0;//������ ��������� �������, ������������ ��� ������
	int nul = 0;//������� ���������� ����� � �������� �������(������ ���� ����� 2)
	int ed = 0;//������� ���������� ������ � �������� �������(������ ���� ����� 1)
	for (int i = 0; i < n; i++)//���� ����� �������������� ��� ��� ���� ������������� �������� � ������� ��������� ������
	{
		if (a[i * m].getchisl() < 0)//�� ������� �� �������
		{
			for (int j = 0; j < m; j++)
			{
				if (a[i * m + j].getchisl() == 1 && a[i * m + j].getznam() == 1)//���� �������� �������
				{
					for (int k = 0; k < n; k++)//���������, �������� �� ������� ��������
					{
						if (a[k * m + j].getchisl() == 0)
						{
							nul++;
						}
						if (a[k * m + j].getchisl() == 1)
						{
							index = j;//���������� ������ ��� ������ �������� ����������
							ed++;
						}
					}
					if (nul == n - 1 && ed == 1)//���� ������� �������� - ����������� �����
					{
						break;
					}
				}
			}
		}
	}
	int k = 0;//������ ����� �������� ����������
	for (int i = 0; i < n; i++)
	{
		if (bas[i] == index)//���� ����� ������ ����������
		{
			cout << "reshenie ne opornoe" << endl;
			int temp = bas[i];//������� � �� ������ � �������� �� ���������
			bas[i] = svob[k];
			svob[k] = temp;
			k++;
			if (k == m - n - 1)//���� �������� �� ��������� ����������
			{
				k = 0;//������������ � ������
			}
			goto m;//����������� ��-�����
		}
	}
}

void z_count(prime *a, prime *z, int n, int m, int *bas, int *svob, int *cof)//��������� ������ ������������� z-������
{	
	for (int i = 0; i < m; i++)//������������� z-������
	{
		z[i] = prime(0, 1);
	}
	int flag = 0;//����, ����������� �� �������������� ���������� ������
	for(int i = 0; i < m; i++)//������ �� ���� ��������� z-������
	{
		flag = 0;
		if(cof[i] != 0)//���� ��� ���������� ����� ��������� ����������� � ������� �������
		{
			for (int j = 0; j < n; j++)//�������, ����������� �� �� �������� ����������
			{
				if (bas[j] == i)//���� �����������
				{
					flag = 1;//������ ����
					for (int k = 0; k < m - n - 1; k++)//�������� �������� ���������� ����� ��������� � ��������� ��������������� �������� z-������
					{
						z[svob[k]] += cof[i] * a[j * m + svob[k]];
					}
					z[0] += cof[i] * a[j * m];//��������� z0
				}
			}
		}
		if (flag == 0)//���� ����������� ��� ��������� ����������
		{
			z[i] = z[i] + (cof[i] * -1);//���������
		}
	}
}

int simplex_table(prime *a, prime *z, int n, int m, int stage)//���������� ��������-�������
{
	prime *max = new prime(0, 1);
	prime *min = new prime(9999, 1);
	prime *res = new prime(0, 1);
	
	prime *so = new prime[n];
	
	int max_index = 0;//������ ������������ �������
	int min_index = 0;//������ ����������� ������
	int flag = 0;//����, ����������� ������������� �����
	int bas_stolb = 0;//������ �������������� 1 � �������� �������, ������� �������� ����� ���������� �������
	int t = 0;//������ �������
	int nil = 0;//������� ����� �� ������ ���������� ������ �������
	int count = 0;//������� ���������� ������ ������������� ������� �� ������ ���������� ������ �������

	for(int i = 0; i < n; i++)//������������� ��������-���������
	{
		so[i] = prime(0, 1);
	}	
	
	while(1)
	{	
		for (int i = 0; i < n; i++)//�������� �� ��������� �������
		{
			if (a[i * m].getchisl() < 0)
			{
				print2(a, so, z, n, m, t);
				cout << "Plan ne oporen" << endl;
				exit(1);
			}
		}

		nil = 0;
		flag = 0;
		t++;//������ �������	
		for(int i = 0; i < n; i++)//������������� ��������-���������
		{
			so[i] = prime(0, 1);
		}
		
		*max = z[1];
		max_index = 1;
		for(int i = 1; i < m; i++)//���� �����������/������������ ������� � z-������
		{
			if (stage)//���� ���� ����� ������������
			{
				if (z[i].getchisl() > 0)
				{
					flag = 1;
				}
				if ((z[i].getchisl() * max->getznam() > max->getchisl() * z[i].getznam()))//���� ������� z-������ ������ ���������
				{
					*max = z[i];//���������� ��������
					max_index = i;//� ������ ������������ �������
				}
			}
			else//�����
			{
				if (z[i].getchisl() < 0)
				{
					flag = 1;
				}
				if ((z[i].getchisl() * max->getznam() < max->getchisl() * z[i].getznam()))//���� ������� z-������ ������ ��������
				{
					*max = z[i];//���������� �������
					max_index = i;//� ������ ������������ �������
				}
			}
		}

		for (int i = 1; i < m; i++)//������� ����� � z-������
		{
			if (z[i].getchisl() == 0)
			{
				nil++;
			}
		}

		if (nil > n)//���� ����� ������, ��� �������� ����������
		{
			for (int i = 1; i < m; i++)//����, ��� ����� 0 �� ��� �������
			{
				if (z[i].getchisl() == 0)
				{
					for (int j = 0; j < n; j++)
					{
						if (a[j * m + i].getchisl() != 0 && a[j * m + i].getchisl() != 1)
						{
							max_index = i;//� ���������� ������
						}
					}
				}
			}
			count++;//������� ���������� ������ ������������� �������
		}

		if((flag == 0 && nil == n) || count == 2)//���� ��� �������� z-������ ������������� � ���������� ������� ������� ��� ��� ������� ������� ������������� �������
		{
			print2(a, so, z, n, m, t);
			cout << "plan optimalen" << endl;//�� ���� ��������� - ����� �����������
			return 0;
		}

		for(int i = 0; i < n; i++)//������ ��������-���������
		{
			if (a[i * m + max_index].getchisl() <= 0)
			{
				continue;
			}
			else
			{
				so[i] = a[i * m] / a[i * m + max_index];
			}
			if((so[i].getchisl() * min->getznam() < min->getchisl() * so[i].getznam()) && so[i].getchisl() > 0)//���� ����������� ��������-���������
			{
				*min = so[i];//���������� ������� ��
				min_index = i;//� ������ ����������� ������
			}
		}

		print2(a, so, z, n, m, t);
		if (min->getchisl() == 9999 && min->getznam() == 1)//���� � �� ��� ��������� ��� ��� �������������
		{
			cout << "Net resheniya" << endl;
			exit(1);
		}
		if (nil == n)
		{
			cout << "plan ne optimalen" << endl;
		}
		else
		{
			cout << "beskonechno mnogo reshenii" << endl;
		}
		cout << "max stolbets - " << *max << " " << max_index << endl;
		cout << "min_stroka - " << *min << " " << min_index << endl;
		*res = a[min_index * m + max_index];//����������� �������
		cout << "res elem - " << *res << endl;

		int nul = 0;//������� ���������� ����� � �������� �������(������ ���� ����� 2)
		int ed = 0;//������� ���������� ������ � �������� �������(������ ���� ����� 1)
		for(int i = 0; i < m; i++)//����, ����� �������(����������) �������� �� ������
		{
			if(a[min_index * m + i].getchisl() == 1 && a[min_index * m + i].getznam() == 1)//���� ��������� ������� - 1
			{
				for(int j = 0; j < n; j++)//���������, �������� �� ������� ��������
				{
					if(a[j * m + i].getchisl() == 0)
					{
						nul++;	
					}
					if(a[j * m + i].getchisl() == 1)
					{
						bas_stolb = j;//���������� ������ ��� ���������� �������� ��������� �������
						ed++;	
					}
				}
				if(nul == n - 1 && ed == 1)//���� ������� �������� - ����������� �����
				{
					break;
				}
			}
		}
		
		for(int i = 0; i < n; i++)//������ ��� �������� ���������
		{
			if(i == min_index)//���� �� ����������� ������ - ����������
			{
				continue;
			}
			for(int j = 0; j < m; j++)
			{
				if(j == max_index)//���� �� ����������� ������� - ���������� 
				{
					continue;
				}
				a[i * m + j] -= ((a[i * m + max_index] * a[min_index * m + j]) / *res);//��������������	�������� ��������������	
			}	
		}
		
		for(int i = 0; i < m; i++)//������ z-������ �� ������� ��������������
		{
			if(i == max_index)//���� �� ����������� ������� - ����������
			{
				continue;
			}
			z[i] -= ((a[min_index * m + i] * z[max_index]) / *res);
		}
		
		z[max_index] = prime(0, 1);//������ 0 ��� ����� �������� ��������
					
		for(int i = 0; i < m; i++)//����� ����������� ������ �� ����������� �������
		{
			a[min_index * m + i] /= *res;
		}
		
		for(int i = 0; i < n; i++)//��������� ���������� � �����
		{
			if(i == bas_stolb)//���� ������� � ��������, �� 1
			{
				a[i * m + max_index] = prime(1, 1);	
			}
			else
			{
				a[i * m + max_index] = prime(0, 1);//����� - 0	
			}
		}
		
		max = new prime(0, 1);
		min = new prime(9999, 1);
		
		max_index = 0;
		min_index = 0;
		bas_stolb = 0;
	}	
}

void svob_count(int *bas, int *svob, int n, int m)//���������� ��������� ����������
{
	int k = 0;//������ ��������� ����������
	int flag = 0;//����, �������� �� �������� ���������� � ������
	for (int i = 1; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (bas[j] == i)//���� ���������� � ������
			{
				flag = 1;//�������� ���
			}
		}
		if (flag == 0)//���� ���������� � ������ �� ����
		{
			svob[k] = i;//��������� � � ���������
			k++;//����������� ������
			if (k == m - n - 1)//����� ��������� ��� ����������
			{
				break;//�������
			}
		}
		flag = 0;
	}
}

int main()
{   
	//////////////////////////////////////////////���� �� �����

	int n;//������
	int m;//�������
	int stage;//���� ��������(1)/���������(0)

	ifstream fin("file.txt"); 

	fin >> n >> m;
	
	prime* a = new prime[m * n];//�������� ������� � ���� ������� ������
	prime* z = new prime[m];//z-������

	int* cof = new int[m];//������������ ��� ������� �������
	int* svob = new int[m - n - 1];//��������� ����������
	int* bas = new int[n];//�������� ����������

	int **matr = new int*[n];
	for (int i = 0; i < n; i++)
	{
		matr[i] = new int[m];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			fin >> matr[i][j];
		}
	}
	for (int i = 0; i < m; i++)
	{
		fin >> cof[i];
	}
	for (int i = 0; i < n; i++)
	{
		fin >> bas[i];
	}

	svob_count(bas, svob, n, m);

	fin >> stage;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			a[i * m + j] = prime(matr[i][j], 1);
		}
	}
	
	///////////////////////////////// ���� �� ���������
	/*const int n = 3; 
	const int m = 6;

	int stage = 1;//���� ��������(1)/���������(0)

	prime* a = new prime[m * n];//�������� ������� � ���� ������� ������
	prime* z = new prime[m];//z-������

	int* cof = new int[m];//������������ ��� ������� �������
	int* svob = new int[m - n - 1];//��������� ����������
	int* bas = new int[n];//�������� ����������

	int matr[n * m] = //�������� �������
	{
		14, 1, 2, -1, 0, 0, 
		68, 4, 11, 0, -1, 0, 
		12, 3, 1, 0, 0, -1, 
	};
	

	cof[0] = 0;
	cof[1] = 9;
	cof[2] = 2;
	cof[3] = 0;
	cof[4] = 0;
	cof[5] = 0;

	bas[0] = 1;
	bas[1] = 2;
	bas[2] = 5;

	svob_count(bas, svob, n, m);

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			a[i * m + j] = prime(matr[i * m + j], 1);
		}
	}*/

	print(a, n , m);
	gauss(a, n, m, bas, svob);		
	z_count(a, z, n, m, bas, svob, cof);	
	simplex_table(a, z, n, m, stage);	
	
	return 0;
}
