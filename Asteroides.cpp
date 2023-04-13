/**<

INFORMATIONS :

LE PROGRAMME PEUT ETRE LENT SELON LA QUALITE DE VOTRE ORDINATEUR.

SI VOUS ETES BLOQUE, ALLEZ DANS LE MENU 'PAUSE' ET APPUYEZ SUR LA TOUCHE 'K' POUR REINITIALISER VOTRE PARTIE.
SI CELA NE FONCTIONNE PAS, FERMEZ LE PROGRAMME AVEC LA TOUCHE 'ESPACE' ET RELANCEZ LE JEU.

(c) Améliorations récentes
(i) Modifications du 09/04/2023
- Modification de la structure 'Asteroid' : les images des astéroïdes ont été déplacées dans la structure 'World' pour qu'elles ne soient chargées qu'une seule fois.
- Ajout d'une planète et d'un fond d'écran (Background) différent pour chaque stage.
- Ajout de trois lasers de couleur différentes, choisi aléatoirement lorsque le laser est activé.
- Ajout d'une UI (User Interface) supplémentaire : mini-histoire pour chaque stage.
- Ajout du curseur.
- Modification de l'Easter Egg pour problèmes de copyright.
- Modification du mouvement du laser lors d'une partie perdue. Le laser s'immobilise. [Apparition du bug de la partie perdu moins fréquente (Cf. readme Article V, (b))]
- Resolution du bug de score pour la dernière planete. Le score de la dernière planete n'était pas comptabilisé.
- Correction de l'UI mini-histoire. Il n'y avait pas d'affichage lorsque le joueur choisissait de continuer le jeu après l'avoir fini.
(ii) Modification du 10/04/2023
- Ajout de 'w.collision' qui permet d'afficher les messages de la partie perdue meme quand l'asteroide est detruit [Plus d'appartition du bug de la partie perdu]

/**< -------------------------------------------------- //

        LIBRAIRIES

//   -------------------------------------------------- */

#include <Grapic.h>

using namespace grapic;

#include <ctime>
#include <cstdlib>

#include <ostream>

#include <Windows.h>
#include "MMsystem.h"

using namespace std;

/**< -------------------------------------------------- //

        CONSTANTES

//   -------------------------------------------------- */

const int MAX_ASTEROID = 50;

const float EPS = 1E-07;
const float G = 6.67408 * 1E-11;

const float dt = 0.01;

const int DIMW = 550;

/**< -------------------------------------------------- //

        STRUCTURES

//   -------------------------------------------------- */

struct Vecteur
{
    float x, y;
};

const Vecteur g = {0, -9.81};

struct Particle
{
    Vecteur position;
    Vecteur vitesse;
    Vecteur force;
    float masse;
};

struct Asteroid
{
    Vecteur position;
    float rayon;

    float masse;
};

struct World
{
    /**< SOUCOUPE */

    Particle soucoupe;
    Particle laser;

    Image imSoucoupe = image("apps/Cherazade/Asteroides/Data/Soucoupe.png");
    Image imReactor = image("apps/Cherazade/Asteroides/Data/Reacteur.png");
    Image imCollide = image("apps/Cherazade/Asteroides/Data/Explosion.png");

    Image imLaser;

    Image imLaserRed = image("apps/Cherazade/Asteroides/Data/laserRed.png");
    Image imLaserOrange = image("apps/Cherazade/Asteroides/Data/laserOrange.png");
    Image imLaserYellow = image("apps/Cherazade/Asteroides/Data/laserYellow.png");

    int nbLaser;

    /**< LUNE */

    Asteroid lune;

    /**< TABLEAU D'ASTEROIDES */

    int nbAsteroid;
    Asteroid tabAsteroid[MAX_ASTEROID];
    Image imAst = image("apps/Cherazade/Asteroides/Data/Asteroide.png");
    Image imDeb = image("apps/Cherazade/Asteroides/Data/Debris.png");

    /**< STAGES */

    int nbStage;

