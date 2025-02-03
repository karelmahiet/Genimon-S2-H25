#include "joueur.h"

Joueur::Joueur(int x0, int y0) {
    initialiserPosition(x0, y0);
    creerTerrain();
}

void Joueur::initialiserPosition(int x0, int y0)
{
    position_x = x0;
    position_y = y0;
    anciennePosition_x = x0;
    anciennePosition_y = y0;
}

void Joueur::creerTerrain()
{
    srand(time(0));
    for (int y = 0; y < dimensionTerrain; y++) {
        for (int x = 0; x < dimensionTerrain; x++) {
            terrain[x][y] = '.';
            if ((rand() % 20) == 1) {
                terrain[x][y] = '2';
            }
            if (x == 20 && (y == 11 || y == 10 || y == 9))
            {
                terrain[x][y] = 'X';
            }
        }
    }
    terrain[position_x][position_y] = '1';
}

void Joueur::reinitialiserGenidex()
{
    for (int i = 0; i < 8; i++)
    {
        genidex[i].nbGenimonRencontr� = 0;
        genidex[i].nbGenimonAttrap�s = 0;
        genidex[i].listeGenimonRencontr�.clear();
    }
}

bool Joueur::estSurGenimon()
{
    return terrain[position_x][position_y] == '2';
}

void Joueur::gererGenimon()
{
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                               Duel contre un Genimon !                           " << endl << endl;
    cout << "                         Vous avez 5 chances pour l'attraper                      " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    Genimon genimon;
    genimon.apparait();
    int typeGenimon = genimon.getTypeNum�rique();
    genidex[typeGenimon].nbGenimonRencontr�++;
    genidex[typeGenimon].listeGenimonRencontr�.push_back(genimon);

    genimon.capture();
    if (genimon.getEtat() == "capture")
    {
        genidex[typeGenimon].nbGenimonAttrap�s++;
        //R�glage de bogue sur l'�tat
        int index = genidex[typeGenimon].listeGenimonRencontr�.size() - 1;
        genidex[typeGenimon].listeGenimonRencontr�[index].setEtat("capture");
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
        else
        {
            cout << "Touche invalide" << endl;
            cout << "Appuyez sur --R-- pour revenir au jeu" << endl;
        }
    }
}

void Joueur::consulterD�tailsType(int typeNum�rique, string type)
{
    int tailleListe = genidex[typeNum�rique].listeGenimonRencontr�.size();
    cout << "Details pour le type: " << type << endl;

    if (tailleListe == 0)
    {
        cout << "Aucun Genimon pour ce type" << endl;
    }

    for (int i = 0; i < tailleListe; i++)
    {
        cout << i << ") " << "Nom: " << genidex[typeNum�rique].listeGenimonRencontr�[i].getNom() << "\n   Type: " << genidex[typeNum�rique].listeGenimonRencontr�[i].getType();
        cout << "\n   Rarete: " << genidex[typeNum�rique].listeGenimonRencontr�[i].getRaret�() << "\n   Etat: " << genidex[typeNum�rique].listeGenimonRencontr�[i].getEtat() << endl;
    }

    cout << endl;
}

void Joueur::demanderInformationsGenimon(int typeNum�rique, string type)
{
    cout << "Voulez-vous consulter les informations de chaque Genimon? (O/N)" << endl;
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();
        if (touche == 'o' || touche == 'O')
        {
            consulterD�tailsType(typeNum�rique, type);
            operationFinie = true;
        }
        else if (touche == 'n' || touche == 'N')
        {
            cout << "----Informations non desires----" << endl << endl;
            operationFinie = true;
        }
        else
        {
            cout << "Touche invalide" << endl;
        }
    }
}

