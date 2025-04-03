#include <stdio.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

void print(int m[][R]) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++)
            printf("%d ", m[i][j]);
        printf("\n");
    }
}

int isSafe(int processes[], int available[], int max[][R], int allot[][R]) {
    int need[P][R];
    int finish[P] = {0};

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }
    
    printf("Resource Need:\n");
    print(need);
    
    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < P) {
        int found = 0;
        for (int i = 0; i < P; i++) {
            if (finish[i] == 0) {
                int flag = 1;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 0;
                        break;
                    }
                }
                if (flag == 1) {
                    printf("Process P%d can be allocated\n", i);
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[i][k];
                    }
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (found == 0) {
            return 0;
        }
    }
    return 1;
}

void bankerAlgorithm(int processes[], int available[], int max[][R], int allot[][R]) {
    if (isSafe(processes, available, max, allot)) {
        printf("System is in a Safe State. Resources can be allocated.\n");
    } else {
        printf("System is in an Unsafe State. Deadlock possible.\n");
    }
}

int main() {
    int processes[P];
    int available[R];
    int max[P][R];
    int allot[P][R];

    printf("Enter the process IDs: ");
    for (int i = 0; i < P; i++) {
        scanf("%d", &processes[i]);
    }
    
    printf("Enter available resources: ");
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the Max Requirement Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allot[i][j]);
        }
    }
    
    printf("Max Requirement:\n");
    print(max);
    printf("Resource Allotment:\n");
    print(allot);
    
    bankerAlgorithm(processes, available, max, allot);
    return 0;
}

