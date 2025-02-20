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
	virtual void apparait();
	bool capture();
	void SetNom();
	virtual void setRaret�();
	int getTypeNum�rique();
	string getType();
	string getTypeSup�rieur();
	string getTypeInf�rieur();
	string getNom();
	string getRaret�();;
	int getPV();
	void setPV(int nouveauPV);
	void varierPV(int variation);
	int getDegats();
	int getFacteurDegats();
	int position_x;
	int position_y;
	int pvMax;
protected:
	string nom;
	string rarete;
	string type;
	int typeNum�rique;
	int nbBalle;
	int facteurChance;

	//variables pour les combats
	string typeSup�rieur;
	string typeInf�rieur;
	int pv;
	int degats;
	int facteurDegats;
};

#endif
