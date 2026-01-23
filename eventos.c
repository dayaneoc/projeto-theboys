#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "eventos.h"


// Laço principal da simulação dos eventos

//===============================SIMULAÇÃO A EVENTOS DISCRETOS==========================================
void simula_mundo (Mundo *mundo)
{
    struct evento_t *ev;
    int fim = 0;

    while (!fim)
    {
        ev = retira_lef (mundo->lef);
        if (ev != NULL)
        {
            mundo->relogio = ev->tempo;
            switch (ev->tipo)
            {
                case EV_CHEGA:
                {
                    evento_chega (mundo, ev->tempo, ev->dado1, ev->dado2);
                    destroi_evento(ev); 
                    break;
                }
                case EV_ESPERA:
                {
                    evento_espera (mundo, ev->tempo, ev->dado1, ev->dado2);
                    destroi_evento(ev); 
                    break;
                }
                case EV_DESISTE:
                {
                    evento_desiste (mundo, ev->tempo, ev->dado1, ev->dado2);
                    destroi_evento(ev); 
                    break;
                }
                case EV_AVISA:
                {
                    evento_avisa (mundo, ev->tempo, ev->dado1, ev->dado2);
                    destroi_evento(ev); 
                    break;
                }
                case EV_ENTRA:
                {
                    evento_entra (mundo, ev->tempo, ev->dado1, ev->dado2);
                    destroi_evento(ev);
                    break;
                }
                case EV_SAI:
                {
                    evento_sai (mundo, ev->tempo, ev->dado1, ev->dado2);
                    destroi_evento(ev);
                    break;
                }
                case EV_VIAJA:
                {
                    evento_viaja (mundo, ev->tempo, ev->dado1, ev->dado2);
                    destroi_evento(ev);
                    break;
                }
                case EV_MISSAO:
                {
                    evento_missao (mundo, ev, ev->tempo, ev->dado1);
                    break;
                }
                case EV_FIM:
                {
                    evento_fim (mundo, ev->tempo);
                    fim = 1;
                    destroi_evento(ev);
                    break ;
                }
            }
           
        }
        else
            fim = -1;
    }
}

void evento_chega (Mundo *mundo, int t, int h, int b)
{
    struct evento_t *evento;
    bool             espera;

    // Verifica se o ponteiro é nulo.
    if (!mundo)
        return;
    
    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || b < 0 || b >= mundo->n_bases)
        return;

    // Atualiza a base do herói.
    mundo->heroi[h].base = b;


    // Se há vagas na Base e a fila de espera na Base está vazia.
    // Se há vagas em B e a fila de espera em B está vazia.
    if (set_card(mundo->base[b].presentes) < mundo->base[b].lotacao && lista_vazia(mundo->base[b].fila_espera))
        espera = true;
    else
        espera = (mundo->heroi[h].paciencia) > (10 * mundo->base[b].fila_espera->size);

    if (espera == true)
    {
        evento = cria_evento (t, EV_ESPERA, h, b); 
        insere_lef (mundo->lef, evento);
        printf (" %6d: CHEGA  HEROI %2d BASE %d (%1d/%1d) ESPERA\n", t, h, b, 
                set_card (mundo->base[b].presentes), mundo->base->lotacao);
    }
    else
    {
        evento = cria_evento (t, EV_DESISTE, h, b);
        insere_lef (mundo->lef, evento);
        printf (" %6d: CHEGA  HEROI %2d BASE %d (%1d/%1d) DESISTE\n", t, h, b, 
                mundo->base->presentes->num, mundo->base->lotacao);
    }
     
}

void evento_espera (Mundo *mundo, int t, int h, int b)
{
    struct evento_t *evento;

   // Verifica se o ponteiro é nulo.
    if (!mundo)
        return;
    
    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || b < 0 || b >= mundo->n_bases)
        return;

    printf (" %6d: ESPERA HEROI %2d BASE %d (%1d)\n", t, h, b, 
            set_card(mundo->base[b].presentes));

    
    lista_insere (mundo->base[b].fila_espera, h, -1);
    evento = cria_evento (t, EV_AVISA, h, b);
    insere_lef (mundo->lef, evento);
}

void evento_desiste (Mundo *mundo, int t, int h, int b)
{
    struct evento_t *evento;

    int base_d;
    
    // Verifica se o ponteiro é nulo.
    if (!mundo)
        return;

    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || b < 0 || b >= mundo->n_bases)
    {
        return;
    }
         

    printf (" %6d: DESISTE HEROI %2d BASE %d (%1d)\n", t, h, b, set_card(mundo->base[b].presentes));

    base_d = aleat (0, mundo->n_bases -1);
    evento = cria_evento (t, EV_VIAJA, h, base_d);
    insere_lef (mundo->lef, evento);
}

