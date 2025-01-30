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
#include <Windows.h>
using namespace std;

struct caseGenidex
{
	int nbGenimonRencontré = 0;
	int nbGenimonAttrapés = 0;
	vector<Genimon> listeGenimonRencontré;
};

class Joueur {
public:
	Joueur(int x0 = 4, int y0 = 5);
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
private:
	int terrain[9][9];
	caseGenidex genidex[8];
};

#endif
