#include "Character.h"

Character::Character(string param, bool avail, const vector<Weapon>& weaps) {
	name = param;
	available = avail;
	favWeapons = vector<Weapon>(0);
	for (int i = 0; i < weaps.size(); i++)
		favWeapons.emplace_back(weaps[i]);
}

bool Character::isAvail() const {
	return available;
}

bool Character::isFavored(const Weapon& param) const {
	for (int i = 0; i < favWeapons.size(); i++)
		if (favWeapons[i] == param)
			return true;
	return false;
}

bool Character::isFavored(const Collab& param) const {
	bool check = false;
	for (auto& weapon : favWeapons)
		check = check || param.hasWeapon(weapon);
	return check;
}

ostream& operator << (ostream& myCout, const Character& param) {
	myCout << param.name;
	return myCout;
}