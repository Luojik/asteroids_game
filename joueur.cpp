#include <Grapic.h>

using namespace grapic;

#include <cstdlib>
#include <ctime>

#include<ostream>

using namespace std;

#define EPS 1E-07

struct complexe{
    float x;
    float y;
};

complexe makeComplexe (float x, float y){
complexe c;
c.x = x;
c.y = y;
return c;
}

complexe makeComplexeExp (float r, float ThetaRad){
return makeComplexe(r*cos(ThetaRad), r*sin(ThetaRad));
}

float toRadian (float degre){
return ((degre * M_PI) / 180);
}

complexe operator + (complexe a, complexe b){
return makeComplexe(a.x + b.x, a.y + b.y);
}

complexe operator - (complexe a, complexe b){
return makeComplexe(a.x - b.x, a.y - b.y);
}

complexe operator * (complexe a, float b){
return makeComplexe(b * a.x, b * a.y);
}

complexe operator * (float b, complexe a){
return makeComplexe(b * a.x, b * a.y);
}

complexe operator * (complexe a, complexe b){
return makeComplexe((a.x * b.x) - (a.y * b.y), (a.x * b.y) + (a.y * b.x));
}

complexe operator / (complexe a, float lambda)
{
    return makeComplexe(a.x/lambda, a.y/lambda);
}

complexe operator / (float lambda, complexe a)
{
     return makeComplexe(a.x/lambda, a.y/lambda);
}

complexe Rotate(complexe a, complexe c, float angle)
{
    complexe rot;
    rot = makeComplexeExp(1, toRadian(angle));
    return (a-c)*rot + c;
}

int const DIMW = 500;

/**< COMPLEXES 2019 */

void draw_polygon(int cx, int cy, int r, int n)
{
    color(255, 0, 0);
    complexe tab[n];
    complexe centre = makeComplexe(cx, cy);
    for(int i=0; i<n; i++)
    {
        //tab[i] = centre + makeComplexeExp(r, toRadian(i*(360/n))); Fonctionne aussi
        tab[i] = makeComplexe(centre.x + r, centre.y);
        tab[i] = Rotate(tab[i], centre, i*(360/n));

    }
    for(int j = 0; j<n-1; j++)
    {
        line(tab[j].x, tab[j].y, tab[j+1].x, tab[j+1].y);
    }
    line(tab[0].x, tab[0].y, tab[n-1].x, tab[n-1].y);
}

complexe normaliseVecteur(complexe v)
{
float n;
n = sqrt(v.x*v.x + v.y*v.y);
if(fabs(n)>EPS) //fabs valeur absolue
{
v.x = v.x/n;
v.y = v.y/n;
}
return v;
}

struct Vaisseau
{
    complexe pos;
    float vit;
    complexe dir;
};

void dessine_vaisseau(Vaisseau& vais)
{
    color(255, 0, 0);
    circleFill(vais.pos.x, vais.pos.y, 20);
}

void initVaisseau(Vaisseau& vais)
{
    vais.pos = makeComplexe(DIMW/2, DIMW/10);
    vais.vit = 10.;
    vais.dir = makeComplexe(0, 1);
}

void update_vaisseau(Vaisseau& vais)
{
    vais.pos = vais.pos + vais.vit * vais.dir * 0.01;

    if(isKeyPressed(SDLK_UP))
    {
        vais.vit = vais.vit * 2;
    }
    if(isKeyPressed(SDLK_DOWN))
    {
        vais.vit = vais.vit * 0.5;
    }
}

/**< INTERPOLATION 2019 */

/**< INTERPOLATION 2018 */ /**< PAS TESTE */

const int MAX_H = 10;

struct Lieu
{
    complexe GPS;
    int nbUsine;
    int tabVoiture[MAX_H]; /**< nbVoitures */
    float tabVent[MAX_H]; /**< VitesseVent */
    float tabPluie[MAX_H]; /**< QuantitéDePluieTombée */
    float tabconc[MAX_H];
};

const float Pusine = 0.1 ;
const float Pvoiture = 0.001 ;
const float Dvent = 0.1 ;
const float Dpluie = 0.5 ;

