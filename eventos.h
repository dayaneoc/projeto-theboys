
#ifndef _EVENTOS_H
#define _EVENTOS_H

#include "mundo.h"
#include "lef.h"
#include "lista.h"
#include "set.h"
#include "funcoes.h"

#define EV_CHEGA   0
#define EV_ESPERA  1
#define EV_DESISTE 2
#define EV_AVISA   3
#define EV_ENTRA   4
#define EV_SAI     5
#define EV_VIAJA   6
#define EV_MISSAO  7
#define EV_FIM     8

//=============================================EVENTOS==========================================================
/* Os eventos implementam as mudanças de estado que fazem evoluir a simulação. 
 * Cada evento tem um instante (t) de ocorrência, pode alterar variáveis (atributos das entidades)
 * e pode criar outros eventos no presente ou no futuro. */


/* O simulador executa os eventos e evolui o modelo de simulação no tempo. Para isso, ele mantém um
 * relógio global, representando o tempo atual no modelo, e uma Lista de Eventos Futuros (LEF), que é
 * uma lista de eventos ordenada por datas de ocorrências crescentes. */
void simula_mundo (Mundo *mundo);

/* Representa um herói H chegando em uma base B no instante T. Ao chegar, o herói analisa o tamanho da 
 * fila e decide se espera para entrar ou desiste. */ 
void evento_chega (Mundo *mundo, int t, int h, int b);


/* O herói H entra na fila de espera da base B. Assim que H entrar na fila, o porteiro da base B deve ser
 * avisado para verificar a fila. */ 
void evento_espera (Mundo *mundo, int t, int h, int b);


// O herói H desiste de entrar na base B, escolhe uma base aleatória D e viaja para lá.
void evento_desiste (Mundo *mundo, int t, int h, int b);


// O porteiro da base B trata a fila de espera.
void evento_avisa (Mundo *mundo, int h, int t, int b);


// O herói H entra na base B. Ao entrar, o herói decide quanto tempo vai ficar e agenda sua saída da base.
void evento_entra (Mundo *mundo, int t, int h, int b);


/* O herói H sai da base B. Ao sair, escolhe uma base de destino para viajar; o porteiro de B é avisado, 
 * pois uma vaga foi liberada. */ 
void evento_sai (Mundo *mundo, int t, int h, int b);


// O herói H se desloca para uma base D (que pode ser a mesma onde já está).
void evento_viaja (Mundo *mundo, int t, int h, int d);


/* Uma missão M é disparada no instante T. 
 * Cada missão ocorre em um local aleatório e requer um conjunto aleatório de habilidades; ambos são 
 * definidos durante a inicialização.
 * Cada equipe é formada pelo conjunto de heróis presentes em uma base.
 * Uma equipe está apta para a missão se a união das habilidades de seus heróis contém as habilidades 
 * requeridas pela missão.
 * Deve ser escolhida para a missão a equipe da base mais próxima ao local da missão e que esteja apta
 * para ela.
 * Ao completar uma missão, os heróis da equipe escolhida ganham pontos de experiência.
 * Se uma missão não puder ser completada, ela é marcada como impossível e adiada de 24 horas.*/
void evento_missao (Mundo *mundo, struct evento_t *evento, int t, int m);


// Encerra a simulação no instante T.
void evento_fim (Mundo *mundo, int t);

#endif