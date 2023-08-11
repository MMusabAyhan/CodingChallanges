#include <iostream>

int calculateNumberOfMatching(const std::string& input) 
{
	int matchCount{ 0 };
	int size = input.size();

	if (size < 2)
		return 0;

	if (input[0] == input[size - 1])
		matchCount++;

	char lastLetter = input[0];

	for (int i = 1; i < size; i++)
	{
		if(input[i] == lastLetter)
			matchCount++;

		lastLetter = input[i];
	}

	return matchCount;
}

int main(int argc, char* argv[])
{
	std::string input{ "aaabbbbbb" };

	std::cout << calculateNumberOfMatching(input) << std::endl;
}