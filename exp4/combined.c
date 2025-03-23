#include <stdio.h>
#include <stdlib.h>


struct Block {
    int id;
    int size;
    struct Block* next;
};

// Function to create a new memory block
struct Block* createBlock(int size, int id) {
    struct Block* newBlock = (struct Block*)malloc(sizeof(struct Block));
    newBlock->size = size;
    newBlock->id = id;
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

// Function to copy memory block list for fresh allocation
struct Block* copyMemoryBlocks(struct Block* original) {
    struct Block* head = NULL, *tail = NULL, *temp = original;
    while (temp) {
        struct Block* newBlock = createBlock(temp->size, temp->id);
        if (!head)
            head = newBlock;
        else
            tail->next = newBlock;
        tail = newBlock;
        temp = temp->next;
    }
    return head;
}

// Function to display remaining free memory blocks
void displayMemory(struct Block* head) {
    printf("\nRemaining Free Blocks:\n");
    struct Block* temp = head;
    while (temp) {
        printf("Block %d: %d KB\n", temp->id, temp->size);
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
            if (temp->size >= processSize[i]) {
                printf("  %d\t\t%d\t\t%d\n", i + 1, processSize[i], temp->id);
                temp->size -= processSize[i];
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
            if (temp->size >= processSize[i] &&
                (!bestBlock || temp->size < bestBlock->size)) {
                bestBlock = temp;
            }
            temp = temp->next;
        }
        if (bestBlock) {
            printf("  %d\t\t%d\t\t%d\n", i + 1, processSize[i], bestBlock->id);
            bestBlock->size -= processSize[i];
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
            if (temp->size >= processSize[i] &&
                (!worstBlock || temp->size > worstBlock->size)) {
                worstBlock = temp;
            }
            temp = temp->next;
        }
        if (worstBlock) {
            printf("  %d\t\t%d\t\t%d\n", i + 1, processSize[i], worstBlock->id);
            worstBlock->size -= processSize[i];
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
    struct Block* originalHead = createMemoryBlocks(numBlocks); // Keep original memory state

    // Get process details
    printf("\nEnter number of processes: ");
    scanf("%d", &numProcesses);
    int processSize[numProcesses];
    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    while (1) { // Loop to allow reallocation
        // Create a fresh copy of memory blocks
        struct Block* head = copyMemoryBlocks(originalHead);

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
                freeMemory(originalHead); // Free original memory list
                return 0;
            default:
                printf("Invalid choice! Try again.\n");
                freeMemory(head);
                continue;
        }

        // Display remaining memory blocks
        displayMemory(head);

        // Free copied memory list after each allocation cycle
        freeMemory(head);
    }

    return 0;
}

