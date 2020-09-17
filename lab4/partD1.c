#include <stdio.h>

int main(){
	char dirpath[] = "/sys/class/gpio/gpio23/direction";
	char valuepath[] = "/sys/class/gpio/gpio23/value";
	FILE *direction;
	FILE *value;
	direction = fopen(dirpath,"w");
	value = fopen(valuepath,"w");
	if((direction == NULL) || (value == NULL)){
		printf("null\n");
		return 1;
	}
	
	fprintf(direction,"out\n");
	fclose(direction);
	for(;;){
		fprintf(value,"%d",1);
		rewind(value);
		fprintf(value,"%d",0);
		rewind(value);
	}
}