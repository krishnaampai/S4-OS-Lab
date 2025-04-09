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
