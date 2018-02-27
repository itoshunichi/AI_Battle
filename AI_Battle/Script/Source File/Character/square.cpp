#include"../../Header File/Character/square.h"

SQUARE Square(int x, int y)
{
	SQUARE result = { x, y };
	return result;
}

bool operator==(const SQUARE &s1, const SQUARE &s2)
{
	return s1.X == s2.X&&s1.Y == s2.Y;
}