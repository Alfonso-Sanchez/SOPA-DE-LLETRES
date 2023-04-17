#include <stdbool.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */

typedef struct 
{
    char ll[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    bool enc;   // La paraula s'ha encertat
} paraula_t;

typedef struct 
{
    int dim;        // Nombre de files = nombre de columnes
    char *lletres;  // Taula amb les lletres
    bool *encertades;   // Les lletres son d'una paraula que s'ha encertat
    paraula_t par[MAX_PARAULES];    // Les paraules
    int n_par;  // Nombre de paraules
    int n_encerts;    // Nombre de paraules encertades
} sopa_t;

/** @brief [Descripcion]
*
* @param [parametro 1]
* @param [parametro 2]
* @return [return funcion]
*
*/
void genera_sopa(sopa_t *s);
/** @brief [Descripcion]
*
* @param [parametro 1]
* @param [parametro 2]
* @return [return funcion]
*
*/
void mostra_sopa (sopa_t *s);
