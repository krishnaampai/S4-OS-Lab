#include <stdio.h>
#include <stdlib.h>
#define DISK_SIZE 200
#define MAX_REQUESTS 100

void sort(int *requests, int numRequests){
    for (int i = 0; i < numRequests; i++){
        for (int j = 0; j < numRequests - 1; j++){
            if (requests[j] > requests[j + 1]){
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

int calculateTotalSeekTime(int *requests, int numRequests, int currentTrack) {
    int totalSeekTime = 0;
    int direction = 1;  
    int i = 0;
    printf("Seek Sequence: %d", currentTrack);
    // Find the first request greater than or equal to the current track
    while (i < numRequests && requests[i] < currentTrack) {
        i++;
    }

    // Move right first
    for (int j = i; j < numRequests; j++) {
        totalSeekTime += abs(currentTrack - requests[j]);
        currentTrack = requests[j];
        printf(" -> %d", currentTrack);
    }

     if (currentTrack != DISK_SIZE - 1) {
        totalSeekTime += abs(currentTrack - (DISK_SIZE - 1));
        currentTrack = DISK_SIZE - 1;
         printf(" -> %d", currentTrack);
    }

    // Move left if needed
    if (i > 0) {
        totalSeekTime += abs(currentTrack - requests[i - 1]);
        currentTrack = requests[i - 1];
        printf(" -> %d", currentTrack);

        for (int j = i - 2; j >= 0; j--) {
            totalSeekTime += abs(currentTrack - requests[j]);
            currentTrack = requests[j];
            printf(" -> %d", currentTrack);
        }
    }

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
    printf("Total seek time using SCAN: %d\n", totalSeekTime);

    return 0;
}

