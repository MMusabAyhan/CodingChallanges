#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Coord
{
    int x{ 0 };
    int y{ 0 };
};
struct Node
{
    Coord location{ 0,0 };
    char character{ ' ' };
    bool explored{ false };
    Node* parent{ nullptr };
    int distanceToStart{-1};

    vector<Node*> neighbours{};

    void fillNeighbours(const int& w, const int& h)
    {
        int neighbourx = this->location.x;
        int neighboury = this->location.y;

        if (neighbourx + 1 < w)
        {
            neighbours.emplace_back(this + 1);
        }
        else
        {
            neighbours.emplace_back(this - (w - 1));
        }
        if (neighbourx - 1 >= 0)
        {
            neighbours.emplace_back(this - 1);
        }
        else
        {
            neighbours.emplace_back(this + (w - 1));
        }
        if (neighboury + 1 < h)
        {
            neighbours.emplace_back(this + 30);
        }
        else
        {
            neighbours.emplace_back(this - 30 * (h - 1));
        }
        if (neighboury - 1 >= 0)
        {
            neighbours.emplace_back(this - 30);
        }
        else
        {
            neighbours.emplace_back(this + 30 * (h - 1));
        }
    }
};

// Use targetNode as nullptr so that it will calculate all nodes in area.

Node* BFS(Node* startNode, Node* targetNode)
{
    queue<Node*> exploredNodes;
    startNode->explored = true;
    exploredNodes.push(startNode);

    while (!exploredNodes.empty())
    {
        Node* u = exploredNodes.front();
        exploredNodes.pop();

        if (u == targetNode)
        {
            //cerr << "Found " << endl;
            return targetNode;
        }

        for (Node* neighbourNode : u->neighbours)
        {
            //cerr << "neighbor for:" << u->location.x << " " << u->location.y << "  "<<  neighbourNode->location.x << " " << neighbourNode->location.y<<endl;
            if (!neighbourNode->explored && neighbourNode->character != '#')
            {
                neighbourNode->explored = true;
                neighbourNode->parent = u;
                exploredNodes.push(neighbourNode);
                //cerr << "neighbour node: " << neighbourNode->location.x << ":" <<  neighbourNode->location.y << endl << "parent assigned: " << u->location.x << ":" << u->location.y << endl;
            }
        }
    }

    return nullptr;
}

char calculateDistanceToStart(Node* nodeToCalculate)
{
    char cToReturn{};
    int distance{};
    Node* parentNode = nodeToCalculate->parent;

    while (parentNode)
    {
        distance++;
        parentNode = parentNode->parent;
    }

    if (0 < distance && distance <= 9)
    {
        cToReturn = 48 + distance;
    }
    else // 10 <= distance <= 35
    {
        int letterA = 'A';
        cToReturn = letterA + distance - 10;
    }

    return cToReturn;
}

void clearNodeExploration(Node(*grid)[30], const int& w, const int& h)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            grid[i][j].explored = false;
            grid[i][j].parent = nullptr;
        }
    }
}

int main()
{

    const int w{ 10 };
    const int h{ 5 };

    string maze[h]
    {
        {"##########"},
        {"#S.......#"},
        {"##.#####.#"},
        {"##.#.....#"},
        {"##########"}
    };

    int startx{};
    int starty{};
    Node grid[30][30];

    for (int i = 0; i < h; i++) {

        string row = maze[i];

        cerr << row << endl;

        for (int j = 0; j < row.size();j++)
        {
            grid[i][j].location = { j,i };
            grid[i][j].character = row[j];

            if (row[j] == 'S')
            {
                grid[i][j].distanceToStart = '0';
                startx = j;
                starty = i;
            }
        }
    }

    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++)
        {
            grid[i][j].fillNeighbours(w, h);
        }
    }


    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            clearNodeExploration(grid, w, h);

            if (grid[i][j].character == '.')
            {
                Node* targetNode = BFS(&grid[i][j], &grid[starty][startx]);

                if (!targetNode)
                {
                    grid[i][j].distanceToStart = '.';
                    continue;
                }

                grid[i][j].distanceToStart = calculateDistanceToStart(targetNode);
            }
        }
    }

    string output{};

    for (int i = 0; i < h; i++) {

        for (int j = 0; j < w; j++)
        {
            if (grid[i][j].character != '#')
            {
                output += grid[i][j].distanceToStart;
            }
            else
            {
                output += grid[i][j].character;
            }
        }
        if (i != h - 1)
        {
            output += "\n";
        }

    }

    cerr << endl;
    // Display output

    cout << output << endl;
}