#include "joueur.h"

Joueur::Joueur(int x0, int y0) {
    initialiserPosition(x0, y0);
    creerTerrain();
}

void Joueur::initialiserPosition(int x0, int y0)
{
    position_x = x0;
    position_y = y0;
}

void Joueur::creerTerrain()
{
    srand(time(0));
    for (int y = 9; y > 0; y--) {
        for (int x = 0; x < 9; x++) {
            terrain[x][y] = 0;
            if ((rand() % 10) == 1) {
                terrain[x][y] = 2;
            }
        }
    }
    terrain[position_x][position_y] = 1;
}

bool Joueur::estSurGeniMon()
{
    return terrain[position_x][position_y] == 2;
}

void Joueur::gererGenimon()
{
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                               Duel contre un GeniMon !                           " << endl << endl;
    cout << "                         Vous avez 5 chances pour l'attraper                      " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

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
    if (c_genimon == 1)
    {
        c_genidex[a_genimon]++;
    }

    bool retourJeu = false;
    char touche;
    cout << "Appuyez sur --R-- pour revenir au jeu" << endl;
    while (!retourJeu)
    {
        touche = _getch();
        if (touche == 'r' || touche == 'R')
        {
            retourJeu = true;
        }
    }
}

void Joueur::consulterGenidexPartiel(char type)
{
    if (type == 'i' || type == 'I')
    {
        cout << "Nombre de Jeremie rencontres: " << a_genidex[7] << endl;
        cout << "Nombre de Jeremie captures: " << c_genidex[7] << endl;
    }
    else if (type == 'e' || type == 'E')
    {
        cout << "Nombre de Vincent rencontres: " << a_genidex[3] << endl;
        cout << "Nombre de Vincent captures: " << c_genidex[3] << endl;
    }
    else if (type == 'r' || type == 'R')
    {
        cout << "Nombre de Karel rencontres: " << a_genidex[5] << endl;
        cout << "Nombre de Karel captures: " << c_genidex[5] << endl;
    }
    else if (type == 'm' || type == 'M')
    {
        cout << "Nombre de Dylan rencontres: " << a_genidex[2] << endl;
        cout << "Nombre de Dylan captures: " << c_genidex[2] << endl;
    }
    else if (type == 'c' || type == 'C')
    {
        cout << "Nombre de Alexis rencontres: " << a_genidex[0] << endl;
        cout << "Nombre de Alexis captures: " << c_genidex[0] << endl;
    }
    else if (type == 'b' || type == 'B')
    {
        cout << "Nombre de Marek rencontres: " << a_genidex[4] << endl;
        cout << "Nombre de Marek captures: " << c_genidex[4] << endl;
    }
    else if (type == 't' || type == 'T')
    {
        cout << "Nombre de Florian rencontres: " << a_genidex[1] << endl;
        cout << "Nombre de Florian captures: " << c_genidex[1] << endl;
    }
    else if (type == 'q' || type == 'Q')
    {
        cout << "Nombre de Darnley rencontres: " << a_genidex[6] << endl;
        cout << "Nombre de Darnley captures: " << c_genidex[6] << endl;
    }
}

void Joueur::consulterGenidexComplet() {
    cout << "Nombre de Alexis rencontres: " << a_genidex[0] << endl;
    cout << "Nombre de Alexis captures: " << c_genidex[0] << endl << endl;

    cout << "Nombre de Florian rencontres: " << a_genidex[1] << endl;
    cout << "Nombre de Florian captures: " << c_genidex[1] << endl << endl;

    cout << "Nombre de Dylan rencontres: " << a_genidex[2] << endl;
    cout << "Nombre de Dylan captures: " << c_genidex[2] << endl << endl;

    cout << "Nombre de Vincent rencontres: " << a_genidex[3] << endl;
    cout << "Nombre de Vincent captures: " << c_genidex[3] << endl << endl;

    cout << "Nombre de Marek rencontres: " << a_genidex[4] << endl;
    cout << "Nombre de Marek captures: " << c_genidex[4] << endl << endl;

    cout << "Nombre de Karel rencontres: " << a_genidex[5] << endl;
    cout << "Nombre de Karel captures: " << c_genidex[5] << endl << endl;

    cout << "Nombre de Darnley rencontres: " << a_genidex[6] << endl;
    cout << "Nombre de Darnley captures: " << c_genidex[6] << endl << endl;

    cout << "Nombre de Jeremie rencontres: " << a_genidex[7] << endl;
    cout << "Nombre de Jeremie captures: " << c_genidex[7] << endl << endl;
}

void Joueur::afficherPartie() {
    #ifdef _WIN32
        system("cls");
    #endif

    afficherMenuPrincipal();

    for (int y = 9; y > 0; y--) {
        for (int x = 0; x < 9; x++) {
            if (terrain[x][y] == 1) {
                terrain[x][y] = 0;
            }
        }
    }
    terrain[position_x][position_y] = 1;

    for (int y = 9; y > 0; y--) {
        for (int x = 0; x < 9; x++) {
            std::cout << terrain[x][y] << " ";
        }
        std::cout << std::endl;
    }
}

void Joueur::afficherMenuPrincipal()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                 Menu Principal                                   " << endl << endl;
    cout << "                        Pour ouvrir le Genidex: --G--                             " << endl;
    cout << "                        Pour mettre le jeu en pause: --ESPACE--                   " << endl;
    cout << "                        Pour reinitialiser le jeu: --R--                          " << endl;
    cout << "                        Pour sortir du jeu: --Z--                                 " << endl << endl << endl;
    cout << "                 Utilisez les touches w,a,s,d pour vous deplacer                  " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void Joueur::afficherMenuGeniedex()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                  Menu Genidex                                    " << endl << endl;
    cout << "                      Pour visualiser une categorie du Genidex: --V--             " << endl;
    cout << "                      Pour visualiser l'ensemble du Genidex: --E--                " << endl;
    cout << "                      Pour fermer le Genidex: --F--                               " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}