    Image bg0 = image("apps/Cherazade/Asteroides/Data/Background3.png");
    Image bg1 = image("apps/Cherazade/Asteroides/Data/Background1.png");
    Image bg2 = image("apps/Cherazade/Asteroides/Data/Background4.png");

    Image planet0 = image("apps/Cherazade/Asteroides/Data/Aquamarine.png");
    Image planet1 = image("apps/Cherazade/Asteroides/Data/Cratered.png");
    Image planet2 = image("apps/Cherazade/Asteroides/Data/Snowy.png");

    /**< JEU/AUTRE */

    int score;
    int win;
    int collision;

    Menu m;

    Image imCursor = image("apps/Cherazade/Asteroides/Data/cursor_hand.png");
    Image imYouWin = image("apps/Cherazade/Asteroides/Data/YouWin.png");
    Image imYouLose = image("apps/Cherazade/Asteroides/Data/YouLose.png");
    Image menu = image("apps/Cherazade/Asteroides/Data/MenuSF.jpg");
    Image imRobot = image("apps/Cherazade/Asteroides/Data/robot-preview.png");
    Image imBorderSF = image("apps/Cherazade/Asteroides/Data/BorderSF.png");
    Image imStory = image("apps/Cherazade/Asteroides/Data/glassPanel.png");

    /**< EASTER EGG */

    Image imC = image("apps/Cherazade/Asteroides/Data/spaceCat.png");
    Image iml = image("apps/Cherazade/Asteroides/Data/layachi.png");
};

/**< -------------------------------------------------- //

 SURCHARGE D'OPERATEURS / FONCTIONS DE BASE (VECTEURS)

//   -------------------------------------------------- */

Vecteur makeVecteur (float x, float y)
{
    Vecteur v;
    v.x = x;
    v.y = y;
    return v;
}

Vecteur makeVecteurExp (float r, float ThetaRad)
{
    return makeVecteur(r*cos(ThetaRad), r*sin(ThetaRad));
}

float toRadian (float degre)
{
    return ((degre * M_PI) / 180);
}

Vecteur operator + (Vecteur a, Vecteur b)
{
    return makeVecteur(a.x + b.x, a.y + b.y);
}

Vecteur operator - (Vecteur a, Vecteur b)
{
    return makeVecteur(a.x - b.x, a.y - b.y);
}

Vecteur operator * (Vecteur a, float lambda)
{
    return makeVecteur(lambda*a.x, lambda*a.y);
}

Vecteur operator * (float lambda, Vecteur a)
{
    return makeVecteur(lambda*a.x, lambda*a.y);
}

Vecteur operator * (Vecteur a, Vecteur b)
{
    return makeVecteur(a.x*b.x - a.y*b.y, a.y*b.x + a.x*b.y);
}

Vecteur operator / (Vecteur a, float lambda)
{
    return makeVecteur(a.x/lambda, a.y/lambda);
}

Vecteur operator / (float lambda, Vecteur a)
{
     return makeVecteur(a.x/lambda, a.y/lambda);
}

Vecteur Rotate (Vecteur a, float vx, float vy, float angleRad)
{
    Vecteur v, b, rot;
    v = makeVecteur(vx, vy);
    rot = makeVecteurExp(1, angleRad);
    b = (a-v) * rot + v;
    return b;
}

float distance(Vecteur positionA, Vecteur positionB)
{
    return (sqrt((positionA.x - positionB.x)*(positionA.x - positionB.x)+(positionA.y - positionB.y)*(positionA.y - positionB.y)));
}

Vecteur normaliseVecteur(Vecteur v)
{
    float n;
    n = sqrt(v.x*v.x + v.y*v.y);
    if(fabs(n)>EPS)
    {
        v.x = v.x/n;
        v.y = v.y/n;
    }
    return v;
}

/**< -------------------------------------------------- //

        INITIALISATION DES PARAMETRES

//   -------------------------------------------------- */

void initPart(Particle& p, Vecteur pos, Vecteur v, Vecteur f, float m)
{
    p.position = pos;
    p.vitesse = v;
    p.force = f;
    p.masse = m;
}

