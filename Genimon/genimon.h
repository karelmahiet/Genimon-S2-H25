#ifndef GENIMON_H
#define GENIMON_H
#include <iostream>
#include <string>
#include <ctime>
#include "random"
#include "joueur.h"
using namespace std;

class Genimon {
public:
	Genimon();
	void apparait();
	void capture();
	string nom;
	int balles;
	int chance;
protected:

};

#endif