void calculeConcentration(Lieu& li)
{
    /**< Concentration = PolluantProduit - PolluantDispersé
    PolluantProduit = nbUsines * Pusine (constante) + nbVoitures * Pvoitures (constante)
    PolluantDispersé = VitesseVent * Dvent (constante) + Qpluie * Dpluie (constante) */

    /**< les tableaux voitures, pluie, vent sont remplis. On suppose également que la
concentration initiale est de 0.  */

    li.tabconc[0] = li.nbUsine * Pusine + li.tabVoiture[0] * Pvoiture - Dvent * li.tabVent[0] - Dpluie * li.tabPluie[0];

    for(int i=1; i<MAX_H; i++)
    {
        li.tabconc[i] = li.tabconc[i-1] + li.nbUsine * Pusine + li.tabVoiture[i] * Pvoiture - Dvent * li.tabVent[i] - Dpluie * li.tabPluie[i];
    }
}

float interpolationConcentration(Lieu& li, int H, int M)
{
    /**< (1-t)*a + t*b, t = poids */
    return (1-(M/60)) * li.tabconc[H] + (M/60) * li.tabconc[H+1];
}

/**< COMPLEXES 2018 */ /**< TESTE */

const int MAX_ELECTRONS = 10;
const int MAX_ATOMES = 20;
const int CARRE_ELECTRON = 40*3;
const int CARRE_ATOME = 100*3;

struct Atome
{
    complexe pos;
    int nbElectrons;
    complexe tab[MAX_ELECTRONS];
};

struct Molecule
{
    complexe pos;
    Atome tab[MAX_ATOMES];
    int nbAtomes;
};

void initMolecule(Molecule& mol)
{
    mol.pos = makeComplexe(DIMW/2, DIMW/2);
    mol.nbAtomes = rand()%MAX_ATOMES + 3;
    for(int i=0; i<mol.nbAtomes; i++)
    {
        mol.tab[i].pos = makeComplexe(mol.pos.x - CARRE_ATOME/2 + rand()%CARRE_ATOME, mol.pos.y - CARRE_ATOME/2 + rand()%CARRE_ATOME);
        mol.tab[i].nbElectrons = rand()%MAX_ELECTRONS;
        for(int j=0; j<mol.tab[i].nbElectrons; j++)
        {
            mol.tab[i].tab[j] = makeComplexe(mol.tab[i].pos.x - CARRE_ELECTRON/2 + rand()%CARRE_ELECTRON, mol.tab[i].pos.y - CARRE_ELECTRON/2 + rand()%CARRE_ELECTRON);
            //cout << mol.nbAtomes << endl;
            //cout << mol.tab[i].nbElectrons << endl;
        }
    }
}

void drawMolecule(Molecule& mol)
{
    color(0, 0, 0);
    circleFill(mol.pos.x, mol.pos.y, 10);
    for(int i=0; i<mol.nbAtomes; i++)
    {
        color(255, 0, 0);
        circleFill(mol.tab[i].pos.x, mol.tab[i].pos.y, 5);

        for(int j=0; j<mol.tab[i].nbElectrons; j++)
        {
            color(0, 0, 255);
            circle(mol.tab[i].tab[j].x, mol.tab[i].tab[j].y, 3);
        }
    }
}

void updateMolecule(Molecule& mol)
{
    complexe tr;

    for(int i=0; i<mol.nbAtomes; i++)
    {
        mol.tab[i].pos = Rotate(mol.tab[i].pos, mol.pos, toRadian(1));
        for(int j=0; j<mol.tab[i].nbElectrons; j++)
        {
            tr = mol.tab[i].tab[j] - mol.tab[i].pos;
            mol.tab[i].tab[j] = mol.tab[i].pos + tr;
            mol.tab[i].tab[j] = Rotate(mol.tab[i].tab[j], mol.tab[i].pos, toRadian(10));
        }
    }
}