/**< FONCTION RAND() [CALCUL DE LA POSITION / DU RAYON ALEATOIRE DES ASTEROIDES] */

float randPositionX()
{
    int randPositionX = (rand() % DIMW);
    return (float(randPositionX));
}

float randPositionY()
{
    int randPositionY = (rand() % ((8*DIMW)/10) + 2 * DIMW/10);
    return (float (randPositionY));
}

float randRayon() /**< LE RAYON DE L'ASTEROIDE EST COMPRIS ENTRE 10 ET 30 AFIN QUE CELUI-CI RESTE VISIBLE AU YEUX DU JOUEUR */
{
    int randRayon = (rand() % 30 + 10);
    return (float(randRayon));
}

/**< PROCEDURES D'INITIALISATION */

void initScore(World& w) /**< LE SCORE EST INITIALISE SEPAREMENT POUR QU'IL NE SOIT PAS REINITIALISE LORSQUE LE JOUEUR PASSE AU STAGE SUIVANT */
{
    w.nbStage = 0;
    w.score = 0;
    w.win = 0;
}

void initLaser(World& w)
{
    w.nbLaser = rand()%2; /**< COULEUR DU LASER ALEATOIRE */

    if(w.nbLaser == 0)
    {
        w.imLaser = w.imLaserRed;
    }
    if(w.nbLaser == 1)
    {
        w.imLaser = w.imLaserOrange;
    }
    else
    {
        w.imLaser = w.imLaserYellow;
    }

    if(w.laser.masse > 0) /**< UNE MASSE POSITIVE SIGNIFIE QUE LE LASER A ETE ACTIVE */
    {
        w.laser.position = makeVecteur(w.soucoupe.position.x, w.soucoupe.position.y + 10);
        w.laser.force = w.laser.vitesse = makeVecteur(0, 0);
    }
    else
    {
        w.laser.position = makeVecteur(DIMW*2, DIMW*2);
        w.laser.force = w.laser.vitesse = makeVecteur(0, 0);
    }
}

void initWorld(World& w, int nbAsteroid)
{
    w.collision = 0;

    /**< INIT SOUCOUPE */

    w.soucoupe.masse = 1;
    initPart(w.soucoupe, {DIMW/2, DIMW/10}, {0, 0}, {0, 0}, w.soucoupe.masse);

    /**< INIT LASER */

    w.laser.masse = -1; /**< PAR DEFAUT, LE LASER N'EST PAS ACTIVE */
    initLaser(w);

    /**< INIT LUNE */

    w.lune.position = makeVecteur(DIMW/4, (9*DIMW)/10);
    w.lune.rayon = 15;

    w.lune.masse = 1; /**< CETTE VALEUR N'EST PAS UTILISEE DANS LE PROGRAMME */

    /**< INIT ASTEROID */

    w.nbAsteroid = nbAsteroid;

    for(int i = 0; i<w.nbAsteroid; i++)
    {
        w.tabAsteroid[i].position.x = randPositionX();
        w.tabAsteroid[i].position.y = randPositionY();
        w.tabAsteroid[i].rayon = randRayon();

        w.tabAsteroid[i].masse = w.tabAsteroid[i].rayon * pow(10, 13);
    }
}

/**< -------------------------------------------------- //

 LOI DE L'ATTRACTION UNIVERSELLE (PHYSIQUE CLASSIQUE)
 ATTENTION : SEULEMENT LA SOUCOUPE EST SOUMISE AUX FORCES. LES AUTRES FORCES SONT NEGLIGEE.

//   -------------------------------------------------- */

/**< FONCTIONS - CALCUL DES FORCES APPLIQUES A LA SOUCOUPE */

Vecteur forceNull()
{
    Vecteur v;
    v = makeVecteur(0, 0);
    return v;
}

Vecteur forceAsteroidsSurSoucoupe(World w)
{
    Vecteur fAS = makeVecteur(0, 0);

    for(int i=0; i<w.nbAsteroid; i++)
    {
        fAS = fAS - ((G * w.tabAsteroid[i].masse * w.soucoupe.masse) /
        pow(distance(w.tabAsteroid[i].position, w.soucoupe.position), 2)) *
        normaliseVecteur(w.soucoupe.position - w.tabAsteroid[i].position);
    }

    return fAS;
}

