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

class Genimon
{
public:
	Genimon(int zone1);
	Genimon(char typeC, string nomC, int rarete);
	virtual void apparait();
	void presenter();
	bool capture(int* nbBallesJoueur);
	virtual void setNiveau();
	int getTypeNumérique();
	string getType();
	string getTypeSupérieur();
	string getTypeInférieur();
	string getNom();
	string getRareté();
	int getRareteNumerique();
	int getGainBalles();
	int getPV();
	void setPV(int nouveauPV);
	void varierPV(int variation);
	int getDegats();
	int getFacteurDegats();
	int position_x;
	int position_y;
	int pvMax;
	int niveau;
protected:
	string nom;
	string rarete;
	string type;
	int typeNumérique;
	int rareteNumerique;
	int facteurChance;
	int gainBalles;
	int badge;
	int zone;

	//variables pour les combats
	string typeSupérieur;
	string typeInférieur;
	int pv;
	int degats;
	int facteurDegats;

	void setNom();
};

#endif
