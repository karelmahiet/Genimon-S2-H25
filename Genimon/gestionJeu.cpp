#include "gestionJeu.h"

enum Etat
{
    Initialise, EnCours, Termine
};

const int maxGenimon = 15;

enum Etat etatJeu = Initialise;
Joueur* joueur;
bool apparitionsPermises = false;
bool disparitionsPermises = false;
bool resfreshPermis = true;
int nbCapsulesGuerisonTerrain = 0;

bool evenementActif() {
    time_t now = time(nullptr);

    struct tm localTime;

    localtime_s(&localTime, &now);

    if (localTime.tm_hour >= 17 && localTime.tm_hour < 20) {
        return true;
    }
    else {
        return false;
    }
}

void afficherBienvenue()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                            Bienvenu dans Genimon!                                " << endl << endl;
    cout << "          Promenez-vous dans la faculte de genie et rencontrer des                " << endl;
    cout << "          Genimons. Combattez-les pour tentez de les capturer et de les           " << endl;
    cout << "          ajouter a votre Genidex. Une aventure passionnante vous attend.         " << endl << endl;
    cout << "                                Bonne chasse!                                     " << endl << endl << endl;
    cout << "                        Pour demarer le jeu: --1--                                " << endl;
    cout << "                        Pour sortir du jeu: --4--                                 " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void afficherConfirmation()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                  Voulez-vous vraiment mettre fin a la partie?                    " << endl;
    cout << "                  Si vous confirmez, votre progression sera perdu.                " << endl << endl << endl;
    cout << "                               Pour confirmer: --1--                              " << endl;
    cout << "                               Pour annuler: --4--                                " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
}

void afficherPause()
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                   Jeu en pause                                   " << endl << endl;
    cout << "                         Pour sortir du jeu: --1--                                " << endl;
    cout << "                         Pour reinitialiser le jeu: --2--                         " << endl;
    cout << "                         Pour revenir au jeu: --4--                               " << endl << endl;
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

        if (touche == '1')
        {
            #ifdef _WIN32
                 system("cls");
            #endif

            joueur = new Joueur;
            cout << "----------------------------------------------------------------------------------" << endl;
            cout << "                                 Setup de la partie                               " << endl;
            cout << "----------------------------------------------------------------------------------" << endl << endl;
            cout << "Entrez votre nom: ";
            cin >> joueur->nom;
            joueur->choisirStarter();

            etatJeu = EnCours;
            operationFinie = true;
        }
        else if (touche == '4')
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

void gererPause(bool *finPartie)
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherPause();
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == '2') {
            gererConfirmation(1, finPartie);
            operationFinie = true;
        }
        else if (touche == '1') {
            gererConfirmation(2, finPartie);
            operationFinie = true;
        }
        else if (touche == '4')
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

        if (touche == '1')
        {
            if (option == 1)
            {
                etatJeu = Initialise;            
                apparitionsPermises = false;
                disparitionsPermises = false;
                resfreshPermis = true;
            }
            else
            {
                etatJeu = Termine;
            }
            *finPartie = true;
            operationFinie = true;
        }
        else if (touche == '4')
        {
            operationFinie = true;
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
    joueur->afficherMenuGeniedex(true);
    bool operationFinie = false;

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == '1')
        {
            char toucheSecondaire;
            bool choixFait = false;
            bool refresh = true;
            int indexFleche = 0;
            string optionsType[8] = { "Informatique", "Electrique", "Robotique", "Mecanique", "Civil", "Batiment", "Biotech", "Chimique" };

            while (!choixFait)
            {
                if (refresh)
                {
                    #ifdef _WIN32
                              system("cls");
                    #endif
                    joueur->afficherMenuGeniedex(false);
                    cout << "Choissisez le type de Genimon que vous voulez visualiser (8 choix)" << endl;
                    cout << "Utilisez les touches w et s pour la selection" << endl << endl;

                    for (int i = 0; i < 8; i++)
                    {
                        if (indexFleche == i)
                        {
                            cout << "--> ";
                        }
                        cout << optionsType[i] << endl;
                    }

                    cout << "\nAppuyez sur --1-- pour confirmer le choix" << endl;
                }              
                toucheSecondaire = _getch();

                if (toucheSecondaire == 'w')
                {
                    if (indexFleche > 0)
                    {
                        --indexFleche;
                    }
                    refresh = true;
                }
                else if (toucheSecondaire == 's')
                {
                    if (indexFleche < 7)
                    {
                        ++indexFleche;
                    }
                    refresh = true;
                }
                else if (toucheSecondaire == '1')
                {
                    choixFait = true;
                }
                else
                {
                    refresh = false;
                    cout << "Touche invalide" << endl;
                }
            }           

            joueur->consulterGenidexPartiel(indexFleche);
        }
        else if (touche == '2')
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur->afficherMenuGeniedex(false);
            joueur->consulterGenidexComplet();
        }
        else if (touche == '3')
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur->afficherMenuGeniedex(false);
            joueur->guerirGenimon();
        }
        else if (touche == '4')
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

        if (touche == '4')
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
        apparitionsPermises = true;
        disparitionsPermises = true;
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
            else if (touche == '1') {
                resfreshPermis = false;
                gererGeniedex();
            }
            else if (touche == '2') {
                resfreshPermis = false;
                gererHistorique();
            }
            else if (touche == '3') {
                apparitionsPermises = false;
                disparitionsPermises = false;
                resfreshPermis = false;
                gererPause(&operationFinie);
            }
            else
            {
                toucheValide = false;
            }

            if (joueur->estSurGenimon())
            {
                disparitionsPermises = false;
                resfreshPermis = false;
                joueur->gererGenimon();
            }
            else if (joueur->estSurPorte())
            {
                apparitionsPermises = false;
                disparitionsPermises = false;
                resfreshPermis = false;
                joueur->changerTerrain();
            }
            else
            {
                if (joueur->gererCapsuleVie())
                {
                    nbCapsulesGuerisonTerrain--;
                }
            }


            if (toucheValide && etatJeu == EnCours)
            {
                joueur->afficherPartie();
            }
        }
    }

    apparitionsPermises = false;
    disparitionsPermises = false;
    delete joueur;
}

//Apparition et disparition des genimons
void gererThread()
{
    while (true) {
        if (etatJeu == EnCours)
        {
            if (apparitionsPermises && joueur->listeGenimons.Taille() <= maxGenimon)
            {           
                if (joueur->listeGenimons.Taille() <= maxGenimon / 3)
                {
                    joueur->ajouterGenimon(resfreshPermis);
                }
                else
                {
                    if ((rand() % 2) == 1)
                    {
                        joueur->ajouterGenimon(resfreshPermis);
                    }
                }               
            }
            if (disparitionsPermises && joueur->listeGenimons.Taille() >= 10)
            {
                if ((rand() % 5) == 1)
                {
                    joueur->retirerGenimon(resfreshPermis);
                }
            }
        }

        this_thread::sleep_for(chrono::milliseconds(4000));
    }
}

//Capsules de vie
void gererThread2()
{
    while (true) {
        if (etatJeu == EnCours)
        {
            if (apparitionsPermises && nbCapsulesGuerisonTerrain < 1)
            {
                int choix = rand() % 6;
                if (choix == 0)
                {
                    joueur->creerCapsuleVie(resfreshPermis);
                    nbCapsulesGuerisonTerrain++;
                }
            }          
        }

        this_thread::sleep_for(chrono::milliseconds(20000));
    }
}

int main()
{
    srand(time(0));
    thread t(gererThread);
    t.detach();
    thread t2(gererThread2);
    t2.detach();

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

