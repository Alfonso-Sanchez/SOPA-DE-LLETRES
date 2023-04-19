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

/** @brief Genera la sopa de lletres a partir del tamany indicat i les paraules ja carregades.
* @param sopa Estructura sopa_t
*/
void genera_sopa(sopa_t *s);

/** @brief Mostra la sopa de lletres generada en sopa_t.
*
* @param sopa Estructura sopa_t
*
*/
void mostra_sopa (sopa_t *s);

/**
 *  @brief Da la benvinguda al jugador.
*/
void saludar();

/** @brief Muestra les paraules que conte la sopa de lletres.
*
* @param sopa Estructura sopa_t
*
*/
void mostra_paraules(sopa_t *s);

/** 
 * @brief Mostra instruccions per a jugar al joc.
*/
void mostra_menu_joc();

/** @brief Lee palabras de un archivo.
*
* @param f Archiu a llegir.
* @param sopa Estructura sopa_t.
* @return Retorna true = si va tot be | false = si algo va mal.
*
*/
bool llegir_fitxer(sopa_t *s);

/** @brief Comproba la sopa de lletres.
*
* @param fil Numero fila.
* @param col Numero columna.
* @return true = encertat | false = no encertat.
*/
bool comprobar_sopa(int fil, int col, int dir, sopa_t *s);

/** @brief Comproba si l'usuari se ha rendit o no.
*
* @param rend_arr Array amb la posible paraula rendicio.
* @return True = Si hi ha rendicio | False = si no hi ha rendicio.
*
*/
bool comprobar_rendicio(char rend_arr[9]);
