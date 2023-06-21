#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{

    string sequence{"(()()(((((()()))))()()"};


    int currentOpen = (sequence[0] == '(') ? 1 : 0;
    int totalMax = currentOpen;

    int depth{1};
    bool continued{ true };
    for (int i = 1; i < sequence.size(); i++)
    {
        char prevChar = sequence[i - 1];
        char currentChar = sequence[i];

        continued = (prevChar == currentChar);

        if (currentChar == '(' && continued)
        {
            currentOpen++;
        }
        else if (sequence[i] == ')' && continued)
        {
            depth++;
        }
        else
        {
            totalMax = (totalMax < currentOpen) ? currentOpen : totalMax;
            currentOpen = 0;
        }
    }

    depth = (depth > totalMax) ? totalMax : depth;

    cout << depth << endl;
}