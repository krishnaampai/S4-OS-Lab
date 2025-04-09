#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100
#define DISK_SIZE 200

void sort(int requests[MAX_REQUESTS], int numRequests) {
    for (int i = 0; i < numRequests - 1; i++) {
        for (int j = 0; j < numRequests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

int calculateTotalSeekTime(int requests[MAX_REQUESTS], int numRequests, int currentTrack) {
    int totalSeekTime = 0;
    int i = 0;

    printf("Seek Sequence: %d", currentTrack);

    while (i < numRequests && requests[i] < currentTrack) {
        i++;
    }

    // Move right to service remaining requests
    for (int j = i; j < numRequests; j++) {
        totalSeekTime += abs(currentTrack - requests[j]);
        currentTrack = requests[j];
        printf(" -> %d", currentTrack);
    }

    // Move to end of disk
    if (currentTrack != DISK_SIZE - 1) {
        totalSeekTime += abs(currentTrack - (DISK_SIZE - 1));
        currentTrack = DISK_SIZE - 1;
        printf(" -> %d", currentTrack);
    }

    
    printf(" -> 0");
    currentTrack = 0;

    // Continue from beginning up to requests < original position
    for (int j = 0; j < i; j++) {
        totalSeekTime += abs(currentTrack - requests[j]);
        currentTrack = requests[j];
        printf(" -> %d", currentTrack);
    }

    printf("\n");
    return totalSeekTime;
}

int main() {
    int requests[MAX_REQUESTS], numRequests, currentTrack;

    printf("Enter the initial head position: ");
    scanf("%d", &currentTrack);

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    if (numRequests <= 0 || numRequests > MAX_REQUESTS) {
        printf("Invalid number of requests.\n");
        return 1;
    }

    printf("Enter the disk requests (track numbers):\n");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    sort(requests, numRequests);

    int totalSeekTime = calculateTotalSeekTime(requests, numRequests, currentTrack);
    printf("Total seek time using C-SCAN: %d\n", totalSeekTime);

    return 0;
}
