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
    FILE *fitxer;
    char paraula [MAX_LLETRES + 1];
    bool llegir_fitxer = true;
    int i;

    if ((fitxer = fopen("PARAULES.txt", "r")) == NULL)
    {
        llegir_fitxer = false;
    }
    else
    {
        i = 0;
        while (!feof(fitxer))
        {
            fscanf(fitxer, "%s", paraula);
            strcpy(s->par[i].ll, paraula);
            i ++;
        }
        s->n_par = i;
        calcular_mida_maxima(s);
    }
    return (llegir_fitxer);
}

void calcular_mida_maxima(sopa_t *s)
{
    int max = 0;
    int mida_actual;
    for (int i = 0; i <= s->n_par; i++)
    {
        mida_actual = strlen(s->par[i].ll);
        if (mida_actual > max)
        {
            max = strlen(s->par[i].ll);
        }
    }
    s->long_paraula_max = max;
}

/*Ordena paraules de la sopa*/
void ordenar_paraules (sopa_t *s)
{
    //int longitud = sizeof(s->par)/sizeof(s->par[0]);
    char temporal[MAX_LLETRES + 1];
    int x, index_actual;

    for (x = 0; x < s->n_par; x++)
    {
        for (index_actual = 0; index_actual < s->n_par - 1; index_actual++)
        {
            int index_seguent_element = index_actual + 1;

            if (strcmp(s->par[index_actual].ll, s->par[index_seguent_element].ll) > 0)
            {
                // Desplaçem la cadena actual a la temporal
                memcpy(temporal, s->par[index_actual].ll, MAX_LLETRES + 1);
                // Desplaçem al actual el seguent element.
                memcpy(s->par[index_actual].ll, s->par[index_seguent_element].ll, MAX_LLETRES + 1);
                // Y en el seguent element, el que habia en el actual, pero esta en el temporal.
                memcpy(s->par[index_seguent_element].ll, temporal, MAX_LLETRES + 1);
            }
        }
        
    }
    
}

void pregunta_mida(sopa_t *s)
{
    int mida_sopa;

    do
    {
        printf("Segons les paraules en el arxiu, la mida minima es %d\n", s->long_paraula_max);
        printf("Indica la mida de la sopa de lletres:\n");
        scanf("%d", &mida_sopa);
        
    } while (comprobar_mida(*s, mida_sopa));
    fflush(stdin);
    s->dim = mida_sopa; // Guardem la mida dins del struct sopa.
}

bool comprobar_mida(sopa_t s, int mida)
{
    bool correcte = false;
    if (mida < s.long_paraula_max)
    {
        correcte = true;
    }

    return correcte;
}
void mostra_paraules(sopa_t s)
{
    printf("Paraules: \n");
    for (int i = 0; i < s.n_par; i++)
    {
        printf("> %s\n", s.par[i].ll);
       
    }
}

