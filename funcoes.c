#include "funcoes.h"
#include "set.h"


// Criar valores aleatórios.
int aleat (int min, int max)
{
    int num;

    num = min + (rand() % (1 + max - min));

    return (num);
}


/* Calcula a distância cartesiana entre a base atual do herói e
 * a base destino. */
long calcula_distancia (Mundo *mundo, int h, int b)
{
    int         base_atual; 
    long        distancia, x, y;
    Coordenadas local, local_dest;
    
    // Verifica se ponteiros não são nulos.
    if (mundo == NULL || mundo->heroi == NULL || mundo->base == NULL) 
        return (-1);

    // Verifica se os índices são válidos.
    if (h < 0 || h >= mundo->n_herois || b < 0 || b >= mundo->n_bases)
        return (-1);
        
    base_atual = mundo->heroi[h].base;
    local      = mundo->base[base_atual].local;
    local_dest = mundo->base[b].local;

    x = (local_dest.x - local.x) * (local_dest.x - local.x);
    y = (local_dest.y - local.y) * (local_dest.y - local.y);

    // A distância é calculada pelo teorema de pitágoras (raíz quad. de Δx² + Δy²)
    distancia = sqrt(x + y);

    return (distancia);
}

//Calcula duração da viagem.
long duracao_viagem (Mundo *mundo, int h, int b)
{
    long duracao;

    // Verifica se ponteiros não são nulos.
    if (mundo == NULL || mundo->heroi == NULL)
        return (-1);

    /* Verifica se a velocidade do herói não é zero ou negativa, 
     * para evitar divisões por zero. */
    if (mundo->heroi[h].velocidade <= 0)
        return (-1);

    duracao = (calcula_distancia (mundo, h, b) / mundo->heroi[h].velocidade);

    return (duracao);

}
long calcula_distancia_missao(Mundo *mundo, int m, int b)
{
    long        distancia, x, y;
    Coordenadas local, local_dest;
    
    // Verifica se ponteiros não são nulos.
    if (mundo == NULL || mundo->heroi == NULL || mundo->base == NULL)
        return (-1);

    // Verifica se os índices são válidos.
    if (m < 0 || m >= mundo->n_missoes || b < 0 || b >= mundo->n_bases)
        return (-1);

    local      = mundo->base[b].local;
    local_dest = mundo->missao[m].local;

    x = (local_dest.x - local.x) * (local_dest.x - local.x);
    y = (local_dest.y - local.y) * (local_dest.y - local.y);

    // A distância é calculada pelo teorema de pitágoras (raíz quad. de Δx² + Δy²)
    distancia = sqrt(x + y);

    return (distancia);
}
 
// Função para criar a matriz com as bases e suas distâncias.
void cria_matriz (Mundo *mundo, int m, int matriz[][2])
{
    int i;
    long distancia;

    for (i = 0; i < mundo->n_bases; i++)
    {
        distancia    = calcula_distancia_missao (mundo, m, i);
        matriz[i][0] = i;
        matriz[i][1] = distancia;
    }                   
}

// Função para ordenar a matriz com base nas distâncias
void ordena_matriz (Mundo *mundo, int matriz[][2])
{
    int i, j;
    int temp_base, temp_distancia;

    for (i = 0; i < mundo->n_bases; i++)
    {
        for (j = 0; j < mundo->n_bases - i - 1; j++)
        {
            if (matriz[j][1] > matriz[j+1][1])
            {
                // Troca as bases com suas correspondentes distâncias.
                temp_distancia   = matriz[j][1];
                temp_base        = matriz[j][0];
                matriz[j][1]     = matriz[j + 1][1];
                matriz[j][0]     = matriz[j + 1][0];
                matriz[j + 1][1] = temp_distancia;
                matriz[j + 1][0] = temp_base;
            }
        }
    }
}

// Função para imprimir a matriz
void imprimirMatriz(Mundo *mundo, int matriz[][2]) 
{
    int i;

    for (i = 0; i < mundo->n_bases; i++) 
    {
        printf("Base %d: %d\n", matriz[i][0], matriz[i][1]);
    }
}