Vecteur forceReacteursSurSoucoupe(World w, float forceReacteur)
{
    if (isMousePressed(SDL_BUTTON_LEFT))
    {
        int x,y;

        mousePos(x, y);
        Vecteur mouse_pos = makeVecteur(x, y);

        Vecteur soucoupeVersMouse = mouse_pos - w.soucoupe.position ;

        image_draw(w.imReactor, w.soucoupe.position.x - 15, w.soucoupe.position.y - 75, 75, 75);

        return forceReacteur * normaliseVecteur(soucoupeVersMouse);
    }
    else
    {
        return forceNull();
    }
}

Vecteur forceTotaleSoucoupe(World w)
{
    Vecteur fS = forceAsteroidsSurSoucoupe(w) + forceReacteursSurSoucoupe(w, 10);

    return fS;
}

/**< PROCEDURE - MISE A JOUR DE LA VITESSE ET DE LA POSITION DE LA SOUCOUPE */

void vitessePositionSoucoupe(World& w)
{
    w.soucoupe.force = forceTotaleSoucoupe(w);
    w.soucoupe.vitesse = w.soucoupe.vitesse + (w.soucoupe.force / w.soucoupe.masse) * dt ;
    w.soucoupe.position = w.soucoupe.position + w.soucoupe.vitesse * dt ;
}

/**< -------------------------------------------------- //

        PROCEDURE - FONCTIONNEMENT DU LASER

//   -------------------------------------------------- */

void actionlaser(World& w)
{
    /**< ACTIVATION DU LASER */

    if(isKeyPressed(SDLK_z))
    {
        if(w.laser.position.y > DIMW or w.laser.position.y < 0)
        {
            if(w.laser.position.x > DIMW or w.laser.position.x < 0)
            {
                if(w.laser.masse < 0 and w.soucoupe.masse > 0)
                {
                     w.laser.masse = 1;
                     initLaser(w);
                }
            }
        }
    }

    /**< LE LASER EST HORS DE L'ECRAN */

    if(w.laser.position.y > DIMW or w.laser.position.y < 0)
    {
        w.laser.masse = -1;
        w.laser.vitesse = forceNull();
        initLaser(w);
    }

    if(w.laser.position.x > DIMW or w.laser.position.x < 0)
    {
        w.laser.masse = -1;
        w.laser.vitesse = forceNull();
        initLaser(w);
    }

    /**< LE LASER DETRUIT UN ASTEROIDE */

    float distanceAsteroidsLaser[w.nbAsteroid];

    for(int i=0; i<w.nbAsteroid; i++)
    {
        distanceAsteroidsLaser[i] = distance(w.tabAsteroid[i].position, w.laser.position);

            if(distanceAsteroidsLaser[i] < w.tabAsteroid[i].rayon and w.tabAsteroid[i].masse > 0)
            {
                w.laser.masse = -1;
                w.laser.vitesse = forceNull();
                initLaser(w);

                w.tabAsteroid[i].masse = -1;

                w.score = w.score + 100 * w.tabAsteroid[i].rayon;
            }
    }

    /**< MISE A JOUR DE LA VITESSE ET DE LA POSITION DU LASER */

    if(w.laser.masse > 0)
    {
         w.laser.force = makeVecteur(0, 100);
         w.laser.vitesse =  w.laser.vitesse + w.laser.force * dt;
         w.laser.position = w.laser.position + w.laser.vitesse * dt;
    }
}

/**< -------------------------------------------------- //

        PROCEDURE - PARTIE PERDU OU GAGNEE

//   -------------------------------------------------- */

