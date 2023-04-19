#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "headers/funciones.h"

#define MAX_LLETRES 8
#define MAX_PARAULES 10

int main() {

    sopa_t sopa; 
    int mida_sopa, fil, col, dir;
    char rendicio_arr[9];
    bool rendicio;

    saludar(); // Donem la benvingua al joc.
    if(!llegir_fitxer(&sopa))
    {
        printf("Alguna cosa ha sortit malament amb el fitxer. Asegurat que esta en la arrel i que es diu PARAULES.txt\n");
    }
    else
    {
        printf("Indica la mida de la sopa de lletres:\n");
        scanf("%d", &mida_sopa); 
        sopa.dim = mida_sopa;   // Guardem la mida dins del struct sopa.
        genera_sopa(&sopa);       // La generem.
        do
        {
            mostra_sopa(&sopa);      // La mostrem per pantalla.
            mostra_paraules(&sopa);     // Mostrem les paraules ordenades alfabeticament per pantalla.
            mostra_menu_joc();  // Mostrem instruccions joc.
            printf("Encerts: \n", sopa.n_encerts);
            printf("Has trobat una paraula? Y / RENDICIO\n");
            fgets (rendicio_arr, 9, stdin);
            fflush(stdin); // Evitem que es que de malament el fgets i scanf. 
            if(comprobar_rendicio(rendicio_arr))
            {
                rendicio = true;
            }
            else
            {
                printf("Introdueix fila: \n");
                scanf("%d", &fil);
                printf("Introdueix col: \n");
                scanf("%d", &col);
                printf("Introdueix direcció: \n");
                scanf("%d", &dir);
                fflush(stdin);  // Evitem que es que de malament el fgets i scanf.
               if (!comprobar_sopa(fil, col, dir, &sopa))
               {
                printf("No es correcte! \n");
               }
               else
               {
                actualitzar_sopa(fil, col, dir, &sopa);
               } 
            }
        } while (!rendicio);
    }
    return 0;
}