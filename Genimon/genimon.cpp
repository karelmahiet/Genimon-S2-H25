#include "genimon.h"

Genimon::Genimon() {
    nbBalle = 5;
    int random = rand() % 8;
    typeNumérique = random;
    SetNom();
    if (random == 0) {
        type = "informatique";
        typeSupérieur = "aucunI";
        typeInférieur = "civil";
    }
    else if (random == 1) {
        type = "electrique";
        typeSupérieur = "aucunE";
        typeInférieur = "batiment";

    }
    else if (random == 2) {
        type = "robotique";
        typeSupérieur = "bioTech";
        typeInférieur = "aucunR";
   
    }
    else if (random == 3) {
        type = "mecanique";
        typeSupérieur = "civil";
        typeInférieur = "bioTech";
   
    }
    else if (random == 4) {
        type = "civil";
        typeSupérieur = "informatique";
        typeInférieur = "mecanique";
  
    }
    else if (random == 5) {
        type = "batiment";
        typeSupérieur = "electrique";
        typeInférieur = "chimique";
   
    }
    else if (random == 6) {
        type = "bioTech";
        typeSupérieur = "mecanique";
        typeInférieur = "robotique";
  
    }
    else if (random == 7) {
        type = "chimique";
        typeSupérieur = "batiment";
        typeInférieur = "chimique";
     
    }

    setRareté();
    facteurDegats = degats/3;
}

void Genimon::SetNom() {
	if (typeNumérique == 0) { // informatique
        int random = rand() % 4;
        if (random == 0)
            nom = "Jeremie";
        else if (random == 1)
            nom = "Amine";
        else if (random == 2)
            nom = "Alexandre";
        else if (random == 3)
            nom = "Manon";
	}
	else if (typeNumérique == 1) { // electrique
        int random = rand() % 4;
        if (random == 0)
            nom = "Florian";
        else if (random == 1)
            nom = "Dylan";
        else if (random == 2)
            nom = "Natasha";
        else if (random == 3)
            nom = "Elon";
	}
	else if (typeNumérique == 2) { // robotique
        int random = rand() % 4;
		if (random == 0)
			nom = "Alexis";
		else if (random == 1)
			nom = "Melianne";
		else if (random == 2)
			nom = "Joe";
		else if (random == 3)
			nom = "Rose";
	}
	else if (typeNumérique == 3) { // mecanique
        int random = rand() % 4;
		if (random == 0)
			nom = "Eric";
		else if (random == 1)
			nom = "Robert";
		else if (random == 2)
			nom = "Trump";
		else if (random == 3)
			nom = "Isabelle";
	}
	else if (typeNumérique == 4) { // civil
        int random = rand() % 4;
		if (random == 0)
			nom = "Vincent";
		else if (random == 1)
			nom = "Jeff";
		else if (random == 2)
			nom = "Francois";
		else if (random == 3)
			nom = "Laurianne";
		
	}
	else if (typeNumérique == 5) { // batiment
        int random = rand() % 4;
		if (random == 0)
			nom = "Steve";
		else if (random == 1)
			nom = "Marek";
		else if (random == 2)
			nom = "Marianne";
		else if (random == 3)
			nom = "Angelie";
	}
	else if (typeNumérique == 6) { // bioTech
        int random = rand() % 4;
		if (random == 0)
			nom = "Karel";
		else if (random == 1)
			nom = "Lilianne";
		else if (random == 2)
			nom = "Antoine";
		else if (random == 3)
			nom = "Mikael";
	}
	else if (typeNumérique == 7) { // chimique
        int random = rand() % 4;
		if (random == 0)
			nom = "Olivier";
		else if (random == 1)
			nom = "Darnley";
		else if (random == 2)
			nom = "Philippe";
		else if (random == 3)
			nom = "France";
	}

}