void winOrLose(World& w)
{

    /**< PARTIE GAGNEE : LUNE ATTEINTE */

    int ajoutAsteroids = w.nbAsteroid;

    float distanceLuneSoucoupe = distance(w.lune.position, w.soucoupe.position);

    if(distanceLuneSoucoupe<w.lune.rayon)
    {

        /**< STAGE SUIVANT */

        if(ajoutAsteroids < 30)
        {
            ajoutAsteroids = ajoutAsteroids + 10;
            initWorld(w, ajoutAsteroids);

            w.score = w.score + 10000;
            w.nbStage++;

            if(w.nbStage == 1)
            {
                w.bg0 = w.bg1;
                w.planet0 = w.planet1;
            }
            if(w.nbStage == 2)
            {
                w.bg0 = w.bg2;
                w.planet0 = w.planet2;
            }
        }

        /**< FIN DU JEU */

        else
        {
            if(w.win == 0) /**< CORRECTION DU BUG DE LA DERNIERE PLANETE */
            {
                w.score = w.score + 10000;
                w.win++;
            }

            w.soucoupe.masse = -1;

            color(255, 255, 255);
            image_draw(w.imYouWin, DIMW/4, DIMW/3, DIMW/2, DIMW/3);
            print(DIMW/3 - 15, 5*DIMW/8 + 35, " Press the 'g' key to play with the hero !");

            if(isKeyPressed(SDLK_g))
            {
                w.imSoucoupe = w.imC ;

                initWorld(w, 10);
                w.nbStage = 0;

                w.bg0 = image("apps/Cherazade/Asteroides/Data/Background3.png");
                w.planet0 = image("apps/Cherazade/Asteroides/Data/Aquamarine.png");
            }

            if(isKeyPressed(SDLK_k))
            {
                initWorld(w, 10);
                w.nbStage = 0;

                w.bg0 = image("apps/Cherazade/Asteroides/Data/Background3.png");
                w.planet0 = image("apps/Cherazade/Asteroides/Data/Aquamarine.png");
            }
        }
    }

    /**< PARTIE PERDUE : COLLISION INELASTIQUE */

    float distanceAsteroidsSoucoupe[w.nbAsteroid];

    for(int i=0; i<w.nbAsteroid; i++)
    {
        distanceAsteroidsSoucoupe[i] = distance(w.tabAsteroid[i].position, w.soucoupe.position);

        if(distanceAsteroidsSoucoupe[i] < w.tabAsteroid[i].rayon and w.tabAsteroid[i].masse > 0)
        {
            w.collision = 1;

            w.soucoupe.masse = -1;
            w.laser.masse = -1;

            if(w.collision == 1) /**< CORRECTION DU BUG DE LA PARTIE PERDU */
            {
                image_draw(w.imCollide, w.soucoupe.position.x - 15 , w.soucoupe.position.y - 15, 30, 30);

                image_draw(w.imYouLose, DIMW/4, DIMW/4, DIMW/2, DIMW/2);

                color(255, 255, 255);
                print(DIMW/3 , DIMW/5, "Press the 'k' key to start a new game");

                if(isKeyPressed(SDLK_k))
                {
                    initWorld(w, 10);
                    initScore(w);

                    w.bg0 = image("apps/Cherazade/Asteroides/Data/Background3.png");
                    w.planet0 = image("apps/Cherazade/Asteroides/Data/Aquamarine.png");
                }

            }
        }
    }
}

/**< -------------------------------------------------- //

        PROCEDURE - DRAW ET UPDATE

//   -------------------------------------------------- */

