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
	int nbGenimonRencontr� = 0;
	int nbGenimonAttrap�s = 0;
	vector<Genimon> listeGenimonRencontr�;
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
	void consulterD�tailsType(int typeNum�rique, string type);
	void demanderInformationsGenimon(int typeNum�rique, string type);
	void gererGenimon();
	bool estSurGenimon();
	int position_x;
	int position_y;
private:
	int terrain[9][9];
	caseGenidex genidex[8];
};

#endif
