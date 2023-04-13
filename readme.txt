NOM : EL KARROUMI
Prénom : Cherazade
LIFAMI - Mini-projet
Article I. Objectif de l'application et comment l'utiliser (touches, but de l'app, ect.)
Section 1.01 : But de l'app
L'application est un mini jeu vidéo de type " Space Shooter " Avec ajout de particularités physiques (loi de la gravitation universelle dans sa version classique, mécanique classique).
Section 1.02 : Touches
(a) Touches du menu
Lorsque vous démarrez l'application, vous vous trouvez dans le menu 'Pause'. Vous trouvez le menu en bas à gauche de l'écran. Le menu possède deux choix, 'Pause' et 'Resume'. Ce menu reste affiché tant que l'application est ouverte. Le bouton 'Pause' vous permet de revenir à la page sur laquelle vous vous trouvez lorsque vous avez lancé l'application. 'Resume' vous permet de revenir au jeu. Vous trouverez également sur la page du menu 'Pause' les règles écrites en anglais ainsi que l'histoire du jeu. Si vous souhaitez quitter l'application, appuyez sur la touche 'espace'. Pour réinitialiser une partie, appuyez sur la touche 'k' lorsque vous avez perdu, gagné ou bien lorsque vous êtes dans le menu 'Pause'.  IMPORTANT : Si vous êtes coincé à un moment ou à un autre sur l'application, vous pouvez toujours vous rendre dans le menu 'PAUSE' et appuyer sur la touche 'k' pour réinitialiser votre partie.
(b) Touches du jeu
Pour déplacer votre soucoupe vous devez orienter votre souris à l'endroit où vous voulez aller et faire un clic gauche à cet endroit-là. Cependant, gardez en tête que les réacteurs de votre soucoupe fonctionnent avec des forces. Une force appliquée dans une direction devra être compensée par une autre force dans la direction opposée pour rester immobile dans le référentiel de l'écran. Vous pouvez également vous défendre en lançant un laser avec la touche 'z'. Vous ne pouvez pas lancer un laser lorsqu'il y en a déjà un existant sur l'écran.
Section 1.03 : Fonctionnement du jeu
Vous perdez la partie si vous vous écrasez sur un astéroïde. Gardez en mémoire que votre soucoupe ne peut pas sortir de l'écran. Vous gagnez la partie lorsque vous atteignez la dernière planète. Il y a trois stages différents et donc trois planètes différentes à atteindre. Vous pouvez cependant recommencer chaque niveau à l'infini après avoir fini le jeu sans perdre votre score. Votre score dépend de deux paramètres : les planètes sur lesquelles vous avez déjà atterri et le nombre d'astéroïdes détruits. Le score lié à l'astéroïde dépend de sa taille. Plus l'astéroïde est grand, plus sa force gravitationnelle est grande, ce qui entraine un risque plus élevé. La récompense est proportionnelle au risque. Le score lié aux planètes est fixe. La dernière planète n'ajoute pas de score. (Cf. Article V)
Article II. Des explications en français/anglais (et non en code) de comment votre code fait les choses (TRES IMPORTANT)
Mon code se structure en dix points majeurs classés dans l'ordre ou vous les trouverez dans le .cpp ci-joint : 
1. Les librairies
2. Les constantes
3. Les structures 'Particule', 'Astéroïd' et 'World' qui permettent d'afficher tous les objets du jeu (planètes, soucoupe, astéroïdes, lasers, images...) et la structure 'Vecteur' qui est un outil qui va permettre de coder les fonctions de mise en mouvement des objets.
4. La surcharge des opérateurs pour les vecteurs et les fonctions de base d'utilisation des vecteurs : distance, normalisation d'un vecteur et rotation. Ce sont des outils qui vont permettre de coder la physique du jeu et la mise en mouvement des objets.
5. L'initialisation du score, du laser et du monde ainsi que les fonctions qui initialisent la position aléatoire des astéroïdes.
6. Les fonctions qui servent à calculer les forces en présences sur la soucoupe ainsi que la procédure associée qui met à jour la position de la soucoupe. Elles définissent les lois physiques du jeu et le mouvement de la soucoupe.
7. Les procédures du fonctionnement du laser, des parties gagnées ou perdues.
8. La procédure qui affiche le jeu et la procédure 'update' qui appelle toutes les procédures et fonctions du jeu.
9. Le menu
10. La fonction 'main()' qui permet le lancement du jeu.
Vous trouverez également des commentaires dans le code qui vont permettront de comprendre l'utilité de chaque fonction/procédure.
Article III. Des références vers des documents qui vous ont servis (Wikipedia, ect.) (IMPORTANT)
Section 3.01 : Références vers des documents scientifiques
(a) Informations sur les corps célestes :
- https://fr.wikipedia.org/wiki/Syst%C3%A8me_solaire
- https://fr.wikipedia.org/wiki/Ast%C3%A9ro%C3%AFde
(b) Informations sur la gravitation et mouvement des corps célestes :
- https://fr.wikipedia.org/wiki/Loi_universelle_de_la_gravitation
- https://fr.wikipedia.org/wiki/Lois_de_Kepler
- https://fr.wikipedia.org/wiki/Champ_gravitationnel
- https://fr.wikipedia.org/wiki/M%C3%A9canique_quantique
(c) Informations sur les collisions :
- https://fr.wikipedia.org/wiki/Choc_%C3%A9lastique
- https://fr.wikipedia.org/wiki/Lois_de_Snell-Descartes
(d) Informations sur la propulsion spatiale :
- https://fr.wikipedia.org/wiki/Propulsion_spatiale
Section 3.02 : Références vers les sources des images et des musiques
(a) Images
- Dossier 'Background': https://opengameart.org/users/rawdanitsu
- Dossier 'Planet' : https://opengameart.org/users/screaming-brain-studios
- 'cursor_hand.png' et 'glassPanel.png': https://opengameart.org/users/kenney
- 'laserRed.png', 'laserOrange.png' et 'laserYellow.png': https://opengameart.org/users/bonsaiheldin
- 'spaceCat.png' : https://opengameart.org/content/pixel-cat-and-courgette
- 'YouLose.png', 'YouWin.png', 'Reacteur.png', 'Soucoupe.png', 'Asteroide.png', 'Explosion.png', 'Debris.png' ont été trouvées sur un site qui a pour but de partager des images non protégées : https://www.pngmart.com/fr/copyright-policy 
(b) Musiques
- ObservingTheStar.wav: https://opengameart.org/users/yd
Article IV. L'historique des évolution des trois dernières semaines (texte que vous avez déjà largement commencé)
Section 4.01 : DEBUT DU TRAVAIL SUR LE CODE : Structures, Surcharges d'operateurs pour les vecteurs, fonctions de base d'utilisation des vecteurs, procédure d'initialisation, procédure d'affichage. 
(a) Explications
Dans les premiers jours du travail sur ce code, j'ai ajouté les librairies et les constantes. J'ai également écris les structures de base, les surcharges d'opérateurs pour les vecteurs et les fonctions de base d'utilisation des vecteurs. Je me suis concentrée sur la façon de procéder pour faire apparaitre aléatoirement des astéroïdes sur l'écran. J'ai créé une procédure basique d'affichage afin de vérifier mon code. Elle affichait la Lune et la soucoupe de façon immobile. Après avoir fini le TP " SystemeMasseRessort " J'ai pu rajouter les fonctions de normalisation d'un vecteur et de calcul de la distance. Pour finir j'ai écris la procédure d'initialisation.
(b) Qu'est ce que le code affiche ?
Un cercle plein en haut à gauche de l'écran qui représente la Lune. Un cercle plein en bas au milieu de l'écran qui représente la soucoupe. Des cercles pleins de taille comprise entre 0 et 30 qui apparaissent aléatoirement sur l'écran à chaque lancement de l'application (Cf. Article V : Taille des astéroïdes modifiés).
Section 4.02 : STADE INTERMEDIAIRE DU TRAVAIL SUR LE CODE : Modification des structures, de la procédure d'initialisation et de la procédure d'affichage. Fonctions/procédures : Mécanique classique, lois de la gravitation universelles classique, procédure laser.
(a) Explications
La partie suivante concerne principalement le code des lois mécaniques et le fonctionnement du laser. J'ai commencé par ajouter une force d'attraction à chaque astéroïde. Ensuite, j'ai ajouté une vitesse pour la soucoupe. J'ai remarqué que la soucoupe pouvait échapper à n'importe quelle force d'attraction. J'ai corrigé le problème en modifiant cette fonction en la remplaçant par une force. Les lois physiques du jeu fonctionnent. J'ai ensuite travaillé sur le fonctionnement du laser. Dans ses débuts, le laser pouvait être lancé sans " cooldown ". C'est un problème récurrent dans les jeux que l'on retrouve notamment dans les " platformer " ou le nombre de saut doit être limité. J'ai modifié cette procédure afin que le laser fonctionne correctement puis j'ai modifié la procédure d'initialisation et d'affichage afin d'y incorporer ces modifications. Entre temps j'ai également ajouté une image à chaque objet (Cf. dossier 'Images').
(b) Qu'est ce que le code affiche ?
Des astéroïdes avec une position initiale aléatoire, en mouvement, exerçant une force d'attraction sur la soucoupe. Une soucoupe qui peut se mouvoir et lancer des lasers. Un fond d'écran et une image pour chaque objet.
Section 4.03 : FIN DU TRAVAIL SUR LE PROJET : Modification des structures, de la procédure d'initialisation, de la procédure d'affichage. Procédure partie gagné ou partie perdu, procédure 'update' et ajout du menu.
Mon projet s'est terminé par l'écriture de la procédure partie gagnée et partie perdue, 'update' et l'ajout d'un menu. Le jeu contenait initialement dix niveaux, son nombre a été diminué. J'ai dû faire un compromis en réduisant le nombre de niveau. Chaque niveau a à présent une particularité et une mini histoire. La procédure update est principalement une procédure qui fait le lien entre les différentes fonctions et procédures du code tout en ajoutant les limites du monde (Cf. Article V).
Article V. Informations supplémentaires
(a) Informations
Le programme peut être lent selon la qualité de votre ordinateur.
Copyright : La provenance de certaines images ne sont pas précisées (voir Article III). Aucunes images utilisées dans ce programme ne m'appartiennent.
(b) Phases de 'test'
La phase de 'test' a permis de prendre connaissance des problèmes du jeu et de les corriger au mieux.
(1) Problèmes résolus
(i) Amélioration de la jouabilité
- Sortie de l'écran : dans les précédentes versions du jeu la sortie de l'écran équivalait à une partie perdue. Etant donné que les forces en présences sur la soucoupe sont massives, cette difficulté supplémentaire a été retirée.
- Collision avec les limites de l'écran : les collisions ont été modifiées afin d'empêcher la soucoupe de rebondir. Cela a permis d'améliorer la maniabilité.
- Tailles des astéroïdes : les astéroïdes pouvaient initialement prendre une taille entre 0 et 30. Ainsi, certains astéroïdes n'étaient pas visibles aux yeux du joueurs. Cette valeur se situe à présent entre 15 et 30.
(ii) Ajustement de la difficulté
- Forces gravitationnelles trop faible. La masse des astéroïdes a été augmentée.
(iii) Fonctionnement du jeu
- Problèmes de comptabilisation du score.
- Partie perdue : Lorsque la partie était perdue, le joueur ne pouvait plus bouger la soucoupe. Les forces d'attraction qui s'exerçaient sur elles continuaient à agir sur son mouvement et la soucoupe pouvait s'échapper, le jeu reprenait. A présent, lorsque la partie est perdu, tous les éléments du jeu se figent.
- (Problème résolu le 09/04/2023) Score de la dernière planète : Augmentation du score à l'infini à cause d'une boucle 'if'. Ajout d'une nouvelle boucle 'if' avec le compteur 'w.win' à l'interieur de celle-ci afin de pallier au problème. 
(iv) Affichage
- Problème d'affichage des images.
(2) Problèmes non résolus
- Partie perdue : Dans certaines situations où la soucoupe s'écrase sur un astéroïde au même moment ou le laser détruit ce même astéroïde, les éléments du jeu restent figés. La partie est perdu bien que les messages d'informations ne s'affichent pas. La réinitialisation d'une partie ne marche pas dans le jeu. Il faut retourner dans le menu 'Pause' et recommencer une partie. (Modification du 09/04/2023 : ce bug est moins présent car le laser se fige lorsque la partie est perdue)
(c) Améliorations récentes
(i) Modifications du 09/04/2023
- Modification de la structure 'Asteroid' : les images des astéroïdes ont été déplacées dans la structure 'World' pour qu'elles ne soient chargées qu'une seule fois.
- Ajout d'une planète et un fond d'écran (Background) différent pour chaque stage. 
- Ajout de trois lasers de couleur différentes, lancés aléatoirement.
- Ajout d'une UI (User Interface) supplémentaire : mini-histoire pour chaque stage.
- Modification de l'Easter Egg pour problèmes de copyright.
- Modification du mouvement du laser lors d'une partie perdue.
- Resolution du bug de score de la dernière planete.
(d) Licence
- CC-BY-NC (attribution, pas d'utilisation commerciale)
(e) Remerciements
- Layachi MOUSSI (Testeur)



