#pragma once
class Location
{
public:
	void add(Location& delta) {
		x += delta.x;
		y += delta.y;
	}
	bool equal(Location& loc) {
		return x == loc.x && y == loc.y;
	}
	int x;
	int y;
};