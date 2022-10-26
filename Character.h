#pragma once
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#include "Weapon.h"
#include "Collab.h"

class Character {
private:
	string name;
	bool available;
	vector<Weapon> favWeapons;
public:
	Character(string = "-", bool = false, const vector<Weapon> & = vector<Weapon>{});
	bool isAvail() const;
	bool isFavored(const Weapon&) const;
	bool isFavored(const Collab&) const;

	friend ostream& operator << (ostream& myCout, const Character& param);
};