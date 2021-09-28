#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define NX 6
#define NY 7
#define VIDE ' '
#define NOIR 'X'
#define BLANC 'O'

HANDLE hConsole;

#define bleu 1
#define vert 2
#define cyan 3
#define rouge 4
#define rose 5
#define jaune 6
#define blanc 7
#define gris foncé 8

// Fonctions affichage couleur

void color (int colorAttr)
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, colorAttr);
}

void resetcolor ()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, 7);
}

//Initialisation du plateau

void defPlateau (char plateau [NX][NY])
{
    int a,b;

    for (a = 0; a < NX; a++)
    {
        for (b = 0; b < NY; b++)
        {
            plateau [a][b] = VIDE;
        }
    }
}

// Sous programme d'affichage du plateau

void affichage (char plateau [NX][NY])
{
    int a;
    int b;

    /* Première ligne */

    printf("  1   2   3   4   5   6   7\n");

    for (a = 0; a < NX; a++)
    {
        printf("+---+---+---+---+---+---+---+\n");
        for (b = 0; b < NY; b++)
        {
            printf("|");

            if (plateau [a][b] == NOIR) //Joueur 1
            {
                color(rouge);
                printf(" %c ",plateau [a][b]);
                resetcolor();
            }
            else // Joueur 2
            {
                color(jaune);
                printf(" %c ",plateau [a][b]);
                resetcolor();
            }
        }
        printf("|\n");
    }
    printf("+---+---+---+---+---+---+---+\n");

}

//Fonction de saisie de la colonne

int saisie (char plateau [NX][NY], int col, int joueur)
{
    printf("Au tour du joueur %d", joueur);

    printf("\nEntrez la colonne : ");
    scanf("%d", &col);

    //Controle de la colonne saisie (valide et colonne pleine)

    while (plateau [0][col - 1] != VIDE || col < 1 || col > NY)
    {
        if (col < 1 || col > NY)
        {
            printf("\nErreur, entrez un nombre valide (entre 1 et 7) : ");
            scanf("%d", &col);
        }

        if (plateau [0][col - 1] != VIDE)
        {
            printf("\nColonne pleine, entrez une autre colonne : ");
            scanf("%d", &col);
        }
    }

    col--;

    return col;
}

//Placement du jeton dans le plateau

void placement (char plateau [NX][NY], int joueur, int col, int ligne)
{
    char j;

    if (joueur == 1)
    {
        j = NOIR;
    }
    else
    {
        j = BLANC;
    }

    while (plateau [ligne][col] == VIDE && ligne != 6)
    {
        ligne++;
    }

    ligne--;

    plateau [ligne][col] = j;
}

// Detection fin de partie

int  finPartie (char plateau [NX][NY], int joueur, int fin)
{
    int a;
    int b;
    char j;

    if (joueur == 1)
    {
        j = NOIR;
    }
    else
    {
        j = BLANC;
    }

    // Horizontal

    for (a = 0; a < NX; a++)
    {
        for (b = 0; b < NY - 3; b++)
        {
            if (plateau [a][b] == j && plateau [a][b + 1] == j && plateau [a][b + 2] == j && plateau [a][b + 3] == j)
            {
                fin = 0;
            }
        }
    }

    // Vertical

    for (a = 0; a < NX - 3; a++)
    {
        for (b = 0; b < NY; b++)
        {
            if (plateau [a][b] == j && plateau [a + 1][b] == j && plateau [a + 2][b] == j && plateau [a + 3][b] == j)
            {
                fin = 0;
            }
        }
    }

    // Diagonale droite

    for (a = 0; a < NX - 3; a++)
    {
        for (b = 0; b < NY - 3; b++)
        {
            if (plateau [a][b] == j && plateau [a + 1][b + 1] == j && plateau [a + 2][b + 2] == j && plateau [a + 3][b + 3] == j)
            {
                fin = 0;
            }
        }
    }

    //Diagonale gauche

    for (a = 3; a < NX; a++)
    {
        for (b = 0; b < NY - 3; b++)
        {
            if (plateau [a][b] == j && plateau [a - 1][b + 1] == j && plateau [a - 2][b + 2] == j && plateau [a - 3][b + 3] == j)
            {
                fin = 0;
            }
        }
    }
    return fin;
}

//Verification grille pleine

int grille_pleine (char plateau [NX][NY], int full)
{
    int x;
    int y;
    int f = 0;

    for (x = 0; x < NX; x++)
    {
        for (y = 0; y < NY; y++)
        {
            if (plateau [x][y] == VIDE)
            {
                f++;
            }
        }
    }

    if (f == 0)
    {
        full = 0;
    }
    return full;
}

//Affichage du resultat, joueur gagnant ou égalité

void resultatPartie (int joueur, int fin)
{
    if (fin == 0)
    {
        printf("\nLe joueur %d a gagne\n\n", joueur);
    }
    else
    {
        printf("Egalite");
    }
}

int main()
{
    char plateau [NX][NY];
    int col = 0;
    int s;
    int ligne = 0;
    int joueur = 2;
    int fin = 1;
    int full = 1;

    defPlateau (plateau);

    while (fin == 1 && full == 1)
    {
        joueur = (joueur % 2) + 1;
        system("cls");
        affichage(plateau);
        s = saisie(plateau, col, joueur);
        placement (plateau, joueur, s, ligne);
        fin = finPartie(plateau, joueur, fin);
        full = grille_pleine(plateau, full);
    }

    system("cls");

    affichage(plateau);

    resultatPartie(joueur, fin);

    system("pause");

return EXIT_SUCCESS;
}
