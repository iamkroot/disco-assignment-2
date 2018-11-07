#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int v1, v2, cost;
    struct Edge* next;
}Edge;
int n, m;

void insert_sorted(Edge** head, int v1, int v2, int cost){
    Edge* newedge = (Edge*)malloc(sizeof(Edge));
    newedge->v1 = v1;
    newedge->v2 = v2;
    newedge->cost = cost;
    newedge->next = NULL;
    if(*head == NULL){
        *head = newedge;
        return;
    }
    Edge* p = *head;
    Edge* pp=NULL;
    while (p->cost < cost) {
        pp = p;
        if(!p->next)
            break;
        p = p->next;
    }
    if(pp)
        pp->next = newedge;
    else
        *head = newedge;
    if(pp!=p)
        newedge->next = p;
}


int check_cycle(Edge* newedge, int root[]) {
    int r1 = root[newedge->v1], r2 = root[newedge->v2];
    if (r1!=r2){  // no cycle will be created
        int m = r1<r2?r1:r2, M = r1>r2?r1:r2;
        for(int i=0; i<n; i++)
            if(root[i]==M)
                root[i]=m;
        return 0;
    }
    return 1;
}


int main(int argc, char const *argv[]) {
    scanf("%d\n", &n);
    scanf("%d", &m);
    int root[n];
    for(int i=0;i<n;i++){
        root[i]=i;
    }
    Edge* edges=NULL;
    for(int i=0; i<m; i++){
        int a, b, c;
        scanf("%d %d %d\n", &a, &b, &c);
        insert_sorted(&edges, a, b, c);
    }
    Edge* mst[n-1], *p = edges;
    int i=0, cost=0;
    while(p && i<n-1) {
        if(!check_cycle(p, root)) {
            mst[i++] = p;
            cost += p->cost;
        }
        p=p->next;
    }
    printf("%d\n", cost);
    return 0;
}
