#include "genimonS.h"

GenimonS::GenimonS(char typeC, string nomC) {
	nom = nomC;

    if (typeC == '1') {
        type = "informatique";
        typeSup�rieur = "aucunI";
        typeInf�rieur = "civil";
		typeNum�rique = 0;
    
    }
    else if (typeC == '2') {
        type = "electrique";
        typeSup�rieur = "aucunE";
        typeInf�rieur = "batiment";
		typeNum�rique = 1;                                  
     
    }
    else if (typeC == '3') {
        type = "robotique";
        typeSup�rieur = "bioTech";
        typeInf�rieur = "aucunR";
		typeNum�rique = 2;
      
    }
    else if (typeC == '4') {
        type = "mecanique";
        typeSup�rieur = "civil";
        typeInf�rieur = "bioTech";
		typeNum�rique = 3;

    }
    else if (typeC == '5') {
        type = "civil";
        typeSup�rieur = "informatique";
        typeInf�rieur = "mecanique";
		typeNum�rique = 4;
    
    }
    else if (typeC == '6') {
        type = "batiment";
        typeSup�rieur = "electrique";
        typeInf�rieur = "chimique";
		typeNum�rique = 5;
     
    }
    else if (typeC == '7') {
        type = "bioTech";
        typeSup�rieur = "mecanique";
        typeInf�rieur = "robotique";
		typeNum�rique = 6;
    }
    else if (typeC == '8') {
        type = "chimique";
        typeSup�rieur = "batiment";
        typeInf�rieur = "chimique";
		typeNum�rique = 7; 
    }

    setRaret�();
    facteurDegats = degats / 3;
}

void GenimonS::setRaret�()
{
    rarete = "RARE";
    rareteNumerique = 1;
    facteurChance = 2;
    gainBalles = 15;

    pv = 100 + (rand() % 101); //Entre 100 et 200

    degats = 20 + (rand() % 21); //Entre 20 et 40

    pvMax = pv;
}


