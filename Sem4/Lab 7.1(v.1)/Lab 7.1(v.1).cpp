#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <utility>
#include <vector>
#include <locale>
const int CountVowels = 10;
using namespace std;

void StringToLower(string &str) 
{
	for (int i = 0; i < str.length(); i++)
		str[i] = tolower(str[i]);
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "Rus");
	ifstream fin(argv[1]);
	multimap<pair<int, string>, string> Dictionary;
	const char vowels[CountVowels]{'à', 'î', 'ó', 'û', 'ý','å','¸','þ','ÿ','è' };
	if (!fin)
	{
		cout << "The file doesn't open\n";
		exit(-1);
	}

	string tmp;
	while(fin >> tmp)
	{
		string first{};
		int counter{};
		//InputData.push_back(tmp);
		for(int j = 0; j < tmp.length(); j++)
			for (int k = 0; k < CountVowels; k++)
				if (tmp[j] == vowels[k])
				{
					counter++;
					break;
				}
		for (int j = tmp.length() - 1; j >= 0 && tmp.length() - j <= 3; j--)
			if (tmp[j] != '-')
				first.push_back(tolower(tmp[j]));

		Dictionary.emplace(make_pair(counter, first), tmp);
	}

	fin.close();
	ifstream inp(argv[2]);
	if (!inp)
	{
		cout << "The file doesn't open\n";
		exit(-2);
	}
	ofstream out(argv[3]);
	if (!out)
	{
		inp.close();
		cout << "The file doesn't open\n";
		exit(-3);
	}

	//--
	char chr;
	for (int i = 0; !inp.eof(); i++)
	{
		string first{};
		int counter{};
		tmp = {};

		// parse
		while (inp.read(&chr, sizeof(chr)) && (ispunct(chr) || isspace(chr) ))
			out << chr;
		if (inp.eof()) break;
		tmp.push_back(chr);
		while (inp.read(&chr, sizeof(chr)) && !ispunct(chr) && !isspace(chr))
			tmp.push_back(chr);
		StringToLower(tmp);
		// key
		for (int j = 0; j < tmp.length(); j++)
			for (int k = 0; k < CountVowels; k++)
				if (tmp[j] == vowels[k])
				{
					counter++;
					break;
				}

		for (int j = tmp.length() - 1; j >= 0 && tmp.length() - j <= 3; j--)
			first.push_back(tolower(tmp[j]));

		// find
		auto it = Dictionary.find(make_pair(counter, first));
		while (it == Dictionary.end() && first.length() > 0)
		{
			first.erase(first.find(first), 1);
			it = Dictionary.find(make_pair(counter, first));
		}
		if (it != Dictionary.end()) 
			it->second != tmp ? out << it->second : out << (++it)->second;

		if (first.length() <= 0) 
		{
			it = Dictionary.begin();
			while (it->first.first != counter && it != Dictionary.end())
				it++;
			if (it == Dictionary.end()) out << tmp;
			else it->second != tmp ? out << it->second : out << (++it)->second ;
				//out << it->second;
		}
		out << chr;


	}
	out.close();
	inp.close();
}