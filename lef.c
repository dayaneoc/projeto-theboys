#include <stdio.h>
#include <stdlib.h>
#include "lef.h"


/* Cria um evento contendo os parâmetros informados.
 * Retorna um ponteiro para o evento ou NULL se falhar.*/
struct evento_t *cria_evento (int tempo, int tipo, int dado1, int dado2)
{
    struct evento_t *evento;

    // Aloca memória para estrutura evento.
    evento = (struct evento_t *) malloc(sizeof(struct evento_t));

    if (!evento)
        return (NULL);

    evento-> tempo = tempo;
    evento-> tipo  = tipo;
    evento-> dado1 = dado1;
    evento-> dado2 = dado2;

    return (evento);
}

/* Destroi um evento e retorna NULL.*/ 
struct evento_t *destroi_evento (struct evento_t *e)
{
    if (e != NULL)
        free (e); // Libera a memória alocada para o evento.
    
    return (NULL);
}


/* Cria uma LEF vazia 
 * Retorna um ponteiro para a LEF ou NULL se falhar.*/
struct lef_t *cria_lef ()
{
    struct lef_t *lef;

    // Aloca memória para a estrutura Lef.
    lef = (struct lef_t *) malloc(sizeof(struct lef_t));

    if (!lef)
        return (NULL);

    lef-> primeiro = NULL;
    return (lef);
}

/* Destroi a LEF, liberando a memória ocupada por ela, inclusive os eventos.
 * Retorna NULL. */ 
struct lef_t *destroi_lef (struct lef_t *l)
{
    if (l != NULL)
    {
        struct nodo_lef_t *aux = l->primeiro;
        while (aux != NULL)
        {    
            struct nodo_lef_t *aux2 = aux->prox;
            free (aux->evento);
            free (aux);
            aux = aux2;
        }
        free (l);
    }   
    return (NULL);
}


/* Insere o evento apontado na LEF na ordem de tempos crescentes.
 * Eventos com o mesmo tempo devem respeitar a politica FIFO.
 * Retorna 1 em caso de sucesso ou 0 caso contrario. */
int insere_lef (struct lef_t *l, struct evento_t *e)
{
    struct nodo_lef_t *novo_nodo;
    struct nodo_lef_t *aux, *aux2;

    aux = l->primeiro;
    aux2 = NULL;
    
    if (!l || !e)
        return (0);

    // Aloca memória para a estrutura nodo.
    novo_nodo = (struct nodo_lef_t *) malloc(sizeof(struct nodo_lef_t));   

    if (!novo_nodo)
        return (0);

    novo_nodo->evento = e;
    novo_nodo->prox = NULL;

    /* Caso a lista esteja vazia ou o tempo do novo evento (e->tempo)
     * é menor do que o tempo do primeiro evento (l->primeiro->evento->tempo).*/
    if (l->primeiro == NULL || e->tempo < l->primeiro->evento->tempo)
    {
        novo_nodo->prox = l->primeiro;
        l->primeiro = novo_nodo;
        return (1);
    }

    // Caso novo evento tenha mesmo tempo que evento existente
    while (aux != NULL && e->tempo >= aux->evento->tempo)
    {
        if (e->tempo == aux->evento->tempo) // Encontrou evento com tempo igual, aplica FIFO.
        {
            while (aux->prox != NULL && e->tempo == aux->prox->evento->tempo)
            {    
                aux = aux->prox;
            }
            novo_nodo->prox = aux->prox;
            aux->prox = novo_nodo;
            return (1);
        }
        aux2 = aux;
        aux = aux->prox;
    }
    aux2->prox = novo_nodo;
    novo_nodo->prox = aux; 

    return (1);
}


/* Retira o primeiro evento da LEF.
 * Retorna ponteiro para o evento ou NULL se falhar. */
struct evento_t *retira_lef (struct lef_t *l)
{
    struct nodo_lef_t *primeiro_nodo;
    struct evento_t *evento_retirado;

    // Verifica se a lista está vazia ou ponteiro é nulo.
    if (l == NULL || l->primeiro == NULL)
        return (NULL);

    primeiro_nodo = l->primeiro;
    evento_retirado = primeiro_nodo->evento;

    
    l->primeiro = primeiro_nodo->prox; // Atualiza o primeiro nó.
    free (primeiro_nodo); // Libera a memória do primeiro nó retirado.

    return (evento_retirado); // Retorna o evento retirado.
}



/* Informa se a LEF está vazia.
 * Retorna 1 se estiver vazia, 0 se não estiver ou -1 se falhar. */
int vazia_lef (struct lef_t *l)
{
    if (l == NULL) // Falha
        return (-1);

    if (l->primeiro == NULL) // Lista vazia.
        return (1);
    else
        return (0);
}


/* Imprime a LEF. Não faz parte do TAD, mas serve para depuração.
 * Formato de saída:
 * tempo tipo dado1 dado2
 * tempo tipo dado1 dado2
 * ...
 * total XX eventos */
void imprime_lef (struct lef_t *l)
{
    struct nodo_lef_t *aux = l->primeiro;
    int cont;

    cont = 0;

    printf ("LEF:\n");

    while (aux != NULL)
    {
        printf (" tempo %d tipo %d d1 %d d2 %d\n", aux->evento->tempo, aux->evento->tipo, aux->evento->dado1, aux->evento->dado2);
        aux = aux->prox;
        cont++;
    }   
    printf (" Total %d eventos\n", cont);
}