void preguntar_usuari(sopa_t s, char rendicio_arr[])
{
    printf("Encerts: %d\n", s.n_encerts); // Ver donde lo metemos !!!!!!!!!! 
    printf("Has trobat una paraula? Y / RENDICIO\n");
    fgets (rendicio_arr, 9, stdin);
    fflush(stdin); // Evitem que es que de malament el fgets i scanf.
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
void comprobar_rendicio(sopa_t *s, char rend_arr[9])
{
    s->rendicio = false;
    if(strcmp(rend_arr, "RENDICIO") == 0)
    {
        s->rendicio = true;
    }
}

bool comprobar_posicio(int fila, int columna, int direccio, int paraula_actual, sopa_t s)
{
    int longitud_paraula = strlen(s.par[paraula_actual].ll);
    int i;
    bool incorrecte = false;
    switch (direccio)  
    {
    case 0: // (→)
        i = 0;
        while (!incorrecte && i <= longitud_paraula )
        {
            if ((columna + i) > s.dim)
            {
                incorrecte = true;
            }

            if (s.lletres[fila + (columna + i) * s.dim] >= 'A' && s.lletres[fila + (columna + i) * s.dim] <= 'Z')
            {
                incorrecte = true;
            }
            i ++;
        }
        break;
    
    case 1: // (←)
        i = 0;
        while (!incorrecte && i <= longitud_paraula )
        {
            if ((columna - i) < 0)
            {
                incorrecte = true;
            }

            if (s.lletres[fila + (columna - i) * s.dim] >= 'A' && s.lletres[fila + (columna - i) * s.dim] <= 'Z')
            {
                incorrecte = true;
            }
            i ++;
        }
        break;

    case 2: // (↓)
        i = 0;
        while (!incorrecte && i <= longitud_paraula)
        {
            if ((fila + i) > s.dim)
            {
                incorrecte = true;
            }

            if (s.lletres[(fila + i) + columna * s.dim] >= 'A' && s.lletres[(fila + i) + columna * s.dim] <= 'Z')
            {
                incorrecte = true;
            }
            i ++;
        }
        break;

    case 3: // (↑)
        i = 0;
        while (!incorrecte && i <= longitud_paraula)
        {
            if ((fila - i) < 0)
            {
                incorrecte = true;
            }

            if (s.lletres[(fila - i) + columna * s.dim] >= 'A' && s.lletres[(fila - i) + columna * s.dim] <= 'Z')
            {
                incorrecte = true;
            }
            i ++;
        }
        break;
    }
    
    return incorrecte;
}

void introduir_paraula(int fila, int columna, int direccio, int paraula_actual, sopa_t *s)
{
    int longitud_paraula = strlen(s->par[paraula_actual].ll);

    switch (direccio)  
    {
    case 0: // (→)
        for (int i = 0; i < longitud_paraula; i++)
        {
            s->lletres[fila + (columna + i) * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[fila + (columna + i) * s->dim] = false;
        }
        break;
    
    case 1: // (←)
        for (int i = 0; i < longitud_paraula; i++)
        {
            s->lletres[fila + (columna - i) * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[fila + (columna - i) * s->dim] = false;
        }
        break;

    case 2: // (↓)
        for (int i = 0; i < longitud_paraula; i++)
        {
            s->lletres[(fila + i) + columna * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[(fila + i) + columna * s->dim] = false;
        }
        break;

    case 3: // (↑)
        for (int i = 0; i < longitud_paraula; i++)
        {
            s->lletres[(fila - i) + columna * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[(fila - i) + columna * s->dim] = false;
        }
        break;
    }
}

void genera_sopa(sopa_t *s)
{
    /**
     * 1. Posar les paraules aleatoriament
     *  1.1 Mirar si la paraula entra en la direcció aleatoria, y posició aleatoria.
     *  1.2 Si no entra, tornar a generar una direcció aleatoria y posició aleatoria.
     * 2. Comprobar que estan totes les paraules y que no chafa a ninguna paraula anterior.
     * 3. Rellenar tots els buits amb lletres mayuscules aleatories.
     */
    int fila, columna, direccio;
    // Reserve el espai necesari.
    s->lletres = malloc(s->dim * s->dim * sizeof(char));
    s->encertades = malloc(s->dim * s->dim * sizeof(char));
    srand(time(NULL));

    // Generem per cada paraula posicions aleatories.
    for (int i = 0; i < s->n_par; i++)
    {
        fila = rand()%s->dim;
        columna = rand()%s->dim;
        direccio = rand()%4;
        /*
            1.1 Mirar si la paraula entra en la direcció aleatoria, y posició aleatoria.
            1.2 Si no entra, tornar a generar una direcció aleatoria y posició aleatoria.
         2. Comprobar que estan totes les paraules y que no chafa a ninguna paraula anterior. */

        while (comprobar_posicio(fila, columna, direccio, i, *s))
        {
            fila = rand()%s->dim;
            columna = rand()%s->dim;
            direccio = rand()%4;
        }
        introduir_paraula(fila, columna, direccio, i, s);
        // Guardem la informacio al struct.
        s->par[i].columna = columna;
        s->par[i].fila = fila;
        s->par[i].direccio = direccio;
    }

    // Rellenar tots el huecos amb lletres aleatories. 
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        // Inicialitzem totes les lletres com false.
        // Generem una lletra aleatoriament si la posicio on es vol posar esta buida.
        if (!(s->lletres[i] >= 'A' && s->lletres[i] <= 'Z'))
        {
            s->encertades[i] = false;
            s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
        }
    }

    // Inicialitzer variables necesaries:
    s->n_encerts = 0;
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

}