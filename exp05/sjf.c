#include <stdio.h>

typedef struct {
    int id;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int completed;
} Process;

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    Process processes[n];
    
    // Input process details
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Arrival time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].at);
        printf("Burst time for Process P%d: ", i + 1);
        scanf("%d", &processes[i].bt);
        processes[i].completed = 0;
    }

    int time = 0, completed_processes = 0;
    float sum_tat = 0, sum_wt = 0;

    printf("\nGantt Chart:\n");
    printf("Time | Process\n");

    while (completed_processes < n) {
        int smallest = -1;
        
        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].at <= time) {
                if (smallest == -1 || processes[i].bt < processes[smallest].bt) {
                    smallest = i;
                }
            }
        }
        
        if (smallest == -1) {
            // If no process is available to run, increment time
            time++;
            continue;
        }

        // Process execution
        printf("%-4d | P%d\n", time, processes[smallest].id);
        time += processes[smallest].bt;
        processes[smallest].ct = time;
        processes[smallest].tat = processes[smallest].ct - processes[smallest].at;
        processes[smallest].wt = processes[smallest].tat - processes[smallest].bt;
        processes[smallest].completed = 1;
        completed_processes++;

        sum_tat += processes[smallest].tat;
        sum_wt += processes[smallest].wt;
    }

  
    printf("\nProcess Table:\n");
    printf("PId\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].id, processes[i].at, processes[i].bt,
               processes[i].ct, processes[i].tat, processes[i].wt);
    }

  
    printf("\nAverage Turnaround Time: %.2f\n", sum_tat / n);
    printf("Average Waiting Time: %.2f\n", sum_wt / n);

    return 0;
}

