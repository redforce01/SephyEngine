#pragma once
class CProduction_Ship
{
private:
	UINT id;
	UINT fuel;
	UINT time;

public:
	CProduction_Ship();
	~CProduction_Ship();

	void initialize(UINT _id, UINT _fuel, UINT _time)
	{
		id = _id;
		fuel = _fuel;
		time = _time;
	}

	UINT getID() { return id; }
	UINT getFuel() { return fuel; }
	UINT getTime() { return time; }
};

