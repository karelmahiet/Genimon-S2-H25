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
	void setRaret�();
	int getTypeNum�rique();
	string getType();
	string getNom();
	string getRaret�();
	string getEtat();
	void setEtat(string nouvel�tat);
private:
	string nom;
	string raret�;
	string type;
	int typeNum�rique;
	int nbBalle;
	int facteurChance;
	string �tat;
};

#endif
