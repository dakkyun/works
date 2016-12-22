#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define PI 3.14159265359

int main()
{
	FILE *fp;
	int data[1081] = {0};



	int front_index;
	int i,j,k,flag;
	int clcon[1081] = {0};
	int convex[1081] = {0};
	int decision[1081] = {0};
	int step[500] = {0};
	long cldis1[1081] = {0};
	
	double X = 5.871,Y = 10.109,sl = 1.459;
	double x,y,x0,x_t[1081] = {0},y_t[1081] = {0};
	double deg,rad,stddeg,cmpdeg,slope,radius;
	double cldis0;
	double decision_1,decision_2;
	double x_s,y_s,x_a,y_a,part_1,part_2,a,b;
	double a_1,b_1,a_2,b_2,x_c,y_c,x_cc,y_cc,cldis_1,cldis_2,diff_1,diff_2,difference,step_1,step_2,x_0,cldis_0;
	
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
	for(i = 180;i <= 900;i++)
		printf("%d  x : %f   y : %f\n",i,x_t[i],y_t[i]);
	//Linear approximation
	for(i = 180;i < 500;i++){
		j = 1;
		k = 0;
		for(;;){
			if(-0.1 < x_t[i] - x_t[i + j] && x_t[i] - x_t[i + j] < 0.1){
				step[k] = i + j;
				j++;
				k++;
			}
			else
				j++;
			if(j > 500)
				break;
		}
		printf("k : %d\n",k);
		if(k >= 30){
			//sum
			x_s = 0;
			for(j = 0;j < k;j++)
					x_s += x_t[ step[j] ];
			y_s = 0;
			for(j = 0;j < k;j++)
					y_s += y_t[ step[j] ];
			//display
			printf("x_s : %f   y_s : %f\n",x_s,y_s);
			//average
			x_a = x_s / (float)k;
			y_a = y_s / (float)k;
			//display
			printf("x_a : %f   y_a : %f\n",x_a,y_a);
			//Linear equations
			part_1 = 0;
			part_2 = 0;
			for(j = 0;j < k;j++){
				part_1 += x_t[ step[j] ] * y_t[ step[j] ];
				part_2 += pow( x_t[ step[j] ] , 2.0 );
			}
			//display
			printf("part_1 : %f   part_2 : %f\n",part_1,part_2);
			a_1 = ( part_1 - ((float)k * x_a * y_a) ) / ( part_2 - ( (float)k * pow(x_a , 2.0) ) );
			b_1 = y_a - (a_1 * x_a);
			printf("%d  a : %lf     b : %lf\n",i,a_1,b_1);
			flag = 1;
			break;
		}
	}
	printf("----------\n");

	for(i = 900;i > 580;i--){
		if(flag == 1)
			break;
		j = 1;
		k = 0;
		for(;;){
			if(-0.1 < x_t[i] - x_t[i - j] && x_t[i] - x_t[i - j] < 0.1){
				step[k] = i - j;
				j++;
				k++;
			}
			else
				j++;
			if(j > 500)
				break;
		}
		printf("k : %d\n",k);
		if(k >= 30){
			//sum
			x_s = 0;
			for(j = 0;j < k;j++)
					x_s += x_t[ step[j] ];
			y_s = 0;
			for(j = 0;j < k;j++)
					y_s += y_t[ step[j] ];
			//display
			printf("x_s : %f   y_s : %f\n",x_s,y_s);
			//average
			x_a = x_s / (float)k;
			y_a = y_s / (float)k;
			//display
			printf("x_a : %f   y_a : %f\n",x_a,y_a);
			//Linear equations
			part_1 = 0;
			part_2 = 0;
			for(j = 0;j < k;j++){
				part_1 += x_t[ step[j] ] * y_t[ step[j] ];
				part_2 += pow( x_t[ step[j] ] , 2.0 );
			}
			//display
			printf("part_1 : %f   part_2 : %f\n",part_1,part_2);
			a_1 = ( part_1 - ((float)k * x_a * y_a) ) / ( part_2 - ( (float)k * pow(x_a , 2.0) ) );
			b_1 = y_a - (a_1 * x_a);
			printf("%d  a : %lf     b : %lf\n",i,a_1,b_1);
			break;
		}
	}

	//bottom line
	for(i = 400;i <= 700;i++){
		j = 1;
		k = 0;
		for(;;){
			if(-0.1 < y_t[i] - y_t[i + j] && y_t[i] - y_t[i + j] < 0.1){
				step[k] = i + j;
				j++;
				k++;
			}
			else
				j++;
			if(i + j > 900)
				break;
		}
		printf("k : %d\n",k);
		if(k >= 30){
			//sum
			x_s = 0;
			for(j = 0;j < k;j++)
					x_s += x_t[ step[j] ];
			y_s = 0;
			for(j = 0;j < k;j++)
					y_s += y_t[ step[j] ];
			//display
			printf("x_s : %f   y_s : %f\n",x_s,y_s);
			//average
			x_a = x_s / (float)k;
			y_a = y_s / (float)k;
			//display
			printf("x_a : %f   y_a : %f\n",x_a,y_a);
			//Linear equations
			part_1 = 0;
			part_2 = 0;
			for(j = 0;j < k;j++){
				part_1 += x_t[ step[j] ] * y_t[ step[j] ];
				part_2 += pow( x_t[ step[j] ] , 2.0 );
			}
			//display
			printf("part_1 : %f   part_2 : %f\n",part_1,part_2);
			a_2 = ( part_1 - ((float)k * x_a * y_a) ) / ( part_2 - ( (float)k * pow(x_a , 2.0) ) );
			b_2 = y_a - (a_2 * x_a);
			printf("%d  a : %lf     b : %lf\n",i,a_2,b_2);
			break;
		}
	}
	
	printf("---------------------\n");

	//corner
	x_c = (b_2 - b_1) / (a_1 - a_2);
	y_c = (a_1 * x_c) + b_1;
	printf("x_c : %f   y_c : %f\n",x_c,y_c);
	//reverse corner
	x_cc = -sqrt( pow(Y , 2.0) / ( 1 + pow(a_2 , 2.0) ) ) + x_c;
	y_cc = a_2 * (x_cc - x_c) + y_c;
	printf("x_cc : %f   y_cc : %f\n",x_cc,y_cc);
	//distance to corner
	cldis_1 = sqrt( pow(x_c , 2.0) + pow(y_c , 2.0) );
	cldis_2 = sqrt( pow(x_cc , 2.0) + pow(y_cc , 2.0) );
	printf("cldis_1 : %f   cldis_2 : %f\n",cldis_1,cldis_2);
	//step of corner
	for(i = 180;i <= 900;i++){
		diff_1 = x_c - x_t[i];
		diff_2 = y_c - y_t[i];
		diff_1 = fabs(diff_1);
		diff_2 = fabs(diff_2);
		if(i == 180){
			difference = diff_1 + diff_2;
			step_1 = i;
		}
		else if(difference > diff_1 + diff_2){
			difference = diff_1 + diff_2;
			step_1 = i;
		}
	}
	printf("---------------------\n");
	for(i = 180;i <= 900;i++){
		diff_1 = x_cc - x_t[i];
		diff_2 = y_cc - y_t[i];
		diff_1 = fabs(diff_1);
		diff_2 = fabs(diff_2);
		if(i == 180){
			difference = diff_1 + diff_2;
			step_2 = i;
		}
		else if(difference > diff_1 + diff_2){
			difference = diff_1 + diff_2;
			step_2 = i;
		}
	}
	printf("---------------------\n");
	//coordinate
	printf("step_1 : %f   step_2 : %f\n",step_1,step_2);
	deg = (step_2 - step_1) * 0.25;
	rad = deg * PI / 180.0;

	y = ( cldis_1 * cldis_2 * sin(rad) ) / X;
	x = (X / 2.0) - sqrt( pow(cldis_1 , 2.0) - pow(y , 2.0) );
	printf("coordinate : (%f [m], %f [m])\n",x,y);

	//slope
	x_0 = sqrt( pow((X / 2.0) , 2.0) - pow((y - sl) , 2.0) );
	cldis_0 = x_0 - x;
	stddeg = acos( ( (X / 2.0) - x) / cldis_1 ) * (180.0 / PI);
	cmpdeg = (step_1 - 180) * 0.25;

	slope = (stddeg - cmpdeg);
	printf("stddeg : %lf    cmpdeg : %lf\n",stddeg,cmpdeg);
	printf("slope : %lf [deg]\n",slope);



	
	return 0;
}
