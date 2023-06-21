#include <iostream>
#include <vector>
#include <array>

using namespace std;

enum areaStatus 
{
    inSameArea,
    inDifferentArea,
};

void findAreaIndexes(const vector<pair<int, int>>& nonPaintedArea, const int& currentFirst, const int& currentSecond, int& areaIndexFirst, int& areaIndexSecond)
{
    areaIndexFirst = -1;
    areaIndexSecond = -1;

    for (int j = 0; j < nonPaintedArea.size();j++)
    {
        if (currentFirst >= nonPaintedArea[j].first && currentFirst <= nonPaintedArea[j].second)
        {
            areaIndexFirst = j;
        }

        if (currentSecond >= nonPaintedArea[j].first && currentSecond <= nonPaintedArea[j].second)
        {
            areaIndexSecond = j;
        }
    }
}

void calculatePaintedArea(vector<pair<int,int>>& paintReports, int& outPaintedTotalArea,const int& wallLenght)
{
    vector<pair<int, int>> nonPaintedArea;
    nonPaintedArea.push_back({ 0,wallLenght});
    
    // Find area status for current Report
    for (int i = 0; i < paintReports.size(); i++) 
    {
        pair<int, int> currentReport = paintReports[i];
        int currentFirst = currentReport.first;
        int currentSecond = currentReport.second;

        int areaIndexFirst{-1};
        int areaIndexSecond{-1};

        areaStatus areaStatus;

        findAreaIndexes(nonPaintedArea, currentFirst,currentSecond,areaIndexFirst,areaIndexSecond);

        if (areaIndexFirst == -1 && areaIndexSecond == -1)
        {
            continue;
        }

        if (areaIndexFirst == areaIndexSecond)
        {
            areaStatus = areaStatus::inSameArea;
        }
        else
        {
            areaStatus = areaStatus::inDifferentArea;
        }

        if (areaStatus == inSameArea)
        {
            nonPaintedArea.push_back({ nonPaintedArea[areaIndexFirst].first, currentFirst }); // Adding new one
            nonPaintedArea[areaIndexFirst].first = currentSecond; // Updating the older one
        }
        else
        {
            // Check if they are covering an area already, if so delete it
            bool anyDeleted = false;

            for (int j = 0; j < nonPaintedArea.size();j++)
            {
                if (currentFirst <= nonPaintedArea[j].first && currentSecond >= nonPaintedArea[j].second)
                {
                    // remove the one covered from the list
                    nonPaintedArea.erase(nonPaintedArea.begin() + j);
                    anyDeleted = true;
                    j = -1;
                }
            }

            // Here they are in different areas 

            if (anyDeleted)
            {
                findAreaIndexes(nonPaintedArea, currentFirst, currentSecond, areaIndexFirst, areaIndexSecond);
            }

            if (areaIndexFirst >= 0) 
            {
                nonPaintedArea[areaIndexFirst].second = currentFirst;
            }
            if (areaIndexSecond >= 0)
            {
                nonPaintedArea[areaIndexSecond].first = currentSecond;
            }
        }
    }

    int totalNonPaintedArea{};

    for (int i=0; i<nonPaintedArea.size();i++) 
    {
        totalNonPaintedArea += (nonPaintedArea[i].second - nonPaintedArea[i].first);
    }

    outPaintedTotalArea = wallLenght - totalNonPaintedArea;
}

int main()
{
    vector<pair<int, int>> paintReports = { {3,6},{4,5},{4,5},{7,9},{1,3},{0,8}, {7,10} };
    
    int w = 10;

    int paintedArea{};
    calculatePaintedArea(paintReports, paintedArea, w);

    std::cout << paintedArea << endl;

    return 0;
}

