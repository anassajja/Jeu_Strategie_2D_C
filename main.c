#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

// Fonction pour initialiser le plateau de jeu
void newBoard(int board[], int n, int p) {
    srand(time(NULL)); // Initialisation de la graine du g�n�rateur de nombres al�atoires
    int sum = p; // Initialisation de la somme totale des pions

    for (int i = 0; i < n - 1; i++) { // Parcours du plateau jusqu'� l'avant-derni�re case
        int max_pions_case = sum - (n - 1 - i); // Calcul du nombre maximal de pions pour la case actuelle
        if (max_pions_case > p) { // Si le nombre maximal est sup�rieur � p, le r�duire � p
            max_pions_case = p;
        }
        int random_pions = rand() % (max_pions_case + 1); // G�n�ration d'un nombre al�atoire de pions pour la case
        board[i] = random_pions; // Assignation du nombre de pions � la case actuelle
        sum -= random_pions; // Mise � jour de la somme totale des pions restants
    }
    board[n - 1] = sum; // Assignation de la somme restante � la derni�re case du plateau
}

// Proc�dure pour afficher le plateau de jeu
void display(int board[], int n) {
    printf("\nPlateau de jeu :\n");
    printf("\n");

    for (int i = 0; i < n; i++) {
        if (board[i] < 10) { // Si le nombre de pions est inf�rieur � 10, alignement visuel
            printf("%d | ", board[i]); // Affichage de chaque case du plateau
        } else {
            printf("%d | ", board[i]); // Affichage de chaque case du plateau
        }
    }

    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("____"); // Ligne de s�paration sous chaque case du plateau
    }

    printf("\n");
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("%d | ", i+1); // Affichage des indices des cases du plateau
    }
    printf("\n");
}

// Fonction pour v�rifier si une case contient un pion d�pla�able
bool possibleSquare(int board[], int i) {
    return (board[i] > 0); // V�rification si le nombre de pions dans la case est sup�rieur � 0
}

// Fonction pour s�lectionner une case contenant un pion d�pla�able
int selectSquare(int board[], int n) {
    int selection;
    do {
        printf("Choisissez une case contenant un pion deplacable (1 - %d) : ", n);
        scanf("%d", &selection); // Saisie de la case s�lectionn�e par le joueur
        selection--; // Ajustement de l'index 0-based
    } while (selection < 0 || selection >= n || !possibleSquare(board, selection)); // V�rification de la validit� de la case s�lectionn�e
    return selection;
}

// Fonction pour v�rifier si une case est une destination valide pour un pion donn�
bool possibleDestination(int board[], int i, int j) {
    return (j < i && (board[j] == 0 || board[j] > 0)); // V�rification si la case de destination est valide pour le d�placement du pion
}

// Fonction pour s�lectionner une destination pour un pion donn�
int selectDestination(int board[], int i) {
    int destination;
    do {
        printf("Choisissez une destination valide pour le pion (1 - %d) : ", i);
        scanf("%d", &destination); // Saisie de la case de destination s�lectionn�e par le joueur
        destination--; // Ajustement de l'index 0-based
    } while (!possibleDestination(board, i, destination)); // V�rification de la validit� de la case de destination s�lectionn�e
    return destination;
}

// Proc�dure pour d�placer un pion
void move(int board[], int i, int j) {
    board[j] += 1; // Ajout du pion � la case de destination
    board[i] -= 1; // Retrait du pion de la case d'origine
}

// Fonction pour v�rifier si le joueur a perdu
bool lose(int board[], int n) {
    for (int i = 0; i < n; i++) {
        if (board[i] > 0) { // Si au moins une case contient un pion, le joueur n'a pas perdu
            return false;
        }
    }
    return true; // Si aucune case ne contient de pion, le joueur a perdu
}

// Fonction pour v�rifier si le joueur a gagn�
bool win(int board[], int n, int p) {
    return (board[0] == p); // V�rification si la premi�re case contient le nombre maximal de pions
}

// Proc�dure pour jouer une partie compl�te
void jeu(int n, int p) {
    int board[n];
    newBoard(board, n, p); // Initialisation du plateau de jeu
    display(board, n); // Affichage du plateau de jeu initial
    int currentPlayer = 1; // Initialisation du joueur actuel

    while (!lose(board, n)) { // Tant que le jeu n'est pas termin�
        printf("\nJoueur %d :\n", currentPlayer);
        int square = selectSquare(board, n); // S�lection de la case contenant un pion d�pla�able
        int destination = selectDestination(board, square); // S�lection de la case de destination pour le pion
        move(board, square, destination); // D�placement du pion
        display(board, n); // Affichage du plateau de jeu apr�s le d�placement

        if (win(board, n, p)) { // Si le joueur a gagn�
            printf("\nLe joueur %d a gagne !\n", currentPlayer);
            return; // Fin de la partie
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Changement de joueur en utilisantr l'expression conditionnelle ternaire
    }
    printf("\nLe joueur %d a perdu.\n", currentPlayer); // Affichage du joueur ayant perdu apr�s la fin de la partie
}

int main() {
    int n, p;
    printf("Entrez le nombre de cases : ");
    scanf("%d", &n);
    printf("Entrez le nombre maximal de pions par case : ");
    scanf("%d", &p);
    jeu(n, p); // Lancement du jeu avec les param�tres saisis par l'utilisateur
    return 0;
}