void evento_avisa (Mundo *mundo, int t, int h, int b)
{
    struct evento_t *evento;

    // Verifica se o ponteiro é nulo.
    if (!mundo)
        return;
        
    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || b < 0 || b >= mundo->n_bases)
    {
        return;
    }    

    printf (" %6d: AVISA  PORTEIRO BASE %d (%2d/%2d)", t, b, 
            set_card(mundo->base[b].presentes), mundo->base[b].lotacao);
    lista_imprime (" FILA", mundo->base[b].fila_espera);
    printf ("\n");        
            
    /* Enquanto houver vaga na base e houver heróis esperando na fila: retira primeiro herói da fila e 
     * adiciona herói ao conjunto de heróis presentes na base.
     * Cria próximos eventos e insere na lista de eventos futuros.*/
    while (set_card(mundo->base[b].presentes) < mundo->base[b].lotacao && 
           !lista_vazia (mundo->base[b].fila_espera))
    {
        lista_retira (mundo->base[b].fila_espera, &h, 0);
        set_add (mundo->base[b].presentes, h);
        evento = cria_evento (t, EV_ENTRA, h, b);
        insere_lef (mundo->lef, evento); 

        printf(" %6d: AVISA  PORTEIRO BASE %d ADMITE %2d\n", t, b, h);
    }
}

void evento_entra (Mundo *mundo, int t, int h, int b)
{
    struct evento_t *evento;
    int tpb;

    // Verifica se o ponteiro é nulo.
    if (!mundo)
        return; 
   
    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || b < 0 || b >= mundo->n_bases)
    {
        return;
    }


    // Calcula o tempo de permanência do herói na base.
    tpb = 15 + (mundo->heroi[h].paciencia * aleat (1, 20));

    printf (" %6d: ENTRA  HEROI %2d BASE %d (%1d/%1d) (SAI NO TEMPO:%d)\n", t, h, b, 
            set_card(mundo->base[b].presentes), mundo->base[b].lotacao, t + tpb);

    
    evento = cria_evento (t + tpb, EV_SAI, h, b);
    insere_lef (mundo->lef, evento);
}

void evento_sai (Mundo *mundo, int t, int h, int b)
{
    struct evento_t *evento;
    int              base_d;

    // Verifica se o ponteiro é nulo.
    if (!mundo)
        return;

    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || b < 0 || b >= mundo->n_bases)
    {
        return;
    }

    printf (" %6d: SAI    HEROI %2d BASE %d (%1d/%1d)\n", t, h, b, 
            set_card(mundo->base[b].presentes), mundo->base[b].lotacao);

    set_del (mundo->base[b].presentes, h);         // Retira Herói do conjunto.
    base_d = aleat (0, mundo->n_bases -1);        // Escolhe uma base aleatória.

    
    evento = cria_evento (t, EV_VIAJA, h, base_d);
    insere_lef (mundo->lef, evento);
    evento = cria_evento (t, EV_AVISA, h, b);
    insere_lef (mundo->lef, evento);

}

void evento_viaja (Mundo *mundo, int t, int h, int d)
{
    struct evento_t  *evento;
    long             duracao_v;
    long             distancia;

    // Verifica se o ponteiro é nulo.
    if (!mundo)
        return;

    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || d < 0 || d >= mundo->n_bases)
    {
        return;
    }
        
    // Calcula duração da viagem:
    distancia = calcula_distancia (mundo, h, d);
    duracao_v = duracao_viagem (mundo, h, d);

    printf (" %6d: VIAJA  HEROI %2d BASE %d P/ BASE %d (DIST: %ld KM) (VEL: %d KM/H) (CHEGA NO TEMPO: %ld)\n", t, h, 
             mundo->heroi[h].base, d, distancia, mundo->heroi[h].velocidade, t + duracao_v); 
   
    evento = cria_evento (t + duracao_v, EV_CHEGA, h, d);
    insere_lef (mundo->lef, evento);
}

