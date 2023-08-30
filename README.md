# asteroids_game

"asteroids_game" is my first C++ game project. The goal of this project was to use code in a specific field such as physics, biology or economy. The asteroids as well as the spaceship obey Newton's law of universal gravitation.

## Author

- [@lan_qiha](https://github.com/LanQiha)

## Screenshots

![My Image](images_du_jeu/level_3.png)

## README (FR)

Sommaire : 

Article I. Objectif de l'application et indications sur son utilisation

  Section 1.01 : But de l'application
  
  Section 1.02 : Installation du projet
  
  Section 1.03 : Touches
  
  Section 1.04 : Fonctionnement du jeu

Article II. Fonctionnement du code

Article III. Liens vers les documents scientifiques et les images/musiques utilisés dans ce programme

  Section 3.01 : Liens vers les documents scientifiques utilisés
  
  Section 3.02 : Liens vers les créateurs/sites des images et des musiques utilisées

Article IV. Historique des évolutions du code

  Section 4.01 : Début du travail sur le code : structures, surcharges d'opérateurs pour les vecteurs, fonctions de base d'utilisation des vecteurs, procédure d'initialisation, procédure d'affichage. 
  
  Section 4.02 : Stade intermédiaire du travail sur le code : modification des structures, de la procédure d'initialisation et de la procédure d'affichage. Fonctions/procédures : lois de la gravitation universelle, procédure laser.
  
  Section 4.03 : Fin du travail sur le code : modification des structures, de la procédure d'initialisation, de la procédure d'affichage. Procédure partie gagné ou partie perdu, procédure 'update' et ajout du menu, harmonisation et fonctionnalités bonus.

Article V. Informations supplémentaires

  Section 5.01 Phases de tests
  
  Section 5.02 Améliorations
  
  Section 5.03 Licence
  
  Section 5.04 Remerciements


<====================================================================================================>


Article I. Objectif de l'application et indications sur son utilisation

Section 1.01 : But de l'application

L'application est un mini jeu vidéo de type "Space Shooter" avec ajout de particularités physiques, notamment la loi de la gravitation universelle. L'échelle mésoscopique s'étend des dimensions de l'atome jusqu'au micromètre. C'est une échelle intermédiaire entre la physique quantique et la physique classique. Les objets en présence dans ce programme dépassent l'échelle mésoscopique. Ils sont de l'ordre du mètre. Par conséquent, la physique newtonienne est un modèle fiable pour ce projet.

Section 1.02 : Installation du projet

Vous aurez besoin de télécharger la bibliothèque grapic (Cf. https://github.com/ucacaxm/grapic) ainsi que la bibliothèque SDL_mixer (Cf. https://github.com/libsdl-org/SDL_mixer). Il faudra placer les fichiers de SDL_mixier dans les dossiers grapic correspondant puis il faudra ajouter le linker : -lSDL2_mixer à votre projet. Vous aurez besoin du dossier images 'asteroides' et du fichier 'Asteroides.cpp' ci-joint afin de lancer correctement l'application. Le dossier 'asteroides' doit se trouver dans le dossier 'data' de grapic. Vous trouverez également le dossier 'asteroides2'. Ce dossier est à inclure directement dans le projet, c'est à dire dans le dossier 'windows-cb20' de grapic.

Section 1.03 : Touches

(a) Touches du menu

Lorsque vous démarrez l'application, vous vous trouvez dans le menu 'Pause'. Vous trouverez le menu en bas à gauche de l'écran. Le menu possède deux choix, 'Pause' et 'Resume'. Ce menu reste affiché tant que l'application est ouverte. Le bouton 'Pause' vous permet de revenir à la page sur laquelle vous vous trouviez lorsque vous avez lancé l'application. 'Resume' vous permet de revenir au jeu. Vous trouverez également sur la page du menu 'Pause' les règles écrites en anglais ainsi que la mini histoire du jeu. Si vous souhaitez quitter l'application, appuyez sur la touche 'espace'. Pour réinitialiser une partie, appuyez sur la touche 'k' lorsque vous avez perdu, gagné ou bien lorsque vous êtes dans le menu 'Pause'.

IMPORTANT : Si vous êtes coincé à un moment ou à un autre dans l'application, vous pouvez toujours vous rendre dans le menu 'PAUSE' et appuyer sur la touche 'k' pour réinitialiser votre partie. Si cela ne fonctionne pas, fermez l'application avec la touche 'espace' et relancez le jeu.

(b) Touches du jeu

Pour déplacer votre soucoupe, vous devez orienter votre souris à l'endroit où vous voulez aller et faire un clic gauche à cet endroit-là. Cependant, gardez en tête que les réacteurs de votre soucoupe fonctionnent avec des forces. Une force appliquée dans une direction devra être compensée par une autre force dans la direction opposée pour rester immobile dans le référentiel de l'écran. Vous pouvez également vous défendre en lançant un laser avec la touche 'z'. Vous ne pouvez pas lancer un laser lorsqu'il y en a déjà un existant sur l'écran.

Section 1.04 : Fonctionnement du jeu

Vous perdez la partie si vous vous écrasez sur un astéroïde. Gardez en mémoire que votre soucoupe ne peut pas sortir de l'écran. Vous gagnez la partie lorsque vous atteignez la dernière planète. Il y a trois stages différents et donc trois planètes différentes à atteindre. Vous pouvez cependant recommencer chaque niveau à l'infini après avoir fini le jeu sans perdre votre score. Votre score dépend de deux paramètres : les planètes sur lesquelles vous avez déjà atterri et le nombre d'astéroïdes détruits. Le score lié à l'astéroïde dépend de sa taille. Plus l'astéroïde est grand, plus sa force gravitationnelle est grande, ce qui entraîne un risque plus élevé. La récompense est proportionnelle au risque. Le score lié aux planètes est fixe.


<====================================================================================================>


Article II. Fonctionnement du code

Mon code se structure en dix points majeurs classés dans l'ordre ou vous les trouverez dans le .cpp ci-joint : 

1. Les bibliotèques
2. Les constantes
3. Les structures 'Particule', 'Asteroid' et 'World' qui permettent d'afficher tous les objets du jeu (planètes, soucoupe, astéroïdes, lasers, images...) 
et la structure 'Vecteur' qui est un outil qui va permettre de coder les fonctions de mise en mouvement des objets.
4. La surcharge des opérateurs pour les vecteurs et les fonctions de base d'utilisation des vecteurs : distance, normalisation d'un vecteur et rotation. 
Ce sont des outils qui vont permettre de coder la physique du jeu et la mise en mouvement des objets.
5. L'initialisation du score, du laser et du monde ainsi que les fonctions qui initialisent la position aléatoire des astéroïdes.
6. Les fonctions qui servent à calculer les forces en présences sur la soucoupe ainsi que la procédure associée qui met à jour la position de la soucoupe. 
Elles définissent les lois physiques du jeu et le mouvement de la soucoupe.
7. Les procédures du fonctionnement du laser, des parties gagnées ou perdues.
8. La procédure qui affiche le jeu et la procédure 'update' qui appelle toutes les autres procédures et fonctions du jeu. La fonction 'file' qui renvoie le score maximal gardé en memoire dans un fichier texte. La fonction met également ce score à jour.
9. Le menu
10. La fonction 'main()' qui permet le lancement du jeu.

Vous trouverez également des commentaires dans le code qui vont permettront de comprendre l'utilité de chaque fonction/procédure.


<====================================================================================================>


Article III. Liens vers les documents scientifiques et les images/musiques utilisés dans ce programme

Section 3.01 : Liens vers les documents scientifiques utilisés

(a) Informations sur les corps célestes :

- https://fr.wikipedia.org/wiki/Syst%C3%A8me_solaire
- https://fr.wikipedia.org/wiki/Ast%C3%A9ro%C3%AFde
- 
(b) Informations sur la gravitation et mouvement des corps célestes :

- https://fr.wikipedia.org/wiki/Loi_universelle_de_la_gravitation
- https://fr.wikipedia.org/wiki/Lois_de_Kepler
- https://fr.wikipedia.org/wiki/Champ_gravitationnel
- https://fr.wikipedia.org/wiki/M%C3%A9canique_quantique
- https://fr.wikipedia.org/wiki/M%C3%A9soscopique
- https://fr.wikipedia.org/wiki/Relation_de_Chasles

(c) Informations sur les collisions (non utilisé dans ce programme) :

- https://fr.wikipedia.org/wiki/Choc_%C3%A9lastique
- https://fr.wikipedia.org/wiki/Lois_de_Snell-Descartes

(d) Informations sur la propulsion spatiale :

- https://fr.wikipedia.org/wiki/Propulsion_spatiale

Section 3.02 : Liens vers les créateurs/sites des images et des musiques utilisées

(a) Images

- 'Background1.png', 'Background3.png', 'Background4.png' : https://opengameart.org/users/rawdanitsu
- 'Snowy.png', 'Cratered.png', 'Aquamarine.png' : https://opengameart.org/users/screaming-brain-studios
- 'cursor_hand.png', 'Panel04', 'Reacteur.png' : https://opengameart.org/users/kenney
- 'laserRed.png', 'laserOrange.png' et 'laserYellow.png': https://opengameart.org/users/bonsaiheldin
- 'planetoids-1.png', 'planetoids-2.png', 'planetoids-3.png' : https://opengameart.org/users/varkalandar
- 'BG.png', 'YouWin(2).png', 'YouLose(2).png', 'SpaceGame.png' : https://opengameart.org/users/craftpixnet-2d-game-assets
- 'SpaceCat.png' : https://opengameart.org/users/ei
- 'futureui1.png' : https://opengameart.org/users/bart
- 'Explosion.png' : https://opengameart.org/users/sinestesia
- 'score_max.png' : https://opengameart.org/users/ahmadmanga
- 'assroids.ico' : https://opengameart.org/users/mindchamber (icône de l'application sur la version .exe)
- 'Soucoupe.png', 'Debris.png' ont été trouvées sur un site qui a pour but de partager des images non protégées : https://www.pngmart.com/fr/copyright-policy
- 'Menu.png', 'YouWin.png', 'YouLose.png' : J'ai réalisé ces images grace aux autres images du dossier 'asteroides' et grace à l'application Canva.
  
(b) Musiques

- AdrenalineToTheFight.wav : https://bocuma.itch.io


<====================================================================================================>


Article IV. Historique des évolutions du code

Section 4.01 : Début du travail sur le code : structures, surcharges d'opérateurs pour les vecteurs, fonctions de base d'utilisation des vecteurs, procédure d'initialisation, procédure d'affichage. 

(a) Explications

Dans les premiers jours du travail sur ce code, j'ai ajouté les librairies et les constantes. J'ai également écris les structures de base, les surcharges d'opérateurs pour les vecteurs et les fonctions de base d'utilisation des vecteurs. Je me suis concentrée sur la façon de procéder pour faire apparaître aléatoirement des astéroïdes sur l'écran. J'ai créé une procédure basique d'affichage afin de vérifier mon code. Elle affichait la planète et la soucoupe de façon immobile. Après avoir fini le TP "SystemeMasseRessort" J'ai pu rajouter les fonctions de normalisation d'un vecteur et de calcul de la distance. Pour finir, j'ai écris la procédure d'initialisation.

(b) Qu'est-ce que le code affiche ?

Un cercle en haut à gauche de l'écran qui représente la planète. Un cercle en bas au milieu de l'écran qui représente la soucoupe. Des cercles de tailles différentes qui apparaissent aléatoirement sur l'écran à chaque lancement de l'application.

Section 4.02 : Stade intermédiaire du travail sur le code : modification des structures, de la procédure d'initialisation et de la procédure d'affichage. Fonctions/procédures : lois de la gravitation universelle, procédure laser.

(a) Explications

La partie suivante concerne principalement le codage des lois mécaniques et le fonctionnement du laser. J'ai commencé par ajouter une force d'attraction à chaque astéroïde. Ensuite, j'ai ajouté une vitesse pour les réacteurs de la soucoupe. J'ai remarqué que la soucoupe pouvait échapper à n'importe quelle force d'attraction. J'ai corrigé le problème en modifiant la procédure des réacteurs et en la remplaçant par une fonction ajoutant une force. Les lois physiques du jeu fonctionnent. J'ai ensuite travaillé sur le fonctionnement du laser. Dans ses débuts, le laser pouvait être lancé sans "cooldown". C'est un problème récurrent dans les jeux que l'on retrouve notamment dans les "platformer" ou le nombre de sauts doit être limité. J'ai modifié cette procédure afin que le laser fonctionne correctement puis j'ai modifié la procédure d'initialisation et d'affichage afin d'y incorporer ces modifications. Pour finir, j'ai ajouté un mouvement aux astéroïdes grâce à la fonction 'rotation'. Entre temps, j'ai également ajouté une image à chaque objet (Cf. dossier 'asteroides').

(b) Qu'est-ce que le code affiche ?

Des astéroïdes avec une position initiale aléatoire, en mouvement, exerçant une force d'attraction sur la soucoupe. Une soucoupe qui peut se mouvoir et lancer des lasers. Un fond d'écran et une image pour chaque objet. À ce stade, le 'game-over' n'est pas pris en compte et la soucoupe peux quitter l'écran.

Section 4.03 : Fin du travail sur le code : modification des structures, de la procédure d'initialisation, de la procédure d'affichage. Procédure partie gagné ou partie perdu, procédure 'update' et ajout du menu, harmonisation et fonctionnalités bonus.

Mon projet s'est terminé par l'écriture de la procédure partie gagnée et partie perdue, 'update' et l'ajout d'un menu. Ensuite, j'ai consacré plus de 50% du temps à optimiser le projet. J'ai testé le jeu et fais tester le jeu. J'ai corrigé les bugs remarqués grâce à la phase de tests et j'ai modifié le code afin d'y incorporer les améliorations nécessaires. Pour finir, j'ai passé un long moment à comprendre le fonctionnement de la musique avec C++. J'ai tout d'abord essayé de jouer de la musique avec la bibliothèque 'Windows.h'. Cependant, je me suis rendu compte que la musique et le jeu ne fonctionnaient pas en même temps. J'ai ensuite essayé de jouer de la musique avec SDL2 mais les résultats n'étaient pas concluant. La fenêtre d'affichage et la musique buggait. J'ai ensuite téléchargé SDL_mixer. J'ai dû faire face à deux problèmes : les versions de mes bibliothèques SDL2 et SDL_mixer et la position des fichiers de SDL_mixer. Après avoir correctement configuré ces éléments, j'ai pu jouer une musique de fond.


<====================================================================================================>


Article V. Informations supplémentaires

Le programme peut etre lent selon la qualite de votre machine.

Section 5.01 Phases de tests

La phase de test a permis de prendre connaissance des problèmes du jeu et de les corriger au mieux.

(a) Problèmes résolus

- Sortie de l'écran : dans les précédentes versions du jeu, la sortie de l'écran équivalait à une partie perdue. Étant donné que les forces en présence sur la soucoupe sont massives, la soucoupe a tendance à "glisser". Cette difficulté supplémentaire a été retirée.
- Collision avec les limites de l'écran : les collisions ont été modifiées afin d'empêcher la soucoupe de rebondir violemment et de s'écraser involontairement sur un astéroïde. Cela a permis d'améliorer la maniabilité.
- Tailles des astéroïdes : les astéroïdes pouvaient initialement prendre une taille entre 0 et 30 pixels. Ainsi, certains astéroïdes n'étaient pas visibles aux yeux du joueur. Cette valeur se situe à présent entre 10 et 30.
- Position des astéroïdes : les astéroïdes pouvaient prendre une position sur tout l'écran. Certains astéroïdes pouvaient apparaître sur la soucoupe et la partie était perdue avant même de l'avoir commencé. Les astéroïdes ne peuvent plus apparaître dans la zone de la soucoupe de taille 2DIMW/10 en bas de l'écran.
- Forces gravitationnelles trop faible : la masse des astéroïdes a été augmentée.
- Problèmes de comptabilisation du score. Le score se réinitialisait à chaque nouveau niveau. La fonction d'initialisation du score a été retirée de la fonction d'initialisation du monde. La fonction d'initialisation du score est appelée seulement lorsque la partie est perdue.
- Partie perdue : lorsque la partie était perdue, le joueur ne pouvait plus bouger la soucoupe. Les forces d'attraction qui s'exerçaient sur elles continuaient à agir sur son mouvement et la soucoupe pouvait s'échapper. Le jeu reprenait. À présent, lorsque la partie est perdue, tous les éléments du jeu se figent.
- (Problème résolu le 09/04/2023) Score de la dernière planète : lorsque la soucoupe atteignait la dernière planète, le score augmentait à l'infini à cause d'une boucle 'if'. Ajout du compteur 'w.win' afin de pallier au problème. Avant le score de cette dernière planète n'était pas comptabilisé.
- Problème d'affichage des images.

(b) Problèmes non résolus

- Partie perdue : dans certaines situations où la soucoupe s'écrase sur un astéroïde au même moment ou le laser détruit ce même astéroïde, les messages informant que la partie est perdue ne s'affichent pas. La réinitialisation d'une partie ne marche pas dans 'Resume'. Il faut retourner dans le menu 'Pause' et recommencer une partie à partir de là. Ce bug est très rare.
- Lorsque la soucoupe se trouve sur les limites du monde elle est très peu soumise aux forces gravitationnelles. Cependant, il n'est pas recommandé de se coller au mur étant donné que depuis le 28/04/2023, la réapparition des astéroïdes a été ajouté. Ces astéroïdes apparaissent dans la zone supérieur gauche de l'écran et traversent l'écran pour arrivé à la zone inférieur droite. Il y a un risque de collision avec ceux-ci dans les cas ou le joueur reste trop longtemps sur les limites de l'écran.

Section 5.02 Améliorations

(a) Ameliorations récentes

Ces informations se trouvent également au début du .cpp ci-joint.

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
- Mémoire du score maximal dans un fichier texte.

(b) Ameliorations possibles

- Ajout d'effets sonores simultanés : activation du laser de la soucoupe, collision avec un astéroïde, partie gagnée, partie perdue, activation des réacteurs de la soucoupe, menu.
- Avoir un affichage plein écran en fonction des dimensions de l'écran de l'ordinateur du joueur.

Section 5.03 Licence

- MIT

Section 5.04 Remerciements

- Merci à Layachi et à Mélinda pour avoir participé à la phase de tests.
