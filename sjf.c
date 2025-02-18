/*#include <stdio.h>

typedef struct {
	int name;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
} Process;

void sortProcess(Process process[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (process[j].bt > process[j + 1].bt || 
                (process[j].bt == process[j + 1].bt && process[j].at > process[j + 1].at)) {
                // Swap processes[j] and processes[j + 1]
                Process temp = process[j];
                process[j] = process[j + 1];
                process[j + 1] = temp;
            }
        }
    }
}

int main(){
	
	int n;
	printf ("Enter number of process: ");
	scanf("%d", &n);
	Process process[n];
	printf ("Enter Process name, AT and BT in that order for each process- \n");
	for (int i =0;i<n;i++){
		
		scanf("%d%d%d",&process[i].name,&process[i].at,&process[i].bt);
	}
	sortProcess(process,n);
	for (int i =0;i<n;i++){
		
		printf("%d%d%d",process[i].name,process[i].at,process[i].bt);
	}
	int currentTime =0;
	printf ("\nGnatt Chart\n");
	printf ("Time | Process\n");
	
	for (int i =0;i<n;i++){
		if (currentTime < process[i].at) {
            currentTime = process[i].at;  // If current time is less than arrival time, update current time
        }
		printf ("%-4d\tP%d\n",currentTime , process[i].name);
		currentTime += process[i].bt;
		process[i].ct = currentTime;
		process[i].tat = process[i].ct - process[i].at;
		process[i].wt = process[i].tat - process[i].bt;
	}
	
	printf ("\nTable - \n");
	printf ("PID\tBT\tAT\tCT\tTAT\tWT\n");
	for (int i =0;i<n;i++){
		printf ("P%d\t%d\t%d\t%d\t%d\t%d\t\n",process[i].name,process[i].at,process[i].bt,process[i].ct,process[i].tat,process[i].wt);
	}
	
	float avg_tat=0,avg_wt =0;
	for (int i=0;i<n;i++){
		avg_tat += process[i].tat;
		avg_wt += process[i].wt;
	}
	printf ("\nAvg TAT = %.2f\n", avg_tat/n);
	printf ("Avg WT = %.2f\n", avg_wt/n);
	
	return 0;
}
#include <stdio.h>
#include <stdbool.h>

// Structure to represent a process
struct Process {
    int pid; // Process ID
    int arrival_time; // Arrival time
    int burst_time; // Burst time
};

// Function to sort processes based on burst time
void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].burst_time > processes[j + 1].burst_time) {
                // Swap processes[j] and processes[j + 1]
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to calculate waiting time and turnaround time
void calculateTimes(struct Process processes[], int n, int wt[], int tat[]) {
    wt[0] = 0;
    tat[0]=wt[0]+processes[0].burst_time;
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + processes[i - 1].burst_time;
        tat[i] = wt[i] + processes[i].burst_time;
    }
}

// Function to calculate average waiting time and turnaround time
void calculateAvgTimes(struct Process processes[], int n) {
    int wt[n], tat[n];
    calculateTimes(processes, n, wt, tat);

    float avg_wt = 0, avg_tat = 0;
    printf("PID \tWT \tTAT\n");
    for (int i = 0; i < n; i++) {
        avg_wt += wt[i];
        avg_tat += tat[i];
        printf("%d\t %d\t %d\n",processes[i].pid,wt[i],tat[i]);
    }

    printf("Average waiting time = %.2f\n", avg_wt / n);
    printf("Average turnaround time = %.2f\n", avg_tat / n);
}

int main() {
    int n = 5; // Number of processes
    struct Process processes[] = {
        {1, 0, 8},
        {2, 1, 1},
        {3, 2, 3},
        {4, 3, 2},
        {5, 4, 6}
    };

    // Sort processes based on burst time
    sortProcesses(processes, n);
        // Calculate average waiting time and turnaround time
    calculateAvgTimes(processes, n);

    return 0;
}

#include <stdio.h>
int main()
{
    // Matrix for storing Process Id, Burst
    // Time, Average Waiting Time & Average
    // Turn Around Time.
    int A[100][4];
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("Enter Burst Time:\n");
    // User Input Burst Time and alloting Process Id.
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);
        A[i][0] = i + 1;
    }
    // Sorting process according to their Burst Time.
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++)
            if (A[j][1] < A[index][1])
                index = j;
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;
 
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }
    A[0][2] = 0;
    // Calculation of Waiting Times
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++)
            A[i][2] += A[j][1];
        total += A[i][2];
    }
    avg_wt = (float)total / n;
    total = 0;
    printf("P     BT     WT     TAT\n");
    // Calculation of Turn Around Time and printing the
    // data.
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];
        total += A[i][3];
        printf("P%d     %d     %d      %d\n", A[i][0],
               A[i][1], A[i][2], A[i][3]);
    }
    avg_tat = (float)total / n;
    printf("Average Waiting Time= %f", avg_wt);
    printf("\nAverage Turnaround Time= %f", avg_tat);
}
*/

#include<stdio.h>

int main() {
  int time, burst_time[10], at[10], sum_burst_time = 0, smallest, n, i;
  int sumt = 0, sumw = 0;
  printf("enter the no of processes : ");
  scanf("%d", & n);
  for (i = 0; i < n; i++) {
    printf("the arrival time for process P%d : ", i + 1);
    scanf("%d", & at[i]);
    printf("the burst time for process P%d : ", i + 1);
    scanf("%d", & burst_time[i]);
    sum_burst_time += burst_time[i];
  }
  burst_time[9] = 9999;
  for (time = 0; time < sum_burst_time;) {
    smallest = 9;
    for (i = 0; i < n; i++) {
      if (at[i] <= time && burst_time[i] > 0 && burst_time[i] < burst_time[smallest])
        smallest = i;
    }
    printf("P[%d]\t|\t%d\t|\t%d\n", smallest + 1, time + burst_time[smallest] - at[smallest], time - at[smallest]);
    sumt += time + burst_time[smallest] - at[smallest];
    sumw += time - at[smallest];
    time += burst_time[smallest];
    burst_time[smallest] = 0;
  }
  printf("\n\n average waiting time = %.2f", sumw * 1.0 / n);
  printf("\n\n average turnaround time = %.2f", sumt * 1.0 / n);
  return 0;
}


