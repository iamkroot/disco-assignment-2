#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int vert;
    int cost;
    struct node* next;
}node;
int n, m;

void push(node** head, int v, int cost){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->vert = v;
    newnode->cost = cost;
    newnode->next = NULL;
    if(*head == NULL){
        *head = newnode;
        return;
    }
    node* t = *head;
    *head = newnode;
    newnode->next=t;
}

node* pop(node** head){
    if(!(*head))
        return NULL;
    node* t = *head;
    *head=t->next;
    return t;
}

node *cur_path, *min_path;
int min_cost=-1, cost=0, cur_path_len=0;

void get_min_cost(node* adjlst[], int visited[], int vert=0, int prev_vert=-1) {
    visited[vert] = 1;
    for(node* p = adjlst[vert];p;p=p->next){
        if(!visited[p->vert]||(p->vert==0 && cur_path_len==n-1)){
            cost+=p->cost;
            push(&cur_path, p->vert, p->cost);
            cur_path_len++;
            get_min_cost(adjlst, visited, p->vert, vert);
            if((p->vert==0 && cur_path_len==n)&&(cost<min_cost || min_cost == -1)){
                min_path = cur_path;
                min_cost = cost;
            }
            cur_path_len--;
            pop(&cur_path);
            cost-=p->cost;
            visited[p->vert] = 0;
        }
    }
}

int main(int argc, char const *argv[]) {
    scanf("%d %d\n", &n, &m);
    node* adjlst[n];
    int visited[n];
    for(int i=0; i<n; i++){
        adjlst[i] = NULL;
        visited[i] = 0;
    }
    for(int i=0; i<m; i++){
        int a, b, c;
        scanf("%d %d %d\n", &a, &b, &c);
        push(&(adjlst[a]), b, c);
        push(&(adjlst[b]), a, c);
    }
    get_min_cost(adjlst, visited);
    for(node*p = min_path; p;p=p->next){
        printf("%c=>", p->vert+65);
    }
    printf("A\n%d\n", min_cost);
}
