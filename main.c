#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "headers/funciones.h"

#define MAX_LLETRES 8
#define MAX_PARAULES 10

int main() {

    sopa_t sopa;    // La sopa de lletres

    genera_sopa(&sopa);     // La generem (exemple)

    mostra_sopa(&sopa);      // La mostrem per pantalla

    return 0;
}