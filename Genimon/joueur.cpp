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
    nbGenimonAttrapés = 0;
    nbBalles = 20;
    nbCapsuleGuerison = 0;
}

void Joueur::choisirStarter() {
    cout << "\nChoissisez votre premier Genimon" << endl;
    cout << "Donnez son nom: ";
    string nomChoisi;
    cin >> nomChoisi;
    cout << "1) Genie Informatique" << endl;
    cout << "2) Genie Electrique" << endl;
    cout << "3) Genie Robotique" << endl;
    cout << "4) Genie Mecanique" << endl;
    cout << "5) Genie Civil" << endl;
    cout << "6) Genie du Batiment" << endl;
    cout << "7) Genie Biotech" << endl;
    cout << "8) Genie Chimique" << endl;
    cout << "Donnez son type: ";

    char typeChoisi;
    bool toucheValide = false;

    while (!toucheValide)
    {
        typeChoisi = _getch();

        if (typeChoisi == '1' || typeChoisi == '2' || typeChoisi == '3' || typeChoisi == '4'
            || typeChoisi == '5' || typeChoisi == '6' || typeChoisi == '7' || typeChoisi == '8')        
        {
            toucheValide = true;
        }
        else
        {
            cout << "Type invalide" << endl;
            cout << "Donnez son type: ";
        }
    }
    GenimonS* premierGenimon = new GenimonS(typeChoisi, nomChoisi);
    genidex[premierGenimon->getTypeNumérique()].listeGenimonAttrapé.push_back(*premierGenimon);
    nbGenimonAttrapés++;

    cout << "\n\nVotre premier Genimon est " << premierGenimon->getNom() << ", Type: " << premierGenimon->getType();
    cout << ", Rarete: " << premierGenimon->getRareté() << ", PV: " << premierGenimon->getPV();
    cout << ", Degats: " << premierGenimon->getDegats() << endl << endl;

    cout << "Appuyez sur --L-- pour lancer la partie" << endl;

    char touche;
    bool toucheValide2 = false;
    while (!toucheValide2)
    {
        touche = _getch();

        if (touche == 'l' || touche == 'L')
        {
            toucheValide2 = true;
        }
        else
        {
            cout << "Touche invalide" << endl;
        }
    }
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

void Joueur::gererCapsuleVie()
{
    if (terrain[position_x][position_y] == 'V')
    {
        nbCapsuleGuerison++;
        terrain[position_x][position_y] == '.';
    }
}

void Joueur::ajouterGenimon(bool refresh)
{
    Genimon* nouveauGenimon = new Genimon;
    listeGenimons.ajouterElement(nouveauGenimon);

    int pos_x = rand() % dimensionTerrain_x;
    int pos_y  = rand() % dimensionTerrain_y;

    //Genimon n'apparait pas sur un objet
    while (terrain[pos_x][pos_y] == '1' || terrain[pos_x][pos_y] == 'X' || terrain[pos_x][pos_y] == '2' || terrain[pos_x][pos_y] == 'V')
    {
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
    int indexRandom = rand() % listeGenimons.Taille(); //Retire un genimon random
    terrain[listeGenimons[indexRandom]->position_x][listeGenimons[indexRandom]->position_y] = '.';
    listeGenimons.retirerElement(indexRandom);
}

void Joueur::creerCapsuleVie(bool refresh)
{
    int pos_x = rand() % dimensionTerrain_x;
    int pos_y = rand() % dimensionTerrain_y;

    //La capsule de vie n'apparait pas sur un objet
    while (terrain[pos_x][pos_y] == '1' || terrain[pos_x][pos_y] == 'X' || terrain[pos_x][pos_y] == '2' || terrain[pos_x][pos_y] == 'V')
    {
        pos_x = rand() % dimensionTerrain_x;
        pos_y = rand() % dimensionTerrain_y;
    }

    terrain[pos_x][pos_y] = 'V';

    if (refresh)
    {
        afficherPartie();
    }
}

void Joueur::gererGenimon()
{
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
        historique.push_back(*genimon);

        #ifdef _WIN32
                system("cls");
        #endif
        genimon->apparait();

        cout << "\nAppuyer sur --A-- pour l'attraper, sur --C-- pour le combattre ou sur --Q-- pour quitter" << endl;

        bool decisionPrise = false;
        char touche;
        while (!decisionPrise)
        {
            touche = _getch();
            if (touche == 'a' || touche == 'A')
            {
                if (nbBalles <= 0)
                {
                    cout << "Vous n'avez aucune balle, la capture est impossible. Allez combattre des Genimons pour essayer de gagner plus de balles" << endl << endl;
                    cout << "Appuyez sur --R-- pour retourner au jeu" << endl;
                    bool operationFinie = false;

                    while (!operationFinie)
                    {
                        char toucheSecondaire = _getch();

                        if (toucheSecondaire == 'r' || toucheSecondaire == 'R')
                        {
                            operationFinie = true;
                        }
                        else
                        {
                            cout << "Touche invalide" << endl;
                            cout << "Appuyez sur --R-- pour retourner au jeu" << endl;
                        }
                    }
                }
                else
                {
                    gererAttrapage(genimon, indexGenimon);
                }              
                decisionPrise = true;
            }
            else if (touche == 'c' || touche == 'C')
            {
                if (nbGenimonAttrapés <= 0)
                {
                    cout << "Votre Genidex est vide, donc vous ne pouvez pas combattre. Allez capturer des Genimons sur la faculte" << endl << endl;
                    cout << "Appuyez sur --R-- pour retourner au jeu" << endl;
                    bool operationFinie = false;

                    while (!operationFinie)
                    {
                        char toucheSecondaire = _getch();

                        if (toucheSecondaire == 'r' || toucheSecondaire == 'R')
                        {
                            operationFinie = true;
                        }
                        else
                        {
                            cout << "Touche invalide" << endl;
                            cout << "Appuyez sur --R-- pour retourner au jeu" << endl;
                        }
                    }
                }               
                else
                {
                    gererCombat(genimon);
                }             
                decisionPrise = true;
            }
            else if (touche == 'q' || touche == 'Q')
            {
                decisionPrise = true;
            }
            else
            {
                cout << "Touche invalide" << endl;
            }
        }
    }
}

genimonChoisi Joueur::choisirGenimon(Genimon* genimon, int indexFleche)
{
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                               Duel contre un Genimon !                           " << endl << endl;
    cout << "                         Choisissez un Genimon pour le combat                     " << endl << endl << endl;
    cout << "                    Utilisez les touches w et s pour la selection                 " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    genimon->presenter();
    cout << "\nFaites un choix dans l'inventaire:" << endl;

    int compteur = 1;
    genimonChoisi infos;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < genidex[i].listeGenimonAttrapé.size(); j++)
        {
            if (indexFleche == compteur)
            {
                cout << "--> ";
                infos.indexI = i;
                infos.indexJ = j;
            }
            cout << compteur << ") " << "Nom: " << genidex[i].listeGenimonAttrapé[j].getNom() << ", Type: " << genidex[i].listeGenimonAttrapé[j].getType();
            cout << ", Rarete: " << genidex[i].listeGenimonAttrapé[j].getRareté() << ", PV: " << genidex[i].listeGenimonAttrapé[j].getPV();
            cout << ", Degats: " << genidex[i].listeGenimonAttrapé[j].getDegats() << endl;
            compteur++;
        }
    }

    cout << "\nAppuyez sur --C-- pour confirmer le choix ou sur --A-- pour abandonner le combat" << endl << endl;

    return infos;
}

