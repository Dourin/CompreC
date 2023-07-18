#ifndef ZIP_UTILS_H
#define ZIP_UTILS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <zip.h>

#define MAX_PASSWORD_LENGTH 10
#define MAX_CHARSET_LENGTH 100

void print_help();

int try_password(char* fichier_zip, char* password);
void brute_force(char* fichier_zip);

#endif  // ZIP_UTILS_H
