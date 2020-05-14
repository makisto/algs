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

void gauss(vector <prime*> a, int n, int m)//функция жордана-гаусса(1 лаба)
{
	int x = 0, y = 0, f = 0;//текущая строка, столбец и флаг
	prime null_prime(0, 1);//занулятель
	for(int i = 0; i < n; i++) //преобразуем матрицу
	{
		if(a[y * m + x]->getchisl() == 0) //если диагональный элемент - 0
		{
			if(i == n - 1) //если последняя строка - выходим
			{
				break;	
			}
			for(int j = y + 1; j < n; j++)//ищем строку с положительным элементом
			{
				if(a[j * m + x]->getchisl() > 0)//если нашли
				{
					f = 1;//обозначаем это
					for(int k = x; k < m; k++)//и складываем строки
					{
						*a[y * m + k] += *a[j * m + k];	
					}
				}		
			}
			if(f == 0)//если не нашли
			{
				x++;//переходим на след строку
				y++;//переходим на след столбец
				continue;
			}	
		}
		for(int j = 0; j < n; j++)//проход для подсчета элементов
		{
			if (y == j) //если на диагональном элементе - пропускаем
			{
				continue;	
			}
			for(int k = x + 1; k < m; k++) // подсечет элементов правилом прямоугольника
			{
				*a[j * m + k] = ((*a[y * m + x]) * (*a[j * m + k]) - (*a[j * m + x]) * (*a[y * m + k])) / *a[y * m + x]; //преобразование
			}	
		}
		for(int j = 0; j < n; j++) // зануление элементов столбца
		{
			if(y == j) //если на диагональном элементе - пропускаем
			{
				continue;
			}
			*a[j * m + x] = null_prime; //зануляем элементы
		}
		x++;//переходим на след строку
		y++;//переходим на след столбец
	}
	x = 0, y = 0; 
	for(int i = 0; i < n; i++) // делаем единицы в матрице
	{
		if(a[y * m + x]->getchisl() == 0) // если диагональный элемент - 0
		{
			x++;//переходим на след строку
			y++;//переходим на след столбец
			continue;
		}
		for(int j = m - 1; j >= x; j--) //делим строку на диагональный элемент
		{
			*a[i * m + j] /= *a[y * m + x]; //деление строки
		}
		x++;//переходим на след строку
		y++;//переходим на след столбец
	}	
}

void basis(vector <prime*> cp, int* a, int n, int k)//преобразование базиса
{
	k++;//возвращаем столбец ответов
	vector <prime*> m;
	for(int i = 0; i < n * k; i++)//создаем копию исходного вектора
	{
		m.push_back(new prime(cp[i]->getchisl(), cp[i]->getznam()));
	}
	
	for(int i = 0; i < n; i++)//меняем столбцы соответственно комбинации поэлементно сверху вниз слева направо
	{
		for (int j = 0; j < n; j++)
		{
			prime* tp = m[i * k + j];
			m[i * k + j] = m[i * k + a[j]];
			m[i * k + a[j]] = tp;
		}
	}

	cout << "После перестановки" << endl;
	print(m, n, k);
	cout << endl;
	
	gauss(m, n, k);//запускаем метод гаусса
	
	cout << "После Гаусса" << endl;
	print(m, n, k);
	cout << endl;
	
	for (int i = 0; i < n; i++)//обратно меняем столбцы свреху вниз справа налево
	{
		for (int j = 0; j < n; j++)
		{
			prime* tp = m[i * k + n - j - 1];
			m[i * k + n - j - 1] = m[i * k + a[n - j - 1]];
			m[i * k + a[n - j - 1]] = tp;
		}
	}
	
	cout << "После второй перестановки" << endl;
	print(m, n, k);
	cout << endl;
	
	int bas_flag = 0;//флаг корректности решения
	vector <prime*> b;//вектор ответов
	int counter = 0;//счетчик ответов
	for(int i = 0; i < k - 1; i++) 
	{
		if(i == a[counter])//если номер есть в комбинации
		{
			if(m[counter * k + i]->getchisl() == 0)//если базисный элемент - 0
			{
				cout << "Решения нет" << endl;
				bas_flag = 1;//решения для комбинации нет
			}
			else
			{
				b.push_back(m[counter * k + k - 1]);//добавляем число в вектор
				counter++;//увеличиваем счетчик ответов	
			}
		}
		else 
		{
			b.push_back(new prime(0, 1));//записываем 0
		}
	}
	if(bas_flag == 1)
	{
	}
	else
	{
		int flag = 0;//флаг на опорное решение
		for (int i = 0; i < k - 1; i++)//просмотр на опорное решение 
		{
			if (b[i]->getchisl() < 0)//если отрицательное число
			{
				flag = 1;//решение не опорное
			}
		}
		for(int i = 0; i < k - 1; i++)//вывод вектора ответов
		{
			cout << *b[i] << " ";
		}
		if(!flag) 
		{
			cout << endl << "Опорное решение" << endl;
		}
		else
		{
			cout << endl << "Не опорное решение" << endl;
		}
	 	cout << endl;	
	}	
}

void answer(vector <prime*> m, int n, int k)//расчет комбинаций
{
	int p;
	int* a = new int[n];//массив комбинаций
	for(int i = 0; i < n; i++) 
	{
		a[i] = i;//начальная инициализация(0,1,2 и т.д...до n)
	}
	while(1) 
	{
		for(int i = 0; i < n; i++)
		{
			cout << a[i] + 1 << " "; //вывод комбинации - на экране - 1,2,3, но в массиве - 0,1,2 и так ана	
		} 
		cout << endl;
		basis(m, a, n, k);//функция преобразования базиса

		cout << endl;
		if(a[n - 1] < k - 1)//если есть столбцы после последнего
		{
			a[n - 1]++;//увеличиваем номер последнего столбца
		}
		else//иначе - ищем, откуда увеличивать 
		{
			for(p = n - 1; p > 0; p--)//смотрим разницу ближайших элементов начиная с конца
			{
				if(a[p] - a[p - 1] > 1)//если разница между ближайшими больше 1
				{
					break;//нашли элемент - выходим
				}
			}
			if(p == 0)//если все варианты перебрали
			{
				break;//заканчиваем
			}
			a[p - 1]++;//увеличиваем найденный элемент
			for(int i = p; i < n; i++)//увеличиваем остальные перед ним
			{
				a[i] = a[i - 1] + 1;//путем привоения увелеченного предыдущего на 1	
			}
		}
	}
}
	
int main()
{                     
    int n = 3, m = 5;
	vector <prime*> a;//исходная матрица
	
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
	
	for(int i = 0; i < n; i++)//удаление нулевых строк
	{
		int f = 0;//флаг, обозначающий нулевую строку
		for(int j = 0; j < m; j++) 
		{
			if (a[i * m + j]->getchisl() != 0)//если есть ненулевой элемент 
			{
				f = 1;//значит строка ненулевая
			}
		}
		if(f == 0)//если строка нулевая 
		{
			a.erase(a.begin() + i * m, a.begin() + i * m + m);//физически удаляем ее и сдвигаем другие строки
			n--;//и уменьшаем количество строк
		}
	}

	answer(a, n, m - 1);//вектор, количество строк и количество переменных(столбец ответов не входит)
	
	return 0;
}
