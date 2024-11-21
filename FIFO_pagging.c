#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct pagetable{
    int frame_no;
    bool present;
}PageTable;

void printFrame(int m, int frame[m]){
    for(int i = 0; i < m; i++){
        printf("%d\t", frame[i]);
    }
    printf("\n");
}

bool isPagePresent(PageTable pt[50], int k){
    return pt[k].present;
}

void updateTable(PageTable pt[50], int k, int fn, bool status){
    if(k == -1) return;
    pt[k].frame_no = fn;
    pt[k].present = status;
}

int main(){
    printf("Enter the number of Frames available : ");
    int m;  // num of frames
    scanf("%d", &m);
    int frame[m];
    memset(frame, -1, sizeof(frame));
    printf("Enter the number of Queries : ");
    int n;  // num of pages in query
    scanf("%d", &n);
    printf("Enter the Queries : ");
    int query[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &query[i]);
    }
    PageTable pt[50];
    int j = 0;
    int pageFault = 0;
    printf("QUERY\t|\tFRAME CONTENT\n");
    for(int i = 0; i < n; i++){
        printf("%d\t|\t", query[i]);
        if(!isPagePresent(pt, query[i])){
            ++pageFault;
            updateTable(pt, frame[j], j, false);
            frame[j] = query[i];
            j = (j+1)%m;
            updateTable(pt, query[i], j, true);
        }
        printFrame(m, frame);
    }
    printf("Page Fault \t: %d\n", pageFault);
    printf("Page Fault Ratio : %.2f\nPage Hit Ratio \t: %.2f\n", (float)pageFault/n, (float)(n-pageFault)/n);
}