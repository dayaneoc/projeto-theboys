#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set.h"


/* Cria um conjunto vazio capaz de conter valores de "tamanho" (de 0 a tamanho -1)
 * Retorna: ponteiro para o novo conjunto ou NULL se falhar.*/
struct set_t *set_create (int max) 
{
    struct set_t *s;
    int i;

    // Aloca na memória.    
    s = (struct set_t*) malloc (sizeof  (struct set_t));

    // Testa se a estrutura é nula.
    if (!s)
        return (NULL);

    s-> flag = malloc (max * sizeof (bool));
    s-> num = 0;
    s-> size = max;

    for (i = 0; i < max; i++)
        s-> flag[i] = false; 

    return (s);
}

/* Libera a memória.
 * Retorna: NULL.*/
struct set_t *set_destroy (struct set_t *s)
{
    if (s)
    {
        free (s-> flag); // Libera a memória alocada para o array de booleanos.
        free (s); // Libera a memória alocada para a estrutura set_t.
    }
    return (NULL); 
}

/* Adiciona um item ao conjunto.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_add (struct set_t *s, int item)
{
    // Testa se a estrutura é nula.
    if (!s)
        return (0);

    if (item >= s-> size)
        return (0);
    
    if (!s-> flag[item]) // Se elemento não está no conjunto.
    {
        s-> flag[item] = true;
        s-> num++;
    }
    return (1);
}

/* Remove um item do conjunto.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_del (struct set_t *s, int item)
{
    // Testa se a estrutura é nula.
    if (!s)
        return (0);
    
    if (item >= s-> size)
        return (0);

    if (s-> flag[item])
    {
        s-> flag[item] = false;
        s-> num--;
    }
    return (1);
}

/* Verifica se o item pertence (está no) conjunto.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_in (struct set_t *s, int item)
{
    // Testa se a estrutura é nula.
    if (!s)
        return (0);
    
    if (!s-> flag[item])
        return (0);
    return (1);
}

/* Verifica se o conjunto está vazio.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_empty (struct set_t *s)
{
    // Testa se a estrutura é nula.
    if (!s)
        return (0); 

    if (s-> num != 0)
        return (0);
    return (1);
}

/* Informa a cardinalidade do conjunto (número de itens).
 * Retorna: n >=0 em caso de sucesso ou -1 em caso de falha.*/
int set_card (struct set_t *s)
{
    // Testa se a estrutura é nula.
    if (!s)
        return (-1); 
    return (s-> num); // Retorna o número de elementos no conjunto.
}

