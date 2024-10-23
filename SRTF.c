#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct process_struct{
    int id, arrival, burst, rem_burst, start, comp, waiting, tat, response;
}process;

void printProcesses(int n, process ps[]){
    printf("\nID\tAT\tBT\tST\tCT\tWT\tTAT\tRT\n");
    printf("---------------------------------------------------------\n");
    for(int i = 0; i < n; i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].id, ps[i].arrival, ps[i].burst, ps[i].start, ps[i].comp, ps[i].waiting, ps[i].tat, ps[i].response);
    printf("\n");
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
        ps[i].start = -1;
        ps[i].comp = 0;
        ps[i].waiting = 0;
        ps[i].tat = 0;
        ps[i].response = 0;
    }
    int time = 0, idle_time = 0, tat = 0, response = 0, wait = 0;
    int completed_[n];
    memset(completed_, 0, sizeof(completed_));

    printf("Gantt's Chart : ");

    int completed = 0;
    while(completed != n){
        int pid = -1;
        int mini = 1e8;
        for(int i = 0; i < n; i++){
            if(ps[i].arrival <= time && completed_[i] == 0){
                if(ps[i].rem_burst < mini){
                    mini = ps[i].rem_burst;
                    pid = i;
                }else if(ps[i].rem_burst == mini){
                    if(ps[i].arrival < ps[pid].arrival){
                        pid = i;
                    }
                }
            }
        }
        if(pid == -1){
            printf("## ");
            idle_time++;
            time++;
        }else{
            printf("P%d ", ps[pid].id);
            if(ps[pid].start == -1){
                ps[pid].start = time;
            }
            ps[pid].rem_burst -= 1;
            time += 1;
            if(ps[pid].rem_burst <= 0){    
                completed++;
                completed_[pid] = 1;
                ps[pid].comp = time;
                ps[pid].response = (ps[pid].start - ps[pid].arrival);
                ps[pid].tat = (ps[pid].comp - ps[pid].arrival);
                ps[pid].waiting = (ps[pid].tat - ps[pid].burst);
                tat += ps[pid].tat;
                wait += ps[pid].waiting;
                response += ps[pid].response;
            }
        }

    }

    printProcesses(n, ps);
    printf("AVG TAT\t\t: %.2f\t\t AVG WAITING\t: %.2f\n", (float)tat/n, (float)wait/n);
    printf("AVG RESPONSE\t: %.2f\t\t IDLE TIME\t: %.2f\n", (float)response/n, (float)idle_time);
    printf("THROUGHPUT\t: %.2f\t\t CPU UTILIZATION: %.2f%%\n", (float)n/time, (float)(time-idle_time)*100/time);

    return 0;
}