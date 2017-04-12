#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void src_loc_set(char *src_loc,int num,char *arg)
{
	char buffer[5];
	sprintf(buffer,"%d",num);
	strcpy(src_loc,arg);
	strcat(src_loc,"dataset/");
	strcat(src_loc,arg);
	strcat(src_loc,buffer);
	strcat(src_loc,".jpg");
}
void dst_loc_set(char *dst_loc,int num1, int num2,char *arg)
{
	char buffer[5];
	sprintf(buffer,"%d",num1);
	strcpy(dst_loc,buffer);
	strcat(dst_loc,"/");
	sprintf(buffer,"%d",num2);
	strcat(dst_loc,arg);
	strcat(dst_loc,buffer);
	strcat(dst_loc,".jpg");
}
void execute_cmd(char *cmd ,char *src_loc, char *dst_loc)
{
	strcpy(cmd,"cp ");
	strcat(cmd,src_loc);
	strcat(cmd," ");
	strcat(cmd,dst_loc);
	//printf("Executing %s\n",cmd);
	system(cmd);
}
int main(int argc, char **argv)
{
	char *data = (char *)malloc(20);
	strcpy(data,argv[1]);
	strcat(data,"data.txt");
	FILE *fp = fopen(data,"r+"),*src,*dst;
	double pr[11]={0};
	int i,j,num,diff=0;
	char res,*src_loc,*dst_loc,*command;
	src_loc = (char *)malloc(20);
	dst_loc = (char *)malloc(20);
	command = (char *)malloc(50);
	do{
		diff++;
		for(i=1;i<=11;i++)
		{
			for(j=1;j<=10;j++){
				fscanf(fp,"%d %c",&num,&res);
				if(res=='h') pr[i-1]++;
			}
		}
	}while(fscanf(fp,"%c",&res)!=EOF);
	fclose(fp);
	for(i=0;i<11;i++){
		pr[i]=(pr[i]/(diff*10))*100;
		printf("P(%d) = %.1f Aprrox = %.1f\n",i+1,pr[i],ceil(pr[i]));
		pr[i] = ceil(pr[i]);
	}
	for(i=0;i<11;i++){
		for(j=10;j<=100;j=j+10){
			if(!((int)pr[i]/j)){printf("Class(%d) -> %d%%\n",i+1,j); break;}
		}
		src_loc_set(src_loc,i+1,argv[1]);
		dst_loc_set(dst_loc,j,i+1,argv[1]);
		//printf("src_loc = %s\ndst_loc = %s\n",src_loc,dst_loc);
		execute_cmd(command,src_loc,dst_loc);
	}
	return 0;
}