#include "joueur.h"

enum Etat
{
    Initialise, GeniDex, EnCours, EnPause, Termine
};

enum Etat etatJeu = Initialise;
Joueur joueur;
bool enDécision;

void afficherBienvenue()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                            Bienvenu dans Genimon!                                " << endl << endl;
    cout << "          Promenez-vous dans la faculte de genie et rencontrer des                " << endl;
    cout << "          Genimons. Combattez-les pour tentez de les capturer et de les           " << endl;
    cout << "          ajouter a votre Genidex. Une aventure passionnante vous attend.         " << endl << endl;
    cout << "                                Bonne chasse!                                     " << endl << endl << endl;
    cout << "                        Pour demarer le jeu: --D--                           " << endl;
    cout << "                        Pour sortir du jeu: --Z--                                 " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void afficherConfirmation()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                  Voulez-vous vraiment mettre fin a la partie?                    " << endl;
    cout << "                  Si vous confirmez, votre progression sera perdu.                " << endl << endl << endl;
    cout << "                               Pour confirmer: --C--                              " << endl;
    cout << "                               Pour annuler: --A--                                " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void gererInitialisation()
{
    char touche = _getch();

    if (touche == 'd' || touche == 'D')
    {
        etatJeu = EnCours;
        enDécision = false;
    }
    else if (touche == 'z' || touche == 'Z')
    {
        etatJeu = Termine;
        enDécision = false;
    }
    else
    {
        cout << "Touche invalide" << endl;
    }
}

void gererConfirmation(int option)
{
    char touche = _getch();

    if (touche == 'c' || touche == 'C')
    {
        if (option == 1)
        {
            etatJeu = Initialise;
        }
        else
        {
            etatJeu = Termine;
        }
        enDécision = false;
    }
    else if (touche == 'a' || touche == 'A')
    {
        enDécision = false;
    }
    else
    {
        cout << "Touche invalide" << endl;
    }

}

void gererClavier()
{
    if (_kbhit()) {
        char touche = _getch();

        if (touche == 'a' && joueur.position_x > 0) {
            joueur.position_x--;
        }
        else if (touche == 'd' && joueur.position_x < 8) {
            joueur.position_x++;
        }
        else if (touche == 's' && joueur.position_y > 1) {
            joueur.position_y--;
        }
        else if (touche == 'w' && joueur.position_y < 9) {
            joueur.position_y++;
        }
        else if (touche == 'g' || touche == 'G') {
            joueur.consultegenidex();
        }
        else if (touche == ' ') {
            //etatJeu = EnPause;
        }
        else if (touche == 'r' || touche == 'R') {
            #ifdef _WIN32
                   system("cls");
            #endif
            afficherConfirmation();
            while (enDécision)
            {
                gererConfirmation(1);
            }
            if (etatJeu == EnCours) //Si il y a une annulation
            {
                enDécision = true;
            }
        }
        else if (touche == 'z' || touche == 'Z') {
            #ifdef _WIN32
                   system("cls");
            #endif
            afficherConfirmation();
            while (enDécision)
            {
                gererConfirmation(2);
            }
            if (etatJeu == EnCours) //Si il y a une annulation
            {
                enDécision = true;
            }
        }

        if (joueur.estSurGeniMon()) {
            joueur.gererGenimon();
        }

        if (etatJeu == EnCours)
        {
            joueur.afficherPartie();
        }
    }
}

int main() {
    while (true)
    {
        switch (etatJeu)
        {
        case Initialise:
            #ifdef _WIN32
                   system("cls");
            #endif
            afficherBienvenue();
            enDécision = true;
            joueur.initialiserPosition(4, 5); //Si il y a une réinitialisation
            joueur.creerTerrain(); //Si il y a une réinitialisation
            while (enDécision)
            {
                gererInitialisation();
            }
            break;
        case GeniDex:
            // À implémener
            break;
        case EnCours:
            joueur.afficherPartie();
            enDécision = true;
            while (enDécision)
            {
                gererClavier();
            }
            break;
        case EnPause:
            // À implémenter
            break;
        case Termine:
            cout << "----------------------------------------------------------------------------------" << endl;
            cout << "                               ...Fin du jeu...                             " << endl;
            exit(0);
            break;
        default:
            break;
        }
    }

    return 0;
}

