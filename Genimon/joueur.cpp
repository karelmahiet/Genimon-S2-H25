#include "joueur.h"

Joueur::Joueur(int x0, int y0) {
    position_x = x0;
    position_y = y0;
    arret = 0;
    srand(time(0));
    for (int y = 9; y > 0; y--) {
        for (int x = 0; x < 9; x++) {
            position[x][y] = 0;
            if ((rand() % 10) == 1) {
                position[x][y] = 2;
            }
        }
    }
    position[position_x][position_y] = 1;
}

void Joueur::deplacement() {
    if (_kbhit()) {
        char direction = _getch();
        if (direction == 'a' && position_x > 0) {
            position_x--;
        }
        else if (direction == 'd' && position_x < 8) {
            position_x++;
        }
        else if (direction == 's' && position_y > 1) {
            position_y--;
        }
        else if (direction == 'w' && position_y < 9) {
            position_y++;
        }
        else if (direction == 'z') {
            std::cout << "Programme arrêté" << std::endl;
            exit(0);
        }
        else {
            std::cout << "Direction invalide" << std::endl;
        }

        if (position[position_x][position_y] == 2) {
            Genimon genimon1;
            genimon1.apparait();
            genimon1.capture();
        }

        afficher();
    }
}

void Joueur::afficher() {
#ifdef _WIN32
    system("cls");
#endif

    for (int y = 9; y > 0; y--) {
        for (int x = 0; x < 9; x++) {
            if (position[x][y] == 1) {
                position[x][y] = 0;
            }
        }
    }
    position[position_x][position_y] = 1;

    for (int y = 9; y > 0; y--) {
        for (int x = 0; x < 9; x++) {
            std::cout << position[x][y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "wasd pour se deplacer, z pour sortir" << std::endl;
}