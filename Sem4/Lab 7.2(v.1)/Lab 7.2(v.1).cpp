#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <utility>
#include <cctype>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <windows.h>

using namespace std;

void StringToLower(string& str)
{
	for (int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	setlocale(LC_ALL, "Rus");
	ifstream fin(argv[1]);

	if (!fin)
	{
		cout << "The file doesn't open\n";
		exit(-1);
	}

	set <string> MainWords;
	map <string, string> Dictionary;
	vector <string> ExcessW{};

	while (!fin.eof())
	{
		bool flag{}, flag2{}, flag3{};
		string Wstr, FullDstr{}, Dstr{};
		fin >> Wstr >> Wstr;
		StringToLower(Wstr);
		MainWords.insert(Wstr);
		if (fin.eof()) break;
		fin >> Dstr;

		for (int i = 0; Dstr != "}" && !fin.eof(); i++, fin >> Dstr)
		{
			if (Dstr == "~")
			{
				fin >> Dstr;
				break;
			}
			if (Dstr == ">" || Dstr == "{") continue;
			if (Dstr == ",")
			{
				Dictionary.emplace(FullDstr, Wstr);
				FullDstr = {};
			}
			else
			{
				FullDstr.length() == 0 ?
					FullDstr += Dstr :
					FullDstr += " " + Dstr;
			}
		}
	}
	fin.close();
	for (int counterfile = 3; counterfile < argc; counterfile++)
	{
		bool Train{}, InFlag{};
		int tmp;
		cout << "Режим словоря:\n\t1.Автоматический режим\n\t2.Обучающий режим\nВыберите вариант: ";

		while (!InFlag)
		{
			cin >> tmp;
			switch (tmp)
			{
			case 1:
				Train = false;
				InFlag = 1;
				break;
			case 2:
				Train = true;
				InFlag = 1;
				break;
			default:
				cout << "\nНекорректный ввод.Выберите вариант 1 или 2.\nВыберите вариант:";
				continue;
			}
		}
		ofstream out;
		if (!Train)
		{
			out.open(argv[2]);
		}

		ifstream inp(argv[counterfile]);
		for (int i = 0; !inp.eof(); i++)
		{

			string str{}, punc{}, save{};
			bool flag{};
			char chr{};

			while (inp.read(&chr, sizeof(chr)) && !isspace(chr))
			{
				if (chr >= 'А' && chr <= 'я')
				{
					flag = 1;
					str.push_back(tolower(chr));
				}
				else if (!flag)cout << chr;
				else punc.push_back(chr);

			}
			if (MainWords.find(str) != MainWords.end()) cout << str;
			else
			{
				map <string, string>::iterator it = Dictionary.find(str);
				if (it != Dictionary.end()) cout << it->second;
				else
				{
					if (Train)
						ExcessW.push_back(str);
					else
						out << str << endl;
					cout << '<' << str << '>';
				}
			}


			cout << punc << chr;

		}
		string str{};

		if (Train && ExcessW.size() != 0)
		{
			cout << "\n_______________________\n_______________________\n";
			for (auto it = ExcessW.begin(); it != ExcessW.end(); it++)
			{
				cout << "Cлова \"" << *it << "\" нет в словаре. Что с ним сделать? \n\t1. Создать новое эталонное \
слово\n\t2. Добавление к списку синонимов существующего эталонного слова\n\t3. Замена существующего эталонного\
 слова \n\t4. Ничего\nВведите вариант: ";
				InFlag = {};
				while (!InFlag)
				{
					cin >> tmp;
					switch (tmp)
					{
					case 1:
					{
						ofstream fout(argv[1], ios_base::out | ios_base::app);
						fout << *it << " > { ~ }\n";
						fout.close();
						InFlag = 1;
						MainWords.insert(*it);
						cout << "Эталонное слово \"" << *it << "\" успешно добавлено в словарь!\n";
					}
					break;
					case 2:
					{
						string buf, CheakWord, synonym;
						vector<string>DataInFile{};
						cout << "К какому эталонному слову вы хотите добавить синоним: ";
						cin >> CheakWord;
						if (MainWords.find(CheakWord) == MainWords.end())
						{
							cout << "\nДанное слово не является эталонным\
\nВыберите вариант 1 - 4.\nВыберите вариант:";
							break;
						}
						fin.open(argv[1]);
						bool flagfind{};
						while (!fin.eof())
						{
							string shortbuf;
							getline(fin, buf);
							if (!flagfind)
								for (auto strit = buf.begin(); strit != buf.end(); strit++)
									if (*strit == '>')
										break;
									else if (*strit >= 'А' && *strit <= 'я')
										shortbuf.push_back(*strit);

							if (shortbuf == CheakWord)
							{
								flagfind = 1;
								if (buf[buf.length() - 3] != '~')
									buf[buf.length() - 1] = ',';
								else
								{
									buf.erase(buf.find('~') - 1);
								}
								buf += " " + *it + " }";
							}
							DataInFile.push_back(buf);
						}
						fin.close();
						ofstream fout(argv[1]);
						copy(DataInFile.begin(), DataInFile.end(), ostream_iterator<string>(fout, "\n"));
						fout.close();
						InFlag = 1;
						Dictionary.emplace(*it, CheakWord);
						cout << "Cиноним \"" << *it << "\" успешно добавлен к эталонному слову \"" << CheakWord << "\" в словарь!\n";
					}
					break;
					case 3:
					{
						string buf, CheakWord;
						vector<string>DataInFile{};
						cout << "Какое эталонное слово вы хотите заменить: ";
						cin >> CheakWord;
						if (MainWords.find(CheakWord) == MainWords.end())
						{
							cout << "\nДанное слово не является эталонным\
\nВыберите вариант 1 - 4.\nВыберите вариант:";
							break;
						}
						fin.open(argv[1]);
						bool flagfind{};
						while (!fin.eof())
						{
							string shortbuf;
							getline(fin, buf);
							if (!flagfind)
								for (auto strit = buf.begin(); strit != buf.end(); strit++)
									if (*strit == '>')
										break;
									else if (*strit >= 'А' && *strit <= 'я')
										shortbuf.push_back(*strit);

							if (shortbuf == CheakWord)
							{
								buf.erase(0, buf.find('>'));
								buf = "< " + *it + buf;
							}
							DataInFile.push_back(buf);
						}
						fin.close();
						ofstream fout(argv[1]);
						copy(DataInFile.begin(), DataInFile.end(), ostream_iterator<string>(fout, "\n"));
						fout.close();
						InFlag = 1;
						cout << "Успешная замена эталонного слова:\"" << CheakWord << "\" на слово \"" << *it << "\" в словарь!\n";
					}
					break;
					case 4:
					{
						InFlag = 1;
					}
					break;
					default:
						cout << "\nНекорректный ввод.Выберите вариант 1 - 4.\nВыберите вариант:";
						continue;
					}
				}
			}
		}
		inp.close();
		if(argc - counterfile > 1) cout << "\n__________\nNextFile\n__________\n";
	}
}