/* https://www.codingame.com/ide/puzzle/the-labyrinth */
#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>

using vs = std::vector<std::string>;
using point = std::pair<int, int>;
std::string findPath(vs &map, int curr, int curc, int trgr, int trgc);
void showmap(const vs &map);

int main()
{
	/*T=(3,6), C=(8,27) */
	vs map = {
"??????????????????????????????",
"H..............???????????????",
"H.HHHHHHHHHHHHH???????????????",
"H..............???????????????",
"H.......................H.H..H",
"H.HHHHHHHHHHHHHHHHHHHHHHH.H..H",
"H.....HH......HH......H....HHH",
"H...HHHH..HH..HH..HH..H..H...H",
"H.........HH......HH.....H...H",
"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
	};
	/*T=(1,1) C=(8,29)  */
	vs map1 = {
"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH",
"H............................H",
"HH...........................H",
"H............................H",
"H............................H",
"H............................H",
"H............................H",
"H............................H",
"H............................H",
"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
	};
	vs map2 = {
		"HHHHH?????????????????????????",
		"H....?????????????????????????",
		"HH...?????????????????????????",
		"H....?????????????????????????",
		"H....?????????????????????????",
		"H....?????????????????????????",
		"H...??????????????????????????",
		"H...??????????????????????????",
		"H...??????????????????????????",
		"H...??????????????????????????",
		"H...??????????????????????????",
		"H............................H",
		"H............................H",
		"H............................H",
		"HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
	};
	std::cout << findPath(map2, 13, 28, 1, 1) << std::endl;
}

std::string findPath(vs &map, int curr, int curc, int trgr, int trgc)
{
	std::queue<point> nextPoints;
	int distance = 1;
	auto checkAndAdd = [&](int r, int c)->int
	{
		int num(0);
		if (map[r + 1][c] == '.')
		{
			nextPoints.push(point(r + 1, c));
			map[r + 1][c] = distance;
			num++;
		}
		if (map[r - 1][c] == '.')
		{
			nextPoints.push(point(r - 1, c));
			map[r - 1][c] = distance;
			num++;
		}
		if (map[r][c + 1] == '.')
		{
			nextPoints.push(point(r, c + 1));
			map[r][c + 1] = distance;
			num++;
		}
		if (map[r][c - 1] == '.')
		{
			nextPoints.push(point(r, c - 1));
			map[r][c - 1] = distance;
			num++;
		}
		return num;
	};
	
	map[trgr][trgc] = 0;
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
	
	if (map[curr + 1][curc] == '.')
		map[curr + 1][curc] = 255;
	if (map[curr - 1][curc] == '.')
		map[curr - 1][curc] = 255;
	if (map[curr][curc + 1] == '.')
		map[curr][curc + 1] = 255;
	if (map[curr][curc - 1] == '.')
		map[curr][curc - 1] = 255;
	char nextStep;
	int r, c;
	while ((trgr != curr) || (trgc != curc))
	{
		r = curr + ((unsigned char)map[curr + 1][curc] < (unsigned char)map[curr - 1][curc] ? 1 : -1);
		c = curc + ((unsigned char)map[curr][curc + 1] < (unsigned char)map[curr][curc - 1] ? 1 : -1);
		if ((unsigned char)map[r][curc] < (unsigned char)map[curr][c])
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
	//system("cls");
	for (auto s : map)
	{
		std::cout << s << std::endl;
	}
	std::cout << std::endl;
}