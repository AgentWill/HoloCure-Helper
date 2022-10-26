#include "Collab.h"

Collab::Collab(string param, Weapon weap1, Weapon weap2) {
	name = param;
	firWeap = weap1;
	secWeap = weap2;
	notInBuild = false;
}

bool Collab::inBuild() const {
	return notInBuild;
}

bool Collab::isAvail() const {
	return firWeap.isAvail() && secWeap.isAvail();
}

bool Collab::isCompat(const Collab& param) const {
	return !(firWeap == param.firWeap || firWeap == param.secWeap ||
		secWeap == param.firWeap || secWeap == param.secWeap);
}

bool Collab::canPick(const vector<Weapon>& chosen) const {
	bool check1 = false;
	bool check2 = false;

	for (auto& weapon : chosen)
		check1 = check1 || firWeap == weapon;
	for (auto& weapon : chosen)
		check2 = check2 || secWeap == weapon;

	return check1 && check2;
}

bool Collab::finishCollab(const vector<Weapon>& chosen, Weapon& param) const {
	for (auto& weapon : chosen)
		if (hasWeapon(weapon) && !weapon.inBuild())
			return hasWeapon(param);
	return false;
}

bool Collab::hasWeapon(const Weapon& param) const {
	return param == firWeap || param == secWeap;
}

Weapon Collab::otherWeapon(const Weapon& param) const {
	if (firWeap == param)
		return secWeap;
	else if (secWeap == param)
		return firWeap;
	else
		return Weapon();
}

void Collab::setInBuild(bool param) {
	notInBuild = param;
}

bool Collab::operator == (const Collab& other) const {
	return name == other.name;
}

ostream& operator << (ostream& myCout, const Collab& param) {
	myCout << param.name << ": " << param.firWeap
		<< ", " << param.secWeap;
	return myCout;
}