/**<

INFORMATIONS :

LE PROGRAMME PEUT ETRE LENT SELON LA QUALITE DE VOTRE MACHINE.

SI VOUS ETES BLOQUE, ALLEZ DANS LE MENU 'PAUSE' ET APPUYEZ SUR LA TOUCHE 'K' POUR REINITIALISER VOTRE PARTIE.
SI CELA NE FONCTIONNE PAS, FERMEZ LE PROGRAMME AVEC LA TOUCHE 'ESPACE' ET RELANCEZ LE JEU.

(a) Ameliorations récentes
Modifications du 09/04/2023
- Images, UI, mini-histoire.
- Resolution du bug de score pour la dernière planete. (Cf. readme Article V, Section 5.01, (a))
Modification du 10/04/2023
- Travail sur le bug de la partie perdue. (Cf. readme Article V, Section 5.01, (b))
Modification du 14/04/2023
- Ajout du mode INFINITE.
Modification du 15/04/2023
- Images, UI.
Modification du 16/04/2023
- Copyright des images.
Modification du 22/04/2023
- Ajout d'une musique de fond.
Modification du 28/04/2023
- Réaparition des Asteroides.
Modification du 03/05/2023
- Mémoire du score maximal du joueur dans un fichier texte.

/**< -------------------------------------------------- //

        LIBRAIRIES

//   -------------------------------------------------- */

#include <Grapic.h>

using namespace grapic;

#include <ctime>
#include <cstdlib>

#include <ostream>

using namespace std;

#include <SDL2/SDL_mixer.h>

#include <fstream>

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

    Image imAst;
    int nbAst; /**< indice du choix aléatoire de l'image pour l'astéroide */

    /**< ROTATION DES OBJETS */

    float vitesse;
    float angle;
};

struct World
{
    /**< SOUCOUPE */

    Particle soucoupe;
    Particle laser;

    Image imSoucoupe = image("data/asteroides/Soucoupe.png");
    Image imReactor = image("data/asteroides/Reacteur.png");
    Image imExplosion = image("data/asteroides/Explosion.png");

    Image imLaser;

    Image imLaserRed = image("data/asteroides/laserRed.png");
    Image imLaserOrange = image("data/asteroides/laserOrange.png");
    Image imLaserYellow = image("data/asteroides/laserYellow.png");

    int nbLaser; /**< indice du choix aléatoire de l'image pour le laser */

    /**< PLANETE */

    Asteroid planet;

    /**< TABLEAU D'ASTEROIDES */

    int nbAsteroid; /**< nombre d'astéroides réellement simulés */
    Asteroid tabAsteroid[MAX_ASTEROID];

    Image imDeb = image("data/asteroides/Debris.png");

    /**< STAGES */

    int nbStage; /**< indice qui définit l'affichage des différentes planètes et du fond d'écran */
    int nbMission; /**< indice qui définit l'affichage des dialogues */

    Image bg0 = image("data/asteroides/Background3.png");
    Image bg1 = image("data/asteroides/Background1.png");
    Image bg2 = image("data/asteroides/Background4.png");

    Image planet0 = image("data/asteroides/Aquamarine.png");
    Image planet1 = image("data/asteroides/Cratered.png");
    Image planet2 = image("data/asteroides/Snowy.png");

    /**< JEU/AUTRE */

    int score;

    Menu m;
    Image menu = image("data/asteroides/Menu.png");

    Image imYouLose = image("data/asteroides/YouLose.png");
    Image imYouWin = image("data/asteroides/YouWin.png");

    Image imPanel = image("data/asteroides/futureui1.png"); /**< image du score et du niveau */
    Image imPanel04 = image("data/asteroides/Panel04.png"); /**< image des dialogues */

    Image imCursor = image("data/asteroides/cursor_hand.png");

    Image imC = image("data/asteroides/SpaceCat.png"); /**< nouveau personnage jouable après avoir fini le jeu */

    /**< CORRECTION DE BUGS */

