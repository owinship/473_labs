#include <stdio.h>

int main(){
	printf("in the beginning");
	char dirpath[] = "/sys/class/gpio/gpio23/direction";
	char valuepath[] = "/sys/class/gpio/gpio23/value";
	FILE *direction = fopen(dirpath,'w');
	FILE *value = fopen(valuepath,'w');
	
	printf("lmao");
	fprintf(direction,"out");
	printf("rofl");
	fclose(direction);
	printf("lol");
	for(;;){
		fprintf(value,"%d",1);
		printf("holy shit");
		rewind(value);
		printf("fug");
		fprintf(value,"%d",0);
		printf("waddup");
		rewind(value);
		printf("notlikethis");
	}
}