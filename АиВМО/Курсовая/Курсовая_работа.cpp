#include <iostream>
#include <vector>
#include <fstream>

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

void print(prime  *a, int n, int m)//вывод расширенной матрицы 
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

void print2(prime *a, prime *so, prime *z, int n, int m, int t)//вывод симплекс-таблицы 
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
					cout << "x" << bas_stolb << "\t";
					iswrite = 1;
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
			nul = 0;
			ed = 0;
		}	
	}
		
	cout << endl << "Z\t";
	for(int i = 0; i < m; i++)//вывод z-строки
	{
		cout << z[i] << "\t";
	}
	cout << endl;
}

void gauss(prime *a, int n, int m, int* bas, int* svob)//преобразование матрицы методом Жордана-Гаусса
{
	m:int y = 0;//текущий столбец 
	prime *res = new prime(0, 1);//разрешающий элемент
	for (int i = 0; i < n; i++)//избавляемся от отрицательных элементов в столбце свободных членов
	{
		if (a[i * m].getchisl() < 0)//если элемент меньше нуля
		{
			for (int j = 0; j < m; j++)//умножаем всю строку на -1
			{
				a[i * m + j] = -1 * a[i * m + j];
			}
		}
	}
	print(a, n, m);
	for(int i = 0; i < n; i++)//преобразование матрицы(i - номер разрешающей строки)
	{
		y = bas[i];//становимся на разрешающий столбец
		*res = a[i * m + y];//получаем разрешающий элемент
		if (res->getchisl() == 0)//если разрешающий элемент - 0
		{
			for (int j = i + 1; j < n; j++)//ищем в столбце ненулевой элемент
			{
				if (a[j * m + y].getchisl() != 0)//если нашли
				{
					for (int k = 0; k < m; k++)//складываем строки
					{
						a[i * m + k] += a[j * m + k];
					}
					break;//выход из цикла
				}
			}
		}
		*res = a[i * m + y];//переприсовение разрешающего элемента
		if (res->getchisl() == 0)//если разрешающий элемент также 0
		{
			cout << "net reshenia" << endl;//то решения нет
			exit(1);
		}
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

	int index = 0;//индекс базисного столбца, необходимого для замены
	int nul = 0;//счетчик количества нулей в базисном столбце(должен быть равен 2)
	int ed = 0;//счетчик количества единиц в базисном столбце(должен быть равен 1)
	for (int i = 0; i < n; i++)//если после преобразований все еще есть отрицательные элементы в столбце свободных членов
	{
		if (a[i * m].getchisl() < 0)//то решение не опорное
		{
			for (int j = 0; j < m; j++)
			{
				if (a[i * m + j].getchisl() == 1 && a[i * m + j].getznam() == 1)//ищем базисный столбец
				{
					for (int k = 0; k < n; k++)//проверяем, является ли столбец базисным
					{
						if (a[k * m + j].getchisl() == 0)
						{
							nul++;
						}
						if (a[k * m + j].getchisl() == 1)
						{
							index = j;//запоминаем индекс для замены базисной переменной
							ed++;
						}
					}
					if (nul == n - 1 && ed == 1)//если столбец базисный - заканчиваем поиск
					{
						break;
					}
				}
			}
		}
	}
	int k = 0;//индекс новой базисной переменной
	for (int i = 0; i < n; i++)
	{
		if (bas[i] == index)//если нашли нужную переменную
		{
			cout << "reshenie ne opornoe" << endl;
			int temp = bas[i];//убираем её из базиса и заменяем на свободную
			bas[i] = svob[k];
			svob[k] = temp;
			k++;
			if (k == m - n - 1)//если прошлись по свободным переменным
			{
				k = 0;//возвращаемся в начало
			}
			goto m;//расчитываем по-новой
		}
	}
}

void z_count(prime *a, prime *z, int n, int m, int *bas, int *svob, int *cof)//первичный расчет коэффициентов z-строки
{	
	for (int i = 0; i < m; i++)//инициализация z-строки
	{
		z[i] = prime(0, 1);
	}
	int flag = 0;//флаг, указывающий на принадлежность переменной базису
	for(int i = 0; i < m; i++)//проход по всем элементам z-строки
	{
		flag = 0;
		if(cof[i] != 0)//если при переменной стоит ненулевой коэффициент в целевой функции
		{
			for (int j = 0; j < n; j++)//смотрим, принадлежит ли он базисной переменной
			{
				if (bas[j] == i)//если принадлежит
				{
					flag = 1;//ставим флаг
					for (int k = 0; k < m - n - 1; k++)//выражаем базисную переменную через свободные и заполняем соответствующие элементы z-строки
					{
						z[svob[k]] += cof[i] * a[j * m + svob[k]];
					}
					z[0] += cof[i] * a[j * m];//заполняем z0
				}
			}
		}
		if (flag == 0)//если коэффициент при свободной переменной
		{
			z[i] = z[i] + (cof[i] * -1);//добавляем
		}
	}
}

int simplex_table(prime *a, prime *z, int n, int m, int stage)//построение симплекс-таблицы
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
	int nil = 0;//счетчик нулей на случай бесконечно многих решений
	int count = 0;//счетчик количества вершин многогранника решений на случай бесконечно многих решений

	for(int i = 0; i < n; i++)//инициализация симплекс-отношений
	{
		so[i] = prime(0, 1);
	}	
	
	while(1)
	{	
		for (int i = 0; i < n; i++)//проверка на опорность решения
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
		t++;//индекс таблицы	
		for(int i = 0; i < n; i++)//инициализация симплекс-отношений
		{
			so[i] = prime(0, 1);
		}
		
		*max = z[1];
		max_index = 1;
		for(int i = 1; i < m; i++)//ищем минимальный/максимальный элемент в z-строке
		{
			if (stage)//если надо найти максимальный
			{
				if (z[i].getchisl() > 0)
				{
					flag = 1;
				}
				if ((z[i].getchisl() * max->getznam() > max->getchisl() * z[i].getznam()))//если элемент z-строки больше максимума
				{
					*max = z[i];//запоминаем максимум
					max_index = i;//и индекс разрешающего столбца
				}
			}
			else//иначе
			{
				if (z[i].getchisl() < 0)
				{
					flag = 1;
				}
				if ((z[i].getchisl() * max->getznam() < max->getchisl() * z[i].getznam()))//если элемент z-строки меньше минимума
				{
					*max = z[i];//запоминаем минимум
					max_index = i;//и индекс разрешающего столбца
				}
			}
		}

		for (int i = 1; i < m; i++)//подсчет нулей в z-строке
		{
			if (z[i].getchisl() == 0)
			{
				nil++;
			}
		}

		if (nil > n)//если нулей больше, чем базисных переменных
		{
			for (int i = 1; i < m; i++)//ищем, где стоит 0 не под базисом
			{
				if (z[i].getchisl() == 0)
				{
					for (int j = 0; j < n; j++)
					{
						if (a[j * m + i].getchisl() != 0 && a[j * m + i].getchisl() != 1)
						{
							max_index = i;//и запоминаем индекс
						}
					}
				}
			}
			count++;//подсчет количества врешин многогранника решений
		}

		if((flag == 0 && nil == n) || count == 2)//если все элементы z-строки положительные и количество решений конечно или уже найдены вершины многогранника решений
		{
			print2(a, so, z, n, m, t);
			cout << "plan optimalen" << endl;//то план оптимален - можно заканчивать
			return 0;
		}

		for(int i = 0; i < n; i++)//расчет симплекс-отношений
		{
			if (a[i * m + max_index].getchisl() <= 0)
			{
				continue;
			}
			else
			{
				so[i] = a[i * m] / a[i * m + max_index];
			}
			if((so[i].getchisl() * min->getznam() < min->getchisl() * so[i].getznam()) && so[i].getchisl() > 0)//ищем минимальное симплекс-отношение
			{
				*min = so[i];//запоминаем минимум СО
				min_index = i;//и индекс разрешающей строки
			}
		}

		print2(a, so, z, n, m, t);
		if (min->getchisl() == 9999 && min->getznam() == 1)//если в СО нет элементов или все отрицательные
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
		bas_stolb = 0;
	}	
}

