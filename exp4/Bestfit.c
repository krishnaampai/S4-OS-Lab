#include <stdio.h>
#include <string.h>

void bestFit(int processSize[], int blockSize[], int m , int n){
	int allocation[n];
	memset(allocation,-1,sizeof(allocation));
	
	for (int i =0; i < n;i++){
		int best = -1;
		for (int j =0; j < m;j++){
			if (blockSize[j] >= processSize[i]){
				if (best == -1 || blockSize[best] > blockSize[j]){
					best = j;
				}
			}
		}
		if (best != -1){
			allocation[i] = best;
			blockSize[best] -= processSize[i];
		}
	}
	
	printf("Process no.\tProcess size\tBlock No.\n");
	for (int i = 0;i < n;i++){
		printf("%d\t\t%d\t\t",i+1, processSize[i]);
		if (allocation[i]!= -1){
			printf("%d\n", allocation[i]+1);
		}
		else {
			printf("Not allocated\n");
		}
	}
	printf ("Free Blocks: \n");
	for (int i = 0; i < m; i++) {
    	printf("Block %d: %d KB\n", i+1, blockSize[i]);
    }
}

int main(){
	int processSize[] = {212, 417, 112, 426};
	int blockSize[] = {100, 500, 200, 300, 600};
	int m = sizeof(blockSize)/sizeof(blockSize[0]);
	int n = sizeof(processSize)/sizeof(processSize[0]);
	bestFit(processSize, blockSize, m,n);
	return 0;
}
