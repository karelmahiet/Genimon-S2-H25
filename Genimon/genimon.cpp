#include "genimon.h"
#include <cmath>

Genimon::Genimon(int badge1)
{
    badge = badge1;
    int random = rand() % 8;
    typeNumérique = random;
    setNom();
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

    setNiveau();
    facteurDegats = degats/4;
}

Genimon::Genimon(char typeC, string nomC, int rareteC) {
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
    if (rareteC == 0) {
        niveau = rand() % 10 + 1; //Entre 1 et 9
        rarete = "COMMUN";
        rareteNumerique = 0;
    }
    else if (rareteC == 1) {
        niveau = rand() % 15 + 10; //Entre 10 et 24
        rarete = "RARE";
        rareteNumerique = 1;
    }
    else if (rareteC == 2) {
        niveau = rand() % 20 + 25; //Entre 25 et 50
        rarete = "EPIQUE";
        rareteNumerique = 2;
    }
    else if (rareteC == 3) {
        niveau = rand() % 25 + 50; //Entre 50 et 74
        rarete = "!! LEGENDAIRE !!";
        rareteNumerique = 3;
    }
    else if (rareteC == 4) {
        niveau = rand() % 25 + 75; //Entre 75 et 99
        rarete = "*** SECRET ***";
        rareteNumerique = 4;
    }
    facteurDegats = degats / 4;
    pv = niveau * 10 + (rand() % 11); //Entre niveau * 10 et niveau * 10 + 10
    degats = niveau * 2 + (rand() % 3); //Entre niveau * 2 et niveau * 2 + 2
    facteurChance = niveau;
    pvMax = pv;
}


void Genimon::setNom()
{
    if (typeNumérique == 0) { // informatique
        int random = rand() % 4;
        if (random == 0)
            nom = "Jeremie";
        else if (random == 1)
            nom = "Alexis";
        else if (random == 2)
            nom = "Karel";
        else if (random == 3)
            nom = "Raphael";
    }
    else if (typeNumérique == 1) { // electrique
        int random = rand() % 4;
        if (random == 0)
            nom = "Florian";
        else if (random == 1)
            nom = "Dylan";
        else if (random == 2)
            nom = "Marek";
        else if (random == 3)
            nom = "Vincent";
    }
    else if (typeNumérique == 2) { // robotique
        int random = rand() % 4;
        if (random == 0)
            nom = "Zack";
        else if (random == 1)
            nom = "Melianne";
        else if (random == 2)
            nom = "Joe";
        else if (random == 3)
            nom = "Ethan";
    }
    else if (typeNumérique == 3) { // mecanique
        int random = rand() % 4;
        if (random == 0)
            nom = "Eric";
        else if (random == 1)
            nom = "Robert";
        else if (random == 2)
            nom = "Olivier";
        else if (random == 3)
            nom = "Isabelle";
    }
    else if (typeNumérique == 4) { // civil
        int random = rand() % 4;
        if (random == 0)
            nom = "Sammuel";
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
            nom = "Tony";
        else if (random == 2)
            nom = "Marianne";
        else if (random == 3)
            nom = "Angelie";
    }
    else if (typeNumérique == 6) { // bioTech
        int random = rand() % 4;
        if (random == 0)
            nom = "Philippe";
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
            nom = "Darnley";
        else if (random == 1)
            nom = "Elon";
        else if (random == 2)
            nom = "Donald";
        else if (random == 3)
            nom = "Justin";
    }
}

