#include "MObject.hpp"

class Player : public MObject
{
public:
	int x, y;
	Player()
	{
		x = 20;
		y = 7;
	}
	~Player()
	{

	}

	void isKeyPressed()
	{
		y = 5;
	}

	void isKeyUnpressed()
	{
		y = 7;
	}

};