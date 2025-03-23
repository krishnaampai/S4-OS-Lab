#include <stdio.h>
#include <limits.h>

typedef struct {
    int pid, at, bt, rt, ct, tat, wt;
} Process;

int main() {
    int n, time = 0, completed = 0, min_index;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process process[n];
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        process[i].pid = i + 1;
        scanf("%d %d", &process[i].at, &process[i].bt);
        process[i].rt = process[i].bt;  
    }

    printf("\nGantt Chart:\nTime | Process\n");

    while (completed != n) {
        min_index = -1;
        int min_rt = INT_MAX;
        
        // Find process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (process[i].at <= time && process[i].rt > 0 && process[i].rt < min_rt) {
                min_rt = process[i].rt;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;  // No process available, increase time
            continue;
        }

        printf("%-4d | P%d\n", time, process[min_index].pid);
        process[min_index].rt--;  // Reduce remaining time

        if (process[min_index].rt == 0) {  // Process completed
            process[min_index].ct = time + 1;
            process[min_index].tat = process[min_index].ct - process[min_index].at;
            process[min_index].wt = process[min_index].tat - process[min_index].bt;
            completed++;
        }
        
        time++;
    }

    // Printing the final table
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    float total_tat = 0, total_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i].pid, process[i].at, process[i].bt, 
               process[i].ct, process[i].tat, process[i].wt);
        total_tat += process[i].tat;
        total_wt += process[i].wt;
    }

    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
    printf("Average Waiting Time: %.2f\n", total_wt / n);

    return 0;
}

