#include "joueur.h"

Joueur::Joueur(int x0, int y0)
{
    initialiserJoueur(x0, y0);
    creerTerrain();
}

Joueur::~Joueur()
{
    listeGenimons.vider();
}

void Joueur::initialiserJoueur(int pos_x, int pos_y)
{
    position_x = pos_x;
    position_y = pos_y;
    anciennePosition_x = pos_x;
    anciennePosition_y = pos_y;

    borne_x_min = 0;
    borne_y_min = 0;
    borne_x_max = 21;
    borne_y_max = 21;
    nomTerrain = "         Exterieur de la faculte";
    estExterieur = true;
}

void Joueur::changerTerrain()
{
    if (estExterieur)
    {
        borne_x_min = 21;
        borne_y_min = 0;
        borne_x_max = 37;
        borne_y_max = 14;
        nomTerrain = "    Interieur de la faculte";
        estExterieur = false;
        position_x += 2;
    }
    else
    {
        borne_x_min = 0;
        borne_y_min = 0;
        borne_x_max = 21;
        borne_y_max = 21;
        nomTerrain = "         Exterieur de la faculte";
        estExterieur = true;
        position_x -= 2;
    }
}

void Joueur::creerTerrain()
{
    srand(time(0));
    for (int y = 0; y < dimensionTerrain_y; y++) {
        for (int x = 0; x < dimensionTerrain_x; x++) {
            terrain[x][y] = '.';
            if ((x == 20 || x == 21) && (y == 11 || y == 10 || y == 9))
            {
                terrain[x][y] = 'X';
            }
        }
    }
    terrain[position_x][position_y] = '1';

    //On crée 6 Genimons au début
    for (int i = 0; i < 6; i++)
    {
        ajouterGenimon(false);
    }
}

bool Joueur::estSurGenimon()
{
    return terrain[position_x][position_y] == '2';
}

bool Joueur::estSurPorte()
{
    return terrain[position_x][position_y] == 'X';
}

void Joueur::ajouterGenimon(bool refresh)
{
    Genimon* nouveauGenimon = new Genimon;
    listeGenimons.ajouterElement(nouveauGenimon);

    srand(time(0));
    int pos_x = rand() % dimensionTerrain_x;
    int pos_y  = rand() % dimensionTerrain_y;

    //Genimon n'apparait pas sur un objet
    while (terrain[pos_x][pos_y] == '1' || terrain[pos_x][pos_y] == 'X' || terrain[pos_x][pos_y] == '2')
    {
        srand(time(0));
        pos_x = rand() % dimensionTerrain_x;
        pos_y = rand() % dimensionTerrain_y;
    }
    listeGenimons[listeGenimons.Taille() - 1]->position_x = pos_x;
    listeGenimons[listeGenimons.Taille() - 1]->position_y = pos_y;
    terrain[pos_x][pos_y] = '2';

    if (refresh)
    {
        afficherPartie();
    }
}

void Joueur::retirerGenimon(bool refresh)
{
    srand(time(0));
    int indexRandom = rand() % listeGenimons.Taille(); //Retire un genimon random
    terrain[listeGenimons[indexRandom]->position_x][listeGenimons[indexRandom]->position_y] = '.';
    listeGenimons.retirerElement(indexRandom);
}

