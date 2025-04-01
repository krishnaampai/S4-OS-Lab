#include <stdio.h>
#include <stdlib.h>

int main(){
    int f, n;
    int page_fault = 0;
    printf("Enter number of frames: ");
    scanf("%d", &f);
    int frames[f];
    int count[f];
    printf("Enter number of pages: ");
    scanf("%d", &n);
    int pages[n];
    printf("Enter page reference sequence: \n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    
  
    for (int j = 0; j < f; j++) {
        frames[j] = -1;
        count[j] = -1; 
    }

    // LRU algorithm
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;


        for (int j = 0; j < f; j++) {
            if (frames[j] == page) {
                found = 1;
                count[j] = i;  
                break;
            }
        }

        if (found == 0) {
            page_fault++;
            int min = i;
            int req_frame = 0;

            for (int j = 0; j < f; j++) {
                if (count[j] < min) {
                    min = count[j];
                    req_frame = j;
                }
            }

            
            frames[req_frame] = page;
            count[req_frame] = i;  
        }

        // Print the current frames
        for (int j = 0; j < f; j++) {
            if (frames[j] == -1) {
                printf("-\t");
            } else {
                printf("%d\t", frames[j]);
            }
        }
        printf("\n");
    }

    
    printf("\nFinal frame: \n");
    for (int i = 0; i < f; i++) {
        printf("%d\t", frames[i]);
    }
    printf("\nPage faults: %d\n", page_fault);

    return 0;
}

