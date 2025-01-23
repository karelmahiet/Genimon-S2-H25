#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <ctime>
#include "genimon.h"
using namespace std;

class Joueur {
public:
	Joueur(int x0 = 4, int y0 = 5);
	void deplacement();
	void afficher();
	void capture();
private:
	char direction;
	int position_x;
	int position_y;
	int position[9][9];
	int arret;
};

#endif
