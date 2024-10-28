#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void displayAdjList(struct Node* adj[], int V) {
    for (int i = 0; i < V; i++) {
        printf("%d: ", i);
        struct Node* temp = adj[i];
        while (temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
}

int isComplete(struct Node* adj[], int V) {
    for (int i = 0; i < V; i++) {
        int count = 0;
        struct Node* temp = adj[i];
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
        if (count != V - 1) {
            return 0;
        }
    }
    return 1;
}

int getDegree(struct Node* adj[], int u) {
    int degree = 0;
    struct Node* temp = adj[u];
    while (temp != NULL) {
        degree++;
        temp = temp->next;
    }
    return degree;
}

int getInDegree(struct Node* adj[], int V, int u) {
    int inDegree = 0;
    for (int i = 0; i < V; i++) {
        struct Node* temp = adj[i];
        while (temp != NULL) {
            if (temp->data == u) {
                inDegree++;
            }
            temp = temp->next;
        }
    }
    return inDegree;
}

int getOutDegree(struct Node* adj[], int u) {
    return getDegree(adj, u);
}

int hasPath(struct Node* adj[], int start, int end, int visited[], int V) {
    if (start == end) return 1;
    visited[start] = 1;
    struct Node* temp = adj[start];
    while (temp != NULL) {
        if (!visited[temp->data]) {
            if (hasPath(adj, temp->data, end, visited, V)) {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

int main() {
    int V = 5;
    struct Node* undirectedGraph[V];
    struct Node* directedGraph[V];
    for (int i = 0; i < V; i++) {
        undirectedGraph[i] = NULL;
        directedGraph[i] = NULL;
    }

    undirectedGraph[0] = createNode(1);
    undirectedGraph[0]->next = createNode(2);
    undirectedGraph[1] = createNode(0);
    undirectedGraph[1]->next = createNode(3);
    undirectedGraph[2] = createNode(0);
    undirectedGraph[3] = createNode(1);
    undirectedGraph[3]->next = createNode(4);
    undirectedGraph[4] = createNode(3);

    directedGraph[0] = createNode(1);
    directedGraph[0]->next = createNode(2);
    directedGraph[1] = createNode(3);
    directedGraph[2] = createNode(3);
    directedGraph[3] = createNode(4);

    printf("Undirected Graph Adjacency List:\n");
    displayAdjList(undirectedGraph, V);

    printf("\nDirected Graph Adjacency List:\n");
    displayAdjList(directedGraph, V);

    int u = 3;
    printf("\nDegree of node %d in undirected graph: %d\n", u, getDegree(undirectedGraph, u));
    printf("Outdegree of node %d in directed graph: %d\n", u, getOutDegree(directedGraph, u));
    printf("Indegree of node %d in directed graph: %d\n", u, getInDegree(directedGraph, V, u));

    int start = 0, end = 4;
    int visited[V];
    for (int i = 0; i < V; i++) visited[i] = 0;
    if (hasPath(undirectedGraph, start, end, visited, V)) {
        printf("\nThere is a path between %d and %d in the undirected graph\n", start, end);
    } else {
        printf("\nThere is no path between %d and %d in the undirected graph\n", start, end);
    }

    return 0;
}
