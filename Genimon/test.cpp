#include "joueur.h"


int main() {
    Joueur J1;

    J1.afficher();
    while (true) {
        J1.deplacement();
    }

    return 0;
}
