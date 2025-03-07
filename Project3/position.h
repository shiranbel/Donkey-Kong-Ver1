#pragma once
class Position
{
	int x;
	int y;

public:
	// ctor
	Position(int x, int y) : x(x), y(y) {}

	// getters
	int getX() const { return x; }
	int getY() const { return y; }

	// setters
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
};

