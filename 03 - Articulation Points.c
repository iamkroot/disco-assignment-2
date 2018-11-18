#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* next;
}node;
int n, m;

void append(node** head, int v){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->data = v;
    newnode->next = NULL;
    if(*head == NULL){
        *head = newnode;
        return;
    }
    node* t = *head;
    *head = newnode;
    newnode->next=t;
}


int checkmember(node* head, int v) {
    for(;head;head=head->next){
        if(head->data==v)
            return 1;
    }
    return 0;
}

int time = 1;
node* critical;

void find_critical_nodes(node* adjlst[], int disc[], int visited[], int low[], int parent[], int v=0) {
    visited[v] = 1;
    disc[v] = low[v] = time++;
    int child_count = 0;
    for(node* connected_node = adjlst[v];connected_node;connected_node = connected_node->next){
        int i = connected_node->data;
        if(!visited[i]){
            child_count++;
            parent[i] = v;
            find_critical_nodes(adjlst, disc, visited, low, parent, i);
            low[v] = low[i]<low[v]?low[i]:low[v];
            if((parent[v]==-1 && child_count>1)||(parent[v]!=-1 && low[i]>=disc[v])&&!checkmember(critical, v)){
                append(&critical, v);
            }
        }
        else if(parent[v] != i) {
            low[v] = ((low[v]==-1)||(disc[i]<=low[v]))?disc[i]:low[v];
        }
    }
}

int main(int argc, char const *argv[]) {
    scanf("%d %d\n", &n, &m);
    node* adjlst[n];
    int disc[n], visited[n], low[n], parent[n];
    for(int i=0; i<n; i++){
        disc[i] = visited[i] = 0;
        low[i] = parent[i] = -1;
        adjlst[i] = NULL;
    }
    for(int i=0; i<m; i++){
        int a, b;
        scanf("%d %d\n", &a, &b);
        append(&(adjlst[a]), b);
        append(&(adjlst[b]), a);
    }
    find_critical_nodes(adjlst, disc, visited, low, parent, 0);
    int num_undiscovered_nodes = 0, first_node;
    for(int i=0; i<n; i++){
        if(low[i]<0){
            num_undiscovered_nodes++;
            first_node = i;
        }
    }
    if(num_undiscovered_nodes==1){
        critical = NULL;
        for(int i=0; i<n; i++){
            if(i!=first_node){
                append(&critical, i);
            }
        }
    }
    else if(num_undiscovered_nodes>1){
        critical = NULL;
        for(int i=0; i<n; i++){
            append(&critical, i);
        }
    }
    if(!critical){
        printf("No critical point.\n");
        return 0;
    }
    while(critical){
        printf("%d ", critical->data);
        critical = critical->next;
    }
}
