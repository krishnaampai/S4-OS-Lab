/*#include <stdio.h>
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
}*/

#include <stdio.h>
#include<stdlib.h>

struct Block {
	int size;
	int process_id;
	struct Block* next;
};

void bestFit(int processes[],int n,struct Block* head){
	for (int i =0;i<n;i++){
		struct Block* temp = head;
		struct Block* best = NULL;
		while(temp!=NULL){
			if(temp->process_id==-1&&temp->size >=processes[i]){
				if(!best||temp->size<best->size){
					best = temp;
				}
			}
			temp = temp->next;
		}
		if(best!=NULL){
			best->process_id = i+1;
			printf("Process %d of size  %d allocated to block of size %d\n",i+1,processes[i],best->size);
				
		}
		else {
			printf("process %d not allocated\n",i+1);
		}
	}
}

int main(){
	struct Block* head = NULL;
	struct Block* temp;
	int n,m;
	printf("Enter number of blocks: ");
	scanf("%d",&m);
	for (int i =0;i<m;i++){
		
		struct Block *newBlock = (struct Block*)malloc(sizeof(struct Block));
		printf("Enter size of block %d:",i+1);
		scanf("%d",&newBlock->size);
		newBlock->process_id = -1;
		newBlock->next = NULL;
		if(!head){
			head = newBlock;
		}
		else {
			temp->next = newBlock;
			
		}
		
		temp = newBlock;
		
	}
	printf("Enter number of processes: ");
	scanf("%d",&n);
	int processes[n];
	for (int i =0;i<n;i++){
		printf("Enter size of process %d:",i+1);
		scanf("%d",&processes[i]);
	}
	bestFit(processes,n,head);
	
	printf ("Block\t Process\n");
	struct Block* temp1= head;
	while(temp1!=NULL){
		printf("%d\t%d\n",temp1->size,temp1->process_id);
		temp1= temp1->next;
	}
	
	return 0;
}
