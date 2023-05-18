#include "headers/funciones.h"

/*Mostra el missatge de benvingua al joc*/
void saludar()
{
    printf("***********************************************************\n\n");
    printf("Us donem la benvinguda al joc de la sopa de lletres!\n");
    printf("Autors: Joan Arnau, Alfonso Sanchez\n\n");
    printf("***********************************************************\n");
}

/*Mostra el missatge dins del joc amb instruccions de com jugar*/
void mostra_menu_joc()
{
    printf("*************************** INSTRUCCIONS ************************************************\n");
    printf("Per jugar tens que indicar, la fila, la columna i la direcció 1 (→) -1 (←) 2 (↓) -2 (↑).\n");
    printf("Si vols rendirte escriu \"RENDICIO\" en la següent pregunta!\n");
    printf("*****************************************************************************************\n");
}

/* Aquesta funcio llegeix les paraules dun fitzer i las carrega dins de paraula_t dins de sopa_t*/
bool llegir_fitxer(sopa_t *s)
{
    FILE *fitxer;
    char paraula [MAX_LLETRES + 1];
    bool fitxer_valid = true;
    int i;

    if ((fitxer = fopen("PARAULES.txt", "r")) == NULL)
    {
        fitxer_valid = false;
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
    return (fitxer_valid);
}


/*Ordena paraules de la sopa*/
void ordenar_paraules (sopa_t *s)
{
    //int longitud = sizeof(s->par)/sizeof(s->par[0]);
    char temporal[MAX_LLETRES + 1];
    int x, paraula_actual;

    for (x = 0; x < s->n_par; x++)
    {
        for (paraula_actual = 0; paraula_actual < s->n_par - 1; paraula_actual++)
        {
            int seguent_paraula = paraula_actual + 1;

            if (strcmp(s->par[paraula_actual].ll, s->par[seguent_paraula].ll) > 0)
            {
                // Desplaçem la cadena actual a la temporal
                memcpy(temporal, s->par[paraula_actual].ll, MAX_LLETRES + 1);
                // Desplaçem al actual el seguent element.
                memcpy(s->par[paraula_actual].ll, s->par[seguent_paraula].ll, MAX_LLETRES + 1);
                // Y en el seguent element, el que habia en el actual, pero esta en el temporal.
                memcpy(s->par[seguent_paraula].ll, temporal, MAX_LLETRES + 1);
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

void pregunta_i_guarda_mida(sopa_t *s)
{
    int mida_sopa;

    do
    {
        printf("La mida te que ser un valor %d - %d\n", MIN_SOPA, MAX_SOPA);
        printf("Indica la mida de la sopa de lletres:\n");
        scanf("%d", &mida_sopa);
        
    } while (!comprobar_mida(mida_sopa));
    fflush(stdin);
    guardar_mida(s, mida_sopa);
}

void guardar_mida(sopa_t *s, int mida)
{
    s->dim = mida;
}

bool es_mida_correcta(int mida)
{
    bool es_mida_correcta = false;
    if (mida >= MIN_SOPA && mida <= MAX_SOPA)
    {
        es_mida_correcta = true;
    }

    return es_mida_correcta;
}
void mostrar_informacio_sopa(sopa_t s)
{
    printf(">> Paraules: \n");
    for (int paraula = 0; paraula < s.n_par; paraula++)
    {
        if (!s.par[paraula].enc)
        {
            printf("> %s\n", s.par[paraula].ll);
        }
    }
    printf("\n");
    printf(">> Portes %d encerts.\n\n", s.n_encerts);
}

void preguntar_usuari(char resposta_usuari[])
{
    printf("Has trobat una paraula? Y / RENDICIO\n");
    fflush(stdin); // Evitem que es que de malament el fgets i scanf.
    fgets (resposta_usuari, 9, stdin);
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
        if (j->direccio != DIRECCIO_JUGADA_ESQUERRA_DRETA && j->direccio != DIRECCCIO_JUGADA_DRETA_ESQUERRA && j->direccio != DIRECCIO_JUGADA_CAP_ABAIX && j->direccio != DIRECCIO_JUGADA_CAP_AMUNT)
        {
            printf("Direccio incorrecta!\n");
        }
    } while (j->direccio != DIRECCIO_JUGADA_ESQUERRA_DRETA && j->direccio != DIRECCCIO_JUGADA_DRETA_ESQUERRA && j->direccio != DIRECCIO_JUGADA_CAP_ABAIX && j->direccio != DIRECCIO_JUGADA_CAP_AMUNT);
}

void ajustar_jugada(joc_t *j)
{
     switch (j->direccio)
    {
        case DIRECCIO_JUGADA_ESQUERRA_DRETA:
            j->direccio = DIRECCIO_PROGRAMA_ESQUERRA_DRETA;
            break;
        
        case DIRECCCIO_JUGADA_DRETA_ESQUERRA:
            j->direccio = DIRECCCIO_PROGRAMA_DRETA_ESQUERRA;
            break;

        case DIRECCIO_JUGADA_CAP_AMUNT:
            j->direccio = DIRECCIO_PROGRAMA_CAP_AMUNT;
            break;

        case DIRECCIO_JUGADA_CAP_ABAIX:
            j->direccio = DIRECCIO_PROGRAMA_CAP_ABAIX;
            break;
    
    }
    // Ajustem fila i col.
    j->columna --;
    j->fila --;
    // Ajustem la fila i col a com esta en el programa
    int aux = 0;
    aux = j->columna;
    j->columna = j->fila;
    j->fila = aux;

}
/*Comproba si la persona se ha rendit o no*/
void es_rendicio(sopa_t *s, char resposta_usuari[9])
{
    s->rendicio = false;
    if(strcmp(resposta_usuari, "RENDICIO") == 0)
    {
        s->rendicio = true;
    }
}

bool es_pot_introduir_paraula(int fila, int columna, int direccio, int paraula_actual, sopa_t s)
{
    int posicio;
    bool es_pot_introduir_paraula = true;
    switch (direccio)  
    {
        case DIRECCIO_PROGRAMA_ESQUERRA_DRETA: // (→)
            posicio = 0;
            while (es_pot_introduir_paraula && posicio <= s.par[paraula_actual].longitud)
            {
                if (((fila + posicio) > s.dim) || (s.lletres[(fila + posicio) + columna * s.dim] >= 'A' && s.lletres[(fila + posicio) + columna * s.dim] <= 'Z'))
                {
                    es_pot_introduir_paraula = false;
                }
                posicio ++;
            }
            break;
        
        case DIRECCCIO_PROGRAMA_DRETA_ESQUERRA: // (←)
            posicio = 0;
            while (es_pot_introduir_paraula && posicio <= s.par[paraula_actual].longitud)
            {
                if (((fila - posicio) < 0) || (s.lletres[(fila - posicio) + columna * s.dim] >= 'A' && s.lletres[(fila - posicio) + columna * s.dim] <= 'Z'))
                {
                    es_pot_introduir_paraula = false;
                }
                posicio ++;
            }
            break;

        case DIRECCIO_PROGRAMA_CAP_ABAIX: // (↓)
            posicio = 0;
            while (es_pot_introduir_paraula && posicio <= s.par[paraula_actual].longitud)
            {
                if (((columna + posicio) > s.dim) || (s.lletres[fila + (columna + posicio) * s.dim] >= 'A' && s.lletres[fila + (columna + posicio) * s.dim] <= 'Z'))
                {
                    es_pot_introduir_paraula = false;
                }
                posicio ++;
            }
            break;

        case DIRECCIO_PROGRAMA_CAP_AMUNT: // (↑)
            posicio = 0;
            while (es_pot_introduir_paraula && posicio <= s.par[paraula_actual].longitud)
            {
                if (((columna - posicio) < 0) || (s.lletres[fila + (columna - posicio) * s.dim] >= 'A' && s.lletres[fila + (columna - posicio) * s.dim] <= 'Z'))
                {
                    es_pot_introduir_paraula = false;
                }
                posicio ++;
            }
            break;
    }
    
    return es_pot_introduir_paraula;
}

void introduir_paraula(int fila, int columna, int direccio, int paraula_actual, sopa_t *s)
{
    switch (direccio)  
    {
        case DIRECCIO_PROGRAMA_ESQUERRA_DRETA: // (→)
            for (int i = 0; i < s->par[paraula_actual].longitud; i++)
            {
                s->lletres[(fila + i) + columna * s->dim] = s->par[paraula_actual].ll[i];
                s->encertades[(fila + i) + columna * s->dim] = false;
            }
            break;
        
        case DIRECCCIO_PROGRAMA_DRETA_ESQUERRA: // (←)
            for (int i = 0; i < s->par[paraula_actual].longitud; i++)
            {
                s->lletres[(fila - i) + columna * s->dim] = s->par[paraula_actual].ll[i];
                s->encertades[(fila - i) + columna * s->dim] = false;
            }
            break;

        case DIRECCIO_PROGRAMA_CAP_ABAIX: // (↓)
            for (int i = 0; i < s->par[paraula_actual].longitud; i++)
            {
                s->lletres[fila + (columna + i) * s->dim] = s->par[paraula_actual].ll[i];
                s->encertades[fila + (columna + i) * s->dim] = false;
            }
            break;

        case DIRECCIO_PROGRAMA_CAP_AMUNT: // (↑)
            for (int i = 0; i < s->par[paraula_actual].longitud; i++)
            {
                s->lletres[fila + (columna - i) * s->dim] = s->par[paraula_actual].ll[i];
                s->encertades[fila + (columna - i) * s->dim] = false;
            }
            break;
    }
    // Afegim la informació al struct.
    s->par[paraula_actual].fila = fila;
    s->par[paraula_actual].columna = columna;
    s->par[paraula_actual].direccio = direccio;
}

void genera_sopa(sopa_t *s)
{
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
        // Comprovem la posicio.
        while (!es_pot_introduir_paraula(fila, columna, direccio, i, *s))
        {
            fila = rand()%s->dim;
            columna = rand()%s->dim;
            direccio = rand()%4;
        }
        introduir_paraula(fila, columna, direccio, i, s);
    }

    // Rellenar tots el buits amb lletres aleatories. 
    for (int i = 0; i < s->dim * s->dim; i++)
    {
        if (!(s->lletres[i] >= 'A' && s->lletres[i] <= 'Z'))
        {
            s->encertades[i] = false;
            s->lletres[i] = 'A' + (rand() % ('Z'-'A' + 1));
        }
    }
}

void inicialitzar_variables_inicials(sopa_t *s)
{
    s->n_encerts = 0;
    for (int i = 0; i < s->n_par; i++)
    {
        s->par[i].enc = false;
    }
    s->guanya = false;
    s->rendicio = false;
}

void cambiar_encertat_sopa(int fila, int columna, int direccio, int num_paraula, sopa_t *s, bool cambiar)
{
    switch (direccio)  
    {
    case DIRECCIO_PROGRAMA_ESQUERRA_DRETA: // (→)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[(fila + i) + columna * s->dim] = cambiar;
        }
        break;
    
    case DIRECCCIO_PROGRAMA_DRETA_ESQUERRA: // (←)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[(fila - i) + columna * s->dim] = cambiar;
        }
        break;

    case DIRECCIO_PROGRAMA_CAP_ABAIX: // (↓)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[fila + (columna + i) * s->dim] = cambiar;
        }
        break;

    case DIRECCIO_PROGRAMA_CAP_AMUNT: // (↑)
        for (int i = 0; i < s->par[num_paraula].longitud; i++)
        {
            s->encertades[fila + (columna - i) * s->dim] = cambiar;
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

bool es_paraula_correcta(joc_t j, sopa_t s, int *p)
{
    bool es_correcte = false;
    for (int i = 0; i < s.n_par; i++)
    {
        if ((j.fila == s.par[i].fila) && (j.columna == s.par[i].columna) && (j.direccio == s.par[i].direccio))
        {
           es_correcte = true;
           *p = i; // Retornem la paraula trobada.
        }
    }
    return es_correcte;
}

void actualitzar_sopa(joc_t j, sopa_t *s, int p)
{
    // Actualitzem el encert.
    cambiar_encertat_sopa(j.fila, j.columna, j.direccio, p, s, true);
    s->n_encerts++;
    s->par[p].enc = true;
}

void es_guanya(sopa_t *s)
{
    if (s->n_encerts == s->n_par)
    {
        s->guanya = true;
    }
}