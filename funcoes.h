#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mundo.h"


// Criar valores aleatórios.
int aleat (int min, int max);

// Calcula o tempo de permanência na base.
//int tpb (Mundo *mundo, int h);
long calcula_distancia (Mundo *mundo, int h, int b);

//Calcula duração da viagem.
long duracao_viagem (Mundo *mundo, int h, int b);

// Calcula a base mais próxima.
//long bmp (Mundo *mundo, int b, int m);
void cria_matriz (Mundo *mundo, int m, int matriz[][2]);
void ordena_matriz (Mundo *mundo, int matriz[][2]);
void imprimirMatriz(Mundo *mundo, int matriz[][2]); 