#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *data = (char *)malloc(20);
	strcpy(data,"python coinCenter.py ");
	strcat(data,argv[1]);
	strcat(data," | ./test");
	//printf("%s\n" data);
	system(data);
}
