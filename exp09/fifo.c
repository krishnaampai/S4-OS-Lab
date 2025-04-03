#include <stdio.h>
#include<stdlib.h>


int main(){
	int f,n;
	int page_fault = 0;
	printf ("Enter number of frames: ");
	scanf("%d",&f);
	int frames[f];
	printf ("Enter number of pages: ");
	scanf("%d",&n);
	int pages[n];
	printf("Enter each page: \n");
	for (int i =0;i<n;i++){
		scanf("%d",&pages[i]);
	}
	for (int j=0;j<f;j++){
		frames[j] = -1;
	}
	//fifo

	int rear =0;
	for (int i =0;i< n;i++){
		int page = pages[i];
		int found=0;
		for (int j =0;j<f;j++){//check if already in frames
			if (frames[j]==page){
				found =1;
				break;
			}
		}
		if (found ==0){
			page_fault++;
			frames[rear] = page;
			if (rear ==f-1){
				rear =0;
			}
			else {
				rear++;
			}
			
		}
		
		for (int i =0;i< f;i++){
			if (frames[i]==-1){
				printf ("-\t");
			}
			else {
				printf ("%d\t",frames[i]);
			}

		}
					printf("\n");
	}
	//print final frames and page fault
	printf("\nFinal frame: \n");
	for (int i=0;i<f;i++){
		printf ("%d\t",frames[i]);
	}
	printf ("\nPage faults: %d\n",page_fault);
	return 0;
}

