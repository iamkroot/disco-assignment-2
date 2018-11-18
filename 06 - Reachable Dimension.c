#include <stdio.h>
#include <stdlib.h>

int reachable(int n, int m, int z){
    // printf("%d %d %d\n",n,m,z );
    if(n==m)
        return 1;
    if(z<1)
        return 0;
    return reachable(10*n+1, m, z-1) || reachable(n*2, m, z-1);
}

int main(int argc, char const *argv[]) {
    int n, m, z;
    scanf("%d %d %d\n", &n, &m, &z);
    printf("%d\n", reachable(n, m, z));
}
