#include <iostream>
#include <vector>

bool specialUsed{ false };
int longestPath{ 0 };

struct City 
{
    int index{ 0 };
	bool visited{ false };
	std::vector<City*> neighborCities;
};

void fillIndexesAndNeighbors(int T[], int size, City Cities[])
{
    for (int i = 0; i < size; i++)
        Cities[i].index = i;

	for (int i=1; i < size ;i++) 
	{
        City& currentCity = Cities[i];
		City& neighborCity = Cities[T[i]];
        //std::cout << "current City : " << currentCity.index << std::endl;
        //std::cout << "neighbor City : " << neighborCity.index << std::endl;

		currentCity.neighborCities.push_back(&neighborCity);
        neighborCity.neighborCities.push_back(&currentCity);
	}
    std::cout << "\n";
}

int travel(City& cityToTravel, int count)
{
    int m_Count = count;

    if (specialUsed && cityToTravel.index % 2 == 1) 
    {
        std::cout << "Couldn't Enter City# " << cityToTravel.index << " because special Ticket is Used!" << std::endl;
        return m_Count;
    }

    if (cityToTravel.index % 2 == 1)
    {
        std::cout << "Special Ticket is used for City# " << cityToTravel.index << "!" << std::endl;
        specialUsed = true;
    }

    m_Count++;
    cityToTravel.visited = true;


    int numberOfNeighborCities = cityToTravel.neighborCities.size();
    if (numberOfNeighborCities == 1)
        std::cout << "\nNo Neighbors!\n" << std::endl;
    
    for (int i = 0; i < numberOfNeighborCities; i++)
    {
        if (cityToTravel.neighborCities[i]->visited)
            continue;

        std::cout << cityToTravel.index << " ----> " << (*cityToTravel.neighborCities[i]).index 
                  << "   Path Length : " << m_Count << std::endl;
     
        int path = travel(*(cityToTravel.neighborCities[i]), m_Count);
     
        std::cout << cityToTravel.index << " <---- " << (*cityToTravel.neighborCities[i]).index << std::endl;

        if (cityToTravel.index == 0)
        {
            specialUsed = false;
            std::cout << "\nSpecial Ticket is resetted!\n" << std::endl;
        }

        if (path > longestPath)
        {
            longestPath = path;
            std::cout << "\nLongest Path : "<< longestPath << "\n" << std::endl;
        }
    }

    return m_Count;
}

int main(int argc, char* argv [])
{
	const int size = 10;
	int T[size] = {0,9,0,2,6,8,0,8,3,0};

	City Cities[size]{};

	fillIndexesAndNeighbors(T, size, Cities);

    travel(Cities[0], 0);

    std::cout << "Final Longest Path: " << longestPath << std::endl;
    std::cin.ignore();

    return longestPath;
}