void Joueur::afficherStatsManche(Genimon* adversaire, Genimon genimonJoueur, int bonusAdversaire, int bonusJoueur)
{
    cout << adversaire->getNom() << " a " << adversaire->getPV() << " de PV et a un bonus de " << bonusAdversaire - 1 << endl;
    cout << genimonJoueur.getNom() << " a " << genimonJoueur.getPV() << " de PV et a un bonus de " << bonusJoueur - 1 << endl << endl;
}

bool Joueur::gererCombat(Genimon* genimon)
{
    bool victoire = false;

    //Partie choix
    bool operationFinie = false;
    bool annulationCombat = false;
    int indexFleche = 1;
    genimonChoisi infos;
    infos = choisirGenimon(genimon, indexFleche);

    while (!operationFinie)
    {
        char touche = _getch();

        if (touche == 'w' || touche == 'W')
        {
            if (indexFleche > 1)
            {
                --indexFleche;
            }
            infos = choisirGenimon(genimon, indexFleche);
        }
        else if (touche == 's' || touche == 'S')
        {
            if (indexFleche < nbGenimonAttrapés)
            {
                ++indexFleche;
            }
            infos = choisirGenimon(genimon, indexFleche);
        }
        else if (touche == 'a' || touche == 'A')
        {
            annulationCombat = true;
            operationFinie = true;
        }
        else if (touche == 'c' || touche == 'C')
        {
            if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() == 0)
            {
                cout << "Vous ne pouvez pas utiliser un Genimon KO. Veuillez en choisir un autre ou abandonnez le combat" << endl;
            }
            else
            {
                operationFinie = true;
            }         
        }
        else
        {
            cout << "Touche invalide" << endl;
        }
    }

    //Partie combat
    if (!annulationCombat)
    {
        Genimon genimonChoisi = genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ];
        int variationDegatsJoueur = 0;
        int variationDegatsAdversaire = 0;
        #ifdef _WIN32
                system("cls");
        #endif
        cout << "----------------------------------------------------------------------------------" << endl;
        cout << "                               Duel contre un Genimon !                           " << endl << endl;
        cout << "                   Battez-le pour avoir la possiblite de l'attraper               " << endl << endl;
        cout << "----------------------------------------------------------------------------------" << endl << endl;

        //Set les avantages/désaventages de type
        if (genimon->getTypeSupérieur() == genimonChoisi.getType())
        {
            variationDegatsAdversaire = -genimon->getFacteurDegats();
            cout << "ATTENTION: Par desavantage de type, les degats de l'adversaire sont reduits de " << -1 * variationDegatsAdversaire  << endl << endl;
        }
        else  if (genimon->getTypeInférieur() == genimonChoisi.getType())
        {        
            variationDegatsAdversaire = genimon->getFacteurDegats();
            cout << "ATTENTION: Par avantage de type, les degats de l'adversaire sont augmentes de " << variationDegatsAdversaire << endl << endl;
        }

        if (genimonChoisi.getTypeSupérieur() == genimon->getType())
        {
            variationDegatsJoueur = -genimonChoisi.getFacteurDegats();
            cout << "ATTENTION: Par desavantage de type, les degats du joueur sont reduits de " << -1 * variationDegatsJoueur << endl << endl;
        }
        else  if (genimonChoisi.getTypeInférieur() == genimon->getType())
        {
            variationDegatsJoueur = genimonChoisi.getFacteurDegats();
            cout << "ATTENTION: Par avantage de type, les degats du joueur sont augmentes de " << variationDegatsJoueur << endl << endl;
        }

        //Affiche les opposants
        cout << "Genimon a battre\n" << "Nom: " << genimon->getNom() << ", Type: " << genimon->getType();
        cout << ", Rarete: " << genimon->getRareté() << ", PV: " << genimon->getPV();
        cout << ", Degats: " << genimon->getDegats() + variationDegatsAdversaire;
        if (variationDegatsAdversaire < 0)
        {
            cout << " (-)" << endl << endl;
        }
        else if(variationDegatsAdversaire > 0)
        {
            cout << " (+)" << endl << endl;
        }
        else
        {
            cout << endl << endl;
        }

        cout << "Genimon choisi\n" << "Nom: " << genimonChoisi.getNom() << ", Type: " << genimonChoisi.getType();
        cout << ", Rarete: " << genimonChoisi.getRareté() << ", PV: " << genimonChoisi.getPV();
        cout << ", Degats: " << genimonChoisi.getDegats() + variationDegatsJoueur;
        if (variationDegatsJoueur < 0)
        {
            cout << " (-)" << endl << endl;
        }
        else if (variationDegatsJoueur > 0)
        {
            cout << " (+)" << endl << endl;
        }
        else
        {
            cout << endl << endl;
        }

        int pileOuFace = rand() % 2;
        int numeroManche = 1;
        bool unGenimonMort = false;
        bool tourJoueur = true;
        bool joueurCommence = true;

        int degatsJoueur = 0;
        int degatsAdversaire = 0;
        bool joueurAttaque = false;
        bool adversaireAttaque = false;
        float bouclierJoueur = 1;
        float bouclierAdversaire = 1;
        int bonusJoueur = 1;
        int bonusAdversaire = 1;
        string choixJoueur;
        string choixAdversaire;

        cout << "Tirage a pile ou face..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
        if (pileOuFace == 0)
        {
            tourJoueur = true;
            joueurCommence = true;
            cout << "Le Joueur commence!" << endl << endl;
        }
        else if (pileOuFace == 1)
        {
            tourJoueur = false;
            joueurCommence = false;
            cout << "L'adversaire commence!" << endl << endl;
        }

        cout << "\n----Manche #" << numeroManche << "----" << endl;

        while (!unGenimonMort)
        {        
            if (tourJoueur)
            {
                cout << "Tour Joueur" << endl;
                cout << "Appuyez sur --A-- pour attaquer, sur --B-- pour bloquer, sur --C-- pour accumuler un bonus ou sur --Q-- pour quitter le combat" << endl;

                bool toucheValide = false;
                char touche;

                while (!toucheValide)
                {
                    touche = _getch();

                    if (touche == 'a' || touche == 'A')
                    {                      
                        degatsJoueur = (genimonChoisi.getDegats() + variationDegatsJoueur) * bonusJoueur;                      
                        choixJoueur = "Le joueur attaque avec " + to_string(degatsJoueur) + " de degats contre l'adversaire";
                        bonusJoueur = 1; //reset le bonus après l'utilisation
                        joueurAttaque = true;                                             
                        toucheValide = true;
                        cout << "Le joueur a choisi" << endl << endl;
                    }
                    else  if (touche == 'b' || touche == 'B')
                    {
                        bouclierJoueur = 0.5 / bonusJoueur;
                        choixJoueur = "Le joueur bloque l'adversaire a " + to_string((1 - bouclierJoueur) * 100) + "%";
                        toucheValide = true;
                        bonusJoueur = 1; //reset le bonus après l'utilisation
                        cout << "Le joueur a choisi" << endl << endl;
                    }
                    else  if (touche == 'c' || touche == 'C')
                    {
                        bonusJoueur++;
                        choixJoueur = "Le joueur accumule un bonus";
                        toucheValide = true;
                        cout << "Le joueur a choisi" << endl << endl;
                    }
                    else  if (touche == 'q' || touche == 'Q')
                    {
                        cout << "Voulez-vous vraiment quitter le combat? Les PV perdus ne sont pas restaure. (O/N)" << endl;
                        bool operationFinie = false;

                        while (!operationFinie)
                        {
                            char touche = _getch();

                            if (touche == 'o' || touche == 'O')
                            {
                                cout << "---Le joueur abandonne le combat---" << endl;
                                toucheValide = true;
                                unGenimonMort = true;
                                std::this_thread::sleep_for(std::chrono::seconds(2));

                                operationFinie = true;
                            }
                            else if (touche == 'n' || touche == 'N')
                            {
                                cout << "Appuyez sur --A-- pour attaquer, sur --B-- pour bloquer, sur --C-- pour accumuler un bonus ou sur --Q-- pour quitter le combat" << endl;
                                operationFinie = true;
                            }
                            else
                            {
                                cout << "Touche invalide" << endl;
                            }
                        }                      
                    }
                    else
                    {
                        cout << "Touche invalide" << endl;
                    }
                }                         

                if (!joueurCommence && !unGenimonMort)
                {           
                    if (adversaireAttaque)
                    {                        
                        genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].varierPV(-degatsAdversaire * bouclierJoueur);                      
                        bouclierJoueur = 1; //reset le bouclier après l'utilisation
                        degatsAdversaire = 0;
                        adversaireAttaque = false;

                        if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() <= 0)
                        {
                            unGenimonMort = true;
                            genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].setPV(0); //Minimum de pv à 0

                            cout << choixAdversaire << endl;
                            cout << choixJoueur << endl << endl;
                            afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ], bonusAdversaire, bonusJoueur);
                            cout << "Defaite du joueur! " << genimonChoisi.getNom() << " est KO" << endl << endl;
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        }
                    }

                    if (joueurAttaque)
                    {
                        genimon->varierPV(-degatsJoueur * bouclierAdversaire);
                        bouclierAdversaire = 1; //reset le bouclier après l'utilisation
                        degatsJoueur = 0;
                        joueurAttaque = false;

                        if (genimon->getPV() <= 0 && !unGenimonMort)
                        {
                            unGenimonMort = true;
                            victoire = true;
                            genimon->setPV(0); //Minimum de pv à 0

                            cout << choixAdversaire << endl;
                            cout << choixJoueur << endl << endl;
                            afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ], bonusAdversaire, bonusJoueur);
                            cout << "Victoire du joueur! " << genimon->getNom() << " est KO" << endl << endl;
                            genimon->setPV(genimon->pvMax); //pv régénéré
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        }
                    }

                    if (!unGenimonMort)
                    {
                        bouclierJoueur = 1; //reset le bouclier après l'utilisation
                        bouclierAdversaire = 1; //reset le bouclier après l'utilisation
                        cout << choixAdversaire << endl;
                        cout << choixJoueur << endl << endl;
                        afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ], bonusAdversaire, bonusJoueur);
                        ++numeroManche;
                        cout << "\n----Manche #" << numeroManche << "----" << endl;
                    }                

                    joueurCommence = true;
                }
                else
                {
                    tourJoueur = false;
                }
            }
            else
            {
                cout << "Tour Adversaire" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                int choix = rand() % 3;
                if (choix == 0)
                {
                    degatsAdversaire = (genimon->getDegats() + variationDegatsAdversaire) * bonusAdversaire;
                    choixAdversaire = "L'adversaire attaque avec " + to_string(degatsAdversaire) + " de degats contre le joueur";
                    bonusAdversaire = 1; //reset le bonus après l'utilisation
                    adversaireAttaque = true;                  
                }
                else  if (choix == 1)
                {
                    if (!joueurCommence) //L'adversaire ne défend pas si il commence, il va attaquer ou se donner un bonus
                    {
                        int choixSecondaire = rand() % 2;
                        if (choixSecondaire == 0)
                        {
                            degatsAdversaire = (genimon->getDegats() + variationDegatsAdversaire) * bonusAdversaire;
                            choixAdversaire = "L'adversaire attaque avec " + to_string(degatsAdversaire) + " de degats contre le joueur";
                            bonusAdversaire = 1; //reset le bonus après l'utilisation
                            adversaireAttaque = true;
                        }         
                        else if (choixSecondaire == 1)
                        {
                            bonusAdversaire++;
                            choixAdversaire = "L'adversaire accumule un bonus";
                        }
                    }
                    else
                    {
                        bouclierAdversaire = 0.5 / bonusAdversaire;
                        choixAdversaire = "L'adversaire bloque le joueur a " + to_string((1 - bouclierAdversaire) * 100) + "%";
                        bonusAdversaire = 1; //reset le bonus après l'utilisation
                    }              
                }
                else  if (choix == 2)
                {
                    bonusAdversaire++;
                    choixAdversaire = "L'adversaire accumule un bonus";
                }            

                cout << "L'adversaire a choisi" << endl << endl;

                if (joueurCommence)
                {                
                    if (joueurAttaque)
                    {
                        genimon->varierPV(-degatsJoueur * bouclierAdversaire);                      
                        bouclierAdversaire = 1; //reset le bouclier après l'utilisation
                        degatsJoueur = 0;
                        joueurAttaque = false;

                        if (genimon->getPV() <= 0)
                        {
                            unGenimonMort = true;
                            victoire = true;       
                            genimon->setPV(0); //Minimum de pv à 0

                            cout << choixJoueur << endl;
                            cout << choixAdversaire << endl << endl;
                            afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ], bonusAdversaire, bonusJoueur);
                            cout << "Victoire du joueur! " << genimon->getNom() << " est KO" << endl << endl;
                            genimon->setPV(genimon->pvMax); //pv régénéré
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        }
                    }

                    if (adversaireAttaque)
                    {
                        genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].varierPV(-degatsAdversaire * bouclierJoueur);
                        bouclierJoueur = 1; //reset le bouclier après l'utilisation
                        degatsAdversaire = 0;
                        adversaireAttaque = false;

                        if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() <= 0 && !unGenimonMort)
                        {
                            unGenimonMort = true;
                            genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].setPV(0); //Minimum de pv à 0

                            cout << choixJoueur << endl;
                            cout << choixAdversaire << endl << endl;
                            afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ], bonusAdversaire, bonusJoueur);
                            cout << "Defaite du joueur! " << genimonChoisi.getNom() << " est KO" << endl << endl;
                            std::this_thread::sleep_for(std::chrono::seconds(2));
                        }
                    }

                    if (!unGenimonMort)
                    {
                        bouclierJoueur = 1; //reset le bouclier après l'utilisation
                        bouclierAdversaire = 1; //reset le bouclier après l'utilisation
                        cout << choixJoueur << endl;
                        cout << choixAdversaire << endl << endl;
                        afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ], bonusAdversaire, bonusJoueur);
                        ++numeroManche;
                        cout << "\n----Manche #" << numeroManche << "----" << endl;
                    }                  

                    joueurCommence = false;
                }         
                else
                {
                    tourJoueur = true;
                }             
            }
        }

        if (victoire)
        {
            nbBalles += genimon->getGainBalles();
            cout << "Vous avez gagne " << genimon->getGainBalles() << " balles" << endl;
            cout << "Nombre total de balles: " << nbBalles << endl << endl;

            if (genimon->getRareteNumerique() > genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getRareteNumerique())
            {
                cout << "Vous avez battu un Genimon de rarete superieure au votre, bravo!" << endl;
                cout << "Une capsule de guerison vous est donne en recompense" << endl << endl;
                nbCapsuleGuerison++;
            }
        }

        bool retourJeu = false;
        char touche;
        cout << "Appuyez sur --Q-- pour quitter le combat" << endl;
        while (!retourJeu)
        {
            touche = _getch();
            if (touche == 'q' || touche == 'Q')
            {
                retourJeu = true;
            }
            else
            {
                cout << "Touche invalide" << endl;
                cout << "Appuyez sur --Q-- pour quitter le combat" << endl;
            }
        }
    }
    else
    {
        cout << "\n---Combat annule---" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return victoire;
}

