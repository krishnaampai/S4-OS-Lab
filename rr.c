#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int name;
    int arrival;
    int burst;
    int remaining;
    int status;
    int completion;
    int waiting;
    int turnaround;
} Process;

typedef struct Node {
    Process process;
    struct Node* next;
} Node;

Node *front = NULL;
Node *rear = NULL;

void enqueue(Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->process = process;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

Process dequeue() {
    Node* temp = front;
    Process process = temp->process;
    front = front->next;
    free(temp);
    return process;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival, &processes[i].burst);
        processes[i].name = i + 1;
        processes[i].remaining = processes[i].burst;
        processes[i].status = 0;
        processes[i].completion = -1;
        processes[i].turnaround = -1;
        processes[i].waiting = -1;
    }

    int quantum = 4;
    int currentTime = 0;
    int completed = 0;

    enqueue(processes[0]);
    processes[0].status = 1;

    printf("\nGantt Chart:\n");

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].status != 1) {
                enqueue(processes[i]);
                processes[i].status = 1;
            }
        }

        if (front != NULL) {
            Process currentProcess = dequeue();
            int executionTime = (currentProcess.remaining < quantum) ? currentProcess.remaining : quantum;
            currentProcess.remaining -= executionTime;
            currentTime += executionTime;

            printf("P%d(%d) ", currentProcess.name, currentTime);

            if (currentProcess.remaining <= 0) {
                completed++;
                for (int i = 0; i < n; i++) {
                    if (processes[i].name == currentProcess.name) {
                        processes[i].completion = currentTime;
                        break;
                    }
                }
            } else {
                enqueue(currentProcess);
            }
        } else {
            currentTime++;
        }
    }

    float avgWT = 0.0;
    float avgTAT = 0.0;

    printf("\nProcess\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        processes[i].turnaround = processes[i].completion - processes[i].arrival;
        processes[i].waiting = processes[i].turnaround - processes[i].burst;
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].name, processes[i].arrival, processes[i].burst,
               processes[i].completion, processes[i].turnaround, processes[i].waiting);
        avgWT += processes[i].waiting;
        avgTAT += processes[i].turnaround;
    }

    printf("\nAverage Waiting Time = %.2f\n", avgWT / n);
    printf("Average Turnaround Time = %.2f\n", avgTAT / n);

    return 0;
}

