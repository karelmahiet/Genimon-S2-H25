#ifndef GENIMON_H
#define GENIMON_H

#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <thread> // Pour sleep_for
#include <chrono> // Pour chrono::milliseconds
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
using namespace std;

class Genimon {
public:
	Genimon();
	void apparait();
	void capture();
	void setRareté();
	int getTypeNumérique();
	string getType();
	string getNom();
	string getRareté();
	string getEtat();
	void setEtat(string nouvelÉtat);
private:
	string nom;
	string rareté;
	string type;
	int typeNumérique;
	int nbBalle;
	int facteurChance;
	string état;
};

#endif
