#include "genimonS.h"

GenimonS::GenimonS(char typeC, string nomC) {
	nom = nomC;

    if (typeC == '1') {
        type = "informatique";
        typeSuperieur = "aucunI";
        typeInferieur = "civil";
		typeNumerique = 0;
    
    }
    else if (typeC == '2') {
        type = "electrique";
        typeSuperieur = "aucunE";
        typeInferieur = "batiment";
		typeNumerique = 1;                                  
     
    }
    else if (typeC == '3') {
        type = "robotique";
        typeSuperieur = "bioTech";
        typeInferieur = "aucunR";
		typeNumerique = 2;
      
    }
    else if (typeC == '4') {
        type = "mecanique";
        typeSuperieur = "civil";
        typeInferieur = "bioTech";
		typeNumerique = 3;

    }
    else if (typeC == '5') {
        type = "civil";
        typeSuperieur = "informatique";
        typeInferieur = "mecanique";
		typeNumerique = 4;
    
    }
    else if (typeC == '6') {
        type = "batiment";
        typeSuperieur = "electrique";
        typeInferieur = "chimique";
		typeNumerique = 5;
     
    }
    else if (typeC == '7') {
        type = "bioTech";
        typeSuperieur = "mecanique";
        typeInferieur = "robotique";
		typeNumerique = 6;
    }
    else if (typeC == '8') {
        type = "chimique";
        typeSuperieur = "batiment";
        typeInferieur = "chimique";
		typeNumerique = 7; 
    }

    setRarete();
    facteurDegats = degats/4;
}

void GenimonS::setRarete()
{
    rarete = "RARE";
    rareteNumerique = 1;
    facteurChance = 2;
    gainBalles = 15;

    pv = 100 + (rand() % 101); //Entre 100 et 200

    degats = 20 + (rand() % 21); //Entre 20 et 40

    pvMax = pv;
}


