#include <stdio.h>

typedef struct {
    int id, arrival, burst, priority, waiting, turnaround, completed, completion;
} Process;

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time, burst time, and priority for process %d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrival, &p[i].burst, &p[i].priority);
        p[i].completed = 0;
    }

    int currentTime = 0, completedProcesses = 0;
    printf("\nGantt Chart:\n");
    printf("Time | Process\n");

    while (completedProcesses < n) {
        int minPriority = 9999, index = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].arrival <= currentTime) {
                if (p[i].priority < minPriority) { 
                    minPriority = p[i].priority;
                    index = i;
                }
            }
        }

        if (index == -1) { 
            currentTime++; 
        } else {
            printf("%-4d | P%d\n", currentTime, p[index].id);
            p[index].waiting = currentTime - p[index].arrival;
            p[index].turnaround = p[index].waiting + p[index].burst;
            currentTime += p[index].burst;
            p[index].completion = currentTime;
            p[index].completed = 1;
            completedProcesses++;
        }
    }

    printf("\nID\tAT\tBT\tP\tCT\tTAT\tWT\n");
    float totalWT = 0, totalTAT = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].priority, p[i].completion, p[i].turnaround, p[i].waiting);
        totalWT += p[i].waiting;
        totalTAT += p[i].turnaround;
    }

    printf("\nAvg TAT = %.2f\n", totalTAT / n);
    printf("Avg WT = %.2f\n", totalWT / n);

    return 0;
}

