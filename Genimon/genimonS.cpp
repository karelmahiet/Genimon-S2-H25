#include "genimonS.h"

GenimonS::GenimonS(char typeC, string nomC) {
	nom = nomC;

    if (typeC == '1') {
        type = "informatique";
        typeSupérieur = "aucunI";
        typeInférieur = "civil";
		typeNumérique = 0;
    
    }
    else if (typeC == '2') {
        type = "electrique";
        typeSupérieur = "aucunE";
        typeInférieur = "batiment";
		typeNumérique = 1;                                  
     
    }
    else if (typeC == '3') {
        type = "robotique";
        typeSupérieur = "bioTech";
        typeInférieur = "aucunR";
		typeNumérique = 2;
      
    }
    else if (typeC == '4') {
        type = "mecanique";
        typeSupérieur = "civil";
        typeInférieur = "bioTech";
		typeNumérique = 3;

    }
    else if (typeC == '5') {
        type = "civil";
        typeSupérieur = "informatique";
        typeInférieur = "mecanique";
		typeNumérique = 4;
    
    }
    else if (typeC == '6') {
        type = "batiment";
        typeSupérieur = "electrique";
        typeInférieur = "chimique";
		typeNumérique = 5;
     
    }
    else if (typeC == '7') {
        type = "bioTech";
        typeSupérieur = "mecanique";
        typeInférieur = "robotique";
		typeNumérique = 6;
    }
    else if (typeC == '8') {
        type = "chimique";
        typeSupérieur = "batiment";
        typeInférieur = "chimique";
		typeNumérique = 7; 
    }

    setRareté();
    facteurDegats = degats / 3;
}

void GenimonS::setRareté()
{
    rarete = "RARE";
    rareteNumerique = 1;
    facteurChance = 2;
    gainBalles = 15;

    pv = 100 + (rand() % 101); //Entre 100 et 200

    degats = 20 + (rand() % 21); //Entre 20 et 40

    pvMax = pv;
}


