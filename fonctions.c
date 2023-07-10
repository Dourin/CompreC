#include "fonctions.h"

#define MAX_PASSWORD_LENGTH 10
#define MAX_CHARSET_LENGTH 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <zip.h>

void brute_force(char* fichier_zip) {
    int choice;
    printf("Choisissez le type de mot de passe :\n");
    printf("1. Lettres minuscules\n");
    printf("2. Lettres majuscules\n");
    printf("3. Chiffres\n");
    printf("4. Lettres minuscules + Majuscules\n");
    printf("5. Lettres minuscules + Majuscules + Chiffres\n");
    printf("6. Lettres minuscules + Majuscules + Chiffres + Caractères spéciaux\n");
    printf("Entrez votre choix : ");
    scanf("%d", &choice);
    getchar(); // Efface le caractère de nouvelle ligne du tampon d'entrée
    
    char charset[MAX_CHARSET_LENGTH + 1];
    
    switch (choice) {
        case 1:
            strncpy(charset, "abcdefghijklmnopqrstuvwxyz", MAX_CHARSET_LENGTH);
            charset[MAX_CHARSET_LENGTH] = '\0';
            break;
        case 2:
            strncpy(charset, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", MAX_CHARSET_LENGTH);
            charset[MAX_CHARSET_LENGTH] = '\0';
            break;
        case 3:
            strncpy(charset, "0123456789", MAX_CHARSET_LENGTH);
            charset[MAX_CHARSET_LENGTH] = '\0';
            break;
        case 4:
            strncpy(charset, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", MAX_CHARSET_LENGTH);
            charset[MAX_CHARSET_LENGTH] = '\0';
            break;
        case 5:
            strncpy(charset, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", MAX_CHARSET_LENGTH);
            charset[MAX_CHARSET_LENGTH] = '\0';
            break;
        case 6:
            charset[MAX_CHARSET_LENGTH] = '\0';
            break;
        default:
            printf("Choix invalide.\n");
            return;
    }
    // Générer tous les mots de passe possibles
    int charset_length = strlen(charset);
    char password[MAX_PASSWORD_LENGTH + 1];
    for (int length = 1; length <= MAX_PASSWORD_LENGTH; length++) {
        // Générer tous les mots de passe de la longueur "length"
        int num_combinations = 1;
        for (int i = 0; i < length; i++) {
            num_combinations *= charset_length; // Nombre de combinaisons possibles
        }
        
        for (int i = 0; i < num_combinations; i++) {
            // Convertir le nombre en base "charset_length" en une chaîne de caractères
            int remainder = i;
            for (int j = 0; j < length; j++) { // Pour chaque caractère du mot de passe (de gauche à droite)
                password[j] = charset[remainder % charset_length]; // Ajouter le caractère correspondant au mot de passe
                remainder /= charset_length; // Diviser le nombre par la base pour obtenir le caractère suivant
            }
            password[length] = '\0'; // Terminer la chaîne de caractères
            
            printf("Essai du mot de passe : %s\n", password);
            
            if (try_password(fichier_zip, password) == 1) {
                printf("Mot de passe trouvé : %s\n", password);
                return; // Mot de passe trouvé, arrêter la fonction
            }
            
            // Ajouter un court délai entre les tentatives pour éviter les bugs
            usleep(5000);
        }
    }
    
    printf("Mot de passe non trouvé.\n");
}
