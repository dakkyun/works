#include<stdio.h>
#include<math.h>

#define PI 3.14159265359

int main()
{
	FILE *fp;
	int data[1081] = {0};



	int front_index;
	int i,j,k,max,min;
	int clcon[1081] = {0};
	int convex[1081] = {0};
	int decision[1081] = {0};
	int step[10] = {0};
	long cldis1[1081] = {0};
	
	double X = 8.0,Y = 5.0,sp = 0;
	double x,y,x0,x_t[1081] = {0},y_t[1081] = {0};
	double deg,rad,stddeg,cmpdeg,slope,radius;
	double cldis0;
	double decision_1,decision_2;
	double x_s,y_s,x_a,y_a,part_1,part_2,a,b;
	
	fp = fopen("test.txt","r");
	for(i = 0;i < 1081;i++)
		fscanf(fp,"%d",&data[i]);

	fclose(fp);

	// OûÌf[^ÌÝð\¦
	for(i = 1;i <= 1080;i++){
		printf("%d    :   %ld [mm]\n", i, data[i]);
		if(i >= 180 && i <= 900){
			//tunnel coodinate
			rad = (i - 180) * 0.25 * (PI / 180.0);	
			x_t[i] = (data[i] / 1000.0) * cos(-rad);
			y_t[i] = (data[i] / 1000.0) * sin(-rad);	
		}
	}
	//display
	for(i = 180;i < 901;i++)
		printf("%d  x : %f   y : %f\n",i,x_t[i],y_t[i]);
	//Linear approximation
	for(i = 180;i <= 900;i++){
		j = 0;
		for(k = i;k < 910;k++){
			for(;;){
				if(data[k] != 65533)
					break;
				k++;
			}
			step[j] = k;
			j++;
			if(j == 10)
				break;
		}
		//max and min
		max = step[0];
		min = step[0];
		for(j = 1;j < 10;j++){
			if(data[max] < data[ step[j] ])
				max = step[j];
			if(data[min] > data[ step[j] ])
				min = step[j];
		}
		//display
		printf("%d    max : %d   min : %d\n",i,max,min);
		//sum
		x_s = 0;
		for(j = 0;j < 10;j++){
			if(step[j] != max || step[j] != min)
				x_s += x_t[ step[j] ];
		}
		y_s = 0;
		for(j = 0;j < 10;j++){
			if(step[j] != max || step[j] != min)
				y_s += y_t[ step[j] ];
		}
		//display
		printf("x_s : %f   y_s : %f\n",x_s,y_s);
		//average
		x_a = x_s / 8;
		y_a = y_s / 8;
		//display
		printf("x_a : %f   y_a : %f\n",x_a,y_a);
		//Linear equations
		part_1 = 0;
		part_2 = 0;
		for(j = 0;j < 10;j++){
			if(step[j] != max || step[j] != min){
				part_1 += x_t[ step[j] ] * y_t[ step[j] ];
				part_2 += pow( x_t[ step[j] ] , 2.0 );
			}
		}
		//display
		printf("part_1 : %f   part_2 : %f\n",part_1,part_2);
		a = ( part_1 - (8.0 * x_a * y_a) ) / ( part_2 - ( 8.0 * pow(x_a , 2.0) ) );
		b = y_a - (a * x_a);
		printf("a : %lf     b : %lf\n\n",a,b);
	}
	printf("----------\n");
	
	return 0;
}
