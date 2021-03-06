/* https://www.codingame.com/training/hard/the-labyrinth */
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <iomanip>

using vs = std::vector<std::string>;
using point = std::pair<int, int>;
std::string findPath(const vs& map0, int curr, int curc, int trgr, int trgc);
void showmap(const vs &map);
void showDist(const std::vector<std::vector<unsigned>> &dist);
/*T=teleport, entry point; C=control room, target
(row, column) */
int main()
{
	/*T=(3,6), C=(8,27) */
	vs map = {
"??????????????????????????????",
"#..............???????????????",
"#.#############???????????????",
"#.....T........???????????????",
"#.......................#.#..#",
"#.#######################.#..#",
"#.....##......##......#....###",
"#...####..##..##..##..#..#...#",
"#.........##......##.....#.C.#",
"##############################"
	};
	
	/*T=(13,28) C=(1,1)*/
	vs map2 = {
		"#####?????????????????????????",
		"#C...?????????????????????????",
		"##...?????????????????????????",
		"#....?????????????????????????",
		"#....?????????????????????????",
		"#....?????????????????????????",
		"#...??????????????????????????",
		"#...??????????????????????????",
		"#...??????????????????????????",
		"#...??????????????????????????",
		"#...??????????????????????????",
		"#............................#",
		"#............................#",
		"#...........................T#",
		"##############################"
	};
	/* T=(3,6), C=(11, 4) */
	vs map3 = {
"##############################",
"#............................#",
"#.#######################.#..#",
"#.....T.................#.#..#",
"#.....#.................#.#..#",
"#.#######################.#..#",
"#.....##......##......#....###",
"#...####..##..##..##..#..#...#",
"#.........##......##.....#...#",
"###########################.##",
"#......#......#..............#",
"#...C..#.....................#",
"#...#..####################..#",
"#............................#",
"##############################"
	};
	std::cout << findPath(map, 3, 6, 8, 27) << std::endl;
}

std::string findPath(const vs& map0, int curr, int curc, int trgr, int trgc)
{
	std::vector<std::vector<unsigned short>> map(map0.size(), std::vector<unsigned short>(map0[0].size()));
	for (int r = 0; r < map0.size(); r++)
	{
		for (int c = 0; c < map0[r].size(); c++)
			map[r][c] = map0[r][c] == '.' ? 0 : -1;
	}
	std::queue<point> nextPoints;
	int distance = 1;
	auto checkAndAdd = [&](int r, int c)->int
	{
		int num(0);
		if (map[r + 1][c] == 0)
		{
			map[r + 1][c] = distance;
			nextPoints.push(point(r + 1, c));
			num++;
		}
		if (map[r - 1][c] == 0)
		{
			map[r - 1][c] = distance;
			nextPoints.push(point(r - 1, c));
			num++;
		}
		if (map[r][c + 1] == 0)
		{
			map[r][c + 1] = distance;
			nextPoints.push(point(r, c + 1));
			num++;
		}
		if (map[r][c - 1] == 0)
		{
			map[r][c - 1] = distance;
			nextPoints.push(point(r, c - 1));
			num++;
		}
		return num;
	};
	/*for cases when this point is 'C' or 'T'*/
	map[curr][curc] = 0; 
	/*it is done so as algorithm in this phase will not 'go back', will turn into 0 latter*/
	map[trgr][trgc] = -1; 
	int currentNumber = checkAndAdd(trgr, trgc);
	int nextNumber;
	point cur;
	bool targetReached = false;
	while((!targetReached)&&(!nextPoints.empty()))
	{
		//showmap(map);
		distance++;
		nextNumber = 0;
		while (currentNumber > 0)
		{
			cur = nextPoints.front();
			if ((cur.first == curr) && (cur.second == curc))
			{
				targetReached = true;
				break;
			}
			nextNumber += checkAndAdd(cur.first, cur.second);
			nextPoints.pop();
			currentNumber--;
		}
		currentNumber = nextNumber;
	}

	std::string path;
	if (!targetReached)
		return path;
	
	if (map[curr + 1][curc] == 0)
		map[curr + 1][curc] = -1;
	if (map[curr - 1][curc] == 0)
		map[curr - 1][curc] = -1;
	if (map[curr][curc + 1] == 0)
		map[curr][curc + 1] = -1;
	if (map[curr][curc - 1] == 0)
		map[curr][curc - 1] = -1;
	char nextStep;
	int r, c;
	map[trgr][trgc] = 0;
	while ((trgr != curr) || (trgc != curc))
	{
		r = curr + (map[curr + 1][curc] < map[curr - 1][curc] ? 1 : -1);
		c = curc + (map[curr][curc + 1] < map[curr][curc - 1] ? 1 : -1);
		if (map[r][curc] < map[curr][c])
		{
			nextStep = r > curr ? 'd' : 'u';
			curr = r;
		}
		else
		{
			nextStep = c > curc ? 'r' : 'l';
			curc = c;
		}
		path.push_back(nextStep);
	}
	return path;
}

void showmap(const vs &map)
{
	for (auto s : map)
	{
		std::cout << s << std::endl;
	}
	std::cout << std::endl;
}

void showDist(const std::vector<std::vector<unsigned short>> &dist)
{
	for (int r = 0; r < dist.size(); r++)
	{
		for (int c = 0; c < dist[r].size(); c++)
			std::cout << std::setw(4) << (int)dist[r][c];
		std::cout << std::endl;
	}
	std::cout << std::endl;
}