    int lastPlanet; /**< correction du bug de la dernière planète */
    int collision; /**< bug de la partie perdue */
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

float randRayon()
{
    int randRayon = (rand() % 30 + 10);
    return (float(randRayon));
}

/**< PROCEDURES D'INITIALISATION */

void initScore(World& w)
{
    w.nbStage = 0;
    w.nbMission = 0;
    w.score = 0;

    w.lastPlanet = 0;
}

void initImAst(World& w)
{
    /**< IMAGE ET VITESSE DE ROTATION ALEATOIRE POUR L'ASTEROIDE */

    for(int i=0; i<w.nbAsteroid; i++)
    {
        w.tabAsteroid[i].nbAst = rand()%3;
        w.tabAsteroid[i].vitesse = rand()%30 +10;

        if(w.tabAsteroid[i].nbAst == 0)
        {
            w.tabAsteroid[i].imAst = image("data/asteroides/planetoids-1.png");
        }
        if(w.tabAsteroid[i].nbAst == 1)
        {
            w.tabAsteroid[i].imAst = image("data/asteroides/planetoids-2.png");
        }
        if(w.tabAsteroid[i].nbAst == 2)
        {
            w.tabAsteroid[i].imAst = image("data/asteroides/planetoids-3.png");
        }
    }
}

void initLaser(World& w)
{
    /**< IMAGE ALEATOIRE POUR LE LASER */

    w.nbLaser = rand()%2;

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

    /**< LASER */

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

    /**< INIT PLANET */

    w.planet.position = makeVecteur(1.5*DIMW/10, (8.5*DIMW)/10);
    w.planet.rayon = 20;

    w.planet.masse = 1; /**< CETTE VALEUR N'EST PAS UTILISEE DANS LE PROGRAMME */

    /**< INIT ASTEROID */

    w.nbAsteroid = nbAsteroid;
    initImAst(w);

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

        Vecteur soucoupeVersMouse = mouse_pos - w.soucoupe.position ; /**< RELATION DE CHASLES */

        image_draw(w.imReactor, w.soucoupe.position.x - 5, w.soucoupe.position.y - 72, 10, 60);

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
        initLaser(w);
    }

