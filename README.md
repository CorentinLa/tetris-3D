# tetris-3D
Project for IN204 coursework


a. Analyse d'usage du logiciel (Use Case Analysis) :
Identifier les acteurs :

Joueur : Interagit avec le jeu.
Système : Gère la logique du jeu, les règles, et l'affichage.
Cas d'utilisation principaux :

Commencer une nouvelle partie.
Déplacer la pièce.
Faire pivoter la pièce.
Accélérer la descente de la pièce.
Marquer des points.
Fin de partie.
Cas d'utilisation secondaires (évolutifs) :

Ajouter des fonctionnalités spéciales aux pièces.
Introduire des niveaux de difficulté.
Possibilité de sauvegarder/charger une partie.
Mode multijoueur.
Personnalisation des paramètres du jeu.
b. Analyse fonctionnelle du logiciel :
Modules / Fonctionnalités principales :

Gestion de la grille 3D.
Gestion des pièces (géométrie, mouvements, rotations).
Logique du jeu (collision, suppression de lignes).
Système de score.
Affichage 3D.
Fonctionnalités évolutives :

Ajout de nouvelles pièces.
Intégration de bonus ou de malus.
Possibilité de personnaliser l'apparence du jeu.
Implémentation de différents modes de jeu (sprint, marathon, etc.).
Intégration d'un système de classement.
c. Architecture gros grains du logiciel :
Modèle-Vue-Contrôleur (MVC) :

Modèle : Gestion de la logique du jeu, des pièces, et de la grille.
Vue : Affichage 3D, gestion de l'interface utilisateur.
Contrôleur : Gestion des entrées utilisateur, communication entre la vue et le modèle.
Modules du logiciel :

PieceManager : Gestion des pièces (génération, mouvements, rotations).
GridManager : Gestion de la grille 3D, vérification des collisions.
GameManager : Logique principale du jeu (score, conditions de fin).
UIManager : Gestion de l'interface utilisateur.
InputManager : Gestion des entrées utilisateur.
Classe principale :

Tetris3D : Classe principale instanciant et reliant les différents modules.
Évolutif :

Chaque module doit être conçu de manière à pouvoir être étendu facilement.
Utilisation de classes abstraites et de l'héritage pour ajouter de nouvelles fonctionnalités.

Librairies à installer :

libvlc-dev
vlc