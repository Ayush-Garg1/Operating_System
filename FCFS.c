#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

typedef struct process_struct{
    int id, arrival, burst, rem_burst, start, comp, response, waiting, tat;
}process;

void printProcesses(int n, process ps[]){
    printf("\nID\tAT\tBT\tST\tCT\tWT\tTAT\tRT\n");
    printf("---------------------------------------------------------\n");
    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].id, ps[i].arrival, ps[i].burst, ps[i].start, ps[i].comp, ps[i].waiting, ps[i].tat, ps[i].response);
    }
    printf("\n");
}

int cmp(const void* a, const void* b){
    int x = ((process*)a)->arrival;
    int y = ((process*)b)->arrival;
    if(x >= y)  return 1;
    else    return -1;
}

int main(){
    printf("Name\t: AYUSH GARG\nSection\t: A1\nRoll no.: 20\n\n");

    int n;
    printf("Enter the number of processess : ");
    scanf("%d", &n);

    process ps[n];
    for(int i = 0; i < n; i++){
        ps[i].id = i+1;
        scanf("%d %d", &ps[i].arrival, &ps[i].burst);
        ps[i].rem_burst = ps[i].burst;
        ps[i].start = 0;
        ps[i].comp = 0;
        ps[i].response = 0;
        ps[i].waiting = 0;
        ps[i].tat = 0;
    }
    int completed = 0, time = 0, tat = 0, wait = 0, response = 0, idle_time = 0;
    qsort((void*)ps, n, sizeof(process), cmp);
    printf("Gantt's Chart : ");
    if(ps[0].arrival != 0){
        printf("## ");
        idle_time += ps[0].arrival;
        time = ps[0].arrival;
    }

    for(int i = 0; i < n; i++){
        if(ps[i].arrival > time){
            printf("## ");
            idle_time += ps[i].arrival - time;
            time = ps[i].arrival;
        }
        printf("P%d ", ps[i].id);
        ps[i].start = time;
        time += ps[i].burst;
        ps[i].comp = time;
        ps[i].response = (ps[i].start - ps[i].arrival), ps[i].tat = (ps[i].comp - ps[i].arrival);
        ps[i].waiting = (ps[i].tat - ps[i].burst);
        tat += ps[i].tat;
        wait += ps[i].waiting;
        response += ps[i].response;
    }
    printProcesses(n, ps);
    printf("AVG TAT\t\t: %.2f\t\t AVG WAITING\t: %.2f\n", (float)tat/n, (float)wait/n);
    printf("AVG RESPONSE\t: %.2f\t\t IDLE TIME\t: %.2f\n", (float)response/n, (float)idle_time);
    printf("THROUGHPUT\t: %.2f\t\t CPU UTILIZATION: %.2f\n", (float)n/time, (float)(time-idle_time)/time);

    return 0;
}