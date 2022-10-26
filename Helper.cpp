#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#include "Character.h"
#include "Collab.h"

Weapon getWeapon(string);
Character chooseChar();
vector<Collab> createCollabs();
vector<vector<Collab>> createBuilds(const vector<Collab>&, int,
	const vector<Collab>&);
int getMax(const vector<vector<Collab>>&);

vector<Weapon> weapons = {
	Weapon("Spider Cooking", true),
	Weapon("Elite Lava Bucket", true),
	Weapon("CEO's Tears", true),
	Weapon("Wamy Water", true),
	Weapon("Holo Bomb", true),
	Weapon("Psycho Axe", true),
	Weapon("BL Book", true),
	Weapon("Cutting Board", true),
	Weapon("Fan Beam", true),
	Weapon("Plug Type Asacoco", true),
	Weapon("Glowstick", true),
	Weapon("X-Potato", true),
	Weapon("Idol Song", true)
};
vector <Character> characters = {
	Character("Amelia Watson", true, vector<Weapon>{}),
	Character("Gawr Gura", true, vector<Weapon>{getWeapon("Cutting Board")}),
	Character("Ninomae Ina'nis", true, vector<Weapon>{getWeapon("Cutting Board")}),
	Character("Takanashi Kiara", true, vector<Weapon>{}),
	Character("Calliope Mori", true, vector<Weapon>{}),
	Character("Hakos Baelz", true, vector<Weapon>{}),
	Character("Ouro Kronii", true, vector<Weapon>{}),
	Character("Ceres Fauna", true, vector<Weapon>{}),
	Character("Nanashi Mumei", true, vector<Weapon>{}),
	Character("Tsukumo Sana", true, vector<Weapon>{}),
	Character("IRyS", true, vector<Weapon>{}),
	Character("Tokino Sora", true, vector<Weapon>{}),
	Character("Roboco-san", true, vector<Weapon>{}),
	Character("Sakura Miko", true, vector<Weapon>{getWeapon("Elite Lava Bucket")}),
	Character("Hoshimachi Suisei", true, vector<Weapon>{getWeapon("Psycho Axe"), getWeapon("Cutting Board")}),
	Character("AZKi", true, vector<Weapon>{}),
	Character("Shirakami Fubuki", true, vector<Weapon>{}),
	Character("Ookami Mio", true, vector<Weapon>{}),
	Character("Nekomata Okayu", true, vector<Weapon>{}),
	Character("Inugami Korone", true, vector<Weapon>{})
};

