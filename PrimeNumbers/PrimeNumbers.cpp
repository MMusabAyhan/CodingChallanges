#include <iostream>
#include <vector>
#include <math.h>

using std::vector;

bool isPrime(const int& number)
{
	const int lastNumberToCheck = sqrt(number);

	for (int i = 2; i <= lastNumberToCheck; i++)
	{
		if (number % i == 0)
			return false;
	}

	return true;
}

int SumPrimes(int first, int last)
{
	int sum = 0;

	for (int i = first; i <= last; i++)
	{
		if (i == 1) { continue; }

		if (isPrime(i))
			sum += i;
	}

	return sum;
}

int main()
{
	std::cout << SumPrimes(5, 17);
}

