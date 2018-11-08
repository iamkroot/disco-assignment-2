#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    struct node* left;
    struct node* right;
}node;
int n, max_bits;

node* new_leaf() {
    node* newnode = (node*)malloc(sizeof(node));
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

void update_max_bits(int a){
    int bits=0;
    while(a){
        bits++;
        a/=2;
    }
    if(max_bits<bits)
        max_bits = bits;
}

void add_to_trie(node* root, int num) {
    for(int i=max_bits-1; i>=0; i--){
        int mask = num&(1<<i);
        if(mask){
            if(!root->right)
                root->right = new_leaf();
            root=root->right;
        }
        else{
            if(!root->left)
                root->left = new_leaf();
            root=root->left;
        }
    }
}
int get_max_xor(int a, node* root) {
    int p=0;
    for(int i=max_bits-1; i>=0; i--){
        int mask = a&(1<<i);
        p*=2;
        if(mask){
            if(root->left){
                root=root->left;
            }
            else if(root->right){
                p++;
                root=root->right;
            }
        }
        else{
            if(root->right){
                p++;
                root=root->right;
            }
            else if(root->left){
                root=root->left;
            }
        }
    }
    return p^a;
}

int main(int argc, char const *argv[]) {
    scanf("%d\n", &n);
    int arr[n];
    for(int i=0; i<n; i++){
        scanf("%d\n", &arr[i]);
        update_max_bits(arr[i]);
    }
    node* root=new_leaf();
    int t;
    scanf("%d\n", &t);
    int tarr[t];
    for(int i=0; i<t; i++){
        scanf("%d\n", &tarr[i]);
        update_max_bits(tarr[i]);
    }
    for(int i=0; i<n; i++){
        add_to_trie(root, arr[i]);
    }
    for(int i=0;i<t;i++){
        printf("%d\n", get_max_xor(tarr[i], root));
    }
}
