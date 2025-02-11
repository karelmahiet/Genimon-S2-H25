#include "joueur.h"

enum Etat
{
    Initialise, EnCours, Termine
};

const int maxGenimon = 15;

enum Etat etatJeu = Initialise;
Joueur* joueur;
bool generationPermise = false;
bool resfreshPermis = true;

void afficherBienvenue()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                            Bienvenu dans Genimon!                                " << endl << endl;
    cout << "          Promenez-vous dans la faculte de genie et rencontrer des                " << endl;
    cout << "          Genimons. Combattez-les pour tentez de les capturer et de les           " << endl;
    cout << "          ajouter a votre Genidex. Une aventure passionnante vous attend.         " << endl << endl;
    cout << "                                Bonne chasse!                                     " << endl << endl << endl;
    cout << "                        Pour demarer le jeu: --D--                                " << endl;
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

void afficherPause()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                   Jeu en pause                                   " << endl << endl << endl;
    cout << "                           Pour revenir au jeu: --ESPACE--                        " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void gererInitialisation()
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherBienvenue();
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == 'd' || touche == 'D')
        {
            cout << "\nCreation du terrain en cours..." << endl;
            joueur = new Joueur;
            etatJeu = EnCours;
            operationFinie = true;
        }
        else if (touche == 'z' || touche == 'Z')
        {
            etatJeu = Termine;
            operationFinie = true;
        }
        else
        {
            cout << "Touche invalide" << endl;
        }
    }
}

void gererPause()
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherPause();
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == ' ')
        {
            operationFinie = true;
        }
        else
        {
            cout << "Touche invalide" << endl;
        }
    }
}

void gererConfirmation(int option, bool* finPartie)
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherConfirmation();
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == 'c' || touche == 'C')
        {
            if (option == 1)
            {
                etatJeu = Initialise;            
                generationPermise = false;
                resfreshPermis = true;
            }
            else
            {
                etatJeu = Termine;
            }
            operationFinie = true;
            *finPartie = true;
        }
        else if (touche == 'a' || touche == 'A')
        {
            operationFinie = true;
            *finPartie = true;
        }
        else
        {
            cout << "Touche invalide" << endl;
        }
    }
}

void gererGeniedex()
{
    #ifdef _WIN32
        system("cls");
    #endif
    joueur->afficherMenuGeniedex();
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == 'c' || touche == 'C')
        {
            #ifdef _WIN32
                   system("cls");
            #endif
            joueur->afficherMenuGeniedex();
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
            joueur->consulterGenidexPartiel(toucheSecondaire);
        }
        else if (touche == 'e' || touche == 'E')
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur->afficherMenuGeniedex();
            joueur->consulterGenidexComplet();
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

void gererHistorique()
{
    #ifdef _WIN32
        system("cls");
    #endif
    joueur->consulterHistorique();
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == 'f' || touche == 'F')
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
    joueur->afficherPartie();
    bool operationFinie = false;
    bool toucheValide = true;

    while (!operationFinie)
    {
        generationPermise = true;
        resfreshPermis = true;
        if (_kbhit())
        {
            char touche = _getch();
            toucheValide = true;

            if (touche == 'a' && joueur->position_x > joueur->borne_x_min) {
                joueur->position_x--;
            }
            else if (touche == 'd' && joueur->position_x < joueur->borne_x_max - 1) {
                joueur->position_x++;
            }
            else if (touche == 's' && joueur->position_y < joueur->borne_y_max - 1) {
                joueur->position_y++;
            }
            else if (touche == 'w' && joueur->position_y > joueur->borne_y_min) {
                joueur->position_y--;
            }
            else if (touche == 'g' || touche == 'G') {
                resfreshPermis = false;
                gererGeniedex();
            }
            else if (touche == 'h' || touche == 'H') {
                resfreshPermis = false;
                gererHistorique();
            }
            else if (touche == ' ') {
                generationPermise = false;
                resfreshPermis = false;
                gererPause();
            }
            else if (touche == 'r' || touche == 'R') {
                resfreshPermis = false;
                gererConfirmation(1, &operationFinie);
            }
            else if (touche == 'z' || touche == 'Z') {
                resfreshPermis = false;
                gererConfirmation(2, &operationFinie);
            }
            else
            {
                toucheValide = false;
            }

            if (joueur->estSurGenimon())
            {
                resfreshPermis = false;
                joueur->gererGenimon();
            }
            else if (joueur->estSurPorte())
            {
                generationPermise = false;
                resfreshPermis = false;
                joueur->changerTerrain();
            }


            if (toucheValide && etatJeu == EnCours)
            {
                joueur->afficherPartie();
            }
        }
    }

    generationPermise = false;
    delete joueur;
}

//Apparition et disparition des genimons
void gererThread1()
{
    while (true) {
        if (etatJeu == EnCours)
        {
            if (generationPermise && joueur->listeGenimons.Taille() <= maxGenimon)
            {
                srand(time(0));
                if ((rand() % 2) == 1)
                {
                    joueur->ajouterGenimon(resfreshPermis);
                }
            }
            if (joueur->listeGenimons.Taille() >= 10)
            {
                srand(time(0));
                if ((rand() % 5) == 1)
                {
                    joueur->retirerGenimon(resfreshPermis);
                }
            }
        }

        this_thread::sleep_for(chrono::milliseconds(4000));
    }
}

//Déplacement des genimons
void gererThread2()
{
    while (true) {
        if (generationPermise && joueur->listeGenimons.Taille() > 0)
        {
            joueur->deplacerGenimons(resfreshPermis);
        }
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
}

int main()
{
    thread t1(gererThread1);
    t1.detach();

    //Note: les déplacements ne sont pas très bon sous interface console. Option pour Qt
    //thread t2(gererThread2);
    //t2.detach();

    while (true)
    {
        switch (etatJeu)
        {
        case Initialise:
            gererInitialisation();
            break;
        case EnCours:
            gererPartie();
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

