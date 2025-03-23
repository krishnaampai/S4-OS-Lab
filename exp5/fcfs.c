#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int name;
	int at;
	int bt;
	int ct;
	int tat;
	int wt;
} Process;
int main(){
	/*Process process[]={
		{1,0,5},
		{2,1,3},
		{3,2,8}
	};*/
	
	int n;
	printf ("Enter number of process: ");
	scanf("%d", &n);
	Process process[n];
	printf ("Enter Process name, AT and BT in that order for each process- \n");
	for (int i =0;i<n;i++){
		
		scanf("%d%d%d",&process[i].name,&process[i].at,&process[i].bt);
	}
	// Sort processes by Arrival Time (Bubble Sort)
	for (int i = 0; i < n - 1; i++) {
	    for (int j = 0; j < n - i - 1; j++) {
		  if (process[j].at > process[j + 1].at) {
		      Process temp = process[j];
		      process[j] = process[j + 1];
		      process[j + 1] = temp;
		  }
	    }
	}

	
	//int n = sizeof(process)/sizeof(Process);
	int currentTime =0;
	
	printf("\nGnatt Chart\n");
	printf("Time | Process\n");
	for (int i =0;i < n;i++){
		if (currentTime < process[i].at) {
            	currentTime = process[i].at;  // Idle time if CPU is free
        	}
		int execution_time = process[i].bt;
		printf ("%-4d | P%d\n", currentTime , process[i].name);
		currentTime +=execution_time;
		process[i].ct = currentTime;
		process[i].tat = process[i].ct - process[i].at;
		process[i].wt = process[i].tat - process[i].bt;
	}
	
	printf ("\nTable - \n");
	printf ("PId\tBT\tAT\tCT\tTAT\tWT\n");
	for (int i =0;i<n;i++){
		printf ("P%d\t%d\t%d\t%d\t%d\t%d\t\n",process[i].name,process[i].bt,
		process[i].at,process[i].ct,
		process[i].tat,process[i].wt);
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
