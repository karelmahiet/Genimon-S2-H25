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
	int nbGenimonRencontré = 0;
	int nbGenimonAttrapés = 0;
	vector<Genimon> listeGenimonRencontré;
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
	void consulterDétailsType(int typeNumérique, string type);
	void demanderInformationsGenimon(int typeNumérique, string type);
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
