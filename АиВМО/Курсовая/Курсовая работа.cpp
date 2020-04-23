#include <iostream>
#include <vector>

using namespace std;

class prime//класс простых дробей
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

void print(prime  *a, int n, int m)//вывод расширенной матрицы 
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

void print2(prime *a, prime *so, prime *z, int n, int m, int t)//вывод симплекс-таблицы 
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
			if(a[i * m + j].getchisl() == 1 && a[i * m + j].getznam() == 1 && iswrite == 0)//если нашли единицу
			{
				for(int k = 0; k < n; k++)//смотрим, является ли столбец базисным
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
				if(nul == n - 1 && ed == 1)//если столбец - базисный
				{
					switch(bas_stolb)//пишем переменную, соответствующую базису
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
			if(iswrite == 1)//если переменная уже написана
			{
				for(int h = 0; h < m; h++)//выводим оставшиеся элементы
				{
					cout << a[i * m + h] << "\t";	
				}
				cout << so[i] << endl;//вывод симплекс-отношений
				iswrite = 0;	
			}
		}	
	}
		
	cout << endl << "Z\t";
	for(int i = 0; i < m; i++)//вывод z-строки
	{
		cout << z[i] << "\t";
	}
	cout << endl;
}

void gauss(prime *a, prime *z, int n, int m, int* bas)//преобразование матрицы методом Жордана-Гаусса
{
	int y = 0;//текущий столбец 
	prime *res = new prime(0, 1);//разрешающий элемент
	for(int i = 0; i < n; i++)//преобразование матрицы(i - номер разрешающей строки)
	{
		y = bas[i];//становимся на разрешающий столбец
		*res = a[i * m + y];//получаем разрешающий элемент
		for(int j = 0; j < m; j++)//делим строку на разрешающий элемент
		{
			a[i * m + j] /= *res;	
		}
		*res /= *res;//также делим разрешающий элемент сам на себя, чтобы не потерялся		
		for(int j = 0; j < n; j++)//проход по матрице для расчета элементов
		{
			if(i == j) //если элемент на разрешающей строке - пропускаем
			{
				continue;	
			}
			for(int k = 0; k < m; k++)
			{
				if(y == k)//если элемент на разрешающем столбце - пропускаем
				{
					continue;
				}
				a[j * m + k] -= ((a[j * m + y] * a[i * m + k]) / *res);//преобразование по правилу прямоугольника		
			}	
		}
		for(int j = 0; j < n; j++)//зануление элементов столбца
		{
			if(i == j) //если на разрешающей строке - пропускаем
			{
				continue;
			}
			a[j * m + y] = prime(0, 1); //зануляем элементы
		}
		print(a, n, m);	
	}	
}

void z_count(prime *a, prime *z, int n, int m, int *bas, int *svob, int *cof)//первичный расчет коэффициентов z-строки
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

int simplex_table(prime *a, prime *z, int n, int m)//построение симплекс-таблицы
{
	prime *max = new prime(0, 1);
	prime *min = new prime(9999, 1);
	prime *res = new prime(0, 1);
	
	prime *so = new prime[n];
	
	int max_index = 0;//индекс разрешающего столбца
	int min_index = 0;//индекс разрешающей строки
	int flag = 0;//флаг, проверяющий оптимальность плана
	int bas_stolb = 0;//индекс местоположения 1 в базисном столбце, который уберется после построения таблицы
	int t = 0;//индекс таблицы
			
	for(int i = 0; i < n; i++)//инициализация симплекс-отношений
	{
		so[i] = prime(0, 1);
	}	
	
	while(1)
	{	
		t++;//индекс таблицы			
		for(int i = 0; i < n; i++)//инициализация симплекс-отношений
		{
			so[i] = prime(0, 1);
		}
		
		*max = z[1];
		for(int i = 2; i < m; i++)//ищем минимальный элемент в z-строке
		{
			if(z[i].getchisl() < 0)
			{
				flag = 1;
			}
			if(z[i].getchisl() < max->getchisl())//если элемент z-строки меньше минимума
			{
				*max = z[i];//запоминаем минимум
				max_index = i;//и индекс разрешающего столбца
			}
		}
		
		if(flag == 0)//если все элементы z-строки положительные
		{
			print2(a, so, z, n, m, t);
			cout << "plan optimalen" << endl;//то план оптимален - можно заканчивать
			return 0;
		}
		
		for(int i = 0; i < n; i++)//расчет симплекс-отношений
		{
			so[i] = a[i * m] / a[i * m + max_index];
			if(so[i].getchisl() < min->getchisl() && so[i].getchisl() > 0)//ищем минимальное симплекс-отношение
			{
				*min = so[i];//запоминаем минимум СО
				min_index = i;//и индекс разрешающей строки
			}
		}
		
		print2(a, so, z, n, m, t);
		cout << "plan ne optimalen" << endl;
		cout << "max stolbets - " << *max << " " << max_index << endl;
		cout << "min_stroka - " << *min << " " << min_index << endl;
		*res = a[min_index * m + max_index];//разрешающий элемент
		cout << "res elem - " << *res << endl;
		
		int nul = 0;//счетчик количества нулей в базисном столбце(должен быть равен 2)
		int ed = 0;//счетчик количества единиц в базисном столбце(должен быть равен 1)
		for(int i = 0; i < m; i++)//ищем, какой столбец(переменная) уберется из базиса
		{
			if(a[min_index * m + i].getchisl() == 1 && a[min_index * m + i].getznam() == 1)//если найденный элемент - 1
			{
				for(int j = 0; j < n; j++)//проверяем, является ли столбец базисным
				{
					if(a[j * m + i].getchisl() == 0)
					{
						nul++;	
					}
					if(a[j * m + i].getchisl() == 1)
					{
						bas_stolb = j;//запоминаем индекс для построения будущего базисного столбца
						ed++;	
					}
				}
				if(nul == n - 1 && ed == 1)//если столбец базисный - заканчиваем поиск
				{
					break;
				}
			}
		}
		
		for(int i = 0; i < n; i++)//проход для подсчета элементов
		{
			if(i == min_index)//если на разрешающей строке - пропускаем
			{
				continue;
			}
			for(int j = 0; j < m; j++)
			{
				if(j == max_index)//если на разрешающем столбце - пропускаем 
				{
					continue;
				}
				a[i * m + j] -= ((a[i * m + max_index] * a[min_index * m + j]) / *res);//преобразование	правилом прямоугольника	
			}	
		}
		
		for(int i = 0; i < m; i++)//расечт z-строки по правилу прямоугольника
		{
			if(i == max_index)//если на разрешающем столбце - пропускаем
			{
				continue;
			}
			z[i] -= ((a[min_index * m + i] * z[max_index]) / *res);
		}
		
		z[max_index] = prime(0, 1);//ставим 0 под новым базисным столбцом
					
		for(int i = 0; i < m; i++)//делим разрешающую строку на разрешающий элемент
		{
			a[min_index * m + i] /= *res;
		}
		
		for(int i = 0; i < n; i++)//добавляем переменную в базис
		{
			if(i == bas_stolb)//если совпала с индексом, то 1
			{
				a[i * m + max_index] = prime(1, 1);	
			}
			else
			{
				a[i * m + max_index] = prime(0, 1);//иначе - 0	
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
	
	int *cof = new int[n - 1];//коэффициенты при целевой функции
	cof[0] = -9;
	cof[1] = -2;
	int *svob = new int[n - 1];//свободные переменные
	svob[0] = 3;
	svob[1] = 4;
	int* bas = new int[n];//базисные переменные
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
