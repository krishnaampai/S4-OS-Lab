#include <stdio.h>

int main() {
    int numBlocks, numProcesses;

    // Get memory block details
    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);
    int blockSize[numBlocks], blockAllocated[numBlocks];
    for (int i = 0; i < numBlocks; i++) {
        printf("Enter size of Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
        blockAllocated[i] = 0; // Initially, all blocks are free
    }

    // Get process details
    printf("\nEnter number of processes: ");
    scanf("%d", &numProcesses);
    int processSize[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // First-Fit Allocation
    printf("\nFirst-Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        int allocated = 0;
        for (int j = 0; j < numBlocks; j++) {
            if (!blockAllocated[j] && blockSize[j] >= processSize[i]) {
                printf("Process %d (Size %d) -> Block %d\n", i + 1, processSize[i], j + 1);
                blockAllocated[j] = 1;
                allocated = 1;
                break;
            }
        }
        if (!allocated) printf("Process %d (Size %d) -> Not Allocated\n", i + 1, processSize[i]);
    }

    // Reset block allocation
    for (int i = 0; i < numBlocks; i++) blockAllocated[i] = 0;

    // Best-Fit Allocation
    printf("\nBest-Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        int bestIdx = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (!blockAllocated[j] && blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            printf("Process %d (Size %d) -> Block %d\n", i + 1, processSize[i], bestIdx + 1);
            blockAllocated[bestIdx] = 1;
        } else {
            printf("Process %d (Size %d) -> Not Allocated\n", i + 1, processSize[i]);
        }
    }

    // Reset block allocation
    for (int i = 0; i < numBlocks; i++) blockAllocated[i] = 0;

    // Worst-Fit Allocation
    printf("\nWorst-Fit Allocation:\n");
    for (int i = 0; i < numProcesses; i++) {
        int worstIdx = -1;
        for (int j = 0; j < numBlocks; j++) {
            if (!blockAllocated[j] && blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            printf("Process %d (Size %d) -> Block %d\n", i + 1, processSize[i], worstIdx + 1);
            blockAllocated[worstIdx] = 1;
        } else {
            printf("Process %d (Size %d) -> Not Allocated\n", i + 1, processSize[i]);
        }
    }
    return 0;
}
