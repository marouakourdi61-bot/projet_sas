#include <stdio.h>      // Pour printf, scanf, etc.
#include <string.h>     // Pour manipuler les chaînes (strcpy, strcmp, strtok, etc.)
#include <ctype.h>      // Pour les fonctions de gestion des caractères (tolower, isalpha, etc.)
#include <stdlib.h>     // Pour malloc, free, etc.

#define MAX_TEXTE 2000
#define MAX_MOTS 500
#define MAX_POSITIONS 100
#define MAX_TAILLE_valeur 50

typedef struct {
    char valeur[MAX_TAILLE_valeur];
    int occurrences;
    int longueur;
    int positions[MAX_POSITIONS];
    int nbpositions;
} Mot;

Mot dictionnaire[MAX_MOTS];
int nbmots = 0;

// Convertir en minuscules
void minuscules(char mot[]) {
    for (int i = 0; mot[i] != '\0'; i++) {
        mot[i] = tolower(mot[i]);
    }
}

// Ajouter un mot au dictionnaire ou incrementer s'il existe dejà
void ajouter(char mot[], int position) {
    for (int i = 0; i < nbmots; i++) {
        if (strcmp(dictionnaire[i].valeur, mot) == 0) {
            dictionnaire[i].occurrences++;
            dictionnaire[i].positions[dictionnaire[i].nbpositions++] = position;
            return;
        }
    }
    // Nouveau mot
    strcpy(dictionnaire[nbmots].valeur, mot);
    dictionnaire[nbmots].occurrences = 1;
    dictionnaire[nbmots].longueur = strlen(mot);
    dictionnaire[nbmots].positions[0] = position;
    dictionnaire[nbmots].nbpositions = 1;
    nbmots++;
}

// Analyser le texte et extraire les mots
void analyse(char texte[]) {
    char motnettoye[50];
    int position = 1;
    int i = 0, j = 0;

    while (texte[i] != '\0') {
        if (isalpha(texte[i])) {
            motnettoye[j++] = texte[i];
        } else if (j > 0) {
            motnettoye[j] = '\0';
            minuscules(motnettoye);
            ajouter(motnettoye, position++);
            j = 0;
        }
        i++;
    }
    // Dernier mot si le texte finit sans separateur
    if (j > 0) {
        motnettoye[j] = '\0';
        minuscules(motnettoye);
        ajouter(motnettoye, position++);
    }
}

// Afficher tous les mots du dictionnaire
void afficher() {
    printf("\n=== DICTIONNAIRE DES MOTS ===\n");
    for (int i = 0; i < nbmots; i++) {
        printf("Mot: %s\n", dictionnaire[i].valeur);
        printf("Occurrences: %d\n", dictionnaire[i].occurrences);
        printf("Longueur: %d\n", dictionnaire[i].longueur);
        printf("Positions: ");
        for (int j = 0; j < dictionnaire[i].nbpositions; j++) {
            printf("%d ", dictionnaire[i].positions[j]);
        }
        printf("\n\n");
    }
}

// Recherche exacte d'un mot
void rechercheExacte() {
    char mot[50];
    printf("Entrez le mot à rechercher exactement : ");
    fgets(mot, sizeof(mot), stdin);
    mot[strcspn(mot, "\n")] = '\0';  // Supprimer saut de ligne
    minuscules(mot);

    for (int i = 0; i < nbmots; i++) {
        if (strcmp(dictionnaire[i].valeur, mot) == 0) {
            printf("Mot trouve : %s\n", dictionnaire[i].valeur);
            printf("Occurrences : %d\n", dictionnaire[i].occurrences);
            printf("Longueur : %d\n", dictionnaire[i].longueur);
            printf("Positions : ");
            for (int j = 0; j < dictionnaire[i].nbpositions; j++) {
                printf("%d ", dictionnaire[i].positions[j]);
            }
            printf("\n");
            return;
        }
    }
    printf("Mot non trouve dans le dictionnaire.\n");
}

// Recherche partielle d'un fragment
void recherchePartielle() {
    char fragment[50];
    printf("Entrez une partie de mot à rechercher : ");
    fgets(fragment, sizeof(fragment), stdin);
    fragment[strcspn(fragment, "\n")] = '\0';
    minuscules(fragment);

    int trouves = 0;
    for (int i = 0; i < nbmots; i++) {
        if (strstr(dictionnaire[i].valeur, fragment) != NULL) {
            printf("Mot : %s (Occurrences : %d)\n", dictionnaire[i].valeur, dictionnaire[i].occurrences);
            trouves++;
        }
    }
    if (trouves == 0) {
        printf("Aucun mot ne contient \"%s\".\n", fragment);
    }
}

// Statistiques globales
void statistiques() {
    int totalMots = 0, motMax = 0, lenMax = 0;
    char motPlusLong[50] = "";

    for (int i = 0; i < nbmots; i++) {
        totalMots += dictionnaire[i].occurrences;
        if (dictionnaire[i].occurrences > motMax) {
            motMax = dictionnaire[i].occurrences;
        }
        if (dictionnaire[i].longueur > lenMax) {
            lenMax = dictionnaire[i].longueur;
            strcpy(motPlusLong, dictionnaire[i].valeur);
        }
    }

    printf("\n=== STATISTIQUES GLOBALES ===\n");
    printf("Nombre total de mots : %d\n", totalMots);
    printf("Nombre de mots uniques : %d\n", nbmots);
    printf("Mot le plus long : %s (%d lettres)\n", motPlusLong, lenMax);
    printf("Mot(s) le(s) plus frequent(s) :\n");

    for (int i = 0; i < nbmots; i++) {
        if (dictionnaire[i].occurrences == motMax) {
            printf("- %s (%d fois)\n", dictionnaire[i].valeur, motMax);
        }
    }
}

