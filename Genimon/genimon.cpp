#include "genimon.h"

Genimon::Genimon() {
    nbBalle = 5;
    �tat = "enfuit";

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

    typeNum�rique = random;
    setRaret�();
}

void Genimon::setRaret�()
{
    srand(time(0));
    int random = rand() % 100;
    if (random >= 0 && random < 50)
    {
        raret� = "COMMUN";
        facteurChance = 4;
    }
    else if (random >= 50 && random < 80)
    {
        raret� = "RARE";
        facteurChance = 2;
    }
    else if (random >= 80 && random < 95)
    {
        raret� = "EPIQUE";
        facteurChance = 1;
    }
    else if (random >= 95 && random < 99)
    {
        raret� = "!! LEGENDAIRE !!";
        facteurChance = 0;
    }
    else if (random == 99)
    {
        raret� = "*** SECRET ***";
        facteurChance = 0;
    }
}

void Genimon::apparait() {
    cout << endl << "-----Un Genimon sauvage " << raret� << " de type " << type << " apparait!-----" << endl;
    cout << endl << "         -----Il s'agit de " << nom << ". Attrapez-le!-----           " << endl << endl;
}

int Genimon::getTypeNum�rique() {
    return typeNum�rique;
}

string Genimon::getType() {
    return type;
}

string Genimon::getRaret�() {
    return raret�;
}

string Genimon::getNom() {
    return nom;
}

string Genimon::getEtat() {
    return �tat;
}

void Genimon::setEtat(string nouvel�tat) {
    �tat = nouvel�tat;
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
            bool estCaptur� = false;
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
                            estCaptur� = true;
                            �tat = "capture";
                            cout << endl << "-----Fin du combat-----" << endl << endl;
                        }
                    }
                }
                if (!estCaptur�) {
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
