#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <locale>
using namespace std;
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	ifstream inp;
	regex Сorrectness("([А-Я]{1}[а-я]+\\s){3}\\d{16}\\s([a-z|A-Z|\\d])+@[a-z]+\.[a-z]+\\s\
(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])\
(\.(25[0-5]|2[0-4][0-9]|[0-1][0-9]{2}|[0-9]{2}|[0-9])){3}\\s+\
[\+]\\d(([(]\\d{3}[)])|\\d{3})\\\d{3}[-]?\\d{2}[-]?\\d{2}\\s");
	for (unsigned CounterOfFile{ 1 }; CounterOfFile < argc; CounterOfFile++)
	{
		inp.open(argv[CounterOfFile]);
		if (!inp)
		{
			cout << "Файл " << argv[CounterOfFile] << "не открылся!\n";
			exit(-1);
		}



		string allstr, str;


		while (!inp.eof())
		{
			getline(inp, allstr);
			if (!allstr.size()) continue;
			if (allstr[allstr.size() - 1] != ' ') allstr.push_back(' ');
			if (!regex_match(allstr, Сorrectness)) {
				cout << allstr << endl;
				continue;
			}
			unsigned  CounterOfString{};
			while (allstr.size())
			{
				int tmp;
				allstr.find(' ') > allstr.find('\t') ? tmp = allstr.find('\t') 
					: tmp = allstr.find(' ');
				str = allstr.substr(0, tmp);
				allstr.erase(0, tmp + 1);
				switch (CounterOfString)
				{
				case 0:
					cout << str[0];
					for (int i = 1; i < str.size(); i++)
						cout << "x";
					cout << ' ';
					break;
				case 1:
					cout << str[0] << ". ";
					break;
				case 2:
					cout << str[0] << ". ";
					break;
				case 3:
					cout << str[0] << str[1] << str[2];
					for (int i = 3; i < str.size() - 2; i++)
						cout << "x";
					cout << str[str.size() - 2] << str[str.size() - 1] << ' ';
					break;
				case 4:
				{
					int flag{};
					cout << str[0];
					for (auto it = str.begin() + 1; it != str.end(); it++)
					{
						if (*it == '.')
						{
							flag = 2;
							cout << *it;
							continue;
						}
						if (*it == '@')
						{
							flag = 1;
							cout << *it;
							continue;
						}
						if (flag == 0) cout << 'x';
						else if (flag == 1) cout << 'y';
						else if (flag == 2) cout << *it;
					}
					cout << ' ';
				}
				break;
				case 5:
				{
					unsigned countp{};
					for (auto it = str.begin(); it != str.end(); it++)
					{
						if (*it == '.') countp++;
						countp >= 3 ? cout << *it : *it == '.' ? cout << *it : cout << 'X';
					}
					cout << ' ';
				}
				break;
				case 6:
				{
					unsigned countw{};
					for (auto it = str.begin(); it != str.end(); it++)
					{
						if (isdigit(*it)) countw++;
						if (countw >= 2 && countw <= 7 && isdigit(*it) && *it != '+') cout << 'X';
						else cout << *it;
					}
					cout << ' ';
				}
				break;
				default:
					break;
				}
				CounterOfString++;
			}
			cout << endl;
		}
		inp.close();
		if(argc - CounterOfFile > 1) cout << "____________\nNext File\n___________\n";
	}



}
