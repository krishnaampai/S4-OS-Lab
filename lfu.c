#include <stdio.h>
#include<stdlib.h>


int main(){
	int f,n;
	int page_fault = 0;
	printf ("Enter number of frames: ");
	scanf("%d",&f);
	int frames[f];
	int count[f];
	printf ("Enter number of pages: ");
	scanf("%d",&n);
	int pages[n];
	printf("Enter page reference sequence: \n");
	for (int i =0;i<n;i++){
		scanf("%d",&pages[i]);
	}
	for (int j=0;j<f;j++){
		frames[j] = -1;
		count[j] =0;
	}
	//lfu

	for (int i =0;i< n;i++){
		int page = pages[i];
		int found=0;
		for (int j =0;j<f;j++){//check if already in frames
			if (frames[j]==page){
				found =1;
				count[j]++;
				break;
			}
		}
		if (found ==0){
			page_fault++;
			int min = count[0];
			int req_frame =0;
			for (int i=1;i<f;i++){
				if (count[i]<min){
					min = count[i];
					req_frame = i;
				}

			}
			frames[req_frame] = page;
			count[req_frame] = 1;
			
		
			
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

