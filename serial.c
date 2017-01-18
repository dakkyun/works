#define BAUDRATE B9600
#define PI 3.14159265359
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
int serial_ardinowrite(char * , char *);
int serial_ardinoread(char *,char *);
FILE *fp;
int data[1081] = {0};
int step[1081] = {0};

int i,j,k;	//Variable of if
int flag;	//Whether a linear approximation

double X = 8.0,Y = 4.1,sl = 0.13;	//Tunnel size
double x,y;	//UAV's position
double x_t[1081] = {0},y_t[1081] = {0};	//Tunnel coordinates
double deg,rad;	//Angle from corner to corner
double stddeg,cmpdeg;	//Reference angle, Comparison angle
double slope;	//UAV's slope
double x_s,y_s;	//sum
double x_a,y_a;	//average
double part_1,part_2;	//Calculating element of approximate straight line
double a_1,b_1;	//Slope and Intercept of wall line
double a_2,b_2;	//Slope and Intercept of bottom line
double x_c,y_c,x_cc,y_cc;	//Corner coordinates
double cldis_1,cldis_2;	//Distance to corner
double diff_1,diff_2,difference;	//Detection of corner step number
double step_1,step_2;	//Number of steps in the corner
double x_0,cldis_0;	//Coordinates and distance of 180th step

int main()
{
	char name[255],devicename[] = "/dev/ttyACM0";
	serial_ardinowrite(devicename,(char *)"whatyourname");
	//serial_ardinoread(devicename,name);
	printf("%s\n",name);
}

int sensor()
{
	fp = fopen("test.txt","r");
	for(i = 0;i < 1081;i++)
		fscanf(fp,"%d",&data[i]);

	fclose(fp);

	// OûÌf[^ÌÝð\¦
	for(i = 0;i <= 1080;i++){
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
	for(i = 230;i < 450;i++){
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
			if(i + j > 500)
				break;
		}
		printf("k : %d\n",k);
		if(k >= 50){
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

	for(i = 850;i > 580;i--){
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
			if(i - j < 530)
				break;
		}
		printf("k : %d\n",k);
		for(j = 0;j < k;j++)
			printf("step[j] : %d\n",step[j]);
		if(k >= 50){
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
	for(i = 300;i <= 700;i++){
		j = 1;
		k = 0;
		for(;;){
			if(-1.0 < y_t[i] - y_t[i + j] && y_t[i] - y_t[i + j] < 1.0){
				step[k] = i + j;
				j++;
				k++;
			}
			else
				j++;
			if(i + j > 700)
				break;
		}
		printf("k : %d\n",k);
		if(k >= 50){
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
	x_cc = -sqrt( pow(X , 2.0) / ( 1 + pow(a_2 , 2.0) ) ) + x_c;
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
	//printf("stddeg : %lf    cmpdeg : %lf\n",stddeg,cmpdeg);
	printf("slope : %lf [deg]\n",slope);

	return 0;

}

int serial_ardinowrite(char *devicename,char *messege)
{
    int a = 6456,b;
	char buf[255],temp,mark[255];
	int fd;
	struct termios oldtio,newtio;

	//strcpy(buf,messege);//間違ってもmessegeを変更してしまわないように
	fd = open(devicename,O_RDWR|O_NONBLOCK); //デバイスのオープン
	if(fd<0) //デバイスのオープンに失敗した場合
	{
		printf("ERROR on device open.\n");
		exit(1);
	}


	ioctl(fd,TCGETS,&oldtio);//現状のシリアルポート設定を退避
	newtio = oldtio;
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	ioctl(fd,TCSETS,&newtio);

for(i = 0;i < 1;i++){
    mark[0] = 127;
    printf("%c\n",mark[0]);
    write(fd,mark,1);
    
    temp = a;
    buf[0] = a>>8;
    printf("%c\n",buf[0]);
    write(fd,buf,1);

    buf[0] = temp;
    printf("%c\n",buf[0]);
	write(fd,buf,1);
}

    //tcflush(fd,TCOFLUSH);

	ioctl(fd,TCSETS,&oldtio);

	close(fd);

	return 0;

}


/*int serial_ardinoread(char *devicename,char *messege)
{
	char mes[255];
	char CR[2],LF[2],*p_c;
	char buf[255];
	int flg,fd,len;

	CR[0]=0xd;LF[0]=0xa;
	CR[1]=LF[1]='\0';
	struct termios oldtio,newtio;

	fd = open(devicename,O_RDWR|O_NONBLOCK); //デバイスのオープン
	if(fd<0) //デバイスのオープンに失敗した場合
	{
		printf("ERROR on device open.\n");
		exit(1);
	}


	ioctl(fd,TCGETS,&oldtio);//現状のシリアルポート設定を退避
	newtio = oldtio;
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
	ioctl(fd,TCSETS,&newtio);
	flg =1;
	strcpy(mes,"");
	while(flg)
	{
		strcpy(buf,"");
		len =read(fd,buf,sizeof(buf));
		if(len==0)
		{
			continue;
		}
		else if(len<0)//IOエラー
		{
			exit(2);
		}
		else
		{
			strncat(mes,buf,len);
			if(strstr(mes,CR)!=NULL || strstr(mes,LF)!=NULL)
			{
				flg=0;
			}
		}
	
	
	}
	ioctl(fd,TCSETS,&oldtio);

	close(fd);
	//if((p_c = strrchr(mes,CR[0]))!=(char)NULL) *p_c='\0';
	//if((p_c = strrchr(mes,LF[0]))!=(char)NULL) *p_c='\0';
	//strcpy(messege,mes);

	return 0;
}*/
