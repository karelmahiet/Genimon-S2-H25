//#include "genimon.h" marche pas?? donc jai include mon path, devrait pas marche pour vous
//le genimon.h est dans le teams dans le code d'alexis
#include "D:\download\OneDrive_2025-01-23\Genimon (Capture+deplacement)\genimon.h"
#include <random>
#include <iostream>
#include <thread> // Pour sleep_for
#include <chrono> // Pour chrono::milliseconds
using namespace std;

Genimon::Genimon() {
    balles = 5;
    srand(time(0));
    int random = rand() % 8;
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
        nom = "Jérémie";
    }
}

void Genimon::apparait() {
    cout << endl << "-----Un " << nom << " sauvage apparait!-----" << endl << endl;
}

void Genimon::capture() {
    int random = 0;
    if (balles <= 0) {
        cout << "Nombre de balles insuffisantes" << endl;
        cout << nom << " s'est échappé..." << endl;
        cout << endl << "-----Fin du combat-----" << endl << endl;
    }
    else if (balles > 0) {
        cout << "Nombre de balles restantes: " << balles << endl;
        cout << "Voulez-vous le capturer? (Y/N)" << endl;
        char question;
        cin >> question;
        if (question == 'y' || question == 'Y') {
            cout << "balle lancée!" << endl;
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
                        cout << nom << " capturé!" << endl;
                        chance = 1;
                        cout << endl << "-----Fin du combat-----" << endl << endl;
                    }
                }
            }
            if (chance != 1) {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                cout << nom << " s'est échappé de la balle..." << endl;
                cout << endl;
                capture();
            }

        }
        else if (question == 'n' || question == 'N') {
            cout << nom << " s'est échappé..." << endl;
            cout << endl << "-----Fin du combat-----" << endl << endl;
        }
    }
}
