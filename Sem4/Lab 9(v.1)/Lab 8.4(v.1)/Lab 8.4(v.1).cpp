#include <iostream>
#include <fstream>
#include <time.h>
#include <locale.h>
#include <vector>
using namespace std;
class Human
{
private:
	unsigned id;
	unsigned state;// 0 - здоров / 1 - болен / 2 - выздоровел

	static unsigned count;
	static vector<vector<bool>> Table;
	static vector<Human*> People;
public:
	Human()
	{
		id = count++;
		state = {};
		vector<bool> row;
		for (int j = 0; j < count; j++)
			if(j != id)
				row.push_back(rand() % 2);
			else 
				row.push_back(0);
		Human::Table.push_back(row);
		for (auto i = 0 ; i < Human::Table.size() - 1; i++)
			(Table[i]).push_back(row[i]);

		Human::People.push_back(this);
	}
	static void get()
	{
		cout << "------\nТаблица знакомств\n";
		for (auto it = Human::Table.begin(); it != Human::Table.end(); it++)
		{
			for (auto jt = it->begin(); jt!= it->end(); jt++)
				cout << *jt<< ' ';
			cout << endl;
		}
		cout << "------\nСписок заболевших\n";
		for (auto it = Human::People.begin(); it != Human::People.end(); it++)
		{
			cout << (*it)->state << ' ';
		}
		cout << "\n";
	}

	static void SetInfection()
	{
		int Rand = rand() % count;
		People[Rand]->state = 1;
		cout << "_______Начало распростроения вируса\n~ ~ ~ Человек №" << Rand << " заразился !!!\n";
	}

	static bool Tick(double P1, double P2)
	{
		vector<unsigned> List;
		for (auto it = People.begin(); it != People.end(); it++)
			List.push_back((*it)->state);
		if (find(List.begin(), List.end(), 1) == List.end()) return 1;
		for (int i = 0; i < count; i++)
		{
			if (List[i] == 1)
			{
				for (int j = 0; j < count; j++)
				{
					if (Table[i][j] && People[j]->state == 0)
						if (rand() % 101 < P1 * 100)
						{
							People[j]->state = 1;
							cout << "~ ~ ~ Человек №" << People[i]->id << " заразил человека №"
								<< People[j]->id<< "!\n";
						}
				}

				if (rand() % 101 < P2 * 100)
				{
					People[i]->state = 2;
					cout << "~ ~ ~ Человек №" << People[i]->id<< " исцелился!\n";
				}
			}

		}

		return 0;
	}
	static void search1()
	{
		bool flag{};
		for (auto it = Human::People.begin(); it != People.end(); it++)
			if ((*it)->state == 0)
			{
				cout << '№' <<(*it)->id << ' ';
				flag = 1;
			}
		if (!flag) cout << "не заразившихся людей нет. Все заражены\n";
		else cout << "не заражены\n";
	}
	static void search2()
	{
		bool flag{};
		for (auto it = Human::People.begin(); it != People.end(); it++)
			if ((*it)->state == 2)
			{
				cout << '№' << (*it)->id << ' ';
				flag = 1;
			}
		if (!flag) cout << "исцелившихся людей нет. Все заражены или не болеют\n";
		else cout << "исцелились\n";
	}
	static void search3()
	{
		bool flag{}, neaded{};
		for (int i = 0; i < count; i++)
		{
			if (People[i]->state == 2) {
				for (int j = 0; j < count; j++)
					if (Table[i][j] == 1 && People[j]->state != 2) neaded = 1;
				if (neaded)
				{
					cout << '№' << People[i]->id << ' ';
					flag = 1;
				}
			}
			neaded = {};
		}
		if (!flag) cout << "у всех исцелившихся людей окружение исцелилось";
		else cout << "исцелились, а их окружение нет\n";
	}
	static void search4()
	{
		bool flag{}, neaded{};
		for (int i = 0; i < count; i++)
		{
			if (People[i]->state == 0) {
				for (int j = 0; j < count; j++)
					if (Table[i][j] == 1 && People[j]->state != 1) neaded = 1;
				if (!neaded)
				{
					cout << '№' << People[i]->id << ' ';
					flag = 1;
				}
			}
			neaded = {};
		}
		if (!flag) cout << "не заразившихся людей, окуржение которых заражено нет";
		else cout << "не заразились, а их окружение заразилось\n";
	}
	~Human(){}
};
unsigned Human::count{};
vector<vector<bool>> Human::Table;
vector<Human*> Human::People;

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "rus");
	
	double P1{ -1 }, P2{ -1 };
	unsigned CountOfPeople;

	cout << "Вероятность заразиться при контакте P1 = ";
	cin >> P1;
	if (P1 <= 0 || P1 > 1)
	{
		cout << "Неверные данные";
		exit(-1);
	}
	cout << "Вероятность излечиться P2 = ";
	cin >> P2;
	if (P2 < 0 || P2 > 1)
	{
		cout << "Неверные данные";
		exit(-1);
	}
	cout << "Количество людей = ";
	cin >> CountOfPeople;

	Human* objs = new Human[CountOfPeople];

	if (CountOfPeople < 3 || CountOfPeople > 20)
	{
		cout << "Неверные данные";
		exit(-1);
	}
	int tmp;
	cout << "\n__________________\nЗаражение началось :-)) \n\n";
	Human::SetInfection();
	while (true)
	{
		cout << "Выберите действие :\n\t1. Следующий день\n\t2. Показать таблицу знакомств и список зараженных\
\n\t2. Изменить вероятности\n\t4. Поиск\n\t5. Выход \n Введите цифру : ";
		cin >> tmp;
		switch (tmp)
		{
		case 1:
			if (Human::Tick(P1, P2)) 
			{
				cout << "\n\nВ мире не осталось больных людей. Вирус побежден!!!!!";
				return (0);
			}
			break;
		case 2:
			Human::get();
			break;
		case 3:
			cout << "Вероятность заразиться при контакте P1 = ";
			cin >> P1;
			if (P1 <= 0 || P1 > 1)
			{
				cout << "Неверные данные";
				exit(-1);
			}
			cout << "Вероятность излечиться P2 = ";
			cin >> P2;
			if (P2 < 0 || P2 > 1)
			{
				cout << "Неверные данные";
				exit(-1);
			}
			break;
		case 4:
		{
			int search;
			cout << "\tВыберите поиск:\n\t\t1. Поиска всех не заразившихся людей\
\n\t\t2. Поиска всех исцелившихся\n\t\t3. Поиска исцелившихся людей, окружение \
которых не исцелилось\n\t\t4. Поиск не заразившихся людей, окружение которых заразилось\
\n\t\t5. Выход\n\tВыберите поиск :";
			cin >> search;
			switch (search)
			{
			case 1:
				cout << "(?) Результаты поиска незаразившихся людей: ";
				Human::search1();
				break;
			case 2:
				cout << "(?) Результаты поиска исцелившихся людей: ";
				Human::search2();
				break;
			case 3:
				cout << "(?) Результаты поиска исцелившихся людей, окружение которых не исцелилось: ";
				Human::search3();
				break;
			case 4:
				cout << "(?) Результаты поиска незараженных людей, окружение которых заразилось: ";
				Human::search4();
				break;
			default:
				break;
			}
		}
			break;
		case 5:
			return 0;
		default:
			break;
		}
		cout << endl;
	}

}

