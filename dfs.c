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

void addEdge(struct Node* adj[], int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = createNode(u);
    newNode->next = adj[v];
    adj[v] = newNode;
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

void DFSUtil(struct Node* adj[], int v, int visited[], int parent, int* time, int finishTime[], int* hasCycle) {
    visited[v] = 1;
    (*time)++;
    printf("%d ", v);

    struct Node* temp = adj[v];
    while (temp != NULL) {
        if (!visited[temp->data]) {
            DFSUtil(adj, temp->data, visited, v, time, finishTime, hasCycle);
        } else if (temp->data != parent) {
            *hasCycle = 1;
        }
        temp = temp->next;
    }

    finishTime[v] = ++(*time);
}

void DFS(struct Node* adj[], int V) {
    int visited[V], finishTime[V];
    int time = 0, hasCycle = 0;

    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        finishTime[i] = 0;
    }

    printf("DFS Traversal Order: ");
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            DFSUtil(adj, i, visited, -1, &time, finishTime, &hasCycle);
        }
    }
    printf("\n");

    if (hasCycle) {
        printf("The graph contains a cycle.\n");
    } else {
        printf("The graph does not contain a cycle.\n");
    }

    printf("Finishing Times:\n");
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: %d\n", i, finishTime[i]);
    }
}

int main() {
    int V = 5;
    struct Node* adj[V];
    for (int i = 0; i < V; i++) {
        adj[i] = NULL;
    }

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 3, 4);

    printf("Adjacency List:\n");
    displayAdjList(adj, V);

    printf("\n");
    DFS(adj, V);

    return 0;
}
