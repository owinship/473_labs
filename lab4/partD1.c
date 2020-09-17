#include <stdio.h>

int main(){
	char dirpath[] = "/sys/class/gpio/gpio23/direction";
	char valuepath[] = "/sys/class/gpio/gpio23/value";
	direction = fopen(dirpath,'w');
	fprintf(direction,"out");
	fclose(direction);
	value = fopen(valuepath,'w');
	for(;;){
		fprintf(value,"%d",1);
		fprintf(value,"%d",0);
	}
}