#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <ctime>
#include "genimon.h"
#include <thread>
#include <chrono>
#include <conio.h>
#include <cstdlib>
using namespace std;

class Joueur {
public:
	Joueur(int x0 = 4, int y0 = 5);
	void deplacement();
	void afficher();
	void capture();
	void consultegenidex();
private:
	char direction;
	int position_x;
	int position_y;
	int position[9][9];
	int arret;
	int a_genimon;
	int c_genimon;
	int a_genidex[8] = { 0,0,0,0,0,0,0,0 };
	int c_genidex[8] = { 0,0,0,0,0,0,0,0 };
};

#endif