void svob_count(int *bas, int *svob, int n, int m)//вычисление свободных переменных
{
	int k = 0;//индекс свободной переменной
	int flag = 0;//флаг, следящий за наличием переменной в базисе
	for (int i = 1; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (bas[j] == i)//если переменная в базисе
			{
				flag = 1;//отмечаем это
			}
		}
		if (flag == 0)//если переменной в базисе не было
		{
			svob[k] = i;//добавляем её в свободную
			k++;//увеличиваем индекс
			if (k == m - n - 1)//когда расчитали все переменные
			{
				break;//выходим
			}
		}
		flag = 0;
	}
}

int main()
{   
	//////////////////////////////////////////////ввод из файла

	int n;//строки
	int m;//столбцы
	int stage;//флаг минимума(1)/максимума(0)

	ifstream fin("file.txt"); 

	fin >> n >> m;
	
	prime* a = new prime[m * n];//исходная матрица в виде простых дробей
	prime* z = new prime[m];//z-строка

	int* cof = new int[m];//коэффициенты при целевой функции
	int* svob = new int[m - n - 1];//свободные переменные
	int* bas = new int[n];//базисные переменные

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
	
	///////////////////////////////// ввод из программы
	/*const int n = 3; 
	const int m = 6;

	int stage = 1;//флаг минимума(1)/максимума(0)

	prime* a = new prime[m * n];//исходная матрица в виде простых дробей
	prime* z = new prime[m];//z-строка

	int* cof = new int[m];//коэффициенты при целевой функции
	int* svob = new int[m - n - 1];//свободные переменные
	int* bas = new int[n];//базисные переменные

	int matr[n * m] = //исходная матрица
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
