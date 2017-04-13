/*#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

//using namespace cv;

#define sq(x) (x*x)
#define CLASSES 10
typedef struct image{
	int pos;
	char path[20];
	double c[2];
	double mag;
}img;

void insert_sort(img *arr,int n)
{
	img temp;
	int i,j,k;
	for(i=1;i<n;i++)
	{
		temp = arr[i];
		for(j=i-1;j>=0;j--)
		{
			if(arr[j].mag>temp.mag){
				arr[j].pos = j+1;
				arr[j+1]=arr[j]; 
			}
			else break;
		}
		arr[j+1]=temp;
		arr[j+1].pos = j+1;
	}
}
void sort_database(img **database,int *size)
{
	int i,j;
	for(i=0;i<CLASSES;i++)
		if(size[i])
			insert_sort(database[i],size[i]);
}
void print_database(img **database,int *size)
{
	int i,j;
	for(i=0;i<CLASSES;i++)
	{
		if(size[i])
			printf("%d%% Class\n",(i+1)*10);
		for(j=0;j<size[i];j++)
		{
			printf("%d) %s -> %2.lf %.2lf %.2lf\n"
				,database[i][j].pos
				,database[i][j].path
				,database[i][j].c[0]
				,database[i][j].c[1]
				,database[i][j].mag);
		}
	}
}
void create_database(FILE *fp,img **database,int *size)
{
	int i,j,k=0,num;
	while(fscanf(fp,"%d ",&num)!=EOF)
	{
		size[k]=num;
		if(size[k]){
			database[k] = (img *)malloc(num*sizeof(img));
			for(i=0;i<num;i++)
			{
				fscanf(fp,"%[^\n]",database[k][i].path);
				fscanf(fp,"%lf %lf ",
					database[k][i].c+0,
					database[k][i].c+1);
					database[k][i].pos=i;
					database[k][i].mag=sqrt(sq(database[k][i].c[0])+sq(database[k][i].c[1])); 
			}
			k++;
		}
	}
}
img *max(img *arr, int first, int second, double i_mag)
{
	double one = abs(arr[first].mag-i_mag);
	double two = abs(arr[second].mag-i_mag);
	if(one>=two) return (arr+second);
	else return (arr+first);
}
img *search_each(img *arr, int start, int end, int pa_size, double i_mag,int num)
{
	//printf("At start=%d end =%d pa_size=%d num=%d\n",start,end,pa_size,num);
	int mid=(start+end)/2;
	if(start>=end)
	{
		//printf("At strat=end\n");
		if(i_mag>arr[start].mag)
		{
			if(start+1<=pa_size) return max(arr,start,start+1,i_mag);
			else return (arr+start);
		}
		else if(i_mag<arr[start].mag)
		{
			if(start-1>=0) return max(arr,start,start-1,i_mag);
			else return (arr+start);
		}
		else return (arr+start);
	}
	else
	{
		if(i_mag>arr[mid].mag) 
			return search_each(arr,mid+1,end,pa_size,i_mag,num);
		else if(i_mag<arr[mid].mag) 
			return search_each(arr,start,mid-1,pa_size,i_mag,num);
		else
			return (arr+mid);
	}
}
img *search_database(img **database,int *size, img *input, img *output)
{
	int i,k;
	double i_mag = input->mag;
	double eucl_dist,dist,dist_l,dist_r,min_dist=INT_MAX,prev_dist;
	img *prev,*curr,*left,*right,*temp;
	for(i=0;i<CLASSES;i++)
		if(size[i]){
			k=1;
			prev = search_each(database[i],0,size[i]-1,size[i]-1,i_mag,i);
			eucl_dist = sqrt(pow(prev->c[0]-input->c[0],2)+pow(prev->c[1]-input->c[1],2));
			dist = eucl_dist;
			curr = prev;
			temp = prev;
			prev_dist = dist;
			do{
				//printf("dist=%.2f for %s k=%d\n",dist,prev->path,k);
				prev = temp;
				prev_dist = dist;
				if(curr->pos-k>=0){
					left = curr-k;
					dist_l = sqrt(pow(left->c[0]-input->c[0],2)+pow(left->c[1]-input->c[1],2));
				}
				if(curr->pos+k<size[i]){
					right = curr+k;
					dist_r = sqrt(pow(right->c[0]-input->c[0],2)+pow(right->c[1]-input->c[1],2));
				}
				if(curr->pos-k<0||curr->pos+k>=size[i]){
					
					if(curr->pos-k<0&&curr->pos+k>=size[i]) break;
					else if(curr->pos-k<0) {dist = dist_r; temp = right;}
					else if(curr->pos+k>=size[i]) {dist = dist_l; temp = left;}
				}
				else if(dist_l<=dist_r) {dist = dist_l; temp = left;}
				else if(dist_l>dist_r) {dist = dist_r; temp = right;}
				k++;
			}while(dist<=eucl_dist);
			//printf("min_dist = %.2f prev_dist = %.2f\n",min_dist,prev_dist);
			if(abs(min_dist-prev_dist)<40){
				min_dist=(min_dist>=prev_dist)?prev_dist:min_dist;
				output = prev;
				//printf("If prev->name =%s\n",prev->path);
			}
			else
			{
				if(min_dist>=prev_dist){
					min_dist=prev_dist;
					output = prev;
					//printf("else prev->name =%s\n",prev->path);
				}
			}
		}
	return output;
}
int main(int argc, char **argv)
{
	int size[10]={0};
	double i_mag;
	img **database,*output,*input;
	database = (img **)malloc(CLASSES*sizeof(img *));
	output = (img *)calloc(1,sizeof(img));
	input = (img *)calloc(1,sizeof(img));
	output->mag=0;
	FILE *fp = fopen("img_database.txt","r");
	create_database(fp,database,size);
	fclose(fp);
	sort_database(database,size);
	print_database(database,size);
	printf("\nEnter Input X and Y coordinates\n");
	scanf("%lf %lf",input->c+0,input->c+1);
	input->mag = sqrt(sq(input->c[0])+sq(input->c[1]));
	printf("\nInput Magnitude %.2lf\n",input->mag);
	output = search_database(database,size,input,output);
	printf("\nOutput:\nCoin position: %.2lf %.2lf\nMagnitude: %.2lf\n",output->c[0],output->c[1],output->mag);
	printf("Image File: %s\n",output->path);
/*	Mat myimg = imread(output->path,1);
	resize(myimg, myimg, cv::Size(), 0.3, 0.3);
	namedWindow( "myimg", WINDOW_AUTOSIZE );	
	imshow("myimg",myimg);
	waitKey(0);*/	
	return 0;
}
