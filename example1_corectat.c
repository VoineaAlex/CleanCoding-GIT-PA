
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct Graph {
    int v;
    int *visited;
    NODE **adjacency_list;
} GRAPH;

typedef struct Stack {
    int top;
    int capacity;
    int *array;
} STACK;

// ========== Stack Functions ==========
STACK *create_stack(int capacity) {
    STACK *stack = malloc(sizeof(STACK));
    stack->top = -1;
    stack->capacity = capacity;
    stack->array = malloc(capacity * sizeof(int));
    return stack;
}

void push(STACK *stack, int value) {
    stack->top++;
    stack->array[stack->top] = value;
}

// ========== Graph Functions ==========
NODE *create_node(int v) {
    NODE *new_node = malloc(sizeof(NODE));
    new_node->data = v;
    new_node->next = NULL;
    return new_node;
}

GRAPH *create_graph(int v) {
    GRAPH *graph = malloc(sizeof(GRAPH));
    graph->v = v;
    graph->visited = calloc(v, sizeof(int));
    graph->adjacency_list = malloc(v * sizeof(NODE *));
    for (int i = 0; i < v; i++) {
        graph->adjacency_list[i] = NULL;
    }
    return graph;
}

void add_edge(GRAPH *g, int src, int dest) {
    NODE *new_node = create_node(dest);
    new_node->next = g->adjacency_list[src];
    g->adjacency_list[src] = new_node;

    new_node = create_node(src);
    new_node->next = g->adjacency_list[dest];
    g->adjacency_list[dest] = new_node;
}

void DFS(GRAPH *g, STACK *s, int vertex) {
    g->visited[vertex] = 1;
    printf("%d ", vertex);
    push(s, vertex);

    NODE *temp = g->adjacency_list[vertex];
    while (temp != NULL) {
        int connected = temp->data;
        if (g->visited[connected] == 0) {
            DFS(g, s, connected);
        }
        temp = temp->next;
    }
}

void reset_visited(GRAPH *g) {
    for (int i = 0; i < g->v; i++) {
        g->visited[i] = 0;
    }
}

void insert_edges(GRAPH *g, int edge_count) {
    int src, dest;
    printf("Introduceți %d muchii (nodurile pornesc de la 0):\n", edge_count);
    for (int i = 0; i < edge_count; i++) {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

int main() {
    int vertices, edges;
    printf("Câte noduri are graful? ");
    scanf("%d", &vertices);
    printf("Câte muchii are graful? ");
    scanf("%d", &edges);

    GRAPH *graph = create_graph(vertices);
    STACK *stack = create_stack(2 * vertices);

    insert_edges(graph, edges);

    printf("DFS începând de la nodul 0:\n");
    DFS(graph, stack, 0);

    free(graph->visited);
    free(graph->adjacency_list);
    free(graph);
    free(stack->array);
    free(stack);
    return 0;
}
