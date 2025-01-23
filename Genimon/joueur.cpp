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
        else if (direction == 'q') {
            cout << endl << "---Ouverture du Genidex----" << endl;
            consultegenidex();
        }
        else if (direction == 'z') {
            std::cout << "arret programme" << std::endl;
            exit(0);
        }
        else {
            std::cout << "Direction invalide" << std::endl;
        }

        if (position[position_x][position_y] == 2) {
            Genimon genimon1;
            genimon1.apparait();
            a_genimon = genimon1.a_nom();
            if (a_genimon == 0) { a_genidex[0]++; }
            if (a_genimon == 1) { a_genidex[1]++; }
            if (a_genimon == 2) { a_genidex[2]++; }
            if (a_genimon == 3) { a_genidex[3]++; }
            if (a_genimon == 4) { a_genidex[4]++; }
            if (a_genimon == 5) { a_genidex[5]++; }
            if (a_genimon == 6) { a_genidex[6]++; }
            if (a_genimon == 7) { a_genidex[7]++; }
            genimon1.capture();
            c_genimon = genimon1.c_nom();
            if (c_genimon == 1) { c_genidex[a_genimon]++; }
            }

        afficher();
    }
}

void Joueur::consultegenidex() {
    if ((a_genidex[0]) != 0) {
        cout << "Nombre de Alexis rencontrés: " << a_genidex[0] << endl;
        cout << "Nombre de Alexis capturés: " << c_genidex[0] << endl;
    }
    if ((a_genidex[1]) != 0) {
        cout << "Nombre de Florian rencontrés: " << a_genidex[1] << endl;
        cout << "Nombre de Florian capturés: " << c_genidex[1] << endl;
    }
    if ((a_genidex[2]) != 0) {
        cout << "Nombre de Dylan rencontrés: " << a_genidex[2] << endl;
        cout << "Nombre de Dylan capturés: " << c_genidex[2] << endl;
    }
    if ((a_genidex[3]) != 0) {
        cout << "Nombre de Vincent rencontrés: " << a_genidex[3] << endl;
        cout << "Nombre de Vincent capturés: " << c_genidex[3] << endl;
    }
    if ((a_genidex[4]) != 0) {
        cout << "Nombre de Marek rencontrés: " << a_genidex[4] << endl;
        cout << "Nombre de Marek capturés: " << c_genidex[4] << endl;
    }
    if ((a_genidex[5]) != 0) {
        cout << "Nombre de Karel rencontrés: " << a_genidex[5] << endl;
        cout << "Nombre de Karel capturés: " << c_genidex[5] << endl;
    }
    if ((a_genidex[6]) != 0) {
        cout << "Nombre de Darnley rencontrés: " << a_genidex[6] << endl;
        cout << "Nombre de Darnley capturés: " << c_genidex[6] << endl;
    }
    if ((a_genidex[7]) != 0) {
        cout << "Nombre de Jérémie rencontrés: " << a_genidex[7] << endl;
        cout << "Nombre de Jérémie capturés: " << c_genidex[7] << endl;
    }
    cout << "----Fermeture du Genidex----" << endl << endl;
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

    std::cout << "wasd pour se deplacer, z pour sortir, q pour genidex" << std::endl;
}