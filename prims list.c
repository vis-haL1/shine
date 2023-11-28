#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

#define V 6

struct Node {
    int dest;
    int weight;
    struct Node* next;
};

struct List {
    struct Node* head;
};

struct Graph {
    struct List* array;
};

struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->array = (struct List*)malloc(V * sizeof(struct List));

    for (int i = 0; i < V; i++) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(struct Graph* graph, int source, int destination, int weight) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = destination;
    newNode->weight = weight;
    newNode->next = graph->array[source].head;
    graph->array[source].head = newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = source;
    newNode->weight = weight;
    newNode->next = graph->array[destination].head;
    graph->array[destination].head = newNode;
}

int getMinimumVertex(bool mst[], int key[]) {
    int minKey = INT_MAX;
    int vertex = -1;
    for (int i = 0; i < V; i++) {
        if (!mst[i] && minKey > key[i]) {
            minKey = key[i];
            vertex = i;
        }
    }
    return vertex;
}

void primMST(struct Graph* graph) {
    bool mst[V];
    int key[V];

    for (int i = 0; i < V; i++) {
        mst[i] = false;
        key[i] = INT_MAX;
    }

    key[0] = 0;

    for (int i = 0; i < V - 1; i++) {
        int vertex = getMinimumVertex(mst, key);
        mst[vertex] = true;

        struct Node* currentNode = graph->array[vertex].head;
        while (currentNode != NULL) {
            if (!mst[currentNode->dest] && currentNode->weight < key[currentNode->dest]) {
                key[currentNode->dest] = currentNode->weight;
            }
            currentNode = currentNode->next;
        }
    }

    int total_min_weight = 0;
    printf("Minimum Spanning Tree:\n");
    for (int i = 1; i < V; i++) {
        printf("Edge: %d - %d key: %d\n", i, i, key[i]);
        total_min_weight += key[i];
    }
    printf("Total minimum key: %d\n", total_min_weight);
}

int main() {
    struct Graph* graph = createGraph();

    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
        printf("Enter edge %d source, destination, and weight: ", i + 1);
        scanf("%d%d%d", &source, &destination, &weight);
        addEdge(graph, source, destination, weight);
    }

    primMST(graph);

    return 0;
}

