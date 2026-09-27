/* ============================================================
   PCCST303 - Data Structures and Algorithms - Assignment 2, Q11
   Social Network Graph using ADJACENCY LIST
   Vertices : A B C D E F  (indices 0 1 2 3 4 5)
   Edges    : A-B, A-C, B-D, B-E, C-F, E-F
   ============================================================ */
#include <stdio.h>
#include <stdlib.h>

#define V 6
char labels[V] = {'A','B','C','D','E','F'};

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[V] = {NULL};

int indexOf(char v){
    for(int i=0;i<V;i++) if(labels[i]==v) return i;
    return -1;
}

Node* newNode(int v){
    Node* n = (Node*)malloc(sizeof(Node));
    n->vertex = v;
    n->next = NULL;
    return n;
}

/* insert at end so the list order matches the order edges were entered */
void insertEnd(int src, int dest){
    Node* n = newNode(dest);
    if(adjList[src]==NULL){ adjList[src]=n; return; }
    Node* t = adjList[src];
    while(t->next) t = t->next;
    t->next = n;
}

void addEdge(char u, char v){
    int i = indexOf(u), j = indexOf(v);
    insertEnd(i,j);
    insertEnd(j,i);   /* undirected */
}

void printList(){
    printf("\n--- Adjacency List ---\n");
    for(int i=0;i<V;i++){
        printf("%c -> ", labels[i]);
        Node* t = adjList[i];
        while(t){
            printf("%c ", labels[t->vertex]);
            t = t->next;
        }
        printf("\n");
    }
}

/* ---------------- BFS ---------------- */
void bfs(char start){
    int visited[V] = {0};
    int queue[V], front=0, rear=0;
    int s = indexOf(start);

    printf("\n--- BFS (Adjacency List) starting at %c ---\n", start);
    printf("Order visited: ");

    queue[rear++] = s;
    visited[s] = 1;

    while(front < rear){
        int u = queue[front++];
        printf("%c ", labels[u]);
        Node* t = adjList[u];          /* only visits actual neighbours -> O(deg) */
        while(t){
            if(!visited[t->vertex]){
                visited[t->vertex] = 1;
                queue[rear++] = t->vertex;
            }
            t = t->next;
        }
    }
    printf("\n");
}

/* ---------------- DFS ---------------- */
int visitedDFS[V];
void dfsUtil(int u){
    visitedDFS[u] = 1;
    printf("%c ", labels[u]);
    Node* t = adjList[u];
    while(t){
        if(!visitedDFS[t->vertex]) dfsUtil(t->vertex);
        t = t->next;
    }
}
void dfs(char start){
    for(int i=0;i<V;i++) visitedDFS[i]=0;
    printf("\n--- DFS (Adjacency List) starting at %c ---\n", start);
    printf("Order visited: ");
    dfsUtil(indexOf(start));
    printf("\n");
}

/* --------- Search: does edge (u,v) exist? --------- */
void searchEdge(char u, char v){
    int i = indexOf(u), j = indexOf(v);
    int ops = 0;
    Node* t = adjList[i];
    int found = 0;
    while(t){
        ops++;                     /* one comparison per node visited */
        if(t->vertex == j){ found = 1; break; }
        t = t->next;
    }
    printf("\nSearch edge %c-%c using LIST   : ", u, v);
    if(found) printf("FOUND   (operations = %d)\n", ops);
    else      printf("NOT FOUND (operations = %d)\n", ops);
}

int main(){
    addEdge('A','B');
    addEdge('A','C');
    addEdge('B','D');
    addEdge('B','E');
    addEdge('C','F');
    addEdge('E','F');

    printList();
    bfs('A');
    dfs('A');

    printf("\n=== Edge search tests (Adjacency List) ===\n");
    searchEdge('A','C');   /* exists  */
    searchEdge('B','E');   /* exists  */
    searchEdge('A','F');   /* does not exist */
    searchEdge('D','F');   /* does not exist */

    return 0;
}
