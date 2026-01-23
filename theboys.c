// Programa principal do projeto "The Boys - 2023"
// Autor: Dayane O. de Carvalho GRR: 20170021

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "set.h"
#include "lef.h"
#include "eventos.h"
#include "mundo.h"


// programa principal

int main()
{
    Mundo *mundo;
    
    // cria o mundo
    mundo = cria_mundo (N_TAMANHO_MUNDO, N_HEROIS, N_BASES, N_MISSOES, N_HABILIDADES) ;

    if (!mundo)
        printf ("FALHA AO CRIAR MUNDO!\n");
   
    // cria eventos iniciais
    cria_eventos_iniciais (mundo) ;

    // simula o mundo
    simula_mundo (mundo) ;
    
    // destroi lista de eventos
    mundo->lef = destroi_lef (mundo->lef) ;

    // destroi o mundo
    mundo = destroi_mundo (mundo);

    return (0);
}
