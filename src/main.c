#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_PARAMETROS 50

int main(int argc, char **argv) {
    int i;

    /* Recebe os parâmetros via CLI */
    char **parametros = (char**) malloc(sizeof(char*) * TAM_PARAMETROS);
    for (i = 1; i < argc; i++) {
        parametros[i - 1] = (char*) malloc(sizeof(char) * strlen(argv[i]));
        strcpy(parametros[i - 1], argv[i]);
    }

}