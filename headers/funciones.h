#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LLETRES 8
#define MAX_PARAULES 10
#define MIN_SOPA 10
#define MAX_SOPA 40

/* Definicio del tipus per a desar les dades de la sopa de lletres */
/* Es una proposta que podeu canviar, ampliar, etc. */

typedef struct 
{
    char ll[MAX_LLETRES + 1];   // Lletres de la paraula (comptem centinella)
    int columna;
    int fila;
    int direccio;
    int longitud;
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
    bool guanya; //
    bool rendicio;

} sopa_t;

typedef struct 
{
   int fila;
   int columna;
   int direccio; 
} joc_t;

/** @brief Pregunta jugda i la guarda en el struct joc.
*
* @param j (E/S) Struct joc.
*/
void preguntar_jugada(joc_t *j);

/** @brief Genera la sopa de lletres a partir del tamany indicat i les paraules ja carregades.
* @param sopa (E/S) Estructura sopa_t
*/
void genera_sopa(sopa_t *s);

/** @brief Mostra la sopa de lletres generada en sopa_t.
*
* @param sopa Estructura sopa_t
*
*/

void mostra_sopa(sopa_t *s);

/** @brief Calcula la paraula amb la mida maxima.
*
* @param s (E/S) Struct sopa_t.n]
*
*/
void calcular_mida_maxima(sopa_t *s);

/** @brief Mostra solucio de la sopa.
*
* @param sopa Estructura sopa_t.
*
*/
void mostra_solucio(sopa_t *s);

/**
 *  @brief Da la benvinguda al jugador.
*/
void saludar();

/** @brief Mostra informació de la sopa (Paraules i nombre de encerts).
*
* @param sopa Estructura sopa_t
*
*/
void mostrar_informacio_sopa(sopa_t s);

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

/** @brief Ordena les paraules de la sopa.
*
* @param sopa Struct sopa_t.
*
*/
void ordenar_paraules (sopa_t *s);

/** @brief Comproba la sopa de lletres.
*
* @param fil Numero fila.
* @param col Numero columna.
* @return true = encertat | false = no encertat.
*/
bool comprobar_sopa(joc_t j, sopa_t s, int *p);

/** @brief Comproba si l'usuari se ha rendit o no.
*
* @param s Struct sopa_t.
* @param rend_arr Array amb la posible paraula rendicio.
* @return True = Si hi ha rendicio | False = si no hi ha rendicio.
*
*/
void comprobar_rendicio(sopa_t *s, char rend_arr[9]);

/** @brief Actualitza la sopa amb l'encert.
*
* @param j (E) Estructura joc_t.
* @param s (E/S) Estructura sopa_t. 
* @param p (E) Num paraula a actualitzar.
*
*/
void actualitzar_sopa(joc_t j, sopa_t *s, int p);

/** @brief Comrprovem si ha guanyat
 * 
 * @param s estructura sopa_t
 * 
*/
void comprova_guanya(sopa_t *s);

/** @brief Preguntar mida sopa.
*
* @param s Estructura sopa_t.]
*
*/
void pregunta_mida(sopa_t *s);

/** @brief Comproba que la mida siga superior o igual a la longitud maxima de entre totes les paraules.
*
* @param s (E) Estruct sopa_t.
* @return true - La mida es correcta.
* @return false - La mida es incorrecta.
*
*/
bool comprobar_mida(int mida);

/** @brief Pregunta al usuari que vol fer.
*
* @param rendicio_arr Taula que conte el que indique el usuari (Y / RENDICIO)
* 
*
*/
void preguntar_usuari(char rendicio_arr[]);

/** @brief Comproba si la paraula entra en la posicio i direccio indicada i si no hi ha una paraula en eixa posicio.
*
* @param fila (E) fila de posicio. 
* @param columna (E) columna de posicio.
* @param direccio (E) Direccio a comprobar.
* @param s (E) Estructura sopa_t.
* @return True - Si la posicio es correcta.
* @return False - Si la posicio es incorrecta.
*
*/
bool comprobar_posicio(int fila, int columna, int direccio, int paraula_actual, sopa_t s);

/** @brief Introdueix la paraula dins de la sopa. 
*
* @param fila (E) Fila de posicio.
* @param columna (E) Columna de posicio
* @param direccio (E) Direccio de introduccio.
* @param s (E/S) Estructura sopa_t.
*
*/
void introduir_paraula(int fila, int columna, int direccio, int paraula_actual, sopa_t *s);

/** @brief Cambia la paraula, si vols que estigue encertada o no.
*
* @param fila (E) Fila de posicio.
* @param columna (E) Columna de posicio.
* @param direccio (E) Direccio de la paraula.
* @param num_paraula (E) Numero de la paraula que volem cambiar.
* @param s (E/S) Estructura sopa_t.
* @param cambiar (E) Bool - True (Encertada) | False (No encertada)
*
*/
void cambiar_encertat_sopa(int fila, int columna, int direccio, int num_paraula, sopa_t *s, bool cambiar);

/** @brief Calcula la longitud de cada paraula.
*
* @param s (E/S) struct sopa_t.
*
*/
void calcular_longitud_paraules(sopa_t *s);