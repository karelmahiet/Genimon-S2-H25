#ifndef JOUEUR_H
#define JOUEUR_H

#include <iostream>
#include <ctime>
#include "genimon.h"
#include <thread>
#include <vector>
#include <chrono>
#include <conio.h>
#include <cstdlib>
using namespace std;

#define dimensionTerrain 21

struct caseGenidex
{
	int nbGenimonRencontr� = 0;
	int nbGenimonAttrap�s = 0;
	vector<Genimon> listeGenimonRencontr�;
};

class Joueur {
public:
	Joueur(int x0 = 10, int y0 = 10);
	void afficherPartie();
	void afficherMenuPrincipal();
	void afficherMenuGeniedex();
	void creerTerrain();
	void initialiserPosition(int x0, int y0);
	void reinitialiserGenidex();
	void consulterGenidexPartiel(char type);
	void consulterGenidexComplet();
	void consulterD�tailsType(int typeNum�rique, string type);
	void demanderInformationsGenimon(int typeNum�rique, string type);
	void gererGenimon();
	bool estSurGenimon();
	int position_x;
	int position_y;
	int anciennePosition_x;
	int anciennePosition_y;
private:
	char terrain[dimensionTerrain][dimensionTerrain];
	caseGenidex genidex[8];
};

#endif