void Joueur::gererAttrapage(Genimon* genimon, int indexGenimon)
{
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                            Face a face avec un Genimon !                         " << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    
    genimon->presenter();

    int typeGenimon = genimon->getTypeNumérique();

    bool captureReussie = genimon->capture(&nbBalles);
    if (captureReussie)
    {
        genidex[typeGenimon].listeGenimonAttrapé.push_back(*genimon);
        nbGenimonAttrapés++;
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
        cout << "\n   Rarete: " << genidex[typeNumérique].listeGenimonAttrapé[i].getRareté() << "\n   PV: " << genidex[typeNumérique].listeGenimonAttrapé[i].getPV();
        cout << "\n   Degats: " << genidex[typeNumérique].listeGenimonAttrapé[i].getDegats() << endl;
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

void Joueur::guerirGenimon()
{
    bool operationFinie = false;
    int indexFleche = 1;
    genimonChoisi infos;

    if (nbCapsuleGuerison > 0 && nbGenimonAttrapés > 0)
    {
        infos = choisirGuerison(indexFleche);
        while (!operationFinie)
        {
            char touche = _getch();

            if (touche == 'w' || touche == 'W')
            {
                if (indexFleche > 1)
                {
                    --indexFleche;
                }
                infos = choisirGuerison(indexFleche);
            }
            else if (touche == 's' || touche == 'S')
            {
                if (indexFleche < nbGenimonAttrapés)
                {
                    ++indexFleche;
                }
                infos = choisirGuerison(indexFleche);
            }
            else if (touche == 'a' || touche == 'A')
            {
                #ifdef _WIN32
                        system("cls");
                #endif
                afficherMenuGeniedex(true);
                operationFinie = true;
            }
            else if (touche == 'c' || touche == 'C')
            {
                if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() == genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].pvMax)
                {
                    cout << "Le Genimon choisi n'a subi auncun degats. Veuillez en choisir un autre ou annuler la guerison" << endl;
                }
                else
                {
                    genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].setPV(genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].pvMax);
                    nbCapsuleGuerison--;
                    cout << "Guerison effectuee" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    #ifdef _WIN32
                           system("cls");
                    #endif
                    afficherMenuGeniedex(true);
                    operationFinie = true;
                }              
            }
            else
            {
                cout << "Touche invalide" << endl;
            }
        }
    }
    else
    {
        cout << "Action impossible! Vous n'avez aucune capsule de guerison." << endl;
    }
}