void drawWorld(World& w)
{
    /**< AFFICHAGE DES ELEMENTS DU JEU + MENU */

    image_draw(w.bg0, 0, 0, DIMW, DIMW);

    image_draw(w.planet0, w.lune.position.x - w.lune.rayon, w.lune.position.y - w.lune.rayon, 30, 30);

    menu_draw(w.m, 5,5, 100, 102);

    for(int i = 0; i<w.nbAsteroid; i++)
    {
        if(w.tabAsteroid[i].masse > 0)
        {
            /**< ASTEROID NON DETRUIT */

            image_draw(w.imAst, w.tabAsteroid[i].position.x - w.tabAsteroid[i].rayon,
            w.tabAsteroid[i].position.y - w.tabAsteroid[i].rayon, w.tabAsteroid[i].rayon * 2, w.tabAsteroid[i].rayon * 2);
        }
        else
        {
            /**< ASTEROID DETRUIT */

            image_draw(w.imDeb, w.tabAsteroid[i].position.x - w.tabAsteroid[i].rayon,
            w.tabAsteroid[i].position.y - w.tabAsteroid[i].rayon, w.tabAsteroid[i].rayon * 2, w.tabAsteroid[i].rayon * 2);
        }
    }

    image_draw(w.imLaser, w.laser.position.x - 5, w.laser.position.y + 10, 15, 15);

    image_draw(w.imSoucoupe, w.soucoupe.position.x - 15, w.soucoupe.position.y - 15, 30, 30);

    int x, y;
    mousePos(x, y);

    image_draw(w.imCursor, x - 15, y - 15, 30, 30);

    /**< AFFICHAGE STORYLINE */

    image_draw(w.imStory, 21 * DIMW/30, DIMW/40, 150, 150);

    if(w.nbStage == 0)
    {
        image_draw(w.imRobot, 21 * DIMW/30 + 15, DIMW/40 + 100, 50, 50);
        print(21 * DIMW/30 + 15, DIMW/40 + 85, "Reach planet Ywosn !");
        print(21 * DIMW/30 + 15, DIMW/40 + 60, "That is their last known");
        print(21 * DIMW/30 + 15, DIMW/40 + 45, "position !");
    }
    if(w.nbStage ==  1)
    {
        image_draw(w.imRobot, 21 * DIMW/30 + 15, DIMW/40 + 100, 50, 50);
        print(21 * DIMW/30 + 15, DIMW/40 + 85, "Reach planet Ratec !");
        print(21 * DIMW/30 + 15, DIMW/40 + 60, "They have fled with the");
        print(21 * DIMW/30 + 15, DIMW/40 + 45, "hero there !");
        print(21 * DIMW/30 + 15, DIMW/40 + 30, "There is more Asteroids");
        print(21 * DIMW/30 + 15, DIMW/40 + 15, "in this area, be careful !");
    }
    if(w.nbStage == 2)
    {
        image_draw(w.imRobot, 21 * DIMW/30 + 15, DIMW/40 + 100, 50, 50);
        print(21 * DIMW/30 + 15, DIMW/40 + 85, "Reach planet Imuaq !");
        print(21 * DIMW/30 + 15, DIMW/40 + 60, "They have fled again !");
        print(21 * DIMW/30 + 15, DIMW/40 + 45, "But their spaceship is");
        print(21 * DIMW/30 + 15, DIMW/40 + 30, "malfunctioning.");
        print(21 * DIMW/30 + 15, DIMW/40 + 15, "Now is your chance !");
    }


    /**< AFFICHAGE DES INFORMATIONS RELATIVES AU JEU */

    image_draw(w.imBorderSF, DIMW-150, DIMW-100, 135, 85);

    color(255, 255, 255);

    print(DIMW-125, DIMW-60, "LEVEL : ");
    print(DIMW-75, DIMW-60, w.nbAsteroid/10);


    print(DIMW-125, DIMW-75, "SCORE : ");
    print(DIMW-75, DIMW-75, w.score);
}

void updateWorld(World& w)
{
    winOrLose(w);

    actionlaser(w);

    /**< LA SOUCOUPE RESTE DANS L'ECRAN */

    if(w.soucoupe.position.y > DIMW or w.soucoupe.position.y < 0)
    {
        w.soucoupe.vitesse = (-1) * (w.soucoupe.vitesse - (0.8) * w.soucoupe.vitesse);
    }

    if(w.soucoupe.position.x < 0 or w.soucoupe.position.x > DIMW)
    {
        w.soucoupe.vitesse = (-1) * (w.soucoupe.vitesse - (0.8) * w.soucoupe.vitesse);
    }

    /**< MOUVEMENT DE LA SOUCOUPE ET DES ASTEROIDES */

    if(w.soucoupe.masse > 0)
    {
        vitessePositionSoucoupe(w);

        for(int i=0; i<w.nbAsteroid; i++)
        {
            w.tabAsteroid[i].position = Rotate(w.tabAsteroid[i].position, w.tabAsteroid[i].position.x + 1,
            w.tabAsteroid[i].position.y + 1, toRadian(2));
        }
    }
}