void evento_missao (Mundo *mundo, struct evento_t *evento, int t, int m)
{
    struct set_t    *habilidades_base;
    Base            *base;
    Heroi           *heroi;

    int              matriz[mundo->n_bases][2]; // alocação estática da matriz na pilha.
    int              i, h, b, base_missao_cumprida;
    bool             missao_cumprida;

    // Verifica se ponteiro é nulo.
    if (!mundo)
        return;

    // Verifica se os índices são válidos.
    if (m < 0 || m >= mundo->n_missoes)
    {
        return;
    }

    printf (" %6d: MISSAO %d HAB REQ: ", t, m);
    set_print(mundo->missao[m].habilidades);
    

    /* Cria e ordena uma matriz que contém as bases e suas respectivas distâncias.
     * A ordenação auxilia na hora de obter a base mais próxima que contém as habi-
     * lidades requeridas por cada missão, para que a mesma seja cumprida. */
    cria_matriz (mundo, m, matriz);
    ordena_matriz (mundo, matriz);
    
    // Pra cada base verifica os heróis que estão presentes nela.
    missao_cumprida = false;
    for (i = 0; i < mundo->n_bases; i++) 
    {
        b = matriz[i][0];
        base = &mundo->base[b];
        
        // Cria um conjunto de habilidades da base que está sendo verificada.
        habilidades_base = set_create(N_HABILIDADES);

        // Herói na base.
        for (h = 0; h < mundo->n_herois; h++ ) 
        {
            heroi = &mundo->heroi[h];
            // Se herói está presente na base, ele é adicionado ao conjunto de união de habilidades da base.
            if (set_in(base->presentes, h) == 1) 
            {
                set_union(habilidades_base, heroi->habilidades, habilidades_base);
            }
            
        }
        
        printf (" %6d: MISSAO %d HAB BASE %d: ", t, m, b);
        set_print (habilidades_base);
        
        if (missao_cumprida == false)
        {
            /* Se habilidades requeridas da missão estão contidas no conjunto de habilidades da base,
             * valida missão cumprida e incrementa o contador para o número de missões cumpridas.*/
            if (set_contains (habilidades_base, mundo->missao[m].habilidades))
            {
                missao_cumprida = true;
                base_missao_cumprida = b;
                mundo->n_missoes_cumpridas++;
                for (h = 0; h < mundo->n_herois; h++)
                {
                    heroi = &mundo->heroi[h];
                    if (set_in(base->presentes, h) == 1) // Cada herói presente na base que cumpriu a missão é atribuído a experiência. 
                        heroi->experiencia++;           
                } 
  
            }    
                       
        }
        set_destroy(habilidades_base); // Após cumprida a missão, libera o conjunto de habilidades da base.
        
    }

    // Caso a missão não consiga ser cumprida por nenhuma base, a missão é adiada para o dia seguinte.
    if (missao_cumprida == false)
    {
        printf (" %6d: MISSAO %d IMPOSSIVEL\n", t, m);
        evento->tempo = t + 24*60;
        if (evento->tempo < T_FIM_DO_MUNDO)
        {
            insere_lef (mundo->lef, evento);
            mundo->n_missoes_tentativas++;
            //return;
        } 
        else {
            destroi_evento (evento); // Destrói evento caso tempo exceder o tempo do mundo.
        }       
    }
    else {
        printf (" %6d: MISSAO %d CUMPRIDA BASE %d HEROIS: ", t, m, base_missao_cumprida);
        set_print (mundo->base[base_missao_cumprida].presentes);

        destroi_evento (evento); // Destrói evento após a missão ser cumprida.
    } 
}

// Apresenta as experiências dos heróis, estatísticas das missões e encerra a simulação.
void evento_fim (Mundo *mundo, int t)
{
    int i;
    float media_tentativas;
    float medias_cumpridas;

    media_tentativas = mundo->n_missoes_tentativas / (float)mundo->n_missoes;
    medias_cumpridas = (mundo->n_missoes_cumpridas * 100) / (float)mundo->n_missoes;
    
    printf (" %6d: FIM\n", t);
    printf ("\n");
    for (i = 0; i < mundo->n_herois; i++)
    {
        printf ("HEROI %2d PAC %3d VEL %4d EXP %4d HABS", i, mundo->heroi[i].paciencia, mundo->heroi[i].velocidade,
                 mundo->heroi[i].experiencia);
        set_print (mundo->heroi[i].habilidades);
    }
    printf ("%d/%d MISSOES CUMPRIDAS (%.2f%%), MEDIA %.2f TENTATIVAS/MISSAO\n", mundo->n_missoes_cumpridas,
             mundo->n_missoes, medias_cumpridas, media_tentativas);
     
}

