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

	Coord location{ 0,0 };
	char character{ ' ' };
	bool explored{ false };
	Node* parent{ nullptr };
	int distance{-1};

	vector<Node*> neighbours{};

};

// Use targetNode as nullptr so that it will calculate all nodes in area.

Node* BFS(Node* startNode, Node* targetNode)
{
	queue<Node*> exploredNodes;
	startNode->explored = true;
	startNode->distance = 0;
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
			//cerr << neighbourNode->distance << endl;

			if (!neighbourNode->explored && neighbourNode->character != '#' && neighbourNode->distance == -1)
			{
				//cerr << neighbourNode->distance << endl;
				neighbourNode->explored = true;
				neighbourNode->distance = u->distance + 1;
				neighbourNode->parent = u;
				exploredNodes.push(neighbourNode);
				//cerr << "neighbour node: " << neighbourNode->location.x << ":" <<  neighbourNode->location.y << endl << "parent assigned: " << u->location.x << ":" << u->location.y << endl;
			}
		}
	}

	return nullptr;
}

void clearNodeExploration(Node(*grid)[30], const int& w, const int& h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			grid[i][j].explored = false;
			grid[i][j].parent = nullptr;
			grid[i][j].distance = -1;
		}
	}
}

void fillMazeWithDistances(string& output, const Node (&grid)[30][30],const int& w, const int& h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			if (grid[i][j].character != '#')
			{
				int currentDistance = grid[i][j].distance;
				char charToReturn{};
				if (currentDistance == -1)
				{
					charToReturn = '.';
				}
				else if (0 <= currentDistance && currentDistance <= 9)
				{
					charToReturn = 48 + currentDistance;
				}
				else // 10 <= distance <= 35
				{
					int letterA = 'A';
					charToReturn = letterA + currentDistance - 10;
				}

				output += charToReturn;
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
}

int main()
{
	// CodinGame - MovesInMaze - Test case : Everything

	const int w{ 27 };
	const int h{ 13 };

	string maze[h]
	{
		{"###########.###.###.###.###"},
		{"#.........#..............S#"},
		{"###########.....#########.#"},
		{".....#...#.......#...#....."},
		{"####...#...#.......#...####"},
		{"#....#...###....#######...#"},
		{"#.#######..#............#.#"},
		{"#...#........############.#"},
		{"#....#.#####....#.........#"},
		{"#.....#......##...##.###.#."},
		{".....#.#.....#.###.###.###."},
		{"..................#.......#"},
		{"###.###.###.###.###.###.###"},
	};

	int startx{};
	int starty{};
	Node grid[30][30];

	// Filling grid
	for (int i = 0; i < h; i++) {

		string row = maze[i];

		cerr << row << endl;

		for (int j = 0; j < row.size();j++)
		{
			grid[i][j].location = { j,i };
			grid[i][j].character = row[j];

			if (row[j] == 'S')
			{
				startx = j;
				starty = i;
			}
		}
	}

	cerr << endl;

	for (int i = 0; i < h; i++) {

		for (int j = 0; j < w; j++)
		{
			grid[i][j].fillNeighbours(w, h);
		}
	}

	clearNodeExploration(grid, w, h);
	BFS(&grid[starty][startx], nullptr);

	string output{};
	fillMazeWithDistances(output,grid,w,h);

	cout << output << endl;
}