genimonChoisi Joueur::choisirGuerison(int indexFleche)
{
    #ifdef _WIN32
        system("cls");
    #endif
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                           Choisissez un Genimon a soigner                        " << endl << endl;
    cout << "                    Utilisez les touches w et s pour la selection                 " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "\nFaites un choix dans l'inventaire:" << endl;

    int compteur = 1;
    genimonChoisi infos;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < genidex[i].listeGenimonAttrapé.size(); j++)
        {
            if (indexFleche == compteur)
            {
                cout << "--> ";
                infos.indexI = i;
                infos.indexJ = j;
            }
            cout << compteur << ") " << "Nom: " << genidex[i].listeGenimonAttrapé[j].getNom() << ", Type: " << genidex[i].listeGenimonAttrapé[j].getType();
            cout << ", Rarete: " << genidex[i].listeGenimonAttrapé[j].getRareté() << ", PV: " << genidex[i].listeGenimonAttrapé[j].getPV();
            cout << ", PV max: " << genidex[i].listeGenimonAttrapé[j].pvMax << ", Degats: " << genidex[i].listeGenimonAttrapé[j].getDegats() << endl;
            compteur++;
        }
    }

    cout << "\nAppuyez sur --C-- pour confirmer le choix ou sur --A-- pour annuler la guerison" << endl << endl;

    return infos;
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
        cout << ", Rarete: " << historique[i].getRareté() << ", PV: " << historique[i].getPV();
        cout << ", Degats: " << historique[i].getDegats() << endl;
    }

    cout << "\nAppuyez sur --F-- pour fermer l'historique" << endl;
}

