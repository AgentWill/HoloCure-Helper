#include "Weapon.h"

Weapon::Weapon(string param, bool avail) {
	name = param;
	available = avail;
	notInBuild = false;
}

bool Weapon::inBuild() const {
	return notInBuild;
}

bool Weapon::isAvail() const {
	return available;
}

void Weapon::setInBuild(bool param) {
	notInBuild = param;
}

bool Weapon::operator == (const Weapon& other) const {
	return name == other.name;
}

bool Weapon::operator == (const string& other) const {
	return name == other;
}

ostream& operator << (ostream& myCout, const Weapon& param) {
	myCout << param.name;
	return myCout;
}