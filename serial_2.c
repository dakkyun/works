#define BAUDRATE B9600
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
int serial_ardinowrite(char * , char *);
int serial_ardinoread(char *,char *);
int i;

int main()
{
	char name[255],devicename[] = "/dev/ttyACM0";
	serial_ardinowrite(devicename,(char *)"whatyourname");
	//serial_ardinoread(devicename,name);
	//printf("%s\n",name);
}

int serial_ardinowrite(char *devicename,char *messege)
{
    int a=2000,b;
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
   sleep(2); 
for(i = 0;i < 2;i++){
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
