
#include <stdio.h>
#include <stdlib.h>
#include "lef.h"
#include "lista.h"
#include "set.h"
#include "mundo.h"
#include "funcoes.h"
#include "eventos.h"


//========================================INICIALIZA MUNDO=======================================
Mundo *cria_mundo (int tamanho, int n_herois, int n_bases, int n_missoes,
                   int n_habilidades)
{
    Mundo *mundo;
    int i;

    // Aloca memória para a estrutura mundo.
    mundo = (Mundo*) malloc(sizeof(Mundo));

    if (!mundo)
        return (NULL);

    // Inicia mundo.
    mundo->n_herois      = n_herois;
    mundo->n_bases       = n_bases;
    mundo->n_missoes     = n_missoes;
    mundo->n_habilidades = n_habilidades;
    mundo->tamanho.x     = tamanho ;
    mundo->tamanho.y     = tamanho ;    
    mundo->relogio       = 0;

    
//----------------------------ENTIDADES DO MUNDO (Heróis, Bases e Missões)-------------------------
    // Cria vetor de herois.
    mundo->heroi = (Heroi*) malloc(mundo->n_herois * sizeof (Heroi)) ;

    if (!mundo->heroi)
        return (NULL);

    // Inicia os herois
    for (i = 0; i < mundo->n_herois; i++)
    {
        mundo->heroi[i].id          = i;
        mundo->heroi[i].experiencia = 0;
        mundo->heroi[i].paciencia   = aleat(0, 100);
        mundo->heroi[i].velocidade  = aleat(50, 5000);
        mundo->heroi[i].base        = -1;
        mundo->heroi[i].habilidades = set_create(n_habilidades);
        mundo->n_habilidades        = aleat(1, 3);

        while (set_card(mundo->heroi[i].habilidades) < mundo->n_habilidades)
            set_add(mundo->heroi[i].habilidades, aleat(0, N_HABILIDADES));
    }

    // Cria vetor de bases
    mundo->base = (Base*) malloc (mundo->n_bases * sizeof (Base));

    if (!mundo->base)
        return (NULL);

    // Inicia as bases.
    for (i = 0; i < n_bases; i++)
    {
        mundo->base[i].id          = i;
        mundo->base[i].lotacao     = aleat (3, 10);                  // número máximo de heróis na base.
        mundo->base[i].presentes   = set_create (mundo->n_herois);  // heróis presentes na base.
        mundo->base[i].fila_espera = lista_cria ();
        mundo->base[i].local.x     = aleat (0, mundo->tamanho.x);
        mundo->base[i].local.y     = aleat (0, mundo->tamanho.y);
    }


    //Cria vetor de missoes
    mundo->missao = (Missao*) malloc (mundo->n_missoes * sizeof (Missao));

    if (!mundo->missao)
        return (NULL);

    // Inicia as missoes
    for (i = 0; i < n_missoes; i++)
    {
        mundo->missao[i].id          = i;
        mundo->missao[i].habilidades = set_create(n_habilidades); 
        mundo->missao[i].local.x     = aleat(0, mundo->tamanho.x);
        mundo->missao[i].local.y     = aleat(0, mundo->tamanho.y);
        mundo->n_habilidades         = aleat (6, 10);

        while (set_card(mundo->missao[i].habilidades) < mundo->n_habilidades)
            set_add(mundo->missao[i].habilidades, aleat(0, N_HABILIDADES));
    }
    
    // Inicializa estimativas.
    mundo->n_missoes_cumpridas  = 0;
    mundo->n_missoes_tentativas = 0;
    
    // Cria Lef.
    mundo->lef = cria_lef ();

    return (mundo);
}

 //====================================EVENTOS INICIAIS================================================
void cria_eventos_iniciais (Mundo *mundo)
{
    struct evento_t *evento;
    int i, base, tempo;

    // Para cada herói.
    for (i = 0; i < mundo->n_herois; i++)
    {
        base  = aleat(0, mundo->n_bases - 1);
        tempo = aleat (0, 60*24*3);

        // Cria evento chega e insere na Lef.
        evento = cria_evento (tempo, EV_CHEGA, i, base);
        insere_lef (mundo->lef, evento);
    }   

    // Para cada missão.
    for (i = 0; i < mundo->n_missoes; i++)
    {
        tempo = aleat (0, T_FIM_DO_MUNDO);

        // Cria evento missão e insere na Lef.
        evento = cria_evento (tempo, EV_MISSAO, i, -1);
        insere_lef (mundo->lef, evento);
    } 
    
    // Evento Fim
    tempo = T_FIM_DO_MUNDO;

    // Cria evento fim e insere na Lef.
    evento = cria_evento (tempo, EV_FIM, -1, -1);
    insere_lef (mundo->lef, evento);
}


// Destroi_mundo
Mundo *destroi_mundo (Mundo *mundo)
{
    int i;
    
    if (mundo != NULL)
    {
        // Libera a memória alocada para os heróis.
        for (i = 0; i < mundo->n_herois; i++)
        {
            set_destroy (mundo->heroi[i].habilidades);       
        }
        free (mundo->heroi);

        // Libera memória alocada para as bases.
        for (i = 0; i < mundo->n_bases; i++)
        {
            set_destroy (mundo->base[i].presentes);       
            lista_destroi (mundo->base[i].fila_espera);                                   
        }
        free (mundo->base); 

        // Libera a memória alocada para as missões.
        for (i = 0; i < mundo->n_missoes; i++)
        {
            set_destroy (mundo->missao[i].habilidades);   

        }
        free (mundo->missao);

        // Libera a memória alocada para o mundo.
        free (mundo); 
    }    
    return (NULL);
}

