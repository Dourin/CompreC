#include "fonctions.h"

#define MAX_PASSWORD_LENGTH 10
#define MAX_CHARSET_LENGTH 100


/** 
 * Essayer de trouver le mot de passe d'une archive ZIP
 * @param fichier_zip le nom du fichier ZIP
 * @param password le mot de passe à essayer
 * @return 1 si le mot de passe est correct, 0 sinon
 */
int try_password(char* fichier_zip, char* password) {
    struct zip *archive;
    struct zip_file *file;
    struct zip_stat file_info;
    int err;
    // Ouvrir l'archive avec le mot de passe
    archive = zip_open(fichier_zip, 0, &err);
    if (archive == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier zip. Vérifier le nom\n");
        return 0;
    }

    // Parcourir tous les fichiers de l'archive et essayer le mot de passe
    int num_files = zip_get_num_entries(archive, 0);
    for (int i = 0; i < num_files; i++) {
        if (zip_stat_index(archive, i, 0, &file_info) == 0) {
            // Ouvrir le fichier avec le mot de passe
            file = zip_fopen_index_encrypted(archive, i, ZIP_FL_ENC_GUESS, password); // l'option de base est 0
            if (file != NULL) {
                // Le mot de passe est correct, faire quelque chose ici si nécessaire
                printf("Mot de passe trouvé pour le fichier %s : %s\n", file_info.name, password);
                zip_fclose(file);
                zip_close(archive);
                return 1;
            }
        }
    }

    printf("Mot de passe incorrect.\n");
    zip_close(archive);
    return 0;
}


/** 
 * Essayer de trouver le mot de passe d'une archive ZIP en utilisant la méthode brute force
 * @param fichier_zip le nom du fichier ZIP
 */
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
            strncpy(charset, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$^&*", MAX_CHARSET_LENGTH);
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