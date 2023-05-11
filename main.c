#include "headers/funciones.h"

int main() {

    sopa_t sopa; 
    joc_t joc;
    char rendicio_arr[9];
    int paraula_trobada;

    saludar(); // Donem la benvingua al joc.
    if(!llegir_fitxer(&sopa))
    {
        printf("Alguna cosa ha sortit malament amb el fitxer. Asegurat que esta en la arrel i que es diu PARAULES.txt\n");
    }
    else
    {
        ordenar_paraules(&sopa);
        calcular_longitud_paraules(&sopa);
        pregunta_mida(&sopa);
        genera_sopa(&sopa); 
        do
        {
            mostra_sopa(&sopa);
            mostrar_informacio_sopa(sopa);   
            mostra_menu_joc(); 
            preguntar_usuari(sopa, rendicio_arr);
            comprobar_rendicio(&sopa, rendicio_arr);

            if (!sopa.rendicio)
            {
                preguntar_jugada(&joc);
                if (!comprobar_sopa(joc, sopa, &paraula_trobada))
                {
                    printf("No es correcte! \n");
                }
                else
                {
                    actualitzar_sopa(joc, &sopa, paraula_trobada);
                    comprovar_guanya(&sopa);  
                }
                
            }

        } while ((!sopa.rendicio) && (!sopa.guanya));
        if (sopa.rendicio)
        {
            mostra_solucio(&sopa);
            printf("T'has rendit!\n");
        }
    }
    return 0;
}