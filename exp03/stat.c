#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

void printFileProperties (struct stat stats){
	struct tm dt; //structure to hold broken-down time
	
	printf ("\nFile access: ");
	if (stats.st_mode & S_IRUSR) printf("read \n");
	if (stats.st_mode & S_IWUSR) printf("write \n");
	if (stats.st_mode & S_IXUSR) printf("execute\n");
	
	printf("File size : %d bytes\n", stats.st_size);
	
	dt = *(gmtime(&stats.st_ctime));
	printf("\nCreated on: %d-%d-%d %d:%d:%d\n",
           dt.tm_mday, dt.tm_mon + 1, dt.tm_year + 1900,
           dt.tm_hour, dt.tm_min, dt.tm_sec);	
}

int main(){
	char filename[100];
    struct stat stats;

    printf("Enter the file name: ");
    scanf("%s", filename);

    if (stat(filename, &stats) == 0) {
        printFileProperties(stats);
    } else {
        printf("Unable to get file properties.\n");
        printf("Please check whether '%s' file exists.\n", filename);
    }

    return 0;
}