// Verifie si un mot est un palindrome
int estPalindrome(char mot[]) {
    int i = 0, j = strlen(mot) - 1;
    while (i < j) {
        if (mot[i] != mot[j]) return 0;
        i++;
        j--;
    }
    return 1;
}

// Affiche tous les mots palindromes
void afficherPalindromes() {
    printf("\n=== MOTS PALINDROMES ===\n");
    int count = 0;
    for (int i = 0; i < nbmots; i++) {
        if (estPalindrome(dictionnaire[i].valeur)) {
            printf("%s\n", dictionnaire[i].valeur);
            count++;
        }
    }
    if (count == 0) {
        printf("Aucun mot palindrome trouve.\n");
    }
}

// Affiche les groupes d'anagrammes (non implemente)
void afficherAnagrammes() {
    printf("\n=== GROUPES D'ANAGRAMMES ===\n");
    printf("Fonctionnalite non disponible sans tri des lettres.\n");
}

// Nuage de mots 
void nuageMots() {
    printf("\n=== NUAGE DE MOTS ===\n");
    for (int i = 0; i < nbmots; i++) {
        printf("%s: ", dictionnaire[i].valeur);
        for (int j = 0; j < dictionnaire[i].occurrences; j++) {
            printf("*");
        }
        printf(" (%d)\n", dictionnaire[i].occurrences);
    }
}


// Tri alphabetique
void trialphabetique() {
    for (int i = 0; i < nbmots - 1; i++) {
        for (int j = i + 1; j < nbmots; j++) {
            if (strcmp(dictionnaire[i].valeur, dictionnaire[j].valeur) > 0) {
                Mot temp = dictionnaire[i];
                dictionnaire[i] = dictionnaire[j];
                dictionnaire[j] = temp;
            }
        }
    }
    printf("Dictionnaire trie par ordre alphabetique.\n");
    afficher(); 
}

// Tri par longueur croissante
void trilongueur() {
    for (int i = 0; i < nbmots - 1; i++) {
        for (int j = i + 1; j < nbmots; j++) {
            if (dictionnaire[i].longueur > dictionnaire[j].longueur) {
                Mot temp = dictionnaire[i];
                dictionnaire[i] = dictionnaire[j];
                dictionnaire[j] = temp;
            }
        }
    }
    printf("Dictionnaire trie par longueur.\n");
    afficher();
}

// Tri par frequence decroissante
void trifrequence() {
    for (int i = 0; i < nbmots - 1; i++) {
        for (int j = i + 1; j < nbmots; j++) {
            if (dictionnaire[i].occurrences < dictionnaire[j].occurrences) {
                Mot temp = dictionnaire[i];
                dictionnaire[i] = dictionnaire[j];
                dictionnaire[j] = temp;
            }
        }
    }
    printf("Dictionnaire trie par frequence.\n");
    afficher();
}

// Analyse avancee : palindromes, anagrammes, nuage de mots
void analyseAvancee() {
    afficherPalindromes();
    afficherAnagrammes();
    nuageMots();
}

int main() {
    int choix;
    char texte[MAX_TEXTE];

    do {
        printf("\n===== MENU =====\n");
        printf("1. Saisir un texte et analyser\n");
        printf("2. Afficher tous les mots\n");
        printf("3. Rechercher un mot exact\n");
        printf("4. Rechercher un mot partiel\n");
        printf("5. Trier les mots\n");
        printf("6. Statistiques globales\n");
        printf("7. Analyses avancees (palindromes, anagrammes, nuage)\n");
        printf("8. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        getchar(); // Consommer le '\n' laisse par scanf

        switch (choix) {
            case 1:
                printf("Entrez le texte (max 2000 caractères):\n");
                fgets(texte, MAX_TEXTE, stdin);
                nbmots = 0; // Reinitialiser le dictionnaire
                analyse(texte);
                break;
            case 2:
                afficher();
                break;
            case 3:
                rechercheExacte();
                break;
            case 4:
                recherchePartielle();
                break;
            case 5: {
                int choixTri;
                printf("\n-- Choisissez le type de tri --\n");
                printf("1. Tri alphabetique\n");
                printf("2. Tri par longueur croissante\n");
                printf("3. Tri par frequence decroissante\n");
                printf("Votre choix: ");
                scanf("%d", &choixTri);
                getchar();

                switch (choixTri) {
                    case 1: trialphabetique(); break;
                    case 2: trilongueur(); break;
                    case 3: trifrequence(); break;
                    default: printf("Choix invalide.\n");
                }
                break;
            }
            case 6:
                statistiques();
                break;
            case 7:
                analyseAvancee();
                break;
            case 8:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez reessayer.\n");
        }
    } while (choix != 8);

    return 0;
}