/* Verifica se s1 contém s2.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_contains (struct set_t *s1, struct set_t *s2)
{
    int maior;

    // Testa se alguma das estruturas é nula.
    if (!s1 || !s2)
        return (0); 

    // Determina o maior conjunto para fazer a iteração que verifica, caso os conjuntos tenham tamanhos diferentes.
    if (s1-> size > s2-> size)
        maior = s1-> size;
    else
        maior = s2-> size;


    // Verifica se s1 contém s2.
    for (int i = 0; i < maior; i++)
    {
        if (s2-> flag[i] && !s1-> flag[i]) 
            return (0); 
    }
    return (1); 
}

/* Verifica se s1 == s2
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_equal (struct set_t *s1, struct set_t *s2)
{
    int maior;

    // Testa se alguma das estruturas é nula.
    if (!s1 || !s2)
        return 0; 

   // Determina o maior conjunto para fazer a iteração que verifica, caso os conjuntos tenham tamanhos diferentes.
    if (s1-> size > s2-> size)
        maior = s1-> size;
    else
        maior = s2-> size;   

    // Verifica se ambos os conjuntos contêm os mesmos elementos.
    for (int i = 0; i < maior; i++)
    {
        if (s1-> flag[i] != s2-> flag[i])
            return (0); 
    }
    return (1); 
}

/* Coloca em s3 a união dos conjuntos s1 e s2; conteúdo anterior de s3
 * é limpo, mas seu intervalo (0, max) não é modificado.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_union (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    int maior;

    // Testa se alguma das estruturas é nula.
    if (!s1 || !s2 || !s3)
        return (0); 

    // Determina o maior conjunto para fazer a iteração que verifica, caso os conjuntos tenham tamanhos diferentes.
    if (s1-> size > s2-> size)
        maior = s1-> size;
    else
        maior = s2-> size;

    // Realiza a operação de união dos conjuntos.
    for (int i = 0; i < maior; i++)
        s3-> flag[i] = s1-> flag[i] || s2-> flag[i];
    

    // Atualiza a cardinalidade de s3.
    s3-> num = 0;
    for (int i = 0; i < s3-> size; i++)
    {
        if (s3-> flag[i]) 
            s3-> num++;
    }
    return (1); 
}

/* Coloca em s3 a intersecção dos conjuntos s1 e s2; conteúdo anterior de s3
 * é limpo, mas seu intervalo (0, max) não é modificado.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_intersect (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    int maior;

    // Testa se alguma das estruturas é nula.
    if (!s1 || !s2 || !s3)
        return (0);

    // Determina o maior conjunto para fazer a iteração que verifica, caso os conjuntos tenham tamanhos diferentes.
    if (s1-> size > s2-> size)
        maior = s1-> size;
    else
        maior = s2-> size; 

    // Realiza a operação de intersecção dos conjuntos.
    for (int i = 0; i < maior; i++) 
        s3-> flag[i] = s1-> flag[i] && s2-> flag[i];
    

    // Atualiza a cardinalidade de s3.
    s3-> num = 0;
    for (int i = 0; i < s3-> size; i++)
    {
        if (s3-> flag[i]) 
            s3-> num++;
    }
    return (1); 
}

/* Coloca em s3 a diferença s1 - s2; o conteúdo anterior de s3 é apagado,
 * mas seu intervalo (0, max) não é modificado.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_diff (struct set_t *s1, struct set_t *s2, struct set_t *s3)
{
    int maior;

    // Verifica se alguma das estruturas é nula.
    if (!s1 || !s2 || !s3)
        return (0); 

    // Determina o maior conjunto para fazer a iteração que verifica, caso os conjuntos tenham tamanhos diferentes.
    if (s1-> size > s2-> size)
        maior = s1-> size;
    else
        maior = s2-> size;   
    
    
    // Realiza a operação de diferença.
    for (int i = 0; i < maior; i++) 
        s3-> flag[i] = s1-> flag[i] && !s2-> flag[i];

    
    // Atualiza a cardinalidade de s3.
    s3-> num = 0;
    for (int i = 0; i < s3-> size; i++)
    {
        if (s3-> flag[i]) 
            s3-> num++;
    }
    return (1); 
}

/* Coloca em s2 uma cópia do conjunto s1; o conteúdo anterior de s2 é apagado,
 * mas seu intervalo (0, max) não é modificado.
 * Retorna: 1 se sucesso ou 0 se falha.*/
int set_copy (struct set_t *s1, struct set_t *s2)
{
    // Verifica se alguma das estruturas é nula.
    if (!s1 || !s2) 
        return (0); 
    
    // Copia o conteúdo de s1 para s2.
    for (int i = 0; i < s1-> size; i++) 
        s2-> flag[i] = s1-> flag[i];
    
    // Atualiza a cardinalidade de s2.
    s2->num = s1->num;

    return (1); 
}

// Imprime o conteúdo de um conjunto usando este modelo as especificações.
void set_print (struct set_t *s)
{
    int i;

    if (!s)
        return;

    printf("[ ");
    for (i = 0; i < s-> size; i++)
    {
        if (s-> flag[i]) 
            printf("%d ", i);  
    }
    printf ("]\n");
   // printf("] (%d items)\n", s-> num); 
}