#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "headers/funciones.h"

/*Mostra el missatge de benvingua al joc*/
void saludar()
{
    printf("***********************************************************\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: Joan Arnau, Alex ... , Alfonso Sanchez\n");
    printf("***********************************************************\n");
}

/*Mostra el missatge dins del joc amb instruccions de com jugar*/
void mostra_menu_joc()
{
    printf("*************************** INSTRUCCIONS ********************************\n");
    printf("Per jugar tens que indicar, la fila, la columna i la direcció 1 (→) -1 (←) 2 (↓) -2 (↑).\n");
    printf("Si vols rendirte escriu \"RENDICIO\" en la següent pregunta!");
    printf("***********************************************************\n");
}

/* Aquesta funcio llegeix les paraules dun fitzer i las carrega dins de paraula_t dins de sopa_t*/
bool llegir_fitxer(sopa_t *s)
{
    /*Lo que sea*/
    
}

/*Ordena paraules de la sopa*/
void ordenar_paraules (sopa_t *s)
{

}
/*Aquesta funció llegeix les paraules que estan dins de la sopa i les mostra al usuari*/
void mostra_paraules (sopa_t *s)
{
   /*Lo que sea*/
}


/*Comproba la sopa de lletres amb les dades introduides per l'usuari, si la paraula es correcta*/
bool comprobar_sopa(joc_t j, sopa_t *s)
{
    /*Lo que sea*/
}

/*Pregunta les dades al usuari*/
void preguntar_jugada(joc_t *j)
{
    printf("Introdueix fila: \n");
    scanf("%d", &j->fila);
    printf("Introdueix col: \n");
    scanf("%d", &j->columna);
    printf("Introdueix direcció: \n");
    scanf("%d", &j->direccio);
    fflush(stdin);  // Evitem que es que de malament el fgets i scanf.
}

/*Comproba si la persona se ha rendit o no*/
bool comprobar_rendicio(char rend_arr[9])
{
    /*Lo que sea*/
}


/*Actualitza amb l'encert*/
void actualitzar_sopa(joc_t *j, sopa_t *s)
{
    /*Lo quie sea*/
}


/* Aquesta funcio genera la sopa de lletres, a partir del fitxer i altres parametres */
/* que ja decidireu. En aquest cas només l'emplena amb una SOPA d'EXEMPLE, es a dir */
/* que haureu de fer la vostra pròpia. */
void genera_sopa(sopa_t *s)
{
    s->dim = 30;    // Mida màxima: 40 x 40
    s->lletres = malloc(s->dim * s->dim * sizeof(char));   // Espai per a les lletres
    s->encertades = malloc(s->dim * s->dim * sizeof(char)); // Per saber si una lletra correspon a encert
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        s->encertades[i] = false;
        // Generem una lletra aleatoriament
        s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
    }

    s->n_par = 5;
    strcpy(s->par[0].ll, "ALZINA");
    strcpy(s->par[1].ll, "ARBUST");
    strcpy(s->par[2].ll, "BOLET");
    strcpy(s->par[3].ll, "CAMI");
    strcpy(s->par[4].ll, "PEDRA");

    s->n_encerts = 2;
    s->par[0].enc = false;
    s->par[1].enc = true;
    s->par[2].enc = true;
    s->par[3].enc = false;
    s->par[4].enc = false;

    // Ara posem un parell de paraules a la sopa com si s'haguessin encertat
    s->lletres[5] = 'B'; s->encertades[5] = true;
    s->lletres[6] = 'O'; s->encertades[6] = true;
    s->lletres[7] = 'L'; s->encertades[7] = true;
    s->lletres[8] = 'E'; s->encertades[8] = true;
    s->lletres[9] = 'T'; s->encertades[9] = true;

    s->lletres[65 + s->dim] = 'A'; s->encertades[65 + s->dim] = true;
    s->lletres[65 + 2 * s->dim] = 'R'; s->encertades[65 + 2 * s->dim] = true;
    s->lletres[65 + 3 * s->dim] = 'B'; s->encertades[65 + 3 * s->dim] = true;
    s->lletres[65 + 4 * s->dim] = 'U'; s->encertades[65 + 4 * s->dim] = true;
    s->lletres[65 + 5 * s->dim] = 'S'; s->encertades[65 + 5 * s->dim] = true;
    s->lletres[65 + 6 * s->dim] = 'T'; s->encertades[65 + 6 * s->dim] = true;
    
}


/* Mostra la sopa de lletres pel terminal */
/* En principi, NO HAURIEU DE MODIFICAR AQUEST CODI SI NO TOQUEU LES ESTRUCTURES DE DADES*/
void mostra_sopa (sopa_t *s)
{
    // Mostrem els numeros de columna
    printf("\033[0;31m");   // Color 
    printf("  ");
    for (int i = 10; i < s->dim + 1; i+=10)
    {
        for (int j=0; j < 18; j++)
            printf(" ");
        printf(" %d", i/10);

    }

    printf("\n  ");   
    for (int i = 0; i < s->dim; i++)
    {   
        int p = (i % 10) + 1;
        p != 10 ? printf(" %d", p) : printf(" 0");
    }

    printf("\n");
    printf("\033[0m");  // Tornem al color per defecte


    // Mostrem les lletres. Cada lletra ocupa dos espais: 
    // Si correspon a un encert, es marca
    for (int i = 0; i < s->dim ; i++)
    {
        printf("\033[0;31m");   // Color 
        printf("%-2d", i + 1);  // Mostrar numero de linia
        printf("\033[0m");  // Tornem al color per defecte

        for (int j = 0; j < s->dim; j++)
        {
            if (s->encertades[i * s->dim + j]) 
            {
                printf("\033[0;42m");   // Color verd de fons
                printf(" %c", s->lletres[i * s->dim + j]);
                printf("\033[0m");  // Tornem al color per defecte
            }
            else
            {
                printf(" %c", s->lletres[i * s->dim + j]);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("Portes %d encerts.\n", s->n_encerts);
    printf("Paraules a trobar: %d\n", s->n_par - s->n_encerts);
    for (int i = 0; i < s->n_par; i++)
    {
        if (!s->par[i].enc)
            printf("%s\n", s->par[i].ll);
    }

}