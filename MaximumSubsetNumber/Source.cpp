#include <iostream>
#include <vector>
#include <limits.h>

int calculateMaximumSubsetNumber(std::vector<int>& A, int M)
{
	std::vector<std::vector<int>> subsetGroups(M);
	int sizeOfA = A.size();

	for (int i = 0; i < sizeOfA;i++)
	{
		int remain = A[i] % M;
		if (remain < 0)
			remain = M + remain;

		subsetGroups[remain].emplace_back(i);
	}

	int max = INT_MIN;
	for (int i = 0; i < M; i++)
	{
		int size = subsetGroups[i].size();
		if (size > max)
			max = size;
	}

	return max;
}

int main(int argc, char* argv [])
{
	std::vector<int> A = { -3,-2,1,2,3,7,4};
	int M = 8;

	std::cout << calculateMaximumSubsetNumber(A, M) << std::endl;
}