    if(w.laser.position.x > DIMW or w.laser.position.x < 0)
    {
        w.laser.masse = -1;
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

    /**< PARTIE GAGNEE : PLANETE ATTEINTE */

    int ajoutAsteroids = w.nbAsteroid;

    float distanceLuneSoucoupe = distance(w.planet.position, w.soucoupe.position);

    if(distanceLuneSoucoupe<w.planet.rayon)
    {

        /**< STAGE SUIVANT */

        if(ajoutAsteroids < 30)
        {
            ajoutAsteroids = ajoutAsteroids + 10;
            initWorld(w, ajoutAsteroids);

            w.score = w.score + 10000;
            w.nbStage++;
            w.nbMission++;

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
            if(w.lastPlanet == 0)
            {
                w.score = w.score + 10000;
                w.lastPlanet++;
            }

            w.soucoupe.masse = -1;
            w.laser.masse = -1;

            for(int i=0; i<w.nbAsteroid; i++)
            {
                 w.tabAsteroid[i].vitesse = 0;
            }

            w.nbStage = 0;
            w.nbMission++;

            image_draw(w.imYouWin, 0, 0, DIMW, DIMW);

            if(isKeyPressed(SDLK_g))
            {
                w.imSoucoupe = w.imC ;
                initWorld(w, 10);

                w.lastPlanet = 0;

                w.bg0 = image("data/asteroides/Background3.png");
                w.planet0 = image("data/asteroides/Aquamarine.png");
            }

            if(isKeyPressed(SDLK_k))
            {
                initWorld(w, 10);

                w.lastPlanet = 0;

                w.bg0 = image("data/asteroides/Background3.png");
                w.planet0 = image("data/asteroides/Aquamarine.png");
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

            for(int i=0; i<w.nbAsteroid; i++)
            {
                 w.tabAsteroid[i].vitesse = 0;
            }

            if(w.collision == 1)
            {
                image_draw(w.imExplosion, w.soucoupe.position.x - 50 , w.soucoupe.position.y - 50, 100, 100);

                image_draw(w.imYouLose, 0, 0, DIMW, DIMW);

                if(isKeyPressed(SDLK_k))
                {
                    initWorld(w, 10);
                    initScore(w);

                    w.bg0 = image("data/asteroides/Background3.png");
                    w.planet0 = image("data/asteroides/Aquamarine.png");
                }
            }
        }
    }
}

/**< -------------------------------------------------- //

        PROCEDURE - DRAW ET UPDATE / FONCTION - FILE

//   -------------------------------------------------- */

int file(World& w) /**< RENVOIE LE SCORE MAXIMAL DU JOUEUR GARDE EN MEMOIRE DANS UN FICHIER TEXTE */
{
    int scoremax;

    ifstream scoretxt2("AsteroidsScoreMax.txt");
    scoretxt2 >> scoremax;

    if(w.score > scoremax)
    {
        ofstream scoretxt;
        scoretxt.open("AsteroidsScoreMax.txt");
        scoretxt << w.score;
        scoretxt.close();
        scoremax = w.score;
    }

    return scoremax;
}

void drawWorld(World& w)
{
    float temps = elapsedTime();

    float anglePlanet = 10. * temps;

    image_draw(w.bg0, 0, 0, DIMW, DIMW);

    /**< AFFICHAGE DES ELEMENTS DU JEU + MENU */

    image_draw(w.planet0, w.planet.position.x - w.planet.rayon, w.planet.position.y - w.planet.rayon, 30, 30, anglePlanet, 2);

    for(int i = 0; i<w.nbAsteroid; i++)
    {
        w.tabAsteroid[i].angle = w.tabAsteroid[i].vitesse * temps;

        if(w.tabAsteroid[i].masse > 0)
        {
            /**< ASTEROID NON DETRUIT */

            image_draw(w.tabAsteroid[i].imAst, w.tabAsteroid[i].position.x - w.tabAsteroid[i].rayon,
            w.tabAsteroid[i].position.y - w.tabAsteroid[i].rayon, w.tabAsteroid[i].rayon * 2, w.tabAsteroid[i].rayon * 2, w.tabAsteroid[i].angle, 2);
        }
        else
        {
            /**< ASTEROID DETRUIT */

            image_draw(w.imDeb, w.tabAsteroid[i].position.x - w.tabAsteroid[i].rayon,
            w.tabAsteroid[i].position.y - w.tabAsteroid[i].rayon, w.tabAsteroid[i].rayon * 2, w.tabAsteroid[i].rayon * 2, w.tabAsteroid[i].angle, 2);
        }
    }

    menu_draw(w.m, 5,5, 100, 102);

    image_draw(w.imLaser, w.laser.position.x - 5, w.laser.position.y + 10, 15, 15);

    /**< AFFICHAGE DIALOGUE + LEVEL */

    image_draw(w.imPanel04, DIMW/20, 28*DIMW/30, 9*DIMW/10, DIMW/20);

    image_draw(w.imPanel, 22*DIMW/30, DIMW/50+10, 130, 65);

    if(w.nbMission == 0)
    {
        color(255, 255, 255);
        print(24.5*DIMW/30-25, 3*DIMW/50, "LEVEL : ");
        print(27*DIMW/30-25, 3*DIMW/50, w.nbAsteroid/10);

        color(0, 0, 0);
        print(1.5*DIMW/20+53, 28*DIMW/30, "Reach planet Ywosn, the aliens were last spotted there. Be careful !");
    }
    if(w.nbMission ==  1)
    {
        color(255, 255, 255);
        print(24.5*DIMW/30-25, 3*DIMW/50, "LEVEL : ");
        print(27*DIMW/30-25, 3*DIMW/50, w.nbAsteroid/10);

        color(0, 0, 0);
        print(1.5*DIMW/20+40, 28*DIMW/30, "They fled from Ywosn with the hero. They are on Ratec, chase after them !");
    }
    if(w.nbMission == 2)
    {
        color(255, 255, 255);
        print(24.5*DIMW/30-25, 3*DIMW/50, "LEVEL : ");
        print(27*DIMW/30-25, 3*DIMW/50, w.nbAsteroid/10);

        color(0, 0, 0);
        print(1.5*DIMW/20+27, 28*DIMW/30, "Their spaceship broke down on Imuaq. Now is our chance, we count on you !");
    }
    if(w.nbMission >= 3)
    {
        color(255, 255, 255);
        print(24.5*DIMW/30-25, 3*DIMW/50, "LEVEL : ");
        print(27*DIMW/30-25, 3*DIMW/50, "INFINITE !");

        color(0, 0, 0);
        print(1.5*DIMW/20+87, 28*DIMW/30, "INFINITE ! Increase your score as much as you can !");
    }

    /**< AFFICHAGE DU SCORE */

    color(255, 255, 255);
    print(24.5*DIMW/30-25, 6*DIMW/50-10, "SCORE : ");
    print(27*DIMW/30-25, 6*DIMW/50-10, w.score);

    /**< AFFICHAGE DU CURSEUR */

    int x, y;
    mousePos(x, y);

    image_draw(w.imCursor, x - 15, y - 15, 30, 30);

    image_draw(w.imSoucoupe, w.soucoupe.position.x - 15, w.soucoupe.position.y - 15, 30, 30);

    print(27*DIMW/30-115, 45*DIMW/50-15, "SCORE MAX : ");

    print(27*DIMW/30-30, 45*DIMW/50-15, file(w));
}

void updateWorld(World& w)
{
    actionlaser(w);

    winOrLose(w);

    /**< LA SOUCOUPE RESTE DANS L'ECRAN */

    if(w.soucoupe.position.y > DIMW or w.soucoupe.position.y < 0)
    {
        w.soucoupe.vitesse = (-1) * (w.soucoupe.vitesse - (0.7) * w.soucoupe.vitesse);
    }

    if(w.soucoupe.position.x < 0 or w.soucoupe.position.x > DIMW)
    {
        w.soucoupe.vitesse = (-1) * (w.soucoupe.vitesse - (0.7) * w.soucoupe.vitesse);
    }

    /**< MOUVEMENT DE LA SOUCOUPE ET DES ASTEROIDES */

    if(w.soucoupe.masse > 0)
    {
        vitessePositionSoucoupe(w);

        for(int i=0; i<w.nbAsteroid; i++)
        {
            w.tabAsteroid[i].position = Rotate(w.tabAsteroid[i].position, w.tabAsteroid[i].position.x + 1, w.tabAsteroid[i].position.y + 1,
                                               toRadian(w.tabAsteroid[i].vitesse * 0.5));

            /**< ajout de 30px pour que visuellement l'astéroïde soit bien sorti de l'écran étant donné qu'il a un rayon maximal de 30px */

            if(w.tabAsteroid[i].position.x > DIMW + 30 or w.tabAsteroid[i].position.y < 0 - 30)
            {
                w.tabAsteroid[i].position.x = randPositionX() - DIMW;
                w.tabAsteroid[i].position.y = randPositionY() + DIMW/2;
            }
        }
    }
}

/**< SIMPLIFICATION DE L'ECRITURE */

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
    menu_draw(w.m, 5,5, 100, 102);

    /**< NOUVELLE PARTIE */

    if(isKeyPressed(SDLK_k))
    {
        initWorld(w, 10);
        initScore(w);

        w.bg0 = image("data/asteroides/Background3.png");
        w.planet0 = image("data/asteroides/Aquamarine.png");
    }

    /**< CHANGEMENT DE JOUEUR */

    if(isKeyPressed(SDLK_s))
    {
        w.imSoucoupe = image("data/asteroides/Soucoupe.png");
    }
}

/**< -------------------------------------------------- //

        FONCTION - MAIN

//   -------------------------------------------------- */

int main(int , char**)
{
    /**< MUSIQUE */

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *music = Mix_LoadMUS("AdrenalineToTheFight.wav");
    Mix_PlayMusic(music, -1);

    /**< AFFICHAGE */

    bool stop = false;

	winInit("Asteroides",DIMW,DIMW);

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

    Mix_FreeMusic(music);
    Mix_CloseAudio();

	return 0;
}

/**< FIN DU PROGRAMME, MERCI D'AVOIR LU/JOUE */
