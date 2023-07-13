#include "fonctions.h"

#define MAX_PASSWORD_LENGTH 10
#define MAX_CHARSET_LENGTH 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <zip.h>


int parcourir_archive_zip( char *nom_archive) {
    // Ouvrir l'archive ZIP
    struct zip *archive = zip_open(nom_archive, 0, NULL);

    if (archive == NULL) {
        printf("Impossible d'ouvrir l'archive.\n");
        return 1;
    }

    // Obtenir le nombre total de fichiers dans l'archive
    int num_files = zip_get_num_entries(archive, 0);

    // Parcourir les fichiers de l'archive
    for (int i = 0; i < num_files; i++) {
        // Obtenir les informations sur le fichier
         char *filename = zip_get_name(archive, i, 0);
        struct zip_stat file_info;
        zip_stat_init(&file_info);
        zip_stat_index(archive, i, 0, &file_info);

        // Afficher le nom du fichier
        printf("Nom du fichier : %s\n", filename);

        // Afficher la taille du fichier
        printf("Taille du fichier : %lu octets\n", (unsigned long)file_info.size);

        // Afficher d'autres informations si nécessaire (par ex. date de modification, permissions, etc.)

        printf("\n");
    }

    // Fermer l'archive
    zip_close(archive);

    return 0;
}