void Genimon::setNiveau()
{
        int random = 0;
        for (int i = 0; i < 3;i++) {
            random = rand() % 100; //Entre 0 et 99
        }
        if (random < 75)
        {
            niveau = rand() % 10 + 1; //Entre 1 et 9
            rarete = "Commun";
            rareteNumerique = 0;

            /*rarete = "COMMUN";
            rareteNumerique = 0;
            facteurChance = 4;
            gainBalles = 10;
            pv = 50 + (rand() % 51); //Entre 50 et 100
            degats = 10 + (rand() % 11); //Entre 10 et 20
            */
        }
        else if (random < 99)
        {
            niveau = rand() % 15 + 10; //Entre 10 et 24
            rarete = "Rare";
            rareteNumerique = 1;


            /* rarete = "RARE";
             rareteNumerique = 1;
             facteurChance = 2;
             gainBalles = 15;

             pv = 100 + (rand() % 101); //Entre 100 et 200
             degats = 20 + (rand() % 21); //Entre 20 et 40
             */
        }
        else if (random < 100)
        {
            niveau = rand() % 20 + 25; //Entre 25 et 50
            rarete = "Epique";
            rareteNumerique = 2;

        }
            /* rarete = "EPIQUE";
             rareteNumerique = 2;
             facteurChance = 1;
             gainBalles = 20;

             pv = 200 + (rand() % 101); //Entre 200 et 300
             degats = 40 + (rand() % 21); //Entre 40 et 60
             */
        
        /* else if (random < 99)
         {
             niveau = rand() % 25 + 50; //Entre 50 et 74
             rarete = "Legendaire";
             rareteNumerique = 3;

             /*
             rarete = "!! LEGENDAIRE !!";
             rareteNumerique = 3;
             facteurChance = 0;
             gainBalles = 25;

             pv = 300 + (rand() % 201); //Entre 300 et 500
             degats = 60 + (rand() % 31); //Entre 60 et 90

         }
         else
         {
             niveau = rand() % 25 + 75; //Entre 75 et 99
             rarete = "Secret";
             rareteNumerique = 4;

             /*
             rarete = "*** SECRET ***";
             rareteNumerique = 4;
             facteurChance = 100;
             gainBalles = 30;

             pv = 500 + (rand() % 201); //Entre 500 et 700
             degats = 90 + (rand() % 31); //Entre 90 et 120
         }*/
        gainBalles = niveau - 2 + rand() % 5; //Entre niveau - 2 et niveau + 2
        if (gainBalles <= 0) {
            gainBalles = 1;
        }

        pv = niveau * 10 + (rand() % 11); //Entre niveau * 10 et niveau * 10 + 10
        degats = niveau * 2 + (rand() % 3); //Entre niveau * 2 et niveau * 2 + 2
        facteurChance = niveau;
        pvMax = pv;
}

void Genimon::apparait() {
	cout << endl << "Un " << nom <<" " << rarete << " apparait!" << endl;

   /* cout << endl << "    -----Un Genimon sauvage " << rarete << " de type " << type << " apparait!-----" << endl;
    cout << "                   -----Il s'agit de " << nom << "-----                       " << endl;
    cout << "-----Il possede " << pv << " points de vie et il attaque avec " << degats << " de degats.-----" << endl << endl;
    */
}

void Genimon::presenter() {
    cout << "\nInteraction avec " << nom << ", Type: " << type;
    cout << ", Niveau: " << niveau << ", PV: " << pv;
    cout << ", Degats: " << degats << endl << endl;
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

int Genimon::getRareteNumerique() {
    return rareteNumerique;
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

int Genimon::getGainBalles()
{
    return gainBalles;
}

bool Genimon::capture(int* nbBallesJoueur)
{
    bool captureReussie = false;
    bool captureFinie = false;

    while (!captureFinie)
    {      
        if (*nbBallesJoueur <= 0)
        {
            cout << "Nombre de balles insuffisantes" << endl;
            cout << nom << " s'est echappe..." << endl;
            cout << endl << "-----Fin du face a face-----" << endl << endl;
            captureFinie = true;
        }
        else
        {
            cout << "Nombre de balles restantes: " << *nbBallesJoueur << endl;
            cout << "Voulez-vous le capturer? (O/N)" << endl;
            bool decisionPrise = false;
            while (!decisionPrise)
            {
                bool estCapturé = false;
                char question = _getch();
                if (question == 'o' || question == 'O') {
                    cout << "Balle lancee!" << endl;
                    (*nbBallesJoueur)--;
					int random = rand() % (facteurChance + 1); //Entre 0 et facteurChance
                    if (random >= 0 && random < sqrt(facteurChance)) {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << "--1--" << endl;
						random = rand() % (facteurChance / 2 + 1); //Entre 0 et facteurChance/2
                        if (random >= 0 && random < sqrt(facteurChance)) {
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            cout << "--2--" << endl;
							random = rand() % (facteurChance / 3 + 2); //Entre 0 et facteurChance/3
                            if (random >= 0 && random < sqrt(facteurChance)) {
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
