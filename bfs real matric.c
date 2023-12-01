#include <stdio.h>
#include <stdbool.h>
#define MAX_VERTICES 20

int graph[MAX_VERTICES][MAX_VERTICES];
bool visited[MAX_VERTICES];
int queue[MAX_VERTICES];
int front = -1, rear = -1;

void initializeGraph(int vertices) {
    for (int i = 0; i < vertices; ++i) {
        visited[i] = false;
        for (int j = 0; j < vertices; ++j) {
            graph[i][j] = 0;
        }
    }
}

void addEdge(int source, int destination) {
    graph[source][destination] = 1;
    graph[destination][source] = 1; // For undirected graph
}

void displayAdjacencyMatrix(int vertices) {
    printf("\nAdjacency Matrix Representation:\n");
    for (int i = 0; i < vertices; ++i) {
        for (int j = 0; j < vertices; ++j) {
            printf("%d ", graph[i][j]);
        }
        printf("\n");
    }
}

void bfs(int vertex, int vertices) {
    visited[vertex] = true;
    queue[++rear] = vertex;

    while (front <= rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (int i = 0; i < vertices; ++i) {
            if (graph[current][i] && !visited[i]) {
                visited[i] = true;
                queue[++rear] = i;
            }
        }
    }
}

void dfs(int vertex, int vertices) {
    visited[vertex] = true;
    printf("%d ", vertex);

    for (int i = 0; i < vertices; ++i) {
        if (graph[vertex][i] && !visited[i]) {
            dfs(i, vertices);
        }
    }
}

int main() {
    int vertices, edges, source, destination;

    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    initializeGraph(vertices);

    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < edges; ++i) {
        scanf("%d %d", &source, &destination);
        addEdge(source, destination);
    }

    displayAdjacencyMatrix(vertices);

    printf("\nBFS Traversal starting from vertex 0: ");
    bfs(0, vertices);

    // Reset visited array for DFS
    for (int i = 0; i < vertices; ++i) {
        visited[i] = false;
    }

    printf("\nDFS Traversal starting from vertex 0: ");
    dfs(0, vertices);

    return 0;
}

/*INPUT v-5 E-6
    0 1
0 2
1 3
1 4
2 4
3 4
    */
    
