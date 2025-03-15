#include "gestionJeu.h"
#include "joueur.h"

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

//Variables communication
bool bouton1_On = false;
bool bouton2_On = false;
bool bouton3_On = false;
bool bouton4_On = false;
int numBouton = 0;
bool joystick_On = false;
string posJoystick = "centre";  // centre, nord, sud, est, ouest
int accX = 0;
int accY = 0;
int accZ = 0;

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
    cout << "                            Bienvenue dans Genimon!                                " << endl << endl;
    cout << "          Promenez-vous dans la faculte de genie et rencontrez des                " << endl;
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
    while (!bouton1_On && !bouton4_On);

    if (numBouton == 1)
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
    }
    else
    {
        etatJeu = Termine;
    }
}

void gererPause(bool *finPartie)
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherPause();
    while (!bouton1_On && !bouton2_On && !bouton4_On);

    if (numBouton == 2) {
        gererConfirmation(1, finPartie);
    }
    else if (numBouton == 1) {
        gererConfirmation(2, finPartie);
    }
}

void gererConfirmation(int option, bool* finPartie)
{
    #ifdef _WIN32
        system("cls");
    #endif
    afficherConfirmation();
    while (!bouton1_On && !bouton4_On);

    if (numBouton == 1)
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
        while (!bouton1_On && !bouton2_On && !bouton3_On && !bouton4_On);

        if (numBouton == 1)
        {
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

                while (!joystick_On && !bouton1_On);

                if (joystick_On)
                {
                    if (posJoystick == "nord")
                    {
                        if (indexFleche > 0)
                        {
                            --indexFleche;
                        }
                        refresh = true;
                    }
                    else if (posJoystick == "sud")
                    {
                        if (indexFleche < 7)
                        {
                            ++indexFleche;
                        }
                        refresh = true;
                    }
                }
                else
                {
                    choixFait = true;
                }
            }

            joueur->consulterGenidexPartiel(indexFleche);
        }
        else if (numBouton == 2)
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur->afficherMenuGeniedex(false);
            joueur->consulterGenidexComplet();
        }
        else if (numBouton == 3)
        {
            #ifdef _WIN32
                    system("cls");
            #endif
            joueur->afficherMenuGeniedex(false);
            joueur->guerirGenimon();
        }
        else
        {
            operationFinie = true;
        }
    }
}

void gererHistorique()
{
    #ifdef _WIN32
        system("cls");
    #endif
    joueur->consulterHistorique();
    while (!bouton4_On);
}

void gererPartie()
{
    joueur->afficherPartie();
    bool operationFinie = false;

    while (!operationFinie)
    {
        apparitionsPermises = true;
        disparitionsPermises = true;
        resfreshPermis = true;

        while (!bouton1_On && !bouton2_On && !bouton3_On && !bouton4_On && !joystick_On);

        if (joystick_On)
        {
            if (posJoystick == "ouest" && joueur->position_x > joueur->borne_x_min) {
                joueur->position_x--;
            }
            else if (posJoystick == "est" && joueur->position_x < joueur->borne_x_max - 1) {
                joueur->position_x++;
            }
            else if (posJoystick == "sud" && joueur->position_y < joueur->borne_y_max - 1) {
                joueur->position_y++;
            }
            else if (posJoystick == "nord" && joueur->position_y > joueur->borne_y_min) {
                joueur->position_y--;
            }
        }
        else
        {
            if (numBouton == 1) {
                resfreshPermis = false;
                gererGeniedex();
            }
            else if (numBouton == 2) {
                resfreshPermis = false;
                gererHistorique();
            }
            else if (numBouton == 3) {
                apparitionsPermises = false;
                disparitionsPermises = false;
                resfreshPermis = false;
                gererPause(&operationFinie);
            }
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


        if (etatJeu == EnCours)
        {
            joueur->afficherPartie();
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

//Gestion des commandes
void gererThread3()
{
    char commande = '0';

    while (true)
    {
        bouton1_On = false;
        bouton2_On = false;
        bouton3_On = false;
        bouton4_On = false;
        joystick_On = false;

        commande = _getch();

        if (commande == 'w')
        {
            joystick_On = true;
            posJoystick = "nord";
        }
        else if (commande == 'a')
        {
            joystick_On = true;
            posJoystick = "ouest";
        }
        else if (commande == 's')
        {
            joystick_On = true;
            posJoystick = "sud";
        }
        else if (commande == 'd')
        {
            joystick_On = true;
            posJoystick = "est";
        }
        else if (commande == '1')
        {
            bouton1_On = true;
            numBouton = 1;
        }
        else if (commande == '2')
        {
            bouton2_On = true;
            numBouton = 2;
        }
        else if (commande == '3')
        {
            bouton3_On = true;
            numBouton = 3;
        }
        else if (commande == '4')
        {
            bouton4_On = true;
            numBouton = 4;
        }
    }
}

int main()
{
    srand(time(0));
    thread t(gererThread);
    t.detach();
    thread t2(gererThread2);
    t2.detach();
    thread t3(gererThread3);
    t3.detach();

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

