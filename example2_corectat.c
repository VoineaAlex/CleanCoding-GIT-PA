
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int vertices;
    int *visited;
    NODE **adjacency_lists;
} GRAPH;

// === UTILS ===

NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GRAPH *create_graph(int vertices) {
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(NODE *));
    graph->visited = malloc(vertices * sizeof(int));
    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

void add_edge(GRAPH *graph, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void insert_edges(GRAPH *graph, int num_edges) {
    int src, dest;
    printf("Introduceți %d muchii (de la 0 la %d):\n", num_edges, graph->vertices - 1);
    for (int i = 0; i < num_edges; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

void reset_visited(GRAPH *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// === BFS ===

typedef struct Queue {
    NODE *front;
    NODE *rear;
} QUEUE;

int is_empty_queue(QUEUE *queue) {
    return queue->front == NULL;
}

void enqueue(QUEUE *queue, int value) {
    NODE *new_node = create_node(value);
    if (queue->rear == NULL) {
        queue->front = queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

int dequeue(QUEUE *queue) {
    if (is_empty_queue(queue)) return -1;
    NODE *temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL) queue->rear = NULL;
    free(temp);
    return data;
}

// === PARCURGERI ===

void DFS(GRAPH *graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    NODE *temp = graph->adjacency_lists[vertex];
    while (temp != NULL) {
        int connected = temp->data;
        if (!graph->visited[connected]) {
            DFS(graph, connected);
        }
        temp = temp->next;
    }
}

void BFS(GRAPH *graph, int start_vertex) {
    QUEUE queue = {NULL, NULL};
    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty_queue(&queue)) {
        int current = dequeue(&queue);
        printf("%d ", current);

        NODE *temp = graph->adjacency_lists[current];
        while (temp != NULL) {
            int adj_vertex = temp->data;
            if (!graph->visited[adj_vertex]) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

// === MAIN ===

int main() {
    int num_vertices, num_edges;
    printf("Număr noduri: ");
    scanf("%d", &num_vertices);
    printf("Număr muchii: ");
    scanf("%d", &num_edges);

    GRAPH *graph = create_graph(num_vertices);
    insert_edges(graph, num_edges);

    int start;
    printf("Nod start pentru DFS: ");
    scanf("%d", &start);
    printf("DFS: ");
    DFS(graph, start);

    reset_visited(graph);
    printf("\nNod start pentru BFS: ");
    scanf("%d", &start);
    printf("BFS: ");
    BFS(graph, start);

    printf("\n");

    return 0;
}
