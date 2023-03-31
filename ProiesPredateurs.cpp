#include<Grapic.h>

using namespace grapic;

#include <iostream>

using namespace std;

const int DIMW = 500;

const int MAX = 50;

const float DUREE_VIE_PROIE = 5.;
const float DUREE_VIE_PREDATEUR = 10.;
const float MAX_JEUNE_PROIE = 5.;
const float MAX_JEUNE_PREDATEUR = 10.;

/**< I. Proies et prédateurs : version analytique */

struct ecoSysteme
{
    float alpha, beta, gamma, sigma;
    float nb_predateurs, nb_proies;
    int x;
};

void initEcoSysteme(ecoSysteme& eco, float nb_proies, float nb_predateurs)
{
    eco.alpha = 0.045;
    eco.beta = 0.001;
    eco.gamma = 0.025;
    eco.sigma = 0.0002;
    eco.nb_proies = nb_proies;
    eco.nb_predateurs = nb_predateurs;
    eco.x = 0;
}

void evolutionEcoSysteme(ecoSysteme& eco, Plot& p)
{

    float proies = eco.nb_proies;
    float predateurs = eco.nb_predateurs; /**< MISE A JOUR DES PROIES ET PREDATEURS EN MEME TEMPS */

    eco.nb_proies = proies + proies * eco.alpha -  proies * predateurs * eco.beta;
    eco.nb_predateurs = predateurs - predateurs * eco.gamma + predateurs * proies * eco.sigma;

    plot_add (p, eco.x, eco.nb_proies, 0);
    plot_add (p, eco.x, eco.nb_predateurs, 1);

    eco.x++;
}

/**< Proies vs. Prédateurs : version expérimentale ! */

struct individu
{
    int type_individu; /**< 0: herbe, 1: proie, 2: predateur */
    float duree_vie;
    float duree_jeune;
};

struct ecoSys
{
    individu tab[MAX][MAX];
    int dx, dy;
    float nb_predateurs, nb_proies;
};

void initEcoSys(ecoSys& sys, int dx, int dy, int nb_proies, int nb_predateurs)
{
    sys.dx = dx;
    sys.dy = dy;
    sys.nb_proies = nb_proies;
    sys.nb_predateurs = nb_predateurs;

    for(int i=0; i<dx; i++)
    {
        for(int j=0; j<dy; j++)
        {
            sys.tab[i][j].type_individu = 0;
        }
    }

    int position_proies_x, position_proies_y, position_predateurs_x, position_predateurs_y;

    for(int k=0; k<sys.nb_proies; k++)
    {
        do
        {
            position_proies_x = rand()%sys.dx;
            position_proies_y = rand()%sys.dy;
        }while(sys.tab[position_proies_x][position_proies_y].type_individu != 0);

    sys.tab[position_proies_x][position_proies_y].type_individu = 1;
    }

    for(int l=0; l<sys.nb_predateurs; l++)
    {
        do
        {
            position_predateurs_x = rand()%sys.dx;
            position_predateurs_y = rand()%sys.dy;
        }while(sys.tab[position_predateurs_x][position_predateurs_y].type_individu != 0);

    sys.tab[position_predateurs_x][position_predateurs_y].type_individu = 2;
    }
}

void draw_ecosysteme(ecoSys& sys)
{

    for(int i=0; i<sys.dx; i++)
    {
        for(int j=0; j<sys.dy; j++)
        {
            if(sys.tab[i][j].type_individu == 0)
            {
                color(0, 255, 0);
                circle(i * 30 + DIMW/4, j * 30 + DIMW/8, 4);
            }

            if(sys.tab[i][j].type_individu == 1)
            {
                color(0, 0, 255);
                circle(i * 30 + DIMW/4, j * 30 + DIMW/8, 3);
            }

            if(sys.tab[i][j].type_individu == 2)
            {
                color(255, 0, 0);
                circle(i * 30 + DIMW/4, j * 30 + DIMW/8, 3);
            }
        }
    }
}

/**<

3. Ecrivez la procédure evolution_ecosysteme qui prédit le devenir de chaque individu
en fonction de son environnement (voisinage) avec les deux règles suivantes.
 Si deux proies sont dans des cases adjacentes, elles se reproduisent et donnent
donc naissance à un nouvel individu de type proie placé dans une case libre.
 Si un prédateur a dans son voisinage une proie, il la mange, s’il a un autre
prédateur dans son voisinage il se reproduit uniquement s’il reste de la place
dans le voisinage.

*/


void evolution_ecoSys(ecoSys& sys)
{
    int positionAvant_proies_x, positionAvant_proies_y;

    ecoSys sysAvant;
    sysAvant = sys;

    for(int i=0; i<sys.dx; i++)
    {
        for(int j=0; j<sys.dy; j++)
        {
            for(int a=i-1; a<=i+1; a++)
            {
                for(int b=j-1; b<=j+1; b++)
                {
                    if(sysAvant.tab[i][j].type_individu == 2 and sysAvant.tab[a][b].type_individu == 1)
                    {
                        sysAvant.tab[a][b].type_individu = 0;
                    }
                    /**< A COMPLETER */
                    }

                }
            }
        }
    }
    sys = sysAvant;
}



int main(int , char**)
{
    bool stop = false;

	winInit("ProiesPredateurs",DIMW,DIMW);
	backgroundColor(120,70,200);

	ecoSysteme eco;

	Plot p;

	initEcoSysteme(eco, 10., 40.);

	plot_setSize(p, -1);

	/**< PARTIE 2 */

	ecoSys sys;

	initEcoSys(sys, 10, 10, 40, 10);

	while(!stop)
	{
	    winClear();

	    evolutionEcoSysteme(eco, p);

	    plot_draw(p, 0, 4*DIMW/6, DIMW, DIMW, true);

	    /**< PARTIE 2 */

	    draw_ecosysteme(sys);

	    evolution_ecoSys(sys);

        delay(1000);

	    stop = winDisplay();
	}

	pressSpace();
	winQuit();

	return 0;
}