void centreMolecule(Molecule& mol)
{
    complexe centre;
    complexe centreAtome;
    complexe centreElec;
    int nbElec;

    for(int i=0; i<mol.nbAtomes; i++)
    {
        centreAtome = centreAtome + 5*mol.tab[i].pos;
        for(int j=0; j<mol.tab[i].nbElectrons; j++)
        {
            centreElec = centreElec + mol.tab[i].tab[j];
            nbElec ++;
        }
    }
    centre = (centreAtome + centreElec) / (5*mol.nbAtomes + nbElec);
    color(255, 255, 255);
    circle(centre.x, centre.y, 10);
    cout << centre.x << " " << centre.y << endl;
}

/**< COMPLEXES 2017 */ /**< TESTE */

struct Etoile
{
    complexe etoile;
    complexe satellite;
};

int const MAX = 30;

struct Galaxy
{
    complexe centre;
    Etoile tab[MAX];
    int nb;
};

int const CARRE_ETOILE = 50;

void initGalaxy(Galaxy& gala)
{
    gala.centre = makeComplexe(DIMW/2, DIMW/2);
    gala.nb = rand()%MAX + 10;
    for(int i=0; i<gala.nb; i++)
    {
        gala.tab[i].etoile = makeComplexe(rand()%DIMW, rand()%DIMW);
        gala.tab[i].satellite = makeComplexe(gala.tab[i].etoile.x + rand()%CARRE_ETOILE/2, gala.tab[i].etoile.y + rand()%CARRE_ETOILE/2);

    }
}

void drawGalaxy(Galaxy& gala)
{
    for(int i=0; i<gala.nb; i++)
    {
        color(255, 0, 0);
        circleFill(gala.tab[i].etoile.x, gala.tab[i].etoile.y, 10);
        color(0, 0, 255);
        circle(gala.tab[i].satellite.x, gala.tab[i].satellite.y, 5);
    }
}

void updateGalaxy(Galaxy& gala)
{
    complexe c = makeComplexe(DIMW/2, DIMW/2);
    complexe tr;

    for(int i=0; i<gala.nb; i++)
    {
        tr = gala.tab[i].satellite - gala.tab[i].etoile;
        gala.tab[i].etoile = Rotate(gala.tab[i].etoile, c, 0.01);
        gala.tab[i].satellite = gala.tab[i].etoile + tr;
        gala.tab[i].satellite = Rotate(gala.tab[i].satellite, gala.tab[i].etoile, 0.1);
    }
}

/**< INTERPOLATION 2017 */

struct Personne
{
    float poids;
    float C;
    int tabVerre[MAX_H];
    float tabAlcool[MAX_H-1];
};

void initPersonne(Personne& p, float poids)
{
    p.poids = poids;
    p.C = 10 / (0.68 * p.poids);
    for(int i=0; i<MAX_H; i++)
    {
        p.tabVerre[i] = rand()%4; // frand(0, 4);
    }
}

void calculAlcool(Personne& p)
{
    p.tabAlcool[0] = p.C * p.tabVerre[0] - 0.15;

    for(int i=1; i<MAX_H; i++)
    {
        p.tabAlcool[i] = p.tabAlcool[i-1] + p.C * p.tabVerre[i] - 0.15 ;
    }
}

float interpolationAlcool(Personne& p, int H, int M)
{
    return (1.-(M/60.))*p.tabAlcool[H] + (M/60.)*p.tabAlcool[H+1];
}

int main(int , char**)
{
    bool stop=false;

	winInit("joueur",DIMW,DIMW);
	backgroundColor(300, 300, 300);

	Galaxy gala;
	initGalaxy(gala);

	Molecule mol;
	initMolecule(mol);

	Personne p;
	initPersonne(p, 78.);
	calculAlcool(p);
	for(int i=0; i<MAX_H; i++)
    {
        cout << p.tabAlcool[i] << endl;
    }

	cout << "interpolation : " << interpolationAlcool(p, 6, 45) << endl;

	Vaisseau vais;
	initVaisseau(vais);

	while(!stop)
    {
	    winClear();

	    //drawGalaxy(gala);
	    //updateGalaxy(gala);

	    //drawMolecule(mol);
	    //updateMolecule(mol);
	    //centreMolecule(mol);

	    draw_polygon(DIMW/2, DIMW/2, 50, 7);
	    dessine_vaisseau(vais);
	    update_vaisseau(vais);

        stop = winDisplay();
	}

	winQuit();
	return 0;
}
