
#include <iostream>
#include <string>
#include <map>

using std::string;
using std::map;

int charToInt(const char c) 
{
    return int(c) - '0';
}

static void twoSums9(const string& input, string&  outPairs, string& outRemainders, int k) 
{
    map<int, int> numberMap;
    int target = k;
    if (input.size() == 1) {return;}

    outPairs = "";
    outRemainders = input;
    int numberofErased = 0;

    for (int currentIndex = 0; currentIndex < input.size(); currentIndex++)
    {
        int value = charToInt(input[currentIndex]);

        if (numberMap[value] > 0)
        {
            int firstIndex = numberMap[value];
            int secondIndex = currentIndex;

            outPairs.append(std::to_string(charToInt(input[numberMap[value]]))); // target - value;
            outPairs.append(std::to_string(value));

            outRemainders[firstIndex] = 'd';
            outRemainders[secondIndex] = 'd';
            //outRemainders.erase(firstIndex- numberofErased,1);
            //numberofErased++;
            //outRemainders.erase(secondIndex- numberofErased,1);
            //numberofErased++;
        }
        else
        {
            int necessaryNumber = target - value;
            numberMap[necessaryNumber] = currentIndex;
        }
    }

    for (int i = 0; i < outRemainders.size(); i++)
    {

        while (outRemainders[i] == 'd')
        {
           outRemainders.erase(i, 1);
        }
    }
}
int main()
{
    string input = "0011345933456";
    string outPairs = "";
    string outRemainders = "";

    twoSums9(input, outPairs, outRemainders, 9);

    std::cout << "input: " << input << std::endl;
    std::cout << "outPairs: " << outPairs << std::endl;
    std::cout << "outRemainders: " << outRemainders << std::endl;

}
