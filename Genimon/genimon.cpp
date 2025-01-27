#include "genimon.h"
#include <random>
#include <iostream>
#include <thread> // Pour sleep_for
#include <chrono> // Pour chrono::milliseconds
using namespace std;

Genimon::Genimon() {
    balles = 5;
    srand(time(0));
    int random = rand() % 8;
    n_genimon = random;
    if (random == 0) {
        nom = "Alexis";
    }
    else if (random == 1) {
        nom = "Florian";
    }
    else if (random == 2) {
        nom = "Dylan";
    }
    else if (random == 3) {
        nom = "Vincent";
    }
    else if (random == 4) {
        nom = "Marek";
    }
    else if (random == 5) {
        nom = "Karel";
    }
    else if (random == 6) {
        nom = "Darnley";
    }
    else if (random == 7) {
        nom = "Jeremie";
    }
}

void Genimon::apparait() {
    cout << endl << "-----Un " << nom << " sauvage apparait!-----" << endl << endl;
}

int Genimon::a_nom() {
    return n_genimon;
}

int Genimon::c_nom() {
    return chance;
}

void Genimon::capture() {
    int random = 0;
    if (balles <= 0) {
        cout << "Nombre de balles insuffisantes" << endl;
        cout << nom << " s'est echappe..." << endl;
        cout << endl << "-----Fin du combat-----" << endl << endl;
    }
    else if (balles > 0) {
        cout << "Nombre de balles restantes: " << balles << endl;
        cout << "Voulez-vous le capturer? (O/N)" << endl;
        char question = _getch();
        if (question == 'o' || question == 'O') {
            cout << "balle lancee!" << endl;
            balles--;
            srand(time(0));
            random = rand() % 8;
            if (random == 1 || random == 2 || random == 3 || random == 4) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << "--1--" << endl;
                srand(time(0));
                random = rand() % 8;
                if (random == 1 || random == 2 || random == 3 || random == 4) {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    cout << "--2--" << endl;
                    srand(time(0));
                    random = rand() % 8;
                    if (random == 1 || random == 2 || random == 3 || random == 4) {
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        cout << nom << " capture!" << endl;
                        chance = 1;
                        cout << endl << "-----Fin du combat-----" << endl << endl;
                    }
                }
            }
            if (chance != 1) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << nom << " s'est echappe de la balle..." << endl;
                cout << endl;
                capture();
            }

        }
        else if (question == 'n' || question == 'N') {
            cout << nom << " s'est echappe..." << endl;
            cout << endl << "-----Fin du combat-----" << endl << endl;
        }
    }
}
