// =================== UTILITY FUNCTION FILE ======================= //
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "main.h"

////////////////////////// Structures /////////////////////////////////////

struct Queue
{
    int front;
    int rear;
    int *arr;
    int capacity;
};

struct graph_node
{
    int capacity;
    int j; // second_vertex
    struct graph_node *link;
};

struct graph
{
    int n; // n: number of vertices
    struct graph_node **arr;
};

int min(int a, int b)
{
    if (a < b)
    {
        return a;
    }

    else
    {
        return b;
    }
}

////////////////////////// Queue Operations /////////////////////////////////////

struct Queue *create_queue(int capacity)
{
    struct Queue *q = (struct Queue *)malloc(sizeof(struct Queue));
    q->capacity = capacity;
    q->front = -1;
    q->rear = -1;
    q->arr = (int *)malloc(sizeof(int) * q->capacity);
    return q;
}

int isFull(struct Queue *q)
{
    return q->rear == q->capacity;
}

int isEmpty(struct Queue *q)
{
    return ((q->front == q->rear + 1) || (q->front == -1 && q->rear == -1));
}

void enqueue(struct Queue *q, int data)
{
    if (!isFull(q))
    {
        q->rear += 1;
        if (q->front == -1 && q->rear == 0)
        {
            q->front = 0;
        }
        q->arr[q->rear] = data;
    }

    else
    {
        return;
    }
}

int dequeue(struct Queue *q)
{
    if (!isEmpty(q))
    {
        int item = q->arr[q->front];
        q->front += 1;
        return item;
    }

    else
    {
        return -9999; // code ERROR
    }
}

////////////////////////// Graph Operations /////////////////////////////////////

struct graph *create_graph(int n)
{
    struct graph *g = (struct graph *)malloc(sizeof(struct graph));
    g->n = n;
    g->arr = (struct graph_node **)calloc(sizeof(struct graph_node *), n);
    return g;
}

void add_edge(struct graph *g, int i, int j, int c)
{
    struct graph_node *node = (struct graph_node *)malloc(sizeof(struct graph_node));
    node->j = j;
    node->capacity = c;
    node->link = g->arr[i];
    g->arr[i] = node;
}

void display_graph(struct graph *g)
{
    for (int i = 0; i < g->n; i++)
    {
        struct graph_node *temp = g->arr[i];
        while (temp != NULL)
        {
            printf("%d-->", temp->capacity);
            temp = temp->link;
        }
        printf("\n");
    }
}

int bfs(struct graph *res_graph, int s, int t, int *path)
{
    int *visited = (int *)calloc(sizeof(int), res_graph->n); // we still have to create this
    struct Queue *q = create_queue(res_graph->n);
    struct graph_node *p;
    enqueue(q, s);
    visited[s] = 1;
    path[s] = -1; // just storing a random val

    while (!isEmpty(q))
    {
        int dsrc = dequeue(q);
        for (p = res_graph->arr[dsrc]; p != NULL; p = p->link)
        {
            if (visited[p->j] == 0 && p->capacity > 0)
            {
                enqueue(q, p->j);
                path[p->j] = dsrc;
                visited[p->j] = 1;
            }
        }
    }

    // for(int i = 0 ; i<res_graph->n ; i++)
    // {
    //     printf("%d",path[i]);
    // }

    if (visited[t] == 1)
    {
        return 1;
    }

    else
    {
        return 0;
    }
}

int fordFulkerson(struct graph *g, int s, int t)
{
    int u, v;

    struct graph *res_graph = create_graph(g->n);
    struct graph_node *p;
    for (int i = 0; i < g->n; i++)
    {
        for (p = g->arr[i]; p != NULL; p = p->link)
        {
            add_edge(res_graph, i, p->j, p->capacity);
            add_edge(res_graph, p->j, i, 0);
        }
    }

    int path[g->n];
    int max_flow = 0;
    while (bfs(res_graph, s, t, path))
    {

        int bottle_neck = INT_MAX;
        for (v = t; v != s; v = path[v])
        {
            u = path[v];
            struct graph_node *p;
            int capacity;
            for (p = res_graph->arr[u]; p != NULL; p = p->link)
            {
                if (p->j == v)
                {
                    capacity = p->capacity;
                }
            }
            bottle_neck = min(bottle_neck, capacity);
        }

        // printf("Bottle Neck : %d\n", bottle_neck);  // Printing the Bottle Neck Value

        for (v = t; v != s; v = path[v])
        {
            u = path[v];
            for (p = res_graph->arr[u]; p != NULL; p = p->link)
            {
                if (p->j == v)
                {
                    p->capacity -= bottle_neck;
                }
            }

            for (p = res_graph->arr[v]; p != NULL; p = p->link)
            {
                if (p->j == u)
                {
                    p->capacity += bottle_neck;
                }
            }
        }

        max_flow += bottle_neck;
    }

    return max_flow;
}