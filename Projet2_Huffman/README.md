# PROJET 2 - Compression des données par codage de Huffman

## Présentation du projet


Le codage de Huffman est une méthode de compression de données. Elle consiste à remplacer les caractères d'un fichier par un code binaire. Plus le symbole en question est présent dans le texte, plus il sera codé sur peu de bits. Cette méthode permet une compression sans perte et donc une décompression par la suite.
Il existe plusieurs variantes de l'algorithme de Huffman. Dans ce projet, nous utilisons celle semi-adaptative, c'est-à-dire que le fichier est lu intégralement avant de commencer le codage.
Ce projet est codé entièrement en C++.


## Installation

### Méthode 1

Pour exécuter le programme, vous pouvez lancer le fichier excutable *Projet2_Huffman.exe*. Une fenêtre s'ouvre alors et vous n'avez plus qu'à renseigner le nom du fichier que vous voulez compresser. Il faut que ce dernier soit présent dans le répertoire data.
Pour pouvoir récupérer le fichier de fréquence des caractères ainsi que le fichier compressé, il suffit d'aller dans le répertoire data.

Il est cependant possible que votre machine ne gère pas les couleurs et que l'affichage ne soit pas optimal. Je vous conseille dans ce cas d'utiliser la seconde méthode.

### Méthode 2

Ouvrer votre IDE que vous utilisez pour programmez en C++ (par exemple, Visual Studio 2022). Importez le projet et executé le fichier *main.cpp*. Une console s'ouvre et vous n'avez plus qu'à rentrer le nom du fichier que vous voulez compresser.
Comme pour la première méthode, les fichiers créés sont enregistrés dans le répertoire data.


## Description

Voici une brève explication des différentes étapes de la compression et donc du programme :

1. Lecture du fichier et évaluation du nombre d'occurences pour chaque caractère
2. Trie des caractères par fréquence croissante et codage des caractères en ASCII
3. Création de l'arbre
4. Lecture du fichier et parcours de l'arbre pour trouver le code bianire correspondant au caractère
5. Enregistrement du fichier compressé en format binaire
6. Calcul du taux de compression et du nombre de bits moyen par caractère 

## Liens utiles

[Article de référence](https://compression.ru/download/articles/huff/huffman_1952_minimum-redundancy-codes.pdf)

[Aide pour la création de l'arbre](https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/)
