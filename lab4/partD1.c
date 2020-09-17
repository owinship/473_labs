#include <stdio.h>

int main(){
	char dirpath[] = "/sys/class/gpio/gpio23/direction";
	char valuepath[] = "/sys/class/gpio/gpio23/value";
	FILE *direction = fopen(dirpath,'w');
	FILE *value = fopen(valuepath,'w');

	fprintf(direction,"out");
	fclose(direction);
	for(;;){
		fprintf(value,"%d",1);
		fprintf(value,"%d",0);
	}
}