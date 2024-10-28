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

void BFS(struct Node* adj[], int V, int start) {
    int visited[V], distance[V];
    for (int i = 0; i < V; i++) {
        visited[i] = 0;
        distance[i] = -1;
    }

    int queue[V], front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;
    distance[start] = 0;

    printf("BFS Traversal Order: ");
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        struct Node* temp = adj[current];
        while (temp != NULL) {
            int neighbor = temp->data;
            if (!visited[neighbor]) {
                queue[rear++] = neighbor;
                visited[neighbor] = 1;
                distance[neighbor] = distance[current] + 1;
            }
            temp = temp->next;
        }
    }
    printf("\n");

    printf("Shortest Distance from Source (%d):\n", start);
    for (int i = 0; i < V; i++) {
        printf("Vertex %d: %d\n", i, distance[i]);
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
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);

    printf("Adjacency List:\n");
    displayAdjList(adj, V);

    int start = 0;
    printf("\n");
    BFS(adj, V, start);

    return 0;
}
