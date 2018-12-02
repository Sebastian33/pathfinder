/* https://www.codingame.com/ide/puzzle/the-labyrinth */
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <utility>

using vs = std::vector<std::string>;
using point = std::pair<int, int>;
bool findPath(vs &map, int curr, int curc, int trgr, int trgc);
void showmap(const vs &map);

int main()
{
	vs map = {
"??????????????????????????????",
"#..............???????????????",
"#.#############???????????????",
"#.....T........???????????????",
"#.......................#.#..#",
"#.#######################.#..#",
"#.....##......##......#....###",
"#...####..##..##..##..#..#...#",
"#.........##......##.....#...#",
"##############################"
	};
	findPath(map, 3, 6, 8, 27);
}

bool findPath(vs &map, int curr, int curc, int trgr, int trgc)
{
	int stepr(1), stepc(1);
	if (curr > trgr)
		stepr = -1;
	if (curc > trgc)
		stepc = -1;
	int r(-1), c(-1);
	std::stack<point> next;//assuming that labyrinth has "walls"
	auto tryVStepA = [&](int r, int c){
		if (map[r+stepr][c] == '.')
		{
			next.push(point(r+stepr, c));
			map[r+stepr][c] = (stepr > 0) ? 'w' : 's';
		}
	};
	auto tryVStepC = [&](int r, int c) {
		if (map[r - stepr][c] == '.')
		{
			next.push(point(r - stepr, c));
			map[r - stepr][c] = (stepr > 0) ? 's' : 'w';
		}
	};
	auto tryHStepA = [&](int r, int c) {
		if (map[r][c + stepc] == '.')
		{
			next.push(point(r, c + stepc));
			map[r][c + stepc] = (stepc > 0) ? 'a' : 'd';
		}
	};
	auto tryHStepC = [&](int r, int c) {
		if (map[r][c - stepc] == '.')
		{
			next.push(point(r, c - stepc));
			map[r][c - stepc] = (stepc > 0) ? 'd' : 'a';
		}
	};
	
	/*if (map[curr][curc - stepc] == '.')
	{
		next.push(point(curr, curc - stepc));
		map[curr][curc - stepc] = (stepc > 0) ? 'd' : 'a';
	}
	if (map[curr - stepr][curc] == '.')
	{
		next.push(point(curr - stepr, curc));
		map[curr - stepr][curc] = (stepr > 0) ? 's' : 'w';
	}
	if (map[curr + stepr][curc] == '.')
	{
		next.push(point(curr + stepr, curc));
		map[curr + stepr][curc] = (stepr > 0) ? 'w' : 's';
	}
	if (map[curr][curc + stepc] == '.')
	{
		next.push(point(curr, curc + stepc));
		map[curr][curc + stepc] = (stepc > 0) ? 'a' : 'd';
	}*/
	if (curc == trgc)
	{
		tryVStepC(curr, curc);
		tryHStepC(curr, curc);
		tryHStepA(curr, curc);
		tryVStepA(curr, curc);
	}
	else
	{
		tryHStepC(curr, curc);
		tryVStepC(curr, curc);
		tryVStepA(curr, curc);
		tryHStepA(curr, curc);
	}
	point tmp;

	while ((r!=trgr) || (c!=trgc))
	{
		if (next.empty())
			return 0;
		tmp = next.top();
		next.pop();
		r = tmp.first;
		c = tmp.second;

		while ((r != trgr) || (c != trgc))
		{
			showmap(map);
			if (r == trgr)
			{
				tryHStepC(r, c);
				tryVStepA(r, c);
				tryVStepC(r, c);
				if (map[r][c + stepc] == '.')
				{	
					c += stepc;
					map[r][c] = (stepc > 0) ? 'a' : 'd';
				}
				else break;
			}
			else if(c==trgc)
			{
				tryVStepC(r, c);
				tryHStepA(r, c);
				tryHStepC(r, c);
				if (map[r + stepr][c] == '.')
				{
					r += stepr;
					map[r][c] = (stepr > 0) ? 'w' : 's';
				}
				else break;
			}
			else
			{
				tryHStepC(r, c);
				tryVStepC(r, c);
				if (map[r][c + stepc] == '.')
				{
					tryVStepA(r, c);
					c += stepc;
					map[r][c] = (stepc > 0) ? 'a' : 'd';
				}
				else if (map[r + stepr][c] == '.')
				{
					r += stepr;
					map[r][c] = (stepr > 0) ? 'w' : 's';
				}
				else break;
			}
			/*if (map[r][c + stepc] == '.')
			{
				if (map[r + stepr][c] == '.')
				{
					map[r + stepr][c] = (stepr > 0) ? 'w' : 's';
					next.push(point(r + stepr, c));
				}
				if (map[r - stepr][c] == '.')
				{
					map[r - stepr][c] = (stepr > 0) ? 's' : 'w';
					next.push(point(r - stepr, c));
				}
				c += stepc;
				map[r][c] = (stepc > 0) ? 'a' : 'd';
			}
			else if (map[r + stepr][c] == '.')
			{
				r += stepr;
				map[r][c] = (stepr > 0) ? 'w' : 's';
				if (map[r][c - stepc] == '.')
				{
					map[r][c - stepc] = (stepc > 0) ? 'd' : 'a';
					next.push(point(r, c - stepc));
				}
			}
			else
			{
				if (map[r][c - stepc] == '.')
				{
					map[r][c - stepc] = (stepc > 0) ? 'd' : 'a';
					next.push(point(r, c - stepc));
				}
				if (map[r - stepr][c] == '.')
				{
					map[r - stepr][c] = (stepr > 0) ? 's' : 'w';
					next.push(point(r - stepr, c));
				}
				break;
			}*/
		}
	}
	return 1;
}

void showmap(const vs &map)

{
	//system("cls");
	for (auto s : map)
	{
		std::cout << s << std::endl;
	}
	std::cout << std::endl;
}