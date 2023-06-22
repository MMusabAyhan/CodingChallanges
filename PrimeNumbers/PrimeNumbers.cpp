#include <iostream>
#include <vector>

using std::vector;

int SumPrimes(int first, int last)
{
	int sum = 0;

	for (int i = first; i <= last; i++)
	{
		if (i == 1) { continue; }

		bool bPrime{ true };
		for (int j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				bPrime = false;
				break;
			}
		}

		if (bPrime)
		{
			sum += i;
		}
	}

	return sum;
}

int main()
{
	std::cout << SumPrimes(1,100);
}

