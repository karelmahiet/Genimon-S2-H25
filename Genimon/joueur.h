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
	void afficherPartie();
	void afficherMenuPrincipal();
	void afficherMenuGeniedex();
	void capture();
	void creerTerrain();
	void initialiserPosition(int x0, int y0);
	void consulterGenidexPartiel(char type);
	void consulterGenidexComplet();
	void gererGenimon();
	bool estSurGeniMon();
	int position_x;
	int position_y;
private:
	int terrain[9][9];
	int a_genimon;
	int c_genimon;
	int a_genidex[8] = { 0,0,0,0,0,0,0,0 };
	int c_genidex[8] = { 0,0,0,0,0,0,0,0 };
};

#endif