int main() {
	Character character = chooseChar();
	vector<Collab> collabs = createCollabs();
	vector<vector<Collab>> builds = createBuilds(collabs, 0, vector<Collab>());
	if (!character.isAvail())
		return 0;

	vector<Weapon> availWeapons;
	for (auto& weapon : weapons)
		if (weapon.isAvail())
			availWeapons.emplace_back(weapon);
	bool hasWeapon = false;
	for (auto& weapon : availWeapons) {
		for (auto& build : builds)
			if (build.size() == getMax(builds))
				for (auto& collab : build)
					hasWeapon = hasWeapon || collab.hasWeapon(weapon);
		if (hasWeapon)
			hasWeapon = false;
		else
			weapon.setInBuild(true);
	}

	bool hasCollab = false;
	for (auto& collab : collabs) {
		for (auto& build : builds)
			if (build.size() == getMax(builds))
				for (auto& coll : build)
					hasCollab = hasCollab || collab == coll;
		if (hasCollab)
			hasCollab = false;
		else
			collab.setInBuild(true);
	}

	vector<Weapon> chosenWeapons;
	vector<Collab> chosenCollabs;

	string input;
	cout << "Weapon (W) or Collab (C)? (E to exit) ";
	cin >> input;
	cout << endl;
	int num;
	int count = 0;
	int inBuild = 0;
	bool hasNone;
	bool noCollab;
	bool finCollab;
	bool buildCollab;
	bool noWork;
	Weapon other;
	bool onlyOne;
	bool neverFin;
	Weapon conflicting;
	while (input != "e" && input != "E") {
		if (input == "r" || input == "R") {
			character = chooseChar();
			collabs = createCollabs();
			builds = createBuilds(collabs, 0, vector<Collab>());
			if (!character.isAvail())
				return 0;

			availWeapons = vector<Weapon>();
			for (auto& weapon : weapons)
				if (weapon.isAvail())
					availWeapons.emplace_back(weapon);
			hasWeapon = false;
			for (auto& weapon : availWeapons) {
				for (auto& build : builds)
					if (build.size() == getMax(builds))
						for (auto& collab : build)
							hasWeapon = hasWeapon || collab.hasWeapon(weapon);
				if (hasWeapon)
					hasWeapon = false;
				else
					weapon.setInBuild(true);
			}

			hasCollab = false;
			for (auto& collab : collabs) {
				for (auto& build : builds)
					if (build.size() == getMax(builds))
						for (auto& coll : build)
							hasCollab = hasCollab || collab == coll;
				if (hasCollab)
					hasCollab = false;
				else
					collab.setInBuild(true);
			}

			chosenWeapons = vector<Weapon>();
			chosenCollabs = vector<Collab>();

			cout << "Weapon (W) or Collab (C)? (E to exit) ";
			cin >> input;
			cout << endl;
		}
		else {
			if (input == "c" || input == "C") {
				hasNone = true;
				for (int i = 0; i < collabs.size(); i++)
					if (collabs[i].canPick(chosenWeapons)) {
						hasNone = false;
						cout << i + 1 << ". " << collabs[i];
						if (character.isFavored(collabs[i]))
							cout << " (favored)";
						if (collabs[i].inBuild())
							cout << " (not in a build)";
						cout << endl;
					}
				if (hasNone)
					cout << "No Collabs Available" << endl;
				else {
					cout << collabs.size() + 1 << ". None" << endl;
					cout << "\nWhich collab are you picking? ";
					cin >> num;
					while (num < 1 || num > collabs.size() + 1
						|| !(num == collabs.size() + 1 || collabs[num - 1].canPick(chosenWeapons))) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid Choice" << endl
							<< "Which collab are you picking? ";
						cin >> num;
					}

					if (num != collabs.size() + 1) {
						for (int i = 0; i < chosenWeapons.size(); i++) {
							if (collabs[num - 1].hasWeapon(chosenWeapons[i])) {
								for (int j = 0; j < collabs.size(); j++)
									if (j != num - 1 && collabs[j].hasWeapon(chosenWeapons[i])) {
										hasCollab = false;
										for (int k = 0; k < builds.size(); k++) {
											for (auto& collab : builds[k])
												hasCollab = hasCollab || collab == collabs[j];
											if (hasCollab) {
												hasCollab = false;
												builds.erase(builds.begin() + k);
												k--;
											}
										}
										if (j < num - 1)
											num--;
										collabs.erase(collabs.begin() + j);
										j--;
									}
								chosenWeapons.erase(chosenWeapons.begin() + i);
								i--;
							}
						}

						noCollab = true;
						for (int i = 0; i < builds.size(); i++) {
							for (auto& collab : builds[i])
								noCollab = noCollab && !(collab == collabs[num - 1]);
							if (noCollab) {
								builds.erase(builds.begin() + i);
								i--;
							}
							else
								noCollab = true;
						}

						hasWeapon = false;
						for (auto& weapon : availWeapons) {
							for (auto& build : builds)
								for (auto& collab : build)
									hasWeapon = hasWeapon || collab.hasWeapon(weapon);
							if (hasWeapon) {
								hasWeapon = false;
								weapon.setInBuild(false);
							}
							else
								weapon.setInBuild(true);
						}

						for (auto& weapon : chosenWeapons) {
							for (auto& build : builds)
								for (auto& collab : build)
									hasWeapon = hasWeapon || collab.hasWeapon(weapon);
							if (hasWeapon) {
								hasWeapon = false;
								weapon.setInBuild(false);
							}
							else
								weapon.setInBuild(true);
						}

						hasCollab = false;
						for (auto& collab : collabs) {
							for (auto& build : builds)
								if (build.size() == getMax(builds))
									for (auto& coll : build)
										hasCollab = hasCollab || collab == coll;
							if (hasCollab) {
								hasCollab = false;
								collab.setInBuild(false);
							}
							else
								collab.setInBuild(true);
						}

						chosenCollabs.emplace_back(collabs[num - 1]);
						collabs.erase(collabs.begin() + num - 1);
					}
				}
			}
			else if (input != "e" && input != "E") {
				if (chosenCollabs.size() + count > 4)
					cout << "Cannot pick a weapon" << endl;
				else {
					finCollab = false;
					buildCollab = false;
					for (int i = 0; i < availWeapons.size(); i++) {
						cout << i + 1 << ". " << availWeapons[i];
						for (auto& collab : collabs)
							if (collab.finishCollab(chosenWeapons, availWeapons[i])) {
								finCollab = true;
								buildCollab = buildCollab || !collab.inBuild();
							}
						if (buildCollab) {
							cout << " (build collab)";
							buildCollab = false;
						}
						else if (finCollab)
							cout << " (collab)";
						else {
							noWork = true;
							for (auto& collab : collabs)
								if (collab.hasWeapon(availWeapons[i])) {
									other = collab.otherWeapon(availWeapons[i]);
									onlyOne = true;
									neverFin = true;
									for (auto& coll : collabs)
										if (coll.finishCollab(chosenWeapons, other)) {
											neverFin = false;
											conflicting = coll.otherWeapon(other);
											for (auto& colab : collabs)
												onlyOne = onlyOne && (coll == colab || !colab.hasWeapon(conflicting));
											if (!onlyOne) {
												onlyOne = true;
												noWork = false;
											}
										}
									if (neverFin)
										noWork = false;
								}
							if (noWork)
								availWeapons[i].setInBuild(true);
						}
						finCollab = false;
						if (character.isFavored(availWeapons[i]))
							cout << " (favored)";
						if (availWeapons[i].inBuild())
							cout << " (not in a build)";
						cout << endl;
					}
					cout << availWeapons.size() + 1 << ". None" << endl;
					cout << "\nWhich weapon are you picking? ";
					if (chosenCollabs.size() + count == 4)
						cout << "(last slot) ";
					cin >> num;
					while (num < 1 || num > availWeapons.size() + 1) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid Choice" << endl
							<< "Which weapon are you picking? ";
						cin >> num;
					}
					if (num != availWeapons.size() + 1) {
						chosenWeapons.emplace_back(availWeapons[num - 1]);
						availWeapons.erase(availWeapons.begin() + num - 1);
					}
				}
			}

			count = 0;
			inBuild = 0;
			for (auto& weapon : chosenWeapons) {
				count++;
				if (weapon.inBuild())
					inBuild++;
			}
			if (chosenCollabs.size() + inBuild > 4) {
				cout << "\n\n" << character << "\n\nCollabs:" << endl;
				for (auto& collab : chosenCollabs)
					cout << collab << endl;
				cout << "\nWeapons:" << endl;
				for (auto& weapon : chosenWeapons)
					cout << weapon << endl;
				cout << "\nPress R to reset, or E to exit: ";
				cin >> input;
				cout << endl;
			}
			else {
				cout << "\n\nWeapon (W) or Collab (C)? (E to exit) ";
				cin >> input;
				cout << endl;
			}
		}
	}

	return 0;
}

