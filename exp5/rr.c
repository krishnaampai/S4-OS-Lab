#include <stdio.h>

typedef struct {
    int name;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int remaining_bt;
} Process;

void roundRobin(Process process[], int n, int timeQuantum) {
    int currentTime = 0, completed = 0;
    
    // Initialize remaining burst time
    for (int i = 0; i < n; i++) {
        process[i].remaining_bt = process[i].bt;
    }

    printf("\nGantt Chart:\nTime | Process\n");

    while (completed < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (process[i].remaining_bt > 0 && process[i].at <= currentTime) {
                executed = 1; // A process was executed in this iteration

                // Print the Gantt chart
                printf("%-4d | P%d\n", currentTime, process[i].name);

                // Execute process for time quantum or remaining time
                int execTime = (process[i].remaining_bt > timeQuantum) ? timeQuantum : process[i].remaining_bt;
                process[i].remaining_bt -= execTime;
                currentTime += execTime;

                // If process is completed, update completion time
                if (process[i].remaining_bt == 0) {
                    process[i].ct = currentTime;
                    process[i].tat = process[i].ct - process[i].at;
                    process[i].wt = process[i].tat - process[i].bt;
                    completed++;
                }
            }
        }
        if (!executed) currentTime++; // If no process was executed, move time forward
    }

    // Print Table
    printf("\nTable - \n");
    printf("PId\tAT\tBT\tCT\tTAT\tWT\n");
    float avg_tat = 0, avg_wt = 0;
    
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", process[i].name, process[i].at, process[i].bt, process[i].ct, process[i].tat, process[i].wt);
        avg_tat += process[i].tat;
        avg_wt += process[i].wt;
    }

    // Print averages
    printf("\nAvg TAT = %.2f\n", avg_tat / n);
    printf("Avg WT = %.2f\n", avg_wt / n);
}

int main() {
    int n, timeQuantum;
    
    printf("Enter number of processes: ");
    scanf("%d", &n);
    
    Process process[n];
    
    printf("Enter Process name, AT, and BT:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", &process[i].name, &process[i].at, &process[i].bt);
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    roundRobin(process, n, timeQuantum);

    return 0;
}

