#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int numVertices;
    struct Node** adjList;
    bool* visited;
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (bool*)malloc(vertices * sizeof(bool));

    for (int i = 0; i < vertices; ++i) {
        graph->adjList[i] = NULL;
        graph->visited[i] = false;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void displayAdjacencyList(struct Graph* graph) {
    printf("\nAdjacency List Representation:\n");
    for (int i = 0; i < graph->numVertices; ++i) {
        struct Node* temp = graph->adjList[i];
        printf("Vertex %d: ", i);
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void bfs(struct Graph* graph, int startVertex) {
    struct Node* queue[graph->numVertices];
    int front = 0, rear = 0;

    graph->visited[startVertex] = true;
    queue[rear++] = graph->adjList[startVertex];

    printf("BFS Traversal starting from vertex %d: ", startVertex);

    while (front < rear) {
        struct Node* currentNode = queue[front++];
        printf("%d ", currentNode->vertex);

        while (currentNode != NULL) {
            int adjVertex = currentNode->vertex;
            if (!graph->visited[adjVertex]) {
                graph->visited[adjVertex] = true;
                queue[rear++] = graph->adjList[adjVertex];
            }
            currentNode = currentNode->next;
        }
    }
    printf("\n");
}

void dfsUtil(struct Graph* graph, int vertex) {
    graph->visited[vertex] = true;
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp != NULL) {
        int adjVertex = temp->vertex;
        if (!graph->visited[adjVertex]) {
            dfsUtil(graph, adjVertex);
        }
        temp = temp->next;
    }
}

void dfs(struct Graph* graph, int startVertex) {
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    dfsUtil(graph, startVertex);
    printf("\n");
}

int main() {
    int numVertices, numEdges;
    int src, dest;

    printf("Enter the number of vertices: ");
    scanf("%d", &numVertices);
    printf("Enter the number of edges: ");
    scanf("%d", &numEdges);

    struct Graph* graph = createGraph(numVertices);

    printf("Enter edges (source destination):\n");
    for (int i = 0; i < numEdges; ++i) {
        scanf("%d %d", &src, &dest);
        addEdge(graph, src, dest);
    }

    displayAdjacencyList(graph);

    int startVertex;
    printf("\nEnter the starting vertex for BFS and DFS traversal: ");
    scanf("%d", &startVertex);

    bfs(graph, startVertex);

    for (int i = 0; i < numVertices; ++i) {
        graph->visited[i] = false;
    }
    dfs(graph, startVertex);

    return 0;
}
