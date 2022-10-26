#pragma once
#include <string>
#include <sstream>
using namespace std;

class Weapon
{
private:
	string name;
	bool available;
	bool notInBuild;
public:
	Weapon(string param = "-", bool avail = false);
	bool inBuild() const;
	bool isAvail() const;
	void setInBuild(bool param);

	bool operator == (const Weapon& other) const;
	bool operator == (const string& other) const;

	friend ostream& operator << (ostream& myCout, const Weapon& param);
};