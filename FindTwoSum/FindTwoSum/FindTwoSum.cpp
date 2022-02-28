#include <iostream>
#define I INT32_MIN

using namespace std;

// No Duplicates
// Only one solution

int FindMax(int A[], int& n)
{
	int max = I;

	for (int i = 1; i <= n; i++)
	{
		if (A[i] > max)
		{
			max = A[i];
		}
	}

	return max;
}

void FindTwoSum(int A[], int& target, int& n, int Results[])
{
	int NumberNeeded, max, * HT;

	max = FindMax(A, n);
	if (max != I)
	{
		HT = new int[max + 1]{};

		for (int p = 1; p <= n; p++)
		{
			NumberNeeded = target - A[p];

			if (HT[NumberNeeded] > 0 && NumberNeeded < max && NumberNeeded > 0)
			{
				Results[0] = HT[NumberNeeded];
				Results[1] = p;

				delete[] HT;
				return;
			}
			else
			{
				HT[A[p]] = p;
			}
		}

		delete[] HT;
	}
}

int main()
{
	int A[2] = {0,5};
	int n = 1;
	int target = 5;
	int Results[2] = { -1,-1 };

	FindTwoSum(A, target, n, Results);

	cout << Results[0] << " " << Results[1] << endl;

	return 0;
}