void Genimon::setRareté()
{
    int random = rand() % 100;
    if (random >= 0 && random < 50)
    {
        rarete = "COMMUN";
        facteurChance = 4;

        pv = 50 + (rand() % 51); //Entre 50 et 100

        degats = 10 + (rand() % 11); //Entre 10 et 20
    }
    else if (random >= 50 && random < 80)
    {
        rarete = "RARE";
        facteurChance = 2;

        pv = 100 + (rand() % 101); //Entre 100 et 200

        degats = 20 + (rand() % 21); //Entre 20 et 40
    }
    else if (random >= 80 && random < 95)
    {
        rarete = "EPIQUE";
        facteurChance = 1;

        pv = 200 + (rand() % 101); //Entre 200 et 300

        degats = 40 + (rand() % 21); //Entre 40 et 60
    }
    else if (random >= 95 && random < 99)
    {
        rarete = "!! LEGENDAIRE !!";
        facteurChance = 0;

        pv = 300 + (rand() % 201); //Entre 300 et 500

        degats = 60 + (rand() % 31); //Entre 60 et 90
    }
    else if (random == 99)
    {
        rarete = "*** SECRET ***";
        facteurChance = 0;

        pv = 500 + (rand() % 201); //Entre 500 et 700

        degats = 90 + (rand() % 31); //Entre 90 et 120
    }

    pvMax = pv;
}

void Genimon::apparait() {
    cout << endl << "    -----Un Genimon sauvage " << rarete << " de type " << type << " apparait!-----" << endl;
    cout << "                   -----Il s'agit de " << nom << "-----                       " << endl;
    cout << "-----Il possede " << pv << " points de vie et il attaque avec " << degats << " de degats.-----" << endl << endl;
}

int Genimon::getTypeNumérique() {
    return typeNumérique;
}

string Genimon::getType() {
    return type;
}

string Genimon::getTypeSupérieur()
{
    return typeSupérieur;
}

string Genimon::getTypeInférieur()
{
    return typeInférieur;
}

string Genimon::getRareté() {
    return rarete;
}

string Genimon::getNom() {
    return nom;
}

int Genimon::getPV() {
    return pv;
}

void Genimon::setPV(int nouveauPV)
{
    pv = nouveauPV;
}

void Genimon::varierPV(int variation)
{
    pv += variation;
}

int Genimon::getDegats() {
    return degats;
}

int Genimon::getFacteurDegats()
{
    return facteurDegats;
}

bool Genimon::capture()
{
    bool captureReussie = false;
    bool captureFinie = false;

    while (!captureFinie)
    {
        if (nbBalle <= 0) {
            cout << "Nombre de balles insuffisantes" << endl;
            cout << nom << " s'est echappe..." << endl;
            cout << endl << "-----Fin du face a face-----" << endl << endl;
            captureFinie = true;
        }
        else if (nbBalle > 0) {
            cout << "Nombre de balles restantes: " << nbBalle << endl;
            cout << "Voulez-vous le capturer? (O/N)" << endl;
            bool decisionPrise = false;
            while (!decisionPrise)
            {
                bool estCapturé = false;
                char question = _getch();
                if (question == 'o' || question == 'O') {
                    cout << "Balle lancee!" << endl;
                    nbBalle--;
                    int random = rand() % 20;
                    if (random >= 0 && random < (5 + facteurChance)) {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << "--1--" << endl;
                        random = rand() % 20;
                        if (random >= 0 && random < (7 + facteurChance)) {
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            cout << "--2--" << endl;
                            random = rand() % 20;
                            if (random >= 0 && random < (9 + facteurChance)) {
                                std::this_thread::sleep_for(std::chrono::seconds(1));
                                cout << nom << " capture! Bravo" << endl;
                                estCapturé = true;
                                captureReussie = true;
                                captureFinie = true;
                                cout << endl << "-----Fin du face a face-----" << endl << endl;
                            }
                        }
                    }
                    if (!estCapturé) {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << nom << " s'est echappe de la balle..." << endl << endl;
                    }
                    decisionPrise = true;
                }
                else if (question == 'n' || question == 'N') {
                    cout << nom << " s'est enfuit..." << endl;
                    cout << endl << "-----Fin du face a face-----" << endl << endl;
                    decisionPrise = true;
                    captureFinie = true;
                }
                else
                {
                    cout << "Touche invalide" << endl;
                }
            }
        }
    }

    return captureReussie;
}