/**< POUR SIMPLIFIER L'ECRITURE DANS LE MENU */

void jeu(World& w)
{
    drawWorld(w);
    updateWorld(w);
}

/**< -------------------------------------------------- //

        MENU - 'PAUSE'

//   -------------------------------------------------- */

void menu(World& w)
{

    image_draw(w.menu, 0, 0, DIMW, DIMW);

    image_draw(w.imRobot, DIMW/2 - 22, 5*DIMW/8 + 75, DIMW/12, DIMW/12);

    menu_draw(w.m, 5,5, 100, 102);

    if(isKeyPressed(SDLK_k))
    {
        initWorld(w, 10);
        initScore(w);

        w.bg0 = image("apps/Cherazade/Asteroides/Data/Background3.png");
        w.planet0 = image("apps/Cherazade/Asteroides/Data/Aquamarine.png");
    }

    /**< EXPLICATION DU JEU [ENG] */

    color(255, 255, 255);

    print(DIMW/20 + 25, 5*DIMW/8 + 50, " NEW GAME : Press the 'k' key to start a new game");

    print(DIMW/20 + 25, 5*DIMW/8 + 15, " RESUME/PAUSE : Click on the 'resume' button (lower left corner) to resume the");
    print(DIMW/20 + 25, 5*DIMW/8 - 10, " game or on 'pause' to pause the game. Press the 'space' key to quit the game");

    print(DIMW/20 + 25, 5*DIMW/8 - 45, " WIN/LOSE : You win the game if you reach the moon at level 3, you lose if you" );
    print(DIMW/20 + 25, 5*DIMW/8 - 70, " collide with an asteroid" );

    print(DIMW/20 + 25, 5*DIMW/8 - 105, " SCORE : To increase your score you have to reach the moon and shoot at asteroids");

    print(DIMW/20 + 25, 5*DIMW/8 - 140, " KEYS : Press the left mouse button while moving the mouse to move and press");
    print(DIMW/20 + 25, 5*DIMW/8 - 165, " the 'z' key to fire a beam");

    color(255, 0, 0);

    print(DIMW/20 + 65, 5*DIMW/8 - 200, " Aliens have attacked Earth and have kidnapped its almighty hero !");
    print(DIMW/20 + 50, 5*DIMW/8 - 225, " Reach their planet to save him and destroy the asteroids to protect Earth !");

    /**< EASTER EGG */

    if(isKeyPressed(SDLK_g))
    {
        w.imSoucoupe = w.imC;
    }

    if(isKeyPressed(SDLK_s))
    {
        w.imSoucoupe = image("apps/Cherazade/Asteroides/Data/Soucoupe.png");
    }

    if(isKeyPressed(SDLK_l))
    {
        w.imSoucoupe = w.iml;
    }
}

/**< -------------------------------------------------- //

        FONCTION - MAIN

//   -------------------------------------------------- */

int main(int , char**)
{
    bool stop = false;

	winInit("Asteroides",DIMW,DIMW);

	// bool played = PlaySound(TEXT("ObservingTheStar.wav"), NULL, SND_SYNC);

	World w;

	initWorld(w, 10);
	initScore(w);

    menu_add(w.m, "Pause");
    menu_add(w.m, "Resume");

    /**< BOUCLE INFINIE */

	while(!stop)
    {
        winClear();

        menu_draw(w.m, 5,5, 100, 102);

        switch(menu_select(w.m))
        {
            case 0 : menu(w); break;
            case 1 : jeu(w); break;
        }

        stop = winDisplay();

        /**< APPUYEZ SUR LA TOUCHE 'ESPACE' POUR QUITTER LE JEU */

        if(isKeyPressed(SDLK_SPACE))
        {
            winQuit();
        }
    }
	return 0;
}

/**< FIN DU CODE, MERCI D'AVOIR LU/JOUE */
