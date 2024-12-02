#include<stdio.h>
#include<stdbool.h>
#include<string.h>

typedef struct pagetable{
    int frame_no;
    int last_access;
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

void updateTable(PageTable pt[50], int k, int fn, int access, bool status){
    pt[k].present = status;
    if(status == true){
        pt[k].frame_no = fn;
        pt[k].last_access = access;
    }
}

int getLRUpage(PageTable pt[50], int m, int frame[m]){
    int mini = 1e9;
    int idx = -1;
    for(int i = 0; i < m; i++){
        if(pt[frame[i]].last_access < mini){
            mini = pt[frame[i]].last_access;
            idx = i;
        }
    }
    return idx;
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
            if(j < m){
                frame[j] = query[i];
                updateTable(pt, query[i], j, i, true);
                j++;
            }else{
                int idx = getLRUpage(pt, m, frame);
                updateTable(pt, frame[idx], -1, i, false);
                frame[idx] = query[i];
                updateTable(pt, query[i], idx, i, true);
            }

        }
        printFrame(m, frame);
        pt[query[i]].last_access = i;
    }
    printf("Page Fault \t: %d\n", pageFault);
    printf("Page Fault Ratio : %.2f\nPage Hit Ratio \t: %.2f\n", (float)pageFault/n, (float)(n-pageFault)/n);
}