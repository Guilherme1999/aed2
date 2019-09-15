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

int** CriaGrafo(Grafo grafo, int numVertices) {
    int i, j;
    grafo.matAdj = (int **) malloc (numVertices * sizeof(int*));
    for(i = 0; i < numVertices; i++) {
        grafo.matAdj[i] = (int*) malloc (numVertices * sizeof(int));
        for( j = 0; j < numVertices; j++) {
            grafo.matAdj[i][j] = 0;
        }
    }
    return grafo.matAdj;
}

bool Arestas(Grafo grafo) {
    int numArestas, i, peso;
    char origem, dest;
    printf("\nNumero de arestas: ");
    scanf("%d",&numArestas);
    for(i = 0; i < numArestas; i++) {
        printf("\nvertice de origem(%c - %c): ",OFFSET, OFFSET + grafo.vertices - 1);
        scanf(" %c",&origem);
        printf("vertice de destino(%c - %c): ",OFFSET, OFFSET + grafo.vertices - 1);
        scanf(" %c",&dest);
        printf("Peso: ");
        scanf("%d",&peso);
        if(peso < 0) {
            return false;
        }
        grafo.matAdj[origem - OFFSET][dest - OFFSET] = peso;
    }
    return true;
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
    if(passo == dest) { 
        printf("\n\nmenor caminho entre '%c' e '%c': %d", OFFSET + origem, OFFSET + dest, custo[passo]);
        printf("\ncaminho tomado: ");
        auxiliar = dest;
        while(auxiliar >= 0) {
            printf(" %d",auxiliar);
            auxiliar = predecessor[auxiliar];
        }
    }
    else {
        printf("/nNao existe um caminho entre '%c' e '%c'", OFFSET + origem, OFFSET + dest);
    }
}

int main() {
    Grafo g;
    int vertices;
    char inicio, fim;
    printf("\nnumero de vertices do grafo: ");
    scanf(" %d",&vertices);
    g.vertices = vertices;
    g.matAdj = CriaGrafo(g,vertices);
    if(!Arestas(g)) {
        printf("\n\nERRO! Aresta com peso negativo.");
        return 0;
    }
    printf("\nvertice inicial: ");
    scanf(" %c",&inicio);
    printf("vertice final: ");
    scanf(" %c",&fim);
    CaminhoMinimo(g, inicio - OFFSET,fim - OFFSET);
    return 0;
}