void Joueur::deplacerGenimons(bool refresh)
{
    srand(time(0));
    int indexGenimon = rand() % listeGenimons.Taille(); //index random

    srand(time(0));
    int possibilié = rand() % 4;
    int deltaX = 0;
    int deltaY = 0;
    //Cas généraux
    if (possibilié == 0)
    {
        deltaX = 1;
        deltaY = 1;
    }
    else if (possibilié == 1)
    {
        deltaX = -1;
        deltaY = -1;
    }
    else if (possibilié == 2)
    {
        deltaX = 1;
        deltaY = -1;
    }
    else if (possibilié == 3)
    {
        deltaX = -1;
        deltaY = 1;
    }

    //Cas de hors terrain
    if (position_x == dimensionTerrain_x - 1 || position_y == dimensionTerrain_y - 1)
    {
        deltaX = -1;
        deltaY = -1;
    }
    if (position_x == 0 || position_y == 0)
    {
        deltaX = 1;
        deltaY = 1;
    }

    int prochainePositionX = listeGenimons[indexGenimon]->position_x + deltaX;
    int prochainePositionY = listeGenimons[indexGenimon]->position_y + deltaY;
    //Test pour ne pas écraser des objets
    if (terrain[prochainePositionX][prochainePositionY] != '1' && terrain[prochainePositionX][prochainePositionY] != 'X'
        && terrain[prochainePositionX][prochainePositionY] != '2')
    {
        terrain[listeGenimons[indexGenimon]->position_x][listeGenimons[indexGenimon]->position_y] = '.';
        listeGenimons[indexGenimon]->position_x = prochainePositionX;
        listeGenimons[indexGenimon]->position_y = prochainePositionY;
        terrain[listeGenimons[indexGenimon]->position_x][listeGenimons[indexGenimon]->position_y] = '2';

        if (refresh)
        {
            afficherPartie();
        }
    }
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

    //recherche du genimon
    Genimon* genimon = listeGenimons[0]; //par défaut
    bool genimonTrouve = false;
    int indexGenimon = 0;
    for (int i = 0; i < listeGenimons.Taille(); i++)
    {
        if (listeGenimons[i]->position_x == position_x && listeGenimons[i]->position_y == position_y)
        {
            genimon = listeGenimons[i];
            indexGenimon = i;
            genimonTrouve = true;
        }
    }

    if (genimonTrouve)
    {
        //Combat contre genimon
        genimon->apparait();
        int typeGenimon = genimon->getTypeNumérique();
        historique.push_back(*genimon);

        genimon->capture();
        if (genimon->getEtat() == "capture")
        {
            genidex[typeGenimon].listeGenimonAttrapé.push_back(*genimon);
        }

        listeGenimons.retirerElement(indexGenimon); //Le genimon n'est plus sur le terrain

        //Gère le retour au jeu
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
}

void Joueur::consulterDétailsType(int typeNumérique, string type)
{
    int tailleListe = genidex[typeNumérique].listeGenimonAttrapé.size();
    cout << "Details pour le type: " << type << endl;

    if (tailleListe == 0)
    {
        cout << "Aucun Genimon pour ce type" << endl;
    }

    for (int i = 0; i < tailleListe; i++)
    {
        cout << i << ") " << "Nom: " << genidex[typeNumérique].listeGenimonAttrapé[i].getNom() << "\n   Type: " << genidex[typeNumérique].listeGenimonAttrapé[i].getType();
        cout << "\n   Rarete: " << genidex[typeNumérique].listeGenimonAttrapé[i].getRareté() << endl;
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
        cout << "Nombre de Genimon de type informatique captures: " << genidex[0].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(0, "informatique");
    }
    else if (type == 'e' || type == 'E')
    {
        cout << "Nombre de Genimon de type electrique captures: " << genidex[1].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(1, "electrique");
    }
    else if (type == 'r' || type == 'R')
    {
        cout << "Nombre de Genimon de type robotique captures: " << genidex[2].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(2, "robotique");
    }
    else if (type == 'm' || type == 'M')
    {
        cout << "Nombre de Genimon de type mecanique captures: " << genidex[3].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(3, "mecanique");
    }
    else if (type == 'c' || type == 'C')
    {
        cout << "Nombre de Genimon de type civil captures: " << genidex[4].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(4, "civil");
    }
    else if (type == 'b' || type == 'B')
    {
        cout << "Nombre de Genimon de type batiment captures: " << genidex[5].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(5, "batiment");
    }
    else if (type == 't' || type == 'T')
    {
        cout << "Nombre de Genimon de type bioTech captures: " << genidex[6].listeGenimonAttrapé.size() << endl;
        demanderInformationsGenimon(6, "bioTech");
    }
    else if (type == 'q' || type == 'Q')
    {
        cout << "Nombre de Genimon de type chimique captures: " << genidex[7].listeGenimonAttrapé.size() << endl;;
        demanderInformationsGenimon(7, "chimique");
    }

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::consulterGenidexComplet()
{
    cout << "Nombre de Genimon de type informatique captures: " << genidex[0].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(0, "informatique");
   
    cout << "Nombre de Genimon de type electrique captures: " << genidex[1].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(1, "electrique");
    
    cout << "Nombre de Genimon de type robotique captures: " << genidex[2].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(2, "robotique");
    
    cout << "Nombre de Genimon de type mecanique captures: " << genidex[3].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(3, "mecanique");
    
    cout << "Nombre de Genimon de type civil captures: " << genidex[4].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(4, "civil");
    
    cout << "Nombre de Genimon de type batiment captures: " << genidex[5].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(5, "batiment");
   
    cout << "Nombre de Genimon de type bioTech captures: " << genidex[6].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(6, "bioTech");
    
    cout << "Nombre de Genimon de type chimique captures: " << genidex[7].listeGenimonAttrapé.size() << endl;
    consulterDétailsType(7, "chimique");

    cout << "Choisissez une option du menu pour lancer une autre recherche ou pour fermer le Genidex" << endl;
}

void Joueur::consulterHistorique()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                             Historique des rencontres                            " << endl;
    cout << "----------------------------------------------------------------------------------" << endl << endl;

    if (historique.size() == 0)
    {
        cout << "Aucun Genimon rencontre" << endl;
    }

    for (int i = 0; i < historique.size(); i++)
    {
        cout << i << ") " << "Nom: " << historique[i].getNom() << ", Type: " << historique[i].getType();
        cout << ", Rarete: " << historique[i].getRareté() << endl;
    }

    cout << "\nAppuyez sur --F-- pour fermer l'historique" << endl;
}

void Joueur::afficherPartie() {
    #ifdef _WIN32
        system("cls");
    #endif

    afficherMenuPrincipal();

    cout << "\n" << nomTerrain << endl << endl;

    //Mise à jour de la position
    if (terrain[anciennePosition_x][anciennePosition_y] != 'X')
    {
        terrain[anciennePosition_x][anciennePosition_y] = '.'; //On ne détruit pas les portes
    }
    terrain[position_x][position_y] = '1';
    anciennePosition_x = position_x;
    anciennePosition_y = position_y;

    //Affichage du terrain
    for (int y = borne_y_min; y < borne_y_max; y++) {
        for (int x = borne_x_min; x < borne_x_max; x++) {
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
    cout << "                        Pour voir l'historique des rencontres: --H--              " << endl;
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