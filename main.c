#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "headers/funciones.h"

#define MAX_LLETRES 8
#define MAX_PARAULES 10

int main() {

    sopa_t sopa; 
    joc_t joc;
    int mida_sopa;
    char rendicio_arr[9];
    bool rendicio /*guanya*/;

    saludar(); // Donem la benvingua al joc.
    if(!llegir_fitxer(&sopa))
    {
        printf("Alguna cosa ha sortit malament amb el fitxer. Asegurat que esta en la arrel i que es diu PARAULES.txt\n");
    }
    else
    {
        /*ordenar_paraules(&sopa);*/
        printf("Indica la mida de la sopa de lletres:\n");
        scanf("%d", &mida_sopa);
        fflush(stdin);
        sopa.dim = mida_sopa;   // Guardem la mida dins del struct sopa.
        genera_sopa(&sopa);       
        do
        {
            mostra_sopa(&sopa);      
           /*mostra_paraules(&sopa);*/   
            mostra_menu_joc();  // Mostrem instruccions joc.
            printf("Encerts: %d\n", sopa.n_encerts);
            printf("Has trobat una paraula? Y / RENDICIO\n");
            fgets (rendicio_arr, 9, stdin);
            fflush(stdin); // Evitem que es que de malament el fgets i scanf. 
            if(comprobar_rendicio(rendicio_arr))
            {
                rendicio = true;
            }
            else
            {
                preguntar_jugada(&joc);
                /*if (!comprobar_sopa(joc, &sopa))
                {
                    printf("No es correcte! \n");
                }
                else
                {
                    actualitzar_sopa(&joc, &sopa);
                    comprovar_guanya(&sopa);   
                }
                */
            }
        } while ((!rendicio) && (!sopa.guanya));
        if (rendicio)
        {
            /*mostrar_solucio(&sopa);*/
            printf("T'has rendit!\n");
        }
    }
    return 0;
}