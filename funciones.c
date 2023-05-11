#include "headers/funciones.h"

/*Mostra el missatge de benvingua al joc*/
void saludar()
{
    printf("***********************************************************\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: Joan Arnau, Alex Caparros, Alfonso Sanchez\n");
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
    }
    return (llegir_fitxer);
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

void calcular_longitud_paraules(sopa_t *s)
{
    for (int i = 0; i < s->n_par; i++)
    {
        s->par[i].longitud = strlen(s->par[i].ll);
    }
    
}


void pregunta_mida(sopa_t *s)
{
    int mida_sopa;

    do
    {
        printf("La mida te que ser un valor %d - %d\n", MIN_SOPA, MAX_SOPA);
        printf("Indica la mida de la sopa de lletres:\n");
        scanf("%d", &mida_sopa);
        
    } while (!comprobar_mida(mida_sopa));
    fflush(stdin);
    s->dim = mida_sopa; // Guardem la mida dins del struct sopa.
}

bool comprobar_mida(int mida)
{
    bool correcte = false;
    if (mida >= MIN_SOPA && mida <= MAX_SOPA)
    {
        correcte = true;
    }

    return correcte;
}
void mostrar_informacio_sopa(sopa_t s)
{
    printf("Paraules: \n");
    for (int i = 0; i < s.n_par; i++)
    {
        if (!s.par[i].enc)
        {
            printf("> %s\n", s.par[i].ll);
        }
    }
    printf("\n");
    printf("Portes %d encerts.\n", s.n_encerts);
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
    do
    {
        printf("Introdueix direcció: \n");
        scanf("%d", &j->direccio);
        if (j->direccio != 1 && j->direccio != -1 && j->direccio != 2 && j->direccio != -2)
        {
            printf("Direccio incorrecta!\n");
        }
    } while (j->direccio != 1 && j->direccio != -1 && j->direccio != 2 && j->direccio != -2);
    fflush(stdin);  // Evitem que es que de malament el fgets i scanf.

    // Ajustem la direccio a la que usa el programa.
    switch (j->direccio)
    {
    case 1:
        j->direccio = 0;
        break;
    
    case -1:
        j->direccio = 1;
        break;

    case 2:
        j->direccio = 2;
        break;

    case -2:
        j->direccio = 3;
        break;
    
    }
    // Ajustem fila i col.
    j->columna --;
    j->fila --;
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
    int i;
    bool incorrecte = false;
    switch (direccio)  
    {
    case 0: // (→)
        i = 0;
        while (!incorrecte && i <= s.par[paraula_actual].longitud)
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
    
    case 1: // (←)
        i = 0;
        while (!incorrecte && i <= s.par[paraula_actual].longitud)
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

    case 2: // (↓)
        i = 0;
        while (!incorrecte && i <= s.par[paraula_actual].longitud)
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

    case 3: // (↑)
        i = 0;
        while (!incorrecte && i <= s.par[paraula_actual].longitud)
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
    }
    
    return incorrecte;
}

void introduir_paraula(int fila, int columna, int direccio, int paraula_actual, sopa_t *s)
{
    switch (direccio)  
    {
    case 0: // (→)
        for (int i = 0; i < s->par[paraula_actual].longitud; i++)
        {
            s->lletres[(fila + i) + columna * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[(fila + i) + columna * s->dim] = false;

            // Afegim la informació al struct.
            s->par[paraula_actual].fila = columna;
            s->par[paraula_actual].columna = fila;
            s->par[paraula_actual].direccio = 0;
        }
        break;
    
    case 1: // (←)
        for (int i = 0; i < s->par[paraula_actual].longitud; i++)
        {
            s->lletres[(fila - i) + columna * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[(fila - i) + columna * s->dim] = false;

            // Afegim la informació al struct.
            s->par[paraula_actual].fila = columna;
            s->par[paraula_actual].columna = fila;
            s->par[paraula_actual].direccio = 1;
        }
        break;

    case 2: // (↓)
        for (int i = 0; i < s->par[paraula_actual].longitud; i++)
        {
            s->lletres[fila + (columna + i) * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[fila + (columna + i) * s->dim] = false;
            // Afegim la informació al struct.
            s->par[paraula_actual].fila = columna;
            s->par[paraula_actual].columna = fila;
            s->par[paraula_actual].direccio = 2;
        }
        break;

    case 3: // (↑)
        for (int i = 0; i < s->par[paraula_actual].longitud; i++)
        {
            s->lletres[fila + (columna - i) * s->dim] = s->par[paraula_actual].ll[i];
            s->encertades[fila + (columna - i) * s->dim] = false;
            // Afegim la informació al struct.
            s->par[paraula_actual].fila = columna;
            s->par[paraula_actual].columna = fila;
            s->par[paraula_actual].direccio = 3;
        }
        break;
    }
}

void genera_sopa(sopa_t *s)
{
    /**
     * 1. Posar les paraules aleatoriament
     *  1.1 Mirar si la paraula entra en la direcció aleatoria, y posició aleatoria y no chafa ninguna paraula anterior.
     *  1.2 Si no entra, tornar a generar una direcció aleatoria y posició aleatoria, tornar a 1.1.
     * 2. Introduir la paraula en la posicio i direcció que si es pot posar.
     * 3. Rellenar tots els buits amb lletres mayuscules aleatories.
     */
    // Reserve el espai necesari.
    s->lletres = malloc(s->dim * s->dim * sizeof(char));
    s->encertades = malloc(s->dim * s->dim * sizeof(char));
    srand(time(NULL));
    int fila, columna, direccio;
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
    for (int i = 0; i < s->n_par; i++)
    {
        s->par[i].enc = false;
    }
}

void cambiar_encertat_sopa(int fila, int columna, int direccio, int num_paraula, sopa_t *s, bool cambiar)
{
    int fila_correcta, columna_correcta; // Intercambiem les variables fila i colum per que siguen correctes.
    fila_correcta = columna;
    columna_correcta = fila;
    switch (direccio)  
    {
    case 0: // (→)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[(fila_correcta + i) + columna_correcta * s->dim] = cambiar;
        }
        break;
    
    case 1: // (←)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[(fila_correcta - i) + columna_correcta * s->dim] = cambiar;
        }
        break;

    case 2: // (↓)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[fila_correcta + (columna_correcta + i) * s->dim] = cambiar;
        }
        break;

    case 3: // (↑)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[fila_correcta + (columna_correcta - i) * s->dim] = cambiar;
        }
        break;
    }
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
    

}

void mostra_solucio(sopa_t *s)

{
    for (int i = 0; i < s->n_par; i++)
    {
        cambiar_encertat_sopa(s->par[i].fila, s->par[i].columna, s->par[i].direccio, i, s, true);
    }
    mostra_sopa(s);
}

bool comprobar_sopa(joc_t j, sopa_t s, int *p)
{
    bool correcte = false;
    for (int i = 0; i < s.n_par; i++)
    {
        if ((j.fila == s.par[i].fila) && (j.columna == s.par[i].columna) && (j.direccio == s.par[i].direccio))
        {
           correcte = true;
           *p = i; // Retornem la paraula trobada.
        }
    }
    return correcte;
}

void actualitzar_sopa(joc_t j, sopa_t *s, int p)
{
    // Actualitzem el encert.
    cambiar_encertat_sopa(j.fila, j.columna, j.direccio, p, s, true);
    s->n_encerts++;
    s->par[p].enc = true;
}

void comprova_guanya(sopa_t *s)
{
    if (s->n_encerts == s->n_par)
    {
        s->guanya = true;
    }
}