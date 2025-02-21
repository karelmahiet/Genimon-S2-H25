#ifndef GESTIONJEU_H
#define GESTIONJEU_H

#include <ctime>
#include "joueur.h"

bool evenementActif();
void afficherBienvenue();
void afficherConfirmation();
void afficherPause();
void gererInitialisation();
void gererPause();
void gererConfirmation(int option, bool* finPartie);
void gererGeniedex();
void gererHistorique();
void gererPartie();
void gererThread();
void gererThread2();

#endif

