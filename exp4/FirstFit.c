#include <stdio.h>
#include <string.h>

void firstFit(int processSize[], int blockSize[], int m , int n){
	int allocation[n];
	memset(allocation,-1,sizeof(allocation));
	
	for (int i =0;i<n;i++){
		for (int j=0;j<m;j++){
			if (blockSize[j] >= processSize[i]){
				allocation[i] = j;
				blockSize[j] = blockSize[j] - processSize[i];
				break;
			}
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
	int processSize[] = {30,500,200,220,150};
	int blockSize[] = {30,100,50,400,350};
	int m = sizeof(blockSize)/sizeof(blockSize[0]);
	int n = sizeof(processSize)/sizeof(processSize[0]);
	firstFit(processSize, blockSize, m,n);
	return 0;
}
