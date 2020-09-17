#include <stdio.h>

int main(){
	printf("in the beginning \n");
	char dirpath[] = "/sys/class/gpio/gpio23/direction";
	char valuepath[] = "/sys/class/gpio/gpio23/value";
	printf("life was simple\n");
	FILE *direction;
	FILE *value;
	direction = fopen(dirpath,"w");
	value = fopen(valuepath,"w");
	if((direction == NULL) || (value == NULL)){
		printf("null\n");
		return 1;
	}
	
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