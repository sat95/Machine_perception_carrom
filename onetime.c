#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i;
	char list[5][3]={"1_","2_","3_","4_","5_"};
	char *data = (char *)malloc(50);
	for(i=0;i<5;i++){	
		strcpy(data,"./learn ");
		strcat(data,list[i]);
		system(data);
	}
	system("python CoinLocation_dataset.py");	
}
