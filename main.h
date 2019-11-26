// =================== HEADER FILE ======================= //

int min(int a, int b);
struct Queue *create_queue(int capacity);
int isFull(struct Queue *q);
int isEmpty(struct Queue *q);
void enqueue(struct Queue *q, int data);
int dequeue(struct Queue *q);
struct graph *create_graph(int n);
void add_edge(struct graph *g, int i, int j, int c);
void display_graph(struct graph *g);
int bfs(struct graph *res_graph, int s, int t, int *path);
int fordFulkerson(struct graph *g, int s, int t);