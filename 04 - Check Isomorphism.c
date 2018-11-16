#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int vert;
    struct node* next;
}node;

int n1, m1, n2, m2;

void push(node** head, int v){
    node* newnode = (node*)malloc(sizeof(node));
    newnode->vert = v;
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
        if(head->vert==v)
            return 1;
    }
    return 0;
}

int check_iso(node* adjlst1[], node* adjlst2[], int map[]) {
    for(int i=0;i<n1;i++){
        for(node* p=adjlst1[i]; p; p=p->next){
            if(!checkmember(adjlst2[map[i]], map[p->vert]))
                return 0;
        }
    }
    return 1;
}

int gen_all_maps(node* adjlst1[], node* adjlst2[], int map[], int vert=0) {
    if(vert==n1)
        return check_iso(adjlst1, adjlst2, map);
    for(int i=0; i<n1; i++){
        int prev_v = map[vert], prev_i=map[i];
        map[vert] = map[i];
        map[i] = prev_v;
        if(gen_all_maps(adjlst1, adjlst2, map, vert+1)){
            return 1;
        }
        map[vert] = prev_v;
        map[i]=prev_i;
    }
    return 0;
}

int main(int argc, char const *argv[]) {
    scanf("%d %d\n", &n1, &m1);
    node* adjlst1[n1];
    int map[n1], rev_map[n1];
    for(int i=0; i<n1; i++){
        adjlst1[i]=NULL;
        map[i]=rev_map[i]=i;
    }
    for(int i=0; i<m1; i++){
        int a, b;
        scanf("%d %d\n", &a, &b);
        push(&(adjlst1[a]), b);
    }
    scanf("%d %d\n", &n2, &m2);
    node* adjlst2[n2];
    for(int i=0; i<n2; i++){
        adjlst2[i]=NULL;
    }
    for(int i=0; i<m2; i++){
        int a, b;
        scanf("%d %d\n", &a, &b);
        push(&(adjlst2[a]), b);
    }
    if(n1!=n2||m1!=m2||!gen_all_maps(adjlst1, adjlst2, map)){
        printf("No\n");
        return 0;
    }
    else{
        printf("Yes\n");
    }
}
