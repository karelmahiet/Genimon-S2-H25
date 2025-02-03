#include "genimon.h"

Genimon::Genimon() {
    nbBalle = 5;
    état = "enfuit";

    srand(time(0));
    int random = rand() % 8;
    if (random == 0) {
        type = "informatique";
        nom = "Jeremie";
    }
    else if (random == 1) {
        type = "electrique";
        nom = "Vincent";
    }
    else if (random == 2) {
        type = "robotique";
        nom = "Karel";
    }
    else if (random == 3) {
        type = "mecanique";
        nom = "Dylan";
    }
    else if (random == 4) {
        type = "civil";
        nom = "Alexis";
    }
    else if (random == 5) {
        type = "batiment";
        nom = "Marek";
    }
    else if (random == 6) {
        type = "bioTech";
        nom = "Florian";
    }
    else if (random == 7) {
        type = "chimique";
        nom = "Darnley";
    }

    typeNumérique = random;
    setRareté();
}

void Genimon::setRareté()
{
    srand(time(0));
    int random = rand() % 100;
    if (random >= 0 && random < 50)
    {
        rareté = "COMMUN";
        facteurChance = 4;
    }
    else if (random >= 50 && random < 80)
    {
        rareté = "RARE";
        facteurChance = 2;
    }
    else if (random >= 80 && random < 95)
    {
        rareté = "EPIQUE";
        facteurChance = 1;
    }
    else if (random >= 95 && random < 99)
    {
        rareté = "!! LEGENDAIRE !!";
        facteurChance = 0;
    }
    else if (random == 99)
    {
        rareté = "*** SECRET ***";
        facteurChance = 0;
    }
}

void Genimon::apparait() {
    cout << endl << "-----Un Genimon sauvage " << rareté << " de type " << type << " apparait!-----" << endl;
    cout << endl << "         -----Il s'agit de " << nom << ". Attrapez-le!-----           " << endl << endl;
}

int Genimon::getTypeNumérique() {
    return typeNumérique;
}

string Genimon::getType() {
    return type;
}

string Genimon::getRareté() {
    return rareté;
}

string Genimon::getNom() {
    return nom;
}

string Genimon::getEtat() {
    return état;
}

void Genimon::setEtat(string nouvelÉtat) {
    état = nouvelÉtat;
}

void Genimon::capture()
{
    if (nbBalle <= 0) {
        cout << "Nombre de balles insuffisantes" << endl;
        cout << nom << " s'est echappe..." << endl;
        cout << endl << "-----Fin du combat-----" << endl << endl;
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
                srand(time(0));
                int random = rand() % 20;
                if (random >= 0 && random < (5 + facteurChance)) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "--1--" << endl;
                    srand(time(0));
                    random = rand() % 20;
                    if (random >= 0 && random < (7 + facteurChance)) {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << "--2--" << endl;
                        srand(time(0));
                        random = rand() % 20;
                        if (random >= 0 && random < (9 + facteurChance)) {
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            cout << nom << " capture! Bravo" << endl;
                            estCapturé = true;
                            état = "capture";
                            cout << endl << "-----Fin du combat-----" << endl << endl;
                        }
                    }
                }
                if (!estCapturé) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << nom << " s'est echappe de la balle..." << endl << endl;
                    capture();
                }
                decisionPrise = true;
            }
            else if (question == 'n' || question == 'N') {
                cout << nom << " s'est enfuit..." << endl;
                cout << endl << "-----Fin du combat-----" << endl << endl;
                decisionPrise = true;
            }
            else
            {
                cout << "Touche invalide" << endl;
            }
        }
    }
}