void Joueur::consulterGenidexPartiel(char type)
{
    if (type == 'i' || type == 'I')
    {
        cout << "Nombre de Genimon de type informatique rencontres: " << genidex[0].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type informatique rencontres et captures: " << genidex[0].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(0, "informatique");
    }
    else if (type == 'e' || type == 'E')
    {
        cout << "Nombre de Genimon de type electrique rencontres: " << genidex[1].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type electrique rencontres et captures: " << genidex[1].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(1, "electrique");
    }
    else if (type == 'r' || type == 'R')
    {
        cout << "Nombre de Genimon de type robotique rencontres: " << genidex[2].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type robotique rencontres et captures: " << genidex[2].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(2, "robotique");
    }
    else if (type == 'm' || type == 'M')
    {
        cout << "Nombre de Genimon de type mecanique rencontres: " << genidex[3].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type mecanique rencontres et captures: " << genidex[3].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(3, "mecanique");
    }
    else if (type == 'c' || type == 'C')
    {
        cout << "Nombre de Genimon de type civil rencontres: " << genidex[4].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type civil rencontres et captures: " << genidex[4].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(4, "civil");
    }
    else if (type == 'b' || type == 'B')
    {
        cout << "Nombre de Genimon de type batiment rencontres: " << genidex[5].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type batiment rencontres et captures: " << genidex[5].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(5, "batiment");
    }
    else if (type == 't' || type == 'T')
    {
        cout << "Nombre de Genimon de type bioTech rencontres: " << genidex[6].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type bioTech rencontres et captures: " << genidex[6].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(6, "bioTech");
    }
    else if (type == 'q' || type == 'Q')
    {
        cout << "Nombre de Genimon de type chimique rencontres: " << genidex[7].nbGenimonRencontr� << endl;
        cout << "Nombre de Genimon de type chimique rencontres et captures: " << genidex[7].nbGenimonAttrap�s << endl;
        demanderInformationsGenimon(7, "chimique");
    }

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::consulterGenidexComplet()
{
    cout << "Nombre de Genimon de type informatique rencontres: " << genidex[0].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type informatique rencontres et captures: " << genidex[0].nbGenimonAttrap�s << endl;
    consulterD�tailsType(0, "informatique");
   
    cout << "Nombre de Genimon de type electrique rencontres: " << genidex[1].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type electrique rencontres et captures: " << genidex[1].nbGenimonAttrap�s << endl;
    consulterD�tailsType(1, "electrique");
    
    cout << "Nombre de Genimon de type robotique rencontres: " << genidex[2].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type robotique rencontres et captures: " << genidex[2].nbGenimonAttrap�s << endl;
    consulterD�tailsType(2, "robotique");
    
    cout << "Nombre de Genimon de type mecanique rencontres: " << genidex[3].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type mecanique rencontres et captures: " << genidex[3].nbGenimonAttrap�s << endl;
    consulterD�tailsType(3, "mecanique");
    
    cout << "Nombre de Genimon de type civil rencontres: " << genidex[4].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type civil rencontres et captures: " << genidex[4].nbGenimonAttrap�s << endl;
    consulterD�tailsType(4, "civil");
    
    cout << "Nombre de Genimon de type batiment rencontres: " << genidex[5].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type batiment rencontres et captures: " << genidex[5].nbGenimonAttrap�s << endl;
    consulterD�tailsType(5, "batiment");
   
    cout << "Nombre de Genimon de type bioTech rencontres: " << genidex[6].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type bioTech rencontres et captures: " << genidex[6].nbGenimonAttrap�s << endl;
    consulterD�tailsType(6, "bioTech");
    
    cout << "Nombre de Genimon de type chimique rencontres: " << genidex[7].nbGenimonRencontr� << endl;
    cout << "Nombre de Genimon de type chimique rencontres et captures: " << genidex[7].nbGenimonAttrap�s << endl;
    consulterD�tailsType(7, "chimique");

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::afficherPartie() {
    #ifdef _WIN32
        system("cls");
    #endif

    afficherMenuPrincipal();

    cout << "\n         Exterieur de la faculte" << endl << endl;

    //Mise � jour de la position
    terrain[anciennePosition_x][anciennePosition_y] = '.';
    terrain[position_x][position_y] = '1';
    anciennePosition_x = position_x;
    anciennePosition_y = position_y;

    //Affichage du terrain
    for (int y = 0; y < dimensionTerrain; y++) {
        for (int x = 0; x < dimensionTerrain; x++) {
            cout << terrain[x][y] << " ";
        }
        cout << endl;
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
    cout << "                      Pour visualiser une categorie du Genidex: --C--             " << endl;
    cout << "                      Pour visualiser l'ensemble du Genidex: --E--                " << endl;
    cout << "                      Pour fermer le Genidex: --F--                               " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}