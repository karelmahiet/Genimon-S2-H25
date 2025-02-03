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
        genidex[i].nbGenimonRencontré = 0;
        genidex[i].nbGenimonAttrapés = 0;
        genidex[i].listeGenimonRencontré.clear();
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
    int typeGenimon = genimon.getTypeNumérique();
    genidex[typeGenimon].nbGenimonRencontré++;
    genidex[typeGenimon].listeGenimonRencontré.push_back(genimon);

    genimon.capture();
    if (genimon.getEtat() == "capture")
    {
        genidex[typeGenimon].nbGenimonAttrapés++;
        //Réglage de bogue sur l'état
        int index = genidex[typeGenimon].listeGenimonRencontré.size() - 1;
        genidex[typeGenimon].listeGenimonRencontré[index].setEtat("capture");
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

void Joueur::consulterDétailsType(int typeNumérique, string type)
{
    int tailleListe = genidex[typeNumérique].listeGenimonRencontré.size();
    cout << "Details pour le type: " << type << endl;

    if (tailleListe == 0)
    {
        cout << "Aucun Genimon pour ce type" << endl;
    }

    for (int i = 0; i < tailleListe; i++)
    {
        cout << i << ") " << "Nom: " << genidex[typeNumérique].listeGenimonRencontré[i].getNom() << "\n   Type: " << genidex[typeNumérique].listeGenimonRencontré[i].getType();
        cout << "\n   Rarete: " << genidex[typeNumérique].listeGenimonRencontré[i].getRareté() << "\n   Etat: " << genidex[typeNumérique].listeGenimonRencontré[i].getEtat() << endl;
    }

    cout << endl;
}

void Joueur::demanderInformationsGenimon(int typeNumérique, string type)
{
    cout << "Voulez-vous consulter les informations de chaque Genimon? (O/N)" << endl;
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();
        if (touche == 'o' || touche == 'O')
        {
            consulterDétailsType(typeNumérique, type);
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
        cout << "Nombre de Genimon de type informatique rencontres: " << genidex[0].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type informatique rencontres et captures: " << genidex[0].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(0, "informatique");
    }
    else if (type == 'e' || type == 'E')
    {
        cout << "Nombre de Genimon de type electrique rencontres: " << genidex[1].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type electrique rencontres et captures: " << genidex[1].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(1, "electrique");
    }
    else if (type == 'r' || type == 'R')
    {
        cout << "Nombre de Genimon de type robotique rencontres: " << genidex[2].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type robotique rencontres et captures: " << genidex[2].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(2, "robotique");
    }
    else if (type == 'm' || type == 'M')
    {
        cout << "Nombre de Genimon de type mecanique rencontres: " << genidex[3].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type mecanique rencontres et captures: " << genidex[3].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(3, "mecanique");
    }
    else if (type == 'c' || type == 'C')
    {
        cout << "Nombre de Genimon de type civil rencontres: " << genidex[4].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type civil rencontres et captures: " << genidex[4].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(4, "civil");
    }
    else if (type == 'b' || type == 'B')
    {
        cout << "Nombre de Genimon de type batiment rencontres: " << genidex[5].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type batiment rencontres et captures: " << genidex[5].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(5, "batiment");
    }
    else if (type == 't' || type == 'T')
    {
        cout << "Nombre de Genimon de type bioTech rencontres: " << genidex[6].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type bioTech rencontres et captures: " << genidex[6].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(6, "bioTech");
    }
    else if (type == 'q' || type == 'Q')
    {
        cout << "Nombre de Genimon de type chimique rencontres: " << genidex[7].nbGenimonRencontré << endl;
        cout << "Nombre de Genimon de type chimique rencontres et captures: " << genidex[7].nbGenimonAttrapés << endl;
        demanderInformationsGenimon(7, "chimique");
    }

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::consulterGenidexComplet()
{
    cout << "Nombre de Genimon de type informatique rencontres: " << genidex[0].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type informatique rencontres et captures: " << genidex[0].nbGenimonAttrapés << endl;
    consulterDétailsType(0, "informatique");
   
    cout << "Nombre de Genimon de type electrique rencontres: " << genidex[1].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type electrique rencontres et captures: " << genidex[1].nbGenimonAttrapés << endl;
    consulterDétailsType(1, "electrique");
    
    cout << "Nombre de Genimon de type robotique rencontres: " << genidex[2].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type robotique rencontres et captures: " << genidex[2].nbGenimonAttrapés << endl;
    consulterDétailsType(2, "robotique");
    
    cout << "Nombre de Genimon de type mecanique rencontres: " << genidex[3].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type mecanique rencontres et captures: " << genidex[3].nbGenimonAttrapés << endl;
    consulterDétailsType(3, "mecanique");
    
    cout << "Nombre de Genimon de type civil rencontres: " << genidex[4].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type civil rencontres et captures: " << genidex[4].nbGenimonAttrapés << endl;
    consulterDétailsType(4, "civil");
    
    cout << "Nombre de Genimon de type batiment rencontres: " << genidex[5].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type batiment rencontres et captures: " << genidex[5].nbGenimonAttrapés << endl;
    consulterDétailsType(5, "batiment");
   
    cout << "Nombre de Genimon de type bioTech rencontres: " << genidex[6].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type bioTech rencontres et captures: " << genidex[6].nbGenimonAttrapés << endl;
    consulterDétailsType(6, "bioTech");
    
    cout << "Nombre de Genimon de type chimique rencontres: " << genidex[7].nbGenimonRencontré << endl;
    cout << "Nombre de Genimon de type chimique rencontres et captures: " << genidex[7].nbGenimonAttrapés << endl;
    consulterDétailsType(7, "chimique");

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::afficherPartie() {
    #ifdef _WIN32
        system("cls");
    #endif

    afficherMenuPrincipal();

    cout << "\n         Exterieur de la faculte" << endl << endl;

    //Mise à jour de la position
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