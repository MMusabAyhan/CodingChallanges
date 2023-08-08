#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

bool isAnagram(const string& word1, const string& word2)
{
	if (word1.size() != word2.size())
		return false;

	unordered_map<char, int> possessed;
	unordered_map<char, int> seen;

	for (int i = 0; i < word1.size(); i++)
		possessed[word1[i]]++;

	for (int i = 0; i < word2.size(); i++)
	{
		seen[word2[i]]++;

		if (seen[word2[i]] > possessed[word2[i]])
			return false;
	}

	return true;
}

void findAnagrams(string inputs[], int inputsSize, vector<vector<string>>& outAnagramList) 
{
	unordered_set<string> cachedWords;

	for (int i = 0; i < inputsSize - 1; i++)
	{
		vector<string> currentAnagrams;
		currentAnagrams.push_back(inputs[i]);

		for (int j = i + 1; j < inputsSize; j++)
		{
			if (cachedWords.find(inputs[j]) == cachedWords.end() && isAnagram(inputs[i], inputs[j]))
			{
				currentAnagrams.push_back(inputs[j]);
				cachedWords.emplace(inputs[j]);
			}
		}

		if (currentAnagrams.size() > 1)
			outAnagramList.push_back(currentAnagrams);
	}
}

void printAnagrams(vector<vector<string>>& anagramList)
{
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

	vector<vector<string>> anagramList;

	findAnagrams(inputs, inputsize, anagramList);

	printAnagrams(anagramList);
}
