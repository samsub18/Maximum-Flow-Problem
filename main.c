// =================== DRIVER PROGRAM FILE ======================= //

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include "main.h"


int main()
{
    int n = 6;
    struct graph* graph = create_graph(n);

// =====Example1===========
    // add_edge(graph,0,1,16);
    // add_edge(graph,0,2,13);
    // add_edge(graph,1,3,12);
    // add_edge(graph,3,5,20);
    // add_edge(graph,3,2,9);
    // add_edge(graph,2,4,14);
    // add_edge(graph,2,1,4);
    // add_edge(graph,1,2,10);
    // add_edge(graph,4,5,4);
    // add_edge(graph,4,3,7);
// ========================

// =====Example2===========
    add_edge(graph,0,1,10);
    add_edge(graph,0,3,10);
    add_edge(graph,3,4,15);
    add_edge(graph,4,5,10);
    add_edge(graph,2,5,10);
    add_edge(graph,1,2,25);
    add_edge(graph,4,1,6);
// =========================

    display_graph(graph);


    printf("Max flow : %d",fordFulkerson(graph,0,5));
    return 0;
}




