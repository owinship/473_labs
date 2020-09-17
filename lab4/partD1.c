#include <stdio.h>

int main(){
	printf("in the beginning \n");
	char dirpath[] = "/sys/class/gpio/gpio23/direction";
	char valuepath[] = "/sys/class/gpio/gpio23/value";
	printf("life was simple\n");
	FILE *direction = fopen(dirpath,'w');
	FILE *value = fopen(valuepath,'w');
	
	printf("lmao\n");
	fprintf(direction,"out\n");
	printf("rofl\n");
	fclose(direction);
	printf("lol\n");
	for(;;){
		fprintf(value,"%d",1);
		printf("holy shit\n");
		rewind(value);
		printf("fug\n");
		fprintf(value,"%d",0);
		printf("waddup\n");
		rewind(value);
		printf("notlikethis\n");
	}
}