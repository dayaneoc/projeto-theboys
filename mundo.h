// Entidades e atributos do mundo.

#ifndef _MUNDO_H
#define _MUNDO_H

#include "lista.h"
#include "set.h"
#include "lef.h"

#define T_INICIO                         0
#define T_FIM_DO_MUNDO               20000//525600
#define N_TAMANHO_MUNDO              20000
#define N_HABILIDADES                   10
#define N_HEROIS         N_HABILIDADES  * 5
#define N_BASES          N_HEROIS       / 6
#define N_MISSOES        T_FIM_DO_MUNDO / 100

// Estrutura para coordenadas.
typedef struct 
{
    int x;
    int y;
} Coordenadas;

// Representação de cada heroi.
typedef struct
{
    struct set_t *habilidades;
    int           paciencia;
    int           velocidade;
    int           experiencia;
    int           base;
    int           id;
} Heroi;

/* Representa cada local frequentado pelos heróis para formar equipes.
 * Cada base tem uma localização em um plano cartesiano, uma lotação que pode estar cheia e possui uma fila de espera.*/

// Estrutura que define uma base.
typedef struct
{
    //struct set_t  *habilidades;
    Coordenadas    local;
    int            id;
    struct set_t  *presentes;
    lista_t       *fila_espera;
    int            lotacao;
    
} Base;

// Estrutura que define uma missão.
typedef struct
{
    struct set_t  *habilidades;
    Coordenadas    local;
    int            id;
} Missao;

// Estrutura que representa o mundo.
typedef struct
{
    struct lef_t *lef;
    Heroi        *heroi;      // Vetor representando todos os heróis.
    Base         *base;      // Vetor representando todas as bases.
    Missao       *missao;   // Vetor representando todas as missoes.
    Coordenadas   tamanho;
    int           n_herois;
    int           n_bases;
    int           n_missoes;
    int           n_habilidades;
    int           relogio;
    int           t_inicio;
    int           t_fim;
    int           n_missoes_cumpridas;
    int           n_missoes_tentativas;
} Mundo;


// Cria mundo e inicializa todas as entidades do mundo.
Mundo *cria_mundo (int tamanho, int n_herois, int n_bases, int n_missoes, int n_habilidades);


/* Antes de iniciar a simulação, é necessário criar e inserir na LEF alguns eventos iniciais.
 * Esses eventos serão em seguida processados e poderão gerar novos eventos, 
 * o que fará avançar a simulação. */
void cria_eventos_iniciais (Mundo *mundo);

// Destroi_mundo
Mundo *destroi_mundo (Mundo *mundo);


#endif
