#include <stdio.h>
#include <stdlib.h>

// Structure to represent a memory block
struct Block {
    int id;
    int size;
    int allocated; // Flag to check if the block is allocated
    struct Block* next;
};

// Function to create a new memory block
struct Block* createBlock(int size, int id) {
    struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
    newBlock->size = size;
    newBlock->id = id;
    newBlock->allocated = 0; // Initially not allocated
    newBlock->next = NULL;
    return newBlock;
}

// Function to create memory blocks from user input
struct Block* createMemoryBlocks(int numBlocks) {
    struct Block* head = NULL, *tail = NULL;
    for (int i = 0; i < numBlocks; i++) {
        int size;
        printf("Enter size of Block %d: ", i + 1);
        scanf("%d", &size);
        struct Block* newBlock = createBlock(size, i + 1);
        if (!head)
            head = newBlock;
        else
            tail->next = newBlock;
        tail = newBlock;
    }
    return head;
}

// Function to display remaining free memory blocks
void displayMemory(struct Block* head) {
    printf("\nRemaining Free Blocks:\n");
    struct Block* temp = head;
    while (temp) {
        if (!temp->allocated) {
            printf("Block %d: %d KB\n", temp->id, temp->size);
        }
        temp = temp->next;
    }
}

// Function to perform First-Fit allocation
void firstFit(struct Block* head, int processSize[], int numProcesses) {
    struct Block* temp;
    printf("\nFirst-Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < numProcesses; i++) {
        temp = head;
        while (temp) {
            if (!temp->allocated && temp->size >= processSize[i]) {
                printf("  %d\t\t%d\t\t%d\n", i + 1, processSize[i], temp->id);
                temp->allocated = 1; // Mark block as allocated
                break;
            }
            temp = temp->next;
        }
        if (!temp)
            printf("  %d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
    }
}

// Function to perform Best-Fit allocation
void bestFit(struct Block* head, int processSize[], int numProcesses) {
    struct Block* temp, *bestBlock;
    printf("\nBest-Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < numProcesses; i++) {
        temp = head;
        bestBlock = NULL;
        while (temp) {
            if (!temp->allocated && temp->size >= processSize[i] &&
                (!bestBlock || temp->size < bestBlock->size)) {
                bestBlock = temp;
            }
            temp = temp->next;
        }
        if (bestBlock) {
            printf("  %d\t\t%d\t\t%d\n", i + 1, processSize[i], bestBlock->id);
            bestBlock->allocated = 1;
        } else {
            printf("  %d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

// Function to perform Worst-Fit allocation
void worstFit(struct Block* head, int processSize[], int numProcesses) {
    struct Block* temp, *worstBlock;
    printf("\nWorst-Fit Allocation:\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < numProcesses; i++) {
        temp = head;
        worstBlock = NULL;
        while (temp) {
            if (!temp->allocated && temp->size >= processSize[i] &&
                (!worstBlock || temp->size > worstBlock->size)) {
                worstBlock = temp;
            }
            temp = temp->next;
        }
        if (worstBlock) {
            printf("  %d\t\t%d\t\t%d\n", i + 1, processSize[i], worstBlock->id);
            worstBlock->allocated = 1;
        } else {
            printf("  %d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
        }
    }
}

// Function to free memory block list
void freeMemory(struct Block* head) {
    struct Block* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int numBlocks, numProcesses, choice;

    // Get memory block details
    printf("Enter number of memory blocks: ");
    scanf("%d", &numBlocks);
    struct Block* head = createMemoryBlocks(numBlocks);

    // Get process details
    printf("\nEnter number of processes: ");
    scanf("%d", &numProcesses);
    int processSize[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    while (1) { // Loop to allow reallocation
        // Reset allocation status
        struct Block* temp = head;
        while (temp) {
            temp->allocated = 0;
            temp = temp->next;
        }

        // Choose allocation strategy
        printf("\nChoose Allocation Strategy:\n");
        printf("1 - First-Fit\n2 - Best-Fit\n3 - Worst-Fit\n4 - Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                firstFit(head, processSize, numProcesses);
                break;
            case 2:
                bestFit(head, processSize, numProcesses);
                break;
            case 3:
                worstFit(head, processSize, numProcesses);
                break;
            case 4:
                printf("Exiting...\n");
                freeMemory(head);
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
                continue;
        }

        // Display remaining memory blocks
        displayMemory(head);
    }
}

