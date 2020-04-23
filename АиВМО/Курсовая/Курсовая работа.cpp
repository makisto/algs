#include <iostream>
#include <vector>

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
		int set(int a, int b)
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

prime operator*(int b, prime a)
{
	return prime(b * a.getchisl(), a.getznam());	
}

void print(prime  *a, int n, int m)//����� ����������� ������� 
{ 
	cout << "1\tx1\tx2\tx3\tx4\tx5\t" << endl;
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
	cout << "B.P\t1\tx1\tx2\tx3\tx4\tx5\tSO\t" << endl;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
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
					switch(bas_stolb)//����� ����������, ��������������� ������
					{
						case 1:
							cout << "x1\t";
							iswrite = 1;
							break; 
						case 2:
							cout << "x2\t";
							iswrite = 1;
							break; 
						case 3:
							cout << "x3\t";
							iswrite = 1;
							break; 
						case 4:
							cout << "x4\t";
							iswrite = 1;
							break; 
						case 5:	
							cout << "x5\t";
							iswrite = 1;
							break; 
					}
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
		}	
	}
		
	cout << endl << "Z\t";
	for(int i = 0; i < m; i++)//����� z-������
	{
		cout << z[i] << "\t";
	}
	cout << endl;
}

void gauss(prime *a, prime *z, int n, int m, int* bas)//�������������� ������� ������� �������-������
{
	int y = 0;//������� ������� 
	prime *res = new prime(0, 1);//����������� �������
	for(int i = 0; i < n; i++)//�������������� �������(i - ����� ����������� ������)
	{
		y = bas[i];//���������� �� ����������� �������
		*res = a[i * m + y];//�������� ����������� �������
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
}

void z_count(prime *a, prime *z, int n, int m, int *bas, int *svob, int *cof)//��������� ������ ������������� z-������
{	
	for(int i = 0; i < n; i++)
	{
		z[bas[i]] = prime(0, 1);	
	}

	for(int i = 0; i < n - 1; i++)
	{
		z[0] += cof[i] * a[i * m];	
	}
	
	for(int i = 0; i < n - 1; i++)
	{
		for(int j = 0; j < n - 1; j++)
		{
			z[svob[i]] += cof[j] * a[j * m + svob[i]];			
		}
	}
}

int simplex_table(prime *a, prime *z, int n, int m)//���������� ��������-�������
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
			
	for(int i = 0; i < n; i++)//������������� ��������-���������
	{
		so[i] = prime(0, 1);
	}	
	
	while(1)
	{	
		t++;//������ �������			
		for(int i = 0; i < n; i++)//������������� ��������-���������
		{
			so[i] = prime(0, 1);
		}
		
		*max = z[1];
		for(int i = 2; i < m; i++)//���� ����������� ������� � z-������
		{
			if(z[i].getchisl() < 0)
			{
				flag = 1;
			}
			if(z[i].getchisl() < max->getchisl())//���� ������� z-������ ������ ��������
			{
				*max = z[i];//���������� �������
				max_index = i;//� ������ ������������ �������
			}
		}
		
		if(flag == 0)//���� ��� �������� z-������ �������������
		{
			print2(a, so, z, n, m, t);
			cout << "plan optimalen" << endl;//�� ���� ��������� - ����� �����������
			return 0;
		}
		
		for(int i = 0; i < n; i++)//������ ��������-���������
		{
			so[i] = a[i * m] / a[i * m + max_index];
			if(so[i].getchisl() < min->getchisl() && so[i].getchisl() > 0)//���� ����������� ��������-���������
			{
				*min = so[i];//���������� ������� ��
				min_index = i;//� ������ ����������� ������
			}
		}
		
		print2(a, so, z, n, m, t);
		cout << "plan ne optimalen" << endl;
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
		flag = 0;
		bas_stolb = 0;
	}	
}

int main()
{       
    int n = 3, m = 6;
	prime *a = new prime[m * n];
	prime *z = new prime[m];

	//Z(x1, x2) = -9x1 - 2x2 -> max
	int matr[n * m] = 
	{
		14, 1, 2, -1, 0, 0,
		68, 4, 11, 0, -1, 0,
		12, 3, 1, 0, 0, -1
	};
	
	int *cof = new int[n - 1];//������������ ��� ������� �������
	cof[0] = -9;
	cof[1] = -2;
	int *svob = new int[n - 1];//��������� ����������
	svob[0] = 3;
	svob[1] = 4;
	int* bas = new int[n];//�������� ����������
	bas[0] = 1;
	bas[1] = 2;
	bas[2] = 5;
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			a[i * m + j] = prime(matr[i * m + j], 1);
		}
	}

	print(a, n , m);
	gauss(a, z, n, m, bas);		
	z_count(a, z, n, m, bas, svob, cof);		
	simplex_table(a, z, n, m);	
	
	return 0;
}
