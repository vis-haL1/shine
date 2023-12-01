#include <stdio.h>
#include <stdbool.h>
#define INF 9999
#define V 5

void primMST(int graph[V][V]) {
    int parent[V];
    int key[V];
    bool inMST[V];

    for (int i = 0; i < V; ++i) {
        key[i] = INF;
        inMST[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count) {
        int u, minKey = INF;
        for (int v = 0; v < V; ++v) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        inMST[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !inMST[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("Edge \tWeight\n");
    for (int i = 1; i < V; ++i) {
        printf("%d - %d \t%d\n", parent[i], i, key[i]);
    }
}

int main() {
    int graph[V][V];

    printf("Enter the adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph);

    return 0;
}

/* input: 
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0
    */