Weapon getWeapon(string param) {
	for (int i = 0; i < weapons.size(); i++)
		if (weapons[i] == param)
			return weapons[i];
	return Weapon();
}

Character chooseChar() {
	for (int i = 0; i < characters.size(); i++)
		if (characters[i].isAvail())
			cout << i + 1 << ". " << characters[i] << endl;
	cout << endl << "Which character are you playing? (0 to exit) ";
	int num;
	cin >> num;
	while (num < 0 || num > characters.size() || !(num == 0 || characters[num - 1].isAvail())) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Invalid Choice" << endl << "Which character are you playing? (0 to exit) ";
		cin >> num;
	}
	if (num == 0)
		return Character();
	cout << "\n\n";
	return characters[num - 1];
}

vector<Collab> createCollabs() {
	vector<Collab> collabs;
	string colWeap[12][3] = {
		{"Rap Dog", "X-Potato", "Idol Song"},
		{"Breathe-In Type Asacoco", "Plug Type Asacoco", "Holo Bomb"},
		{"Dragon Fire", "Plug Type Asacoco", "Fan Beam"},
		{"Broken Dreams", "CEO's Tears", "Spider Cooking"},
		{"Elite Cooking", "Elite Lava Bucket", "Spider Cooking"},
		{"Idol Concert", "Glowstick", "Idol Song"},
		{"Stream of Tears", "CEO's Tears", "Fan Beam"},
		{"BL Fujoshi", "BL Book", "Psycho Axe"},
		{"MiComet", "Elite Lava Bucket", "Psycho Axe"},
		{"Frozen Sea", "BL Book", "Wamy Water"},
		{"Flattening Board", "Cutting Board", "Holo Bomb"},
		{"Light Beam", "Glowstick", "Fan Beam"}
	};
	for (int i = 0; i < 12; i++)
		collabs.emplace_back(Collab(colWeap[i][0],
			getWeapon(colWeap[i][1]), getWeapon(colWeap[i][2])));

	vector<Collab> availCollabs;
	for (int i = 0; i < collabs.size(); i++)
		if (collabs[i].isAvail())
			availCollabs.emplace_back(collabs[i]);
	return availCollabs;
}

vector<vector<Collab>> createBuilds(const vector<Collab>& collabs, int pos,
	const vector<Collab>& curr) {
	vector<vector<Collab>> builds;
	vector<Collab> newCurr;
	bool check = true;
	for (int i = pos; i < collabs.size(); i++) {
		for (int j = 0; j < curr.size(); j++)
			check = check && collabs[i].isCompat(curr[j]);
		if (check && !collabs[i].inBuild()) {
			newCurr = curr;
			newCurr.emplace_back(collabs[i]);
			if (i < collabs.size() - 1 && newCurr.size() < 4)
				for (auto& build : createBuilds(collabs, i + 1, newCurr))
					builds.emplace_back(build);
			else
				builds.emplace_back(newCurr);
		} else {
			check = true;
			builds.emplace_back(curr);
		}
	}
	return builds;
}

int getMax(const vector<vector<Collab>>& builds) {
	int maxSize = 0;
	for (auto& build : builds)
		maxSize = max(maxSize, (int)build.size());
	return min(maxSize, 4);
}