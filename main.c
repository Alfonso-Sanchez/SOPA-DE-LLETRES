#include "headers/funciones.h"

#define MAX_LLETRES 8
#define MAX_PARAULES 10

int main() {

    sopa_t sopa; 
    joc_t joc;
    char rendicio_arr[9];

    saludar(); // Donem la benvingua al joc.
    if(!llegir_fitxer(&sopa))
    {
        printf("Alguna cosa ha sortit malament amb el fitxer. Asegurat que esta en la arrel i que es diu PARAULES.txt\n");
    }
    else
    {
        ordenar_paraules(&sopa);
        pregunta_mida(&sopa);
        //genera_sopa(&sopa);
        genera_sopa(&sopa); // solo testing, luego sera la general. 
        do
        {
            mostra_sopa(&sopa);
            mostra_paraules(sopa);  
           /*mostra_paraules(&sopa);*/   
            mostra_menu_joc();  // Mostrem instruccions joc.
            
            preguntar_usuari(sopa, rendicio_arr);
            comprobar_rendicio(&sopa, rendicio_arr);

            if (!sopa.rendicio)
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
        } while ((!sopa.rendicio) && (!sopa.guanya));
        if (sopa.rendicio)
        {
            /*mostrar_solucio(&sopa);*/
            printf("T'has rendit!\n");
        }
    }
    return 0;
}