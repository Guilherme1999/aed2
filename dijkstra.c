#include <stdio.h>
#include <stdlib.h>

#define OFFSET 97
#define bool int
#define true 1
#define false 0

typedef struct grafo {
    int vertices;
    int** matAdj;
}Grafo;

Grafo CriaGrafo(Grafo grafo);
void Arestas(Grafo grafo);
void PrintaGrafo(Grafo grafo);
void DeletaGrafo(Grafo grafo);
void CaminhoMinimo(Grafo grafo, int origem, int dest);

int main() {
    Grafo g;
    char inicio, fim;
    g = CriaGrafo(g);
    Arestas(g);
    printf("\nVertice inicial: ");
    scanf(" %c",&inicio);
    printf("Vertice final: ");
    scanf(" %c",&fim);
    CaminhoMinimo(g, inicio - OFFSET,fim - OFFSET);
    DeletaGrafo(g);
    return 0;
}

Grafo CriaGrafo(Grafo grafo) {
    int i, j,vertices;
    printf("\nNumero de vertices do grafo: ");
    scanf(" %d",&vertices);
    grafo.vertices = vertices;
    if(vertices > 20) {
        printf("\nERRO! Limite de 20 vertices.");
        printf("\nDigite o numero de vertices novamente:");
        scanf(" %d",&vertices);
        if(vertices > 20) {
            exit(-1);
        }
    }
    grafo.matAdj = (int **) malloc (vertices * sizeof(int*));
    for(i = 0; i < vertices; i++) {
        grafo.matAdj[i] = (int*) malloc (vertices * sizeof(int));
        for( j = 0; j < vertices; j++) {
            grafo.matAdj[i][j] = 0;
        }
    }
    return grafo;
}

void Arestas(Grafo grafo) {
    int numArestas, i, peso;
    char origem, dest;
    printf("\nNumero de arestas: ");
    scanf("%d",&numArestas);
    printf("\n--Definindo arestas--\n");
    for(i = 0; i < numArestas; i++) {
        printf("\nVertice de origem (letras entre '%c' e '%c'): ",OFFSET, OFFSET + grafo.vertices - 1);
        scanf(" %c",&origem);
        printf("Vertice de destino (letras entre '%c' e '%c'): ",OFFSET, OFFSET + grafo.vertices - 1);
        scanf(" %c",&dest);
        printf("Peso: ");
        scanf("%d",&peso);
        if(peso < 0) {
            printf("\nERRO! Aresta com peso negativo.");
            printf("\nDigite o peso novamente.");
                printf("\nPeso: ");
                scanf("%d",&peso);
                if(peso < 0) {
                    DeletaGrafo(grafo);
                    exit(-1);
                }
        }
        grafo.matAdj[origem - OFFSET][dest - OFFSET] = peso;
    }
}

void PrintaGrafo(Grafo grafo) {
    printf("\n Grafo montando com matriz de adjacencias: ");
    printf("\n\n  ");
    for(int i = 0; i < grafo.vertices; i++) {
        printf("%c\t",i + OFFSET);
    }
    printf("\n");
    for(int i = 0; i < grafo.vertices; i++) {
        printf("%c ",i + OFFSET);
        for(int j = 0; j < grafo.vertices; j++) {
            printf("%d\t",grafo.matAdj[i][j]);
        }
        printf("\n");
    }
}

void DeletaGrafo(Grafo grafo) {
    for(int i = 0; i < grafo.vertices; i++) {
        free(grafo.matAdj[i]);
    }
    free(grafo.matAdj);
}

void CaminhoMinimo(Grafo grafo, int origem, int dest) {
    int i, passo, novaDist, min, auxiliar;
    int *predecessor, *custo;
    bool *fechado;

    predecessor = (int*) malloc (grafo.vertices * sizeof(int));
    custo = (int*) malloc (grafo.vertices * sizeof(int));
    fechado = (bool*) malloc (grafo.vertices * sizeof(bool));
    for(i = 0; i < grafo.vertices; i++) {
        fechado[i] = false;
        custo[i] = 900000;
        predecessor[i] = -1; 
    }
    passo = origem;
    custo[passo] = 0;
    while( passo != dest && passo != -1) {
        for(i = 0; i < grafo.vertices; i++) {
            if(grafo.matAdj[passo][i] != 0 && fechado[i] == false) {
                novaDist = custo[passo] + grafo.matAdj[passo][i];
                if(novaDist < custo[i]) {
                    custo[i] = novaDist;
                    predecessor[i] = passo;
                }
            }
        }
        fechado[passo] = true;
        min = 900000;
        passo = -1;
        for(i = 0; i < grafo.vertices; i++) {
            if(fechado[i] == false && custo[i] < min) {
                min = custo[i];
                passo = i;
            }
        }
    }
    PrintaGrafo(grafo);
    if(passo == dest) { 
        printf("\nMenor caminho entre '%c' e '%c': %d", OFFSET + origem, OFFSET + dest, custo[passo]);
        printf("\nCaminho do destino a origem: ");
        auxiliar = dest;
        while(auxiliar >= 0) {
            printf(" '%c'",auxiliar + OFFSET);
            auxiliar = predecessor[auxiliar];
        }
    }
    else {
        printf("\nNao existe um caminho entre '%c' e '%c'", OFFSET + origem, OFFSET + dest);
    }
    free(predecessor);
    free(custo);
    free(fechado);
}

