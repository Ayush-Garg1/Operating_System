#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define min(a, b)   a < b ? a : b;

struct process_struct{
    int id, arrival, burst, rem_burst, start_time, comp_time, waiting_time, tat, response_time;
};
typedef struct process_struct process;

void printProcesses(int n, process ps[]){
    printf("\nID\tAT\tBT\tST\tCT\tWT\tTAT\tRT\n");
    printf("---------------------------------------------------------\n");
    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].id, ps[i].arrival, ps[i].burst, ps[i].start_time, ps[i].comp_time, ps[i].waiting_time, ps[i].tat, ps[i].response_time);
    }
    printf("\n");
}

void sort(int n, process ps[]){
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n-i-1; j++){
            if(ps[j].arrival > ps[j+1].arrival){
                process temp = ps[j];
                ps[j] = ps[j+1];
                ps[j+1] = temp;
            }
        }
    }
}

void push(int el, int q[], int *f, int *r){
    if(*r == 10000) return;
    q[++(*r)] = el;
    if(*f == -1){
        (*f)++;
    }
}

int pop(int q[], int *f){
    int temp = q[*f];
    (*f) = (*f)+1;
    return temp;
}

int main(){
    printf("Name\t: AYUSH GARG\nSection\t: A1\nRoll no.: 20\n\n");

    int n, quanta;
    printf("Enter the number of process : ");
    scanf("%d", &n);
    process ps[n];

    printf("Enter process arrival and burst time\n");
    for(int i = 0; i < n; i++){
        printf("P%d : ", i+1);
        ps[i].id = i+1;
        scanf("%d %d", &ps[i].arrival, &ps[i].burst);
        ps[i].rem_burst = ps[i].burst;
        ps[i].comp_time = 0;
        ps[i].start_time = 0;
        ps[i].response_time = 0;
        ps[i].tat = 0;
        ps[i].waiting_time = 0;
    }

    printf("Enter quanta : ");
    scanf("%d", &quanta);

    int ready_queue[10000], front = -1, rear = -1, curr = 0, time = 0, completed = 0, idle_time = 0;
    memset(ready_queue, 0, sizeof(ready_queue));
    sort(n, ps);
    printf("Gantt's Chart : ");

    if(ps[0].arrival != 0){
        idle_time += ps[0].arrival;
        printf("## ");
        time = ps[0].arrival;
    }

    push(0, ready_queue, &front, &rear);

    int vis[n], last = 0, tat = 0, waiting = 0, response = 0;;
    memset(vis, 0, sizeof(vis));
    vis[0] = 1;

    bool started[n];
    memset(started, false, sizeof(started));
    started[0] = true;

    while(completed != n){
        int pid = pop(ready_queue, &front);
        if(pid == -1){
            printf("## ");
            idle_time += (ps[last+1].arrival - time);
            time = ps[last+1].arrival;
            pid = last+1;
        }
        if(started[pid] == false){
            ps[pid].start_time = time;
            started[pid] = true;
        }
        printf("P%d ", ps[pid].id);
        time += min(quanta, ps[pid].rem_burst);
        ps[pid].rem_burst -= quanta;
        last = pid;

        for(int i = pid+1; i < n; i++){
            if(ps[i].arrival <= time && vis[i] == 0){
                push(i, ready_queue, &front, &rear);
                vis[i] = 1;
            }
        }
        if(ps[pid].rem_burst <= 0){
            ps[pid].comp_time = time;
            completed++;
            ps[pid].response_time = ps[pid].start_time - ps[pid].arrival;
            ps[pid].tat = ps[pid].comp_time - ps[pid].arrival;
            ps[pid].waiting_time = ps[pid].tat - ps[pid].burst;
            response += ps[pid].response_time;
            waiting += ps[pid].waiting_time;
            tat += ps[pid].tat;
        }
        else    push(pid, ready_queue, &front, &rear);
        if(front > rear)    push(-1, ready_queue, &front, &rear);
        
    }

    printProcesses(n, ps);
    printf("\nAVG TAT\t\t: %.2f\t AVG Waiting Time\t: %.2f\n", (float)tat/n, (float)waiting/n);
    printf("Throughput\t: %.2f\t AVG Response Time\t: %.2f\n", (float)n/time, (float)response/n);
    printf("CPU Utilization : %.2f%%\n", (float)(time-idle_time)*100/time);
    return 0;
}