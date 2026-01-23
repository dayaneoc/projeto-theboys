#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

// Cria uma lista vazia.
// Retorno: ponteiro p/ a lista ou NULL se falhar.
lista_t* lista_cria ()
{
    lista_t *lista;

    // Aloca a lista
    lista = (lista_t *) malloc(sizeof(lista_t));
   
    if (!lista)
    {
        return (NULL);
    }
    lista->head = NULL; // primeiro elemento
    lista->tail = NULL; // último elemento
    lista->size = 0;    // lista vazia

    return (lista);
}

// Remove todos os elementos da lista, libera espaço.
// Retorno: NULL.
lista_t* lista_destroi (lista_t* lst)
{
    int valor;

    while (!(lista_vazia (lst)))
        lista_retira (lst, &valor, 0);
    free (lst);

    return (NULL);
}

// Nas operações insere/retira/consulta, a posição 0 indica o início da lista;
// se a posição for -1 ou for além do fim, considerar o fim da lista.
// Insere o elemento na lista na posição indicada.
// Retorno: número de elementos na lista após a operação ou -1 se falhar.
int lista_insere (lista_t* lst, int elem, int pos)
{
    lnode_t *novo_elem;
    lnode_t *proximo, *anterior;
    int i;

    // Aloca novo elemento.
    novo_elem = (lnode_t*) malloc(sizeof(lnode_t));
    if (!novo_elem)
    {
        return (-1);
    }

    novo_elem->val = elem;

    if (!lst->tail && !lst->head) // Insere na lista vazia.
    {
        lst->tail = novo_elem; // Se a lista está vazia, o novo elemento será tanto a cabeça quanto a cauda.
        lst->head = novo_elem; // Se a lista está vazia, o novo elemento será tanto a cabeça quanto a cauda.
        novo_elem->next = NULL;
        novo_elem->prev = NULL;
    }
    else
    if (pos == 0) // Insere no inicio da lista.
    {
        proximo = lst->head;
        novo_elem->next = proximo;
        proximo->prev = novo_elem;
        lst->head = novo_elem;
    }
    else
    if (pos == -1 || pos >= lista_tamanho (lst)) // Insere no fim da lista
    {
        anterior = lst->tail;
        novo_elem->prev = anterior;
        anterior->next = novo_elem;
        lst->tail = novo_elem;
    }
    else //Insere no meio da lista.
    {
        proximo = lst->head;

        for (i = 1; i < pos; i++)
        {
            proximo = proximo->next;
        }
        anterior = proximo->prev;
        novo_elem->next = proximo;
        proximo->prev = novo_elem;
        novo_elem->prev = anterior;
        anterior->next = novo_elem;
    }
    lst->size++; // Atualiza o tamanho da lista.
    return (lista_tamanho (lst));
}

// Retira o elemento da lista, na posição indicada.
// Retorno: número de elementos na lista após a operação ou -1 se falhar.
int lista_retira (lista_t* lst, int* elem, int pos)
{
    lnode_t *proximo;
    lnode_t *anterior;
    lnode_t *removido;
    int i;

    // Posição inválida.
    if (pos >= lista_tamanho (lst) || pos < 0)
        return (-1);
    else
    if (lista_tamanho (lst) == 1) // Remove único elemento da lista.
    {
        removido = lst->head;
        lst->head = NULL;
        lst->tail = NULL;
    }
    else
    if (pos == lista_tamanho (lst)) // Remove o último elemento da lista.
    {
        removido = lst->tail;
        anterior = removido->prev;
        anterior->next = NULL;
        lst->tail = anterior;
    }
    else
    if (pos == 0) // Remove o primeiro elemento da lista.
    {
        removido = lst->head;
        proximo = removido->next;
        proximo->prev = NULL;
        lst->head = proximo;
    }
    else // Remove elemento do meio da lista.
    {
        removido = lst->head;
        for (i = 0; i < pos; i++)
            removido = removido->next;

        anterior = removido->prev;
        proximo = removido->next;
        anterior->next = proximo;
        proximo->prev = anterior;
    }
    *elem = removido->val;

    // Libera espaço do elemento removido e atualiza o tamanho da lista.
    free (removido);
    lst->size--;

    return (lista_tamanho (lst));
}

// Informa o valor do elemento na posição indicada, sem retirá-lo.
// Retorno: número de elementos na lista ou -1 se falhar.
int lista_consulta (lista_t* lst, int* elem, int pos)
{
    lnode_t *atual;
    int i;

    if (pos == -1)
        pos = lista_tamanho (lst) -1;

    // Posição inválida.
    if (pos >= lista_tamanho (lst) || pos < 0)
        return (-1);
    else // Percorre a lista até a posição indicada.
    {
        atual = lst->head; // Posiciona no início da lista.
        for (i = 0; i < pos; i++)
            atual = atual->next; // Avança na lista.
    }
    *elem = atual->val;

    return (lista_tamanho (lst));
}

// Informa a posição da 1ª ocorrência do elemento indicado.
// Retorno: posição do elemento ou -1 se não encontrar ou falhar.
int lista_procura (lista_t* lst, int elem)
{
    lnode_t *atual;
    int i;

    atual = lst->head; // Posiciona no início da lista.

    for (i = 0; i < lista_tamanho (lst); i++)
    {
        if (atual->val == elem) // Encontrou o valor.
            return (i);

        atual = atual->next; // Senão avança na lista.
    }
    return (-1); // Valor não encontrado.
}

// Informa se a lista está vazia.
// Retorno: 1 se a lista está vazia ou 0 caso contrário.
int lista_vazia (lista_t* lst)
{
    if (lista_tamanho (lst) == -1)
        return (-1);

    if (lista_tamanho (lst) == 0)
        return (1);
    return (0);
}

// Informa o tamanho da lista (o número de elementos presentes nela).
// Retorno: número de elementos na lista ou -1 se falhar.
int lista_tamanho (lista_t* lst)
{
    if (lst == NULL)
        return (-1);
    return (lst->size);
}

// Imprime o conteúdo da lista, do inicio ao fim, neste formato:
// [ valor valor valor valor ... ]
// Esta função não faz parte do TAD, mas é útil para testes.
void lista_imprime (char *nome, lista_t* lst)
{
    lnode_t *atual = lst->head;
    int i;

    printf ("%s [ ", nome);

    for (i = 0; i < lista_tamanho (lst); i++)
    {
        printf ("%d ", atual->val);
        atual = atual->next;
    }
    printf ("]");
   // printf ("] (%d elementos)\n", lista_tamanho (lst));
}
