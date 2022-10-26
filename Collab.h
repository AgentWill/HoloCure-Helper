#pragma once
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#include "Weapon.h"

class Collab {
private:
	string name;
	Weapon firWeap;
	Weapon secWeap;
	bool notInBuild;
public:
	Collab(string param = "-", Weapon weap1 = Weapon(), Weapon weap2 = Weapon());
	bool inBuild() const;
	bool isAvail() const;
	bool isCompat(const Collab&) const;
	bool canPick(const vector<Weapon>&) const;
	bool finishCollab(const vector<Weapon>&, Weapon&) const;
	bool hasWeapon(const Weapon&) const;
	Weapon otherWeapon(const Weapon&) const;
	void setInBuild(bool param);

	bool operator == (const Collab& other) const;

	friend ostream& operator << (ostream& myCout, const Collab& param);
};