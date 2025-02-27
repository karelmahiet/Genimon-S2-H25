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
	Genimon();
	Genimon(char typeC, string nomC, int niveau);
	virtual void apparait();
	void presenter();
	bool capture(int* nbBallesJoueur);
	virtual void setNiveau();
	void LvUp(int Niveau);
	int getTypeNum�rique();
	string getType();
	string getTypeSup�rieur();
	string getTypeInf�rieur();
	string getNom();
	string getRaret�();
	int getNiveau();
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
	int typeNum�rique;
	int rareteNumerique;
	int facteurChance;
	int gainBalles;

	//variables pour les combats
	string typeSup�rieur;
	string typeInf�rieur;
	int pv;
	int degats;
	int facteurDegats;

	void setNom();
};

#endif