void Joueur::afficherPartie() {
    #ifdef _WIN32
        system("cls");
    #endif

    afficherMenuPrincipal();

    if (evenementActif())
    {
        cout << "***** C'EST LE 5@8 *****" << endl;
    }

    cout << "\n" << nomTerrain << endl << endl;

    //Mise à jour de la position
    if (terrain[anciennePosition_x][anciennePosition_y] != 'X')
    {
        terrain[anciennePosition_x][anciennePosition_y] = '.';
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

    //Affichage profil joueur
    cout << "\nDresseur: " << nom;
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

void Joueur::afficherMenuGeniedex(bool afficherObjets)
{
    cout << "----------------------------------------------------------------------------------" << endl;
    cout << "                                  Menu Genidex                                    " << endl << endl;
    cout << "                      Pour visualiser une categorie du Genidex: --C--             " << endl;
    cout << "                      Pour visualiser l'ensemble du Genidex: --E--                " << endl;
    cout << "                      Pour guerir un Genimon: --G--                               " << endl;
    cout << "                      Pour fermer le Genidex: --F--                               " << endl << endl;
    cout << "----------------------------------------------------------------------------------" << endl;

    if (afficherObjets)
    {
        cout << "\nNombre total de balles: " << nbBalles;
        cout << "\nNombre total de capsules de guerison: " << nbCapsuleGuerison << endl;
    }
}