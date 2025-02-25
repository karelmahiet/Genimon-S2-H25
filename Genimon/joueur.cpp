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
    zone = 1;
    nbGenimonAttrapés = 0;
    nbBalles = 200;
    nbCapsuleGuerison = 0;
	badge = 1;
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
    Genimon* premierGenimon = new Genimon(typeChoisi, nomChoisi, 1);
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
    if (zone ==1)
    {
        borne_x_min = 21;
        borne_y_min = 0;
        borne_x_max = 37;
        borne_y_max = 14;
        nomTerrain = "    Interieur de la faculte";
        zone = 2;
        position_x += 2;
		if (badge == 1)
		{
			badge = 2;
		}
    }
	else if (zone == 2)
    {
        borne_x_min = 0;
        borne_y_min = 0;
        borne_x_max = 21;
        borne_y_max = 21;
        nomTerrain = "         Exterieur de la faculte";
		zone = 1;
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

bool Joueur::gererCapsuleVie()
{
    if (terrain[position_x][position_y] == 'V')
    {
        nbCapsuleGuerison++;
        terrain[position_x][position_y] == '.';
        return true;
    }
    else
    {
        return false;
    }
}

void Joueur::ajouterGenimon(bool refresh)
{
    Genimon* nouveauGenimon = new Genimon(zone);
    listeGenimons.ajouterElement(nouveauGenimon);

    int pos_x = rand() % dimensionTerrain_x;
    int pos_y  = rand() % dimensionTerrain_y;

    //Genimon n'apparait pas sur un objet ou hors terrain
    while (terrain[pos_x][pos_y] == '1' || terrain[pos_x][pos_y] == 'X' || terrain[pos_x][pos_y] == '2' || terrain[pos_x][pos_y] == 'V'
        || (pos_x >= 21 && pos_y >= 14))
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

    //La capsule de vie n'apparait pas sur un objet ou hors terrain
    while (terrain[pos_x][pos_y] == '1' || terrain[pos_x][pos_y] == 'X' || terrain[pos_x][pos_y] == '2' || terrain[pos_x][pos_y] == 'V'
        || (pos_x >= 21 && pos_y >= 14))
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

void Joueur::afficherStatsManche(Genimon* adversaire, Genimon genimonJoueur)
{
    cout << adversaire->getNom() << " a " << adversaire->getPV() << " de PV" << endl;
    cout << genimonJoueur.getNom() << " a " << genimonJoueur.getPV() << " de PV" << endl << endl;
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
            else if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getRareteNumerique() > genimon->getRareteNumerique())
            {
                cout << "Vous ne pouvez pas utiliser un Genimon de rarete superieure a celle de l'adversaire. Veuillez en choisir un autre ou abandonnez le combat" << endl;
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
        cout << "                       Battez-le pour recuperer des recompenses                   " << endl << endl;
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

        int nbAttaquesJoueur = 0;
        int nbAttaquesAdversaire = 0;
        float nbBoucliersJoueur = 0;
        float nbBoucliersAdversaire = 0;
        int nbBonusJoueur = 0;
        int nbBonusAdversaire = 0;
        int nbToursJoueur = 0;
        int nbToursAdversaire = 0;

        cout << "Tirage a pile ou face..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
        if (pileOuFace == 0)
        {
            tourJoueur = true;
            joueurCommence = true;
            nbToursJoueur = -1;
            cout << "Le Joueur commence!" << endl << endl;
        }
        else
        {
            tourJoueur = false;
            joueurCommence = false;
            nbToursAdversaire = -1;
            cout << "L'adversaire commence!" << endl << endl;
        }

        cout << "\n----Manche #" << numeroManche << "----" << endl;

        while (!unGenimonMort)
        {        
            if (tourJoueur)
            {
                nbToursJoueur += 2;
                cout << "Tour Joueur. Nombre de coup: " << nbToursJoueur << endl;
                cout << "Appuyez sur --A-- pour attaquer, sur --B-- pour bloquer, sur --C-- pour accumuler un bonus ou sur --Q-- pour quitter le combat" << endl;
                
                while(nbToursJoueur > 0)
                {
                    bool toucheValide = false;
                    char touche;

                    while (!toucheValide)
                    {
                        touche = _getch();

                        if (touche == 'a' || touche == 'A')
                        {
                            cout << "*Ajout d'une attaque" << endl;
                            nbAttaquesJoueur++;
                            nbToursJoueur--;         
                            toucheValide = true;
                        }
                        else  if (touche == 'b' || touche == 'B')
                        {
                            cout << "*Ajout d'un bouclier" << endl;
                            nbBoucliersJoueur++;
                            nbToursJoueur--;
                            toucheValide = true;
                        }
                        else  if (touche == 'c' || touche == 'C')
                        {
                            if (nbBonusJoueur < 4)
                            {
                                cout << "*Ajout d'un bonus" << endl;
                                nbBonusJoueur++;
                                nbToursJoueur--;
                                toucheValide = true;
                            }       
                            else
                            {
                                cout << "Vous avez atteint le maximum de bonus joueur. Choissisez une autre option" << endl;
                                cout << "Appuyez sur --A-- pour attaquer, sur --B-- pour bloquer, sur --C-- pour accumuler un bonus ou sur --Q-- pour quitter le combat" << endl;
                                toucheValide = true;
                            }
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
                                    nbToursJoueur = 0;
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
                }                                  

                if (!unGenimonMort)
                {           
                    //Actions joueur
                    int nbDegatsPotentiels = 0;
                    if (nbAttaquesJoueur > 0)
                    {                       
                        for (int i = 1; i <= nbAttaquesJoueur; i++)
                        {
                            if (i > nbBoucliersAdversaire)
                            {
                                genimon->varierPV(-(genimonChoisi.getDegats() + variationDegatsJoueur));                             
                            }      
                            nbDegatsPotentiels += genimonChoisi.getDegats() + variationDegatsJoueur;
                        }
                        cout << "Le joueur attaque " << nbAttaquesJoueur << " fois. Nombre de degats infliges : " << nbDegatsPotentiels << endl << endl;
                    }                  
                    else
                    {
                        cout << "Le joueur n'attaque pas" << endl << endl;
                    }

                    if (nbBonusJoueur > 0)
                    {
                        nbToursJoueur += nbBonusJoueur;
                    }

                    //Actions cachées de l'adversaire
                    if (nbBoucliersAdversaire > 0 && nbBonusAdversaire > 0)
                    {
                        cout << "L'adversaire avait accumule " << nbBonusAdversaire << " bonus et avait bloque " << nbBoucliersAdversaire << " fois";
                        if (nbAttaquesJoueur == 0)
                        {
                            cout << ". Bouclier de l'adversaire inutile!";
                        }
                        else if (nbBoucliersAdversaire < nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur partiellement bloque";
                        }
                        else if (nbBoucliersAdversaire >= nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur completement bloque";
                        }
                        cout << endl;
                    }
                    else if (nbBoucliersAdversaire > 0)
                    {
                        cout << "L'adversaire avait bloque " << nbBoucliersAdversaire << " fois";
                        if (nbAttaquesJoueur == 0)
                        {
                            cout << ". Bouclier de l'adversaire inutile!";
                        }
                        else if (nbBoucliersAdversaire < nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur partiellement bloque";
                        }
                        else if (nbBoucliersAdversaire >= nbAttaquesJoueur)
                        {
                            cout << ". Attaque du joueur completement bloque";
                        }
                        cout << endl;
                    }
                    else if(nbBonusAdversaire > 0)
                    {
                        cout << "L'adversaire avait accumule " << nbBonusAdversaire << " bonus" << endl;
                    }                                                     

                    //Vérifications de mort
                    if (genimon->getPV() <= 0)
                    {
                        unGenimonMort = true;
                        victoire = true;
                        genimon->setPV(0); //Minimum de pv à 0

                        afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                        cout << "Victoire du joueur! " << genimon->getNom() << " est KO" << endl << endl;
                        genimon->setPV(genimon->pvMax); //pv régénéré
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                    }

                    //Fin de tour
                    if (!unGenimonMort)
                    {
                        afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                        nbAttaquesAdversaire = 0;
                        nbBoucliersAdversaire = 0;
                        nbBonusAdversaire = 0;
                    }

                    //Fin de manche
                    if (!joueurCommence && !unGenimonMort)
                    {                                        
                        ++numeroManche;
                        cout << "\n----Manche #" << numeroManche << "----" << endl;
                    }                
                }

                tourJoueur = false;
            }
            else
            {
                int nbBoucliersMaxAdversaire = 10;
                nbToursAdversaire += 2;
                cout << "Tour Adversaire. Nombre de coup: " << nbToursAdversaire << endl;
                std::this_thread::sleep_for(std::chrono::seconds(3));                           

                //Cas #1: si le joueur fait la première action dans la partie et qu'il n'a pas attaqué
                if (joueurCommence && numeroManche == 1 && nbAttaquesJoueur == 0)
                {
                    int choix;
                    while (nbToursAdversaire > 0)
                    {
                        choix = rand() % 5;
                        if (choix == 0)
                        {
                            nbAttaquesAdversaire++;
                            nbToursAdversaire--;
                        }
                        else if (choix == 1 || choix == 2)
                        {
                            nbBoucliersAdversaire++;
                            nbToursAdversaire--;
                        }
                        else
                        {
                            nbBonusAdversaire++;
                            nbToursAdversaire--;
                        }
                    }                   
                }

                //Cas #2: si l'adversaire peut potentiellement tuer directement le joueur
                if (nbToursAdversaire * (genimon->getDegats() + variationDegatsAdversaire) >= genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV())
                {
                    int choix = rand() % 2;
                    if (choix == 0)
                    {
                        nbAttaquesAdversaire = nbToursAdversaire;
                        nbToursAdversaire = 0;
                    }
                }           

                //Cas #3: si la vie de l'adversaire est en-dessous 50%
                if (genimon->getPV() <= genimon->pvMax/2)
                {
                    int choix = rand() % 2;
                    if (choix == 0)
                    {
                        nbBonusAdversaire = nbToursAdversaire / 2;
                        nbBoucliersAdversaire = nbToursAdversaire - nbBonusAdversaire;
                        nbToursAdversaire = 0;
                    }                 
                }

                //Cas #4: si le joueur fait juste attaquer
                if (nbBoucliersJoueur == 0 && nbBonusJoueur == 0)
                {
                    nbBoucliersMaxAdversaire = nbAttaquesAdversaire;
                }

                //Si aucuns des cas spéciaux
                int choix = rand() % 3;
                if (choix == 0 || choix == 1)
                {
                    int choix2;
                    while (nbToursAdversaire > 0)
                    {
                        choix2 = rand() % 3;
                        if (choix2 == 0)
                        {
                            nbAttaquesAdversaire++;
                            nbToursAdversaire--;
                        }
                        else if (choix2 == 1)
                        {
                            if (nbBoucliersAdversaire < nbBoucliersMaxAdversaire)
                            {
                                nbBoucliersAdversaire++;
                                nbToursAdversaire--;
                            }                          
                        }
                        else
                        {
                            if (nbBonusAdversaire < 4)
                            {
                                nbBonusAdversaire++;
                                nbToursAdversaire--;
                            }
                        }
                    }
                }
                else if (nbToursAdversaire > 0)
                {
                    int choix3 = rand() % 5;
                    if (choix3 == 0)
                    {
                        nbAttaquesAdversaire = nbToursAdversaire;
                    }
                    else if (choix3 == 1 && nbToursAdversaire < 5)
                    {
                        nbBonusAdversaire = nbToursAdversaire;
                    }
                    else if (choix3 == 2)
                    {
                        nbAttaquesAdversaire = nbToursAdversaire / 2;
                        nbBonusAdversaire = nbToursAdversaire - nbAttaquesAdversaire;
                    }
                    else if (choix3 == 3)
                    {
                        nbBonusAdversaire = nbToursAdversaire / 2;
                        nbBoucliersAdversaire = nbToursAdversaire - nbBonusAdversaire;
                    }
                    else
                    {
                        nbAttaquesAdversaire = nbToursAdversaire / 2;
                        nbBoucliersAdversaire = nbToursAdversaire - nbAttaquesAdversaire;
                    }
                    nbToursAdversaire = 0;
                }                       
                
                //Actions adversaire
                int nbDegatsPotentiels = 0;
                if (nbAttaquesAdversaire > 0)
                {
                    for (int i = 1; i <= nbAttaquesAdversaire; i++)
                    {
                        if (i > nbBoucliersJoueur)
                        {
                            genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].varierPV(-(genimon->getDegats() + variationDegatsAdversaire));                          
                        }
                        nbDegatsPotentiels += genimon->getDegats() + variationDegatsAdversaire;
                    }
                    cout << "L'adversaire attaque " << nbAttaquesAdversaire << " fois. Nombre de degats infliges: " << nbDegatsPotentiels << endl << endl;
                }       
                else
                {
                    cout << "L'adversaire n'attaque pas" << endl << endl;
                }

                if (nbBonusAdversaire > 0)
                {
                    nbToursAdversaire += nbBonusAdversaire;
                }         

                // Actions cachées du joueur
                if (nbBoucliersJoueur > 0 && nbBonusJoueur > 0)
                {
                    cout << "Le joueur avait accumule " << nbBonusJoueur << " bonus et avait bloque " << nbBoucliersJoueur << " fois";
                    if (nbAttaquesAdversaire == 0)
                    {
                        cout << ". Bouclier du joueur inutile!";
                    }
                    else if (nbBoucliersJoueur < nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire partiellement bloque";
                    }
                    else if (nbBoucliersJoueur >= nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire completemet bloque";
                    }
                    cout << endl;
                }
                else if (nbBoucliersJoueur > 0)
                {
                    cout << "Le joueur avait bloque " << nbBoucliersJoueur << " fois";
                    if (nbAttaquesAdversaire == 0)
                    {
                        cout << ". Bouclier du joueur inutile!";
                    }
                    else if (nbBoucliersJoueur < nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire partiellement bloque";
                    }
                    else if (nbBoucliersJoueur >= nbAttaquesAdversaire)
                    {
                        cout << ". Attaque de l'adversaire completement bloque";
                    }
                    cout << endl;
                }
                else if (nbBonusJoueur > 0)
                {
                    cout << "Le joueur avait accumule " << nbBonusJoueur << " bonus" << endl;
                }

                //Vérification de mort
                if (genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].getPV() <= 0 && !unGenimonMort)
                {
                    unGenimonMort = true;
                    genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ].setPV(0); //Minimum de pv à 0

                    afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                    cout << "Defaite du joueur! " << genimonChoisi.getNom() << " est KO" << endl << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                }       

                //Fin de tour
                if (!unGenimonMort)
                {
                    afficherStatsManche(genimon, genidex[infos.indexI].listeGenimonAttrapé[infos.indexJ]);
                    nbAttaquesJoueur = 0;
                    nbBoucliersJoueur = 0;
                    nbBonusJoueur = 0;
                }

                //Fin de manche
                if (joueurCommence && !unGenimonMort)
                {                    
                    ++numeroManche;
                    cout << "\n----Manche #" << numeroManche << "----" << endl;
                }
                
                tourJoueur = true;            
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

//le jeu est réussi si le joueur a capturé au moins un Genimon de chaque type
bool Joueur::jeuReussi() {
	for (int i = 0; i < 8; i++)
	{
		if (genidex[i].listeGenimonAttrapé.size() == 0)
		{
			return false;
		}
	}
	cout << "Felicitation! Vous avez capture au moins un Genimon de chaque type!" << endl;
	cout << "Voulez-vous continuer a jouer? (O/N)" << endl;
	bool operationFinie = false;
	if (_getch() == 'o' || _getch() == 'O')
	{
		return false;
	}
	else if (_getch() == 'n' || _getch() == 'N')
	{
		return true;
	}
	return true;
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
		bool jeuReussi1 = false;
		if (jeuReussi() == 1) {
			jeuReussi1 = true;
		}
		else {
			jeuReussi1 = false;
        }
        if (jeuReussi1 == 1) {
            exit(0);
        }

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