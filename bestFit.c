#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void firstFit(int n, int m, int process[n], int block[m], int ans[n]){
    for(int i = 0; i < n; i++){
        int mini = 1e9, idx = -1;
        for(int j = 0; j < m; j++){
            if(block[j] >= process[i]){
                if(block[j] < mini){
                    mini = block[j];
                    idx = j;
                }
            }
        }
        if(idx != -1){
            block[idx] -= process[i];
            ans[i] = idx+1;
        }
    }
}

int main(){
    int n, m;
    printf("Enter n(no. of processes) and m(no. of blocks) : ");
    scanf("%d %d", &n, &m);
    int process[n];
    int block[m];
    printf("Enter the block size of each block : ");
    for(int i = 0; i < m; i++){
        scanf("%d", &block[i]);
    }
    printf("Enter the process size of each process : ");
    for(int i = 0; i < n; i++){
        scanf("%d", &process[i]);
    }
    int ans[n];
    memset(ans, -1, sizeof(ans));
    firstFit(n, m, process, block, ans);
    printf("Process no.\tProcess Size\tBlock allocated\n");
    for(int i = 0; i < n; i++){
        printf("%d\t\t%d\t\t", i+1, process[i]);
        if(ans[i] == -1)    printf("Not Possible\n");
        else    printf("%d\n", ans[i]);
    }
}