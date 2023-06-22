#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool isAnagram(string& word1, string& word2)
{
	if (word1.size() != word2.size())
	{
		return false;
	}

	for (int i = 0; i < word1.size(); i++)
	{
		bool matched{ false };
		char currentLetter = word1[i];

		for (int j = 0; j < word1.size(); j++)
		{
			if (currentLetter == word2[j])
			{
				matched = true;
				break;
			}
		}

		if (!matched)
			return false;
	}

	return true;
}


void updateTemp(vector<string>& temp,const string& str) 
{
	auto it = temp.begin();

	for (;it != temp.end();)
	{
		if (*it == str) 
		{
			it = temp.erase(it);
			continue;
		}

		it++;
	}
}

int main()
{
	const int inputsize = 10;

	string inputs[inputsize]
	{
		{"AHMET"},
		{"HATEM"},
		{"Samet"},
		{"temaS"},
		{"Kahni"},
		{"YokBeOlm"},
		{"JAMIRIYO"},
		{"IRIJAMYO"},
		{"MAJIRIYO"},
		{"TAMHE"},
	};

	vector<string> temp;

	for (int i = 0; i < inputsize; i++)
	{
		temp.push_back(inputs[i]);
	}

	vector<vector<string>> anagramList;

	while (temp.size() > 1) 
	{
		vector<string> currentAnagram;
		currentAnagram.push_back(temp[0]);

		for (int i = 1; i < temp.size(); i++)
		{
			if (isAnagram(temp[0], temp[i]))
			{
				currentAnagram.push_back(temp[i]);
			}
		}

		if (currentAnagram.size() > 1)
		{
			anagramList.push_back(currentAnagram);
		}

		for (int i = 0; i < currentAnagram.size(); i++)
		{
			updateTemp(temp, currentAnagram[i]);
		}
	}
	
	for (int i = 0; i < anagramList.size(); i++)
	{
		
		const vector<string>& currentList = anagramList[i];
		string output{};

		for (int j = 0; j < currentList.size(); j++)
		{
			output += currentList[j];
			output += '/';
		}

		output.pop_back();

		cout << output << endl;
	}

}
