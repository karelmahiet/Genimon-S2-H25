#include "joueur.h"

enum Etat
{
    Initialise, EnCours, EnPause, Termine
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

void gererGeniedex()
{
    #ifdef _WIN32
        system("cls");
    #endif
    bool operationFinie = false;
    joueur.afficherMenuGeniedex();
    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == 'v' || touche == 'V')
        {
            #ifdef _WIN32
                   system("cls");
            #endif
            joueur.afficherMenuGeniedex();
            cout << "Entrer le type de Genimon que vous voulez visualiser (8 choix)" << endl;
            cout << "Informatique: --I--\nElectrique: --E--\nRobotique: --R--\nMecanique: --M--\n";
            cout << "Civil: --C--\nBatiment: --B--\nBiotech: --T--\nChimique: --Q--\n" << endl;

            char toucheSecondaire;
            bool toucheValide = false;

            while (!toucheValide)
            {
                cout << "Votre selection: ";
                toucheSecondaire = _getch();

                if (toucheSecondaire == 'i' || toucheSecondaire == 'I' || toucheSecondaire == 'e' || toucheSecondaire == 'E'
                    || toucheSecondaire == 'r' || toucheSecondaire == 'R' || toucheSecondaire == 'm' || toucheSecondaire == 'M'
                    || toucheSecondaire == 'c' || toucheSecondaire == 'C' || toucheSecondaire == 'b' || toucheSecondaire == 'B'
                    || toucheSecondaire == 't' || toucheSecondaire == 'T' || toucheSecondaire == 'q' || toucheSecondaire == 'Q')
                {
                    toucheValide = true;
                }
                else
                {
                    cout << "Touche invalide" << endl;
                }
            }

            cout << toucheSecondaire << endl;
            joueur.consulterGenidexPartiel(toucheSecondaire);
        }
        else if (touche == 'e' || touche == 'E')
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur.afficherMenuGeniedex();
            joueur.consulterGenidexComplet();
        }
        else if (touche == 'f' || touche == 'F')
        {
            operationFinie = true;
        }
        else
        {
            cout << "Touche invalide" << endl;
        }
    }
}

void gererPartie()
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
            gererGeniedex();
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
        case EnCours:
            joueur.afficherPartie();
            enDécision = true;
            while (enDécision)
            {
                gererPartie();
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

