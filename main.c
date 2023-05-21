#include "headers/funciones.h"

int main() {

    sopa_t sopa;
    joc_t joc;
    char resposta_usuari[9];
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
        pregunta_i_guarda_mida(&sopa);
        genera_sopa(&sopa);
        inicialitzar_variables_inicials(&sopa);
        do
        {
            mostra_sopa(&sopa);
            mostrar_informacio_sopa(sopa);
            mostra_menu_joc();
            preguntar_usuari(resposta_usuari);
            es_rendicio(&sopa, resposta_usuari);
            if (!sopa.rendicio)
            {
                preguntar_jugada(&joc, sopa);
                ajustar_jugada(&joc);
                if (es_paraula_correcta(joc, sopa, &paraula_trobada))
                {
                    actualitzar_sopa(joc, &sopa, paraula_trobada);
                    es_guanya(&sopa);
                }
                else
                {
                     printf("No es correcte! \n");
                }
            }

        } while ((!sopa.rendicio) && (!sopa.guanya));
        if (sopa.rendicio)
        {
            mostra_solucio(&sopa);
            printf("T'has rendit!\n");
        }
        if (sopa.guanya)
        {
            mostra_sopa(&sopa); // Mostra la sopa resultant
            printf("\n\n!!!!!!!! ENHORABONA HAS GUANYAT !!!!!!!!\n");
        }
    }
    return 0;
}