#include<stdio.h>
#include<stdlib.h>

int main(){
	FILE *f1, *f2;
	char filename[100],c;
	
	printf("Enter file name for reading: ");
	scanf("%s",&filename);
	
	f1 = fopen(filename,"r");
	if(f1 == NULL){
		printf("\nCannot open file");
		exit(0);
	}
	
	printf("\nEnter file name for writing: ");
	scanf("%s",&filename);
	
	f2 = fopen(filename,"w");
	if(f2 == NULL){
		printf("\nCannot open file");
		fclose(f1);
		exit(0);
	}
	
	c = fgetc(f1);
	while(c != EOF){
		fputc(c,f2);
		c = fgetc(f1);
	}
	
	printf("\nFiles Copied");
	fclose(f1);
	fclose(f2);
	
	return 0;
}