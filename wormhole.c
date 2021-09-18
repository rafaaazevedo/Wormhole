#include <stdio.h>
#include <stdlib.h>

struct grafo{
    int V; //número de vértices
    int A; //número de arestas
    int **adj; //ponteiro para uma matriz de adjacência
};
typedef struct grafo *Grafo; // qualquer objeto do tipo Grafo tem um endereço da estrutura grafo

Grafo iniciaGrafo(int V);
int **iniciaMatriz(int r, int c, int valor);
void insereAresta(Grafo G, int w, int z, int aresta);
void imprimeMatriz(Grafo G);
int BellmanFord(Grafo G, int V, int fonte);

int main(){
    int conjuntos,n,m,i,j,x,y,t,origem,possibilidade;
    Grafo g;

    printf("Digite o número de conjuntos: \n");
    scanf("%d",&conjuntos);
    for(i=1; i<=conjuntos; i++){
        printf("@Informe o número de galáxias:@ \n");
        do{
            scanf("%d",&n);
        }while(n<1 || n>1000);
        printf("<==Informe o número de buracos de minhoca:== \n");
        do{
            scanf("%d",&m);
        }while(m<1 || m>2000);
        g=iniciaGrafo(n);
        imprimeMatriz(g);
        for(j=1; j<=m; j++){
            printf("Entrada do buraco de minhoca possiveis na matriz: \n");
            do{
                scanf("%d",&x);
            }while(x<0 || x>(n-1));
            if(j==1) // o primeiro vértice lido coloquei como origem
            {
                origem= x;
            }
            
            printf("Saída do buraco de minhoca possiveis na matriz: \n");
            do{
                scanf("%d",&y);
            }while(y<0 || y>(n-1)); // erro
            
            printf("Tempo de viagem: \n");
            do{
                scanf("%d",&t);
            }while(t < -1000 || t > 1000); // (-1000<=t<=1000)
            
            insereAresta(g,x,y,t);
        }
        imprimeMatriz(g);
        possibilidade=BellmanFord(g,n,origem);
        if(possibilidade==1)
        {
            printf("possivel\n");
        }
        else
        {
            printf("impossivel\n");
        }
    }
    return 0;
}

Grafo iniciaGrafo(int V){
    Grafo G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = iniciaMatriz(V, V, 0); //chama iniciaMAtriz para criar uma matriz
    return G;
}

int **iniciaMatriz(int r, int c, int valor){
    int k,l; //contadores
    int **m = malloc(r * sizeof(int *)); //aloca memória para a linha
    for(k=0; k<r; k++){
        m[k] = malloc(c * sizeof(int)); //aloca memória para a coluna
    }
    for(k=0; k<r; k++){
        for(l=0; l<c; l++){
            m[k][l]=valor; // coloca o valor zero na matriz
        }
    }
    return m;
}

void insereAresta(Grafo G, int w, int z, int aresta){
    if(w!=z && G->adj[w][z]==0)
    {
        G->adj[w][z]=aresta;
        G->A++;
    }
}

void imprimeMatriz(Grafo G){
    int k,l;
    for(k=0; k < G->V; k++){
        for(l=0; l < G->V; l++){
            printf("Posição [%d][%d] = %d\n",k,l,G->adj[k][l]);
        }
    }
}

int BellmanFord(Grafo G, int V, int fonte){
    int *distancia, i, j, u, v;
    
    distancia = malloc (V * sizeof(int));
    printf("Vetor Distancia Inicializado\n");
    for(i=0; i<V; i++){
        if(i==fonte)
        {
            distancia[i]= 0;
        }
        else
        {
            distancia[i]= 88888;//infinito
        }
    }
    
    for(i=0; i<V; i++){
        printf("%d ",distancia[i]);
    }
    printf("\n");
    
    for(i=0; i<V; i++){
        for(j=0; j<V; j++){
            if(G->adj[i][j] != 0)
            {
                u= distancia[i];
                v= distancia[j];
                if(v > u + G->adj[i][j])
                {
                    v= u + G->adj[i][j];
                    distancia[j]=v;
                }
            }
        }
    }
    printf("Vetor distancia com o grafo percorrido\n");
    for(i=0; i<V; i++){
        printf("%d ",distancia[i]);
    }
    printf("\n");
    if(distancia[V-1] < 0)
    {
        return 0;//ciclo negativo
    }
    else
    {
        return 1;//sem ciclo negativo no destino
    }
}

