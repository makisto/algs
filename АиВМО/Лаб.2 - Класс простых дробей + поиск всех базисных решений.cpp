#include <iostream>
#include <vector>

using namespace std;

class prime
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

    prime operator+(const prime& b) 
	{
		return prime(this->getchisl() * b.znam + b.chisl * this->getznam(), this->getznam() * b.znam);
	}
	prime operator+(int b)
	{
		return prime(b * this->getznam() + this->getchisl(), this->getznam());
	}
	prime operator-(const prime& b) 
	{
		return prime(this->getchisl() * b.znam - b.chisl * this->getznam(), this->getznam() * b.znam);
	}
	prime operator-(int b)
	{
		return prime(this->getchisl() - b * this->getznam(), this->getznam());
	}
	prime operator*(const prime& b) 
	{
		return prime(this->getchisl() * b.chisl, this->getznam() * b.znam);
	}
	prime operator*(int b)
	{
		return prime(this->getchisl() * b, this->getznam());
	}
	prime operator/(const prime& b) 
	{
		return prime(this->getchisl() * b.znam, this->getznam() * b.chisl);
	}
	prime operator/(int b)
	{
		return prime(this->getchisl(), this->getznam() * b);
	}
	prime& operator+=(const prime& b) 
	{
		prime c(this->getchisl() * b.znam + b.chisl * this->getznam(), this->getznam() * b.znam);
		*this = c;
		return *this;
	}
	prime& operator+=(int b)
	{
		prime c(b * this->getznam() + this->getchisl(), this->getznam());
		*this = c;
		return *this; 
	}
	prime& operator-=(const prime& b) 
	{
		prime c(this->getchisl() * b.znam - b.chisl * this->getznam(), this->getznam() * b.znam);
		*this = c;
		return *this; 
	}	
	prime& operator-=(int b)
	{
		prime c(this->getchisl() - b * this->getznam(), this->getznam());
		*this = c;
		return *this;  
	}	
	prime& operator*=(const prime& b) 
	{
		prime c(this->getchisl() * b.chisl, this->getznam() * b.znam);
		*this = c;
		return *this; 
	}	
	prime& operator*=(int b)
	{
		prime c(b * this->getchisl(), this->getznam());
		*this = c;
		return *this; 
	}	
	prime& operator/=(const prime& b) 
	{
		prime c(this->getchisl() * b.znam, b.chisl * this->getznam());
		*this = c;
		return *this; 
	}	
	prime& operator/=(int b)
	{
		prime c(this->getchisl(), b * this->getznam());
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
	
prime operator+(int b, prime a)
{
	return prime(b * a.getznam() + a.getchisl(), a.getznam());	
}

prime operator-(int b, prime a)
{
	return prime(b * a.getznam() - a.getchisl(), a.getznam());	
}

prime operator*(int b, prime a)
{
	return prime(b * a.getchisl(), a.getznam());	
}

prime operator/(int b, prime a)
{
	return prime(b * a.getznam(), a.getchisl());	
}

void print(vector <prime*> a, int n, int m) 
{ 
	for(int i = 0; i < n; i++) 
	{ 
		for(int j = 0; j < m; j++)
		{
			cout << *a[i * m + j] << " ";
		}   
		cout << endl; 
	} 
	cout << endl;
}

void gauss(vector <prime*> a, int n, int m)//������� �������-������(1 ����)
{
	int x = 0, y = 0, f = 0;//������� ������, ������� � ����
	prime null_prime(0, 1);//����������
	for(int i = 0; i < n; i++) //����������� �������
	{
		if(a[y * m + x]->getchisl() == 0) //���� ������������ ������� - 0
		{
			if(i == n - 1) //���� ��������� ������ - �������
			{
				break;	
			}
			for(int j = y + 1; j < n; j++)//���� ������ � ������������� ���������
			{
				if(a[j * m + x]->getchisl() > 0)//���� �����
				{
					f = 1;//���������� ���
					for(int k = x; k < m; k++)//� ���������� ������
					{
						*a[y * m + k] += *a[j * m + k];	
					}
				}		
			}
			if(f == 0)//���� �� �����
			{
				x++;//��������� �� ���� ������
				y++;//��������� �� ���� �������
				continue;
			}	
		}
		for(int j = 0; j < n; j++)//������ ��� �������� ���������
		{
			if (y == j) //���� �� ������������ �������� - ����������
			{
				continue;	
			}
			for(int k = x + 1; k < m; k++) // �������� ��������� �������� ��������������
			{
				*a[j * m + k] = ((*a[y * m + x]) * (*a[j * m + k]) - (*a[j * m + x]) * (*a[y * m + k])) / *a[y * m + x]; //��������������
			}	
		}
		for(int j = 0; j < n; j++) // ��������� ��������� �������
		{
			if(y == j) //���� �� ������������ �������� - ����������
			{
				continue;
			}
			*a[j * m + x] = null_prime; //�������� ��������
		}
		x++;//��������� �� ���� ������
		y++;//��������� �� ���� �������
	}
	x = 0, y = 0; 
	for(int i = 0; i < n; i++) // ������ ������� � �������
	{
		if(a[y * m + x]->getchisl() == 0) // ���� ������������ ������� - 0
		{
			x++;//��������� �� ���� ������
			y++;//��������� �� ���� �������
			continue;
		}
		for(int j = m - 1; j >= x; j--) //����� ������ �� ������������ �������
		{
			*a[i * m + j] /= *a[y * m + x]; //������� ������
		}
		x++;//��������� �� ���� ������
		y++;//��������� �� ���� �������
	}	
}

void basis(vector <prime*> cp, int* a, int n, int k)//�������������� ������
{
	k++;//���������� ������� �������
	vector <prime*> m;
	for(int i = 0; i < n * k; i++)//������� ����� ��������� �������
	{
		m.push_back(new prime(cp[i]->getchisl(), cp[i]->getznam()));
	}
	
	for(int i = 0; i < n; i++)//������ ������� �������������� ���������� ����������� ������ ���� ����� �������
	{
		for (int j = 0; j < n; j++)
		{
			prime* tp = m[i * k + j];
			m[i * k + j] = m[i * k + a[j]];
			m[i * k + a[j]] = tp;
		}
	}

	cout << "����� ������������" << endl;
	print(m, n, k);
	cout << endl;
	
	gauss(m, n, k);//��������� ����� ������
	
	cout << "����� ������" << endl;
	print(m, n, k);
	cout << endl;
	
	for (int i = 0; i < n; i++)//������� ������ ������� ������ ���� ������ ������
	{
		for (int j = 0; j < n; j++)
		{
			prime* tp = m[i * k + n - j - 1];
			m[i * k + n - j - 1] = m[i * k + a[n - j - 1]];
			m[i * k + a[n - j - 1]] = tp;
		}
	}
	
	cout << "����� ������ ������������" << endl;
	print(m, n, k);
	cout << endl;
	
	int bas_flag = 0;//���� ������������ �������
	vector <prime*> b;//������ �������
	int counter = 0;//������� �������
	for(int i = 0; i < k - 1; i++) 
	{
		if(i == a[counter])//���� ����� ���� � ����������
		{
			if(m[counter * k + i]->getchisl() == 0)//���� �������� ������� - 0
			{
				cout << "������� ���" << endl;
				bas_flag = 1;//������� ��� ���������� ���
			}
			else
			{
				b.push_back(m[counter * k + k - 1]);//��������� ����� � ������
				counter++;//����������� ������� �������	
			}
		}
		else 
		{
			b.push_back(new prime(0, 1));//���������� 0
		}
	}
	if(bas_flag == 1)
	{
	}
	else
	{
		int flag = 0;//���� �� ������� �������
		for (int i = 0; i < k - 1; i++)//�������� �� ������� ������� 
		{
			if (b[i]->getchisl() < 0)//���� ������������� �����
			{
				flag = 1;//������� �� �������
			}
		}
		for(int i = 0; i < k - 1; i++)//����� ������� �������
		{
			cout << *b[i] << " ";
		}
		if(!flag) 
		{
			cout << endl << "������� �������" << endl;
		}
		else
		{
			cout << endl << "�� ������� �������" << endl;
		}
	 	cout << endl;	
	}	
}

void answer(vector <prime*> m, int n, int k)//������ ����������
{
	int p;
	int* a = new int[n];//������ ����������
	for(int i = 0; i < n; i++) 
	{
		a[i] = i;//��������� �������������(0,1,2 � �.�...�� n)
	}
	while(1) 
	{
		for(int i = 0; i < n; i++)
		{
			cout << a[i] + 1 << " "; //����� ���������� - �� ������ - 1,2,3, �� � ������� - 0,1,2 � ��� ���	
		} 
		cout << endl;
		basis(m, a, n, k);//������� �������������� ������

		cout << endl;
		if(a[n - 1] < k - 1)//���� ���� ������� ����� ����������
		{
			a[n - 1]++;//����������� ����� ���������� �������
		}
		else//����� - ����, ������ ����������� 
		{
			for(p = n - 1; p > 0; p--)//������� ������� ��������� ��������� ������� � �����
			{
				if(a[p] - a[p - 1] > 1)//���� ������� ����� ���������� ������ 1
				{
					break;//����� ������� - �������
				}
			}
			if(p == 0)//���� ��� �������� ���������
			{
				break;//�����������
			}
			a[p - 1]++;//����������� ��������� �������
			for(int i = p; i < n; i++)//����������� ��������� ����� ���
			{
				a[i] = a[i - 1] + 1;//����� ��������� ������������ ����������� �� 1	
			}
		}
	}
}
	
int main()
{                     
    int n = 3, m = 5;
	vector <prime*> a;//�������� �������
	
	int b;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			cin >> b;
			a.push_back(new prime(b, 1));
		}
	}

	print(a, n, m);	
	gauss(a, n, m);
	print(a, n, m);	
	
	for(int i = 0; i < n; i++)//�������� ������� �����
	{
		int f = 0;//����, ������������ ������� ������
		for(int j = 0; j < m; j++) 
		{
			if (a[i * m + j]->getchisl() != 0)//���� ���� ��������� ������� 
			{
				f = 1;//������ ������ ���������
			}
		}
		if(f == 0)//���� ������ ������� 
		{
			a.erase(a.begin() + i * m, a.begin() + i * m + m);//��������� ������� �� � �������� ������ ������
			n--;//� ��������� ���������� �����
		}
	}

	answer(a, n, m - 1);//������, ���������� ����� � ���������� ����������(������� ������� �� ������)
	
	return 0;
}
