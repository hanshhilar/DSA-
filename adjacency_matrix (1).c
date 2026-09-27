/* ============================================================
   PCCST303 - Data Structures and Algorithms - Assignment 2, Q11
   Social Network Graph using ADJACENCY MATRIX
   Vertices : A B C D E F  (indices 0 1 2 3 4 5)
   Edges    : A-B, A-C, B-D, B-E, C-F, E-F
   ============================================================ */
#include <stdio.h>

#define V 6

char labels[V] = {'A','B','C','D','E','F'};
int adjMatrix[V][V];

int indexOf(char v){
    for(int i=0;i<V;i++) if(labels[i]==v) return i;
    return -1;
}

void addEdge(char u, char v){
    int i = indexOf(u), j = indexOf(v);
    adjMatrix[i][j] = 1;
    adjMatrix[j][i] = 1;  /* undirected */
}

void printMatrix(){
    printf("\n--- Adjacency Matrix ---\n   ");
    for(int i=0;i<V;i++) printf("%c  ", labels[i]);
    printf("\n");
    for(int i=0;i<V;i++){
        printf("%c  ", labels[i]);
        for(int j=0;j<V;j++) printf("%d  ", adjMatrix[i][j]);
        printf("\n");
    }
}

/* ---------------- BFS ---------------- */
void bfs(char start){
    int visited[V] = {0};
    int queue[V], front=0, rear=0;
    int s = indexOf(start);

    printf("\n--- BFS (Adjacency Matrix) starting at %c ---\n", start);
    printf("Order visited: ");

    queue[rear++] = s;
    visited[s] = 1;

    while(front < rear){
        int u = queue[front++];
        printf("%c ", labels[u]);
        for(int v=0; v<V; v++){          /* scan the row -> O(V) per vertex */
            if(adjMatrix[u][v]==1 && !visited[v]){
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }
    printf("\n");
}

/* ---------------- DFS ---------------- */
int visitedDFS[V];
void dfsUtil(int u){
    visitedDFS[u] = 1;
    printf("%c ", labels[u]);
    for(int v=0; v<V; v++){              /* scan the row -> O(V) per vertex */
        if(adjMatrix[u][v]==1 && !visitedDFS[v]){
            dfsUtil(v);
        }
    }
}
void dfs(char start){
    for(int i=0;i<V;i++) visitedDFS[i]=0;
    printf("\n--- DFS (Adjacency Matrix) starting at %c ---\n", start);
    printf("Order visited: ");
    dfsUtil(indexOf(start));
    printf("\n");
}

/* --------- Search: does edge (u,v) exist? --------- */
void searchEdge(char u, char v){
    int i = indexOf(u), j = indexOf(v);
    int ops = 1; /* one direct array access */
    printf("\nSearch edge %c-%c using MATRIX : ", u, v);
    if(adjMatrix[i][j]==1)
        printf("FOUND   (operations = %d)\n", ops);
    else
        printf("NOT FOUND (operations = %d)\n", ops);
}

int main(){
    addEdge('A','B');
    addEdge('A','C');
    addEdge('B','D');
    addEdge('B','E');
    addEdge('C','F');
    addEdge('E','F');

    printMatrix();
    bfs('A');
    dfs('A');

    printf("\n=== Edge search tests (Adjacency Matrix) ===\n");
    searchEdge('A','C');   /* exists  */
    searchEdge('B','E');   /* exists  */
    searchEdge('A','F');   /* does not exist */
    searchEdge('D','F');   /* does not exist */

    return 0;
}
