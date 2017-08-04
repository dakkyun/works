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
#include <time.h>

clock_t start,end;

int serial_ardinowrite(char * , char *);
int serial_ardinoread(char *,char *);
int a = 0;
int fd;
char buf[255];

char data[255] = {0};

int main()
{
  int i,count = 0;
  char name[255],devicename[] = "/dev/ttyACM0";
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

  start = 0;
  end = 0;
  for(;;){
    if(end - start >= 30000){
      printf("clock : %ld\n",end - start);
      serial_ardinoread(devicename,name);
      if(data[0] == '1')
        serial_ardinowrite(devicename,(char *)"whatyourname");
      start = clock();
    }
    count++;
    if(count == 10)
      count = 0;

    end = clock();

    if(a == 8000)
      a = 0;
  }
  //printf("%s\n",name);

  ioctl(fd,TCSETS,&oldtio);
  close(fd);      
}

int serial_ardinowrite(char *devicename,char *messege)
{
  char temp,mark[255];

  a += 10;
  printf("%d\n",a);
  strcpy(buf,"");
  strcpy(mark,"");

  mark[0] = 126;
  //      printf("mark : %c\n",mark[0]);
  write(fd,mark,1);

  temp = a;
  buf[0] = a>>8;
  //      printf("%c\n",buf[0]);
  write(fd,buf,1);

  buf[0] = temp;
  //      printf("%c\n",buf[0]);
  write(fd,buf,1);

  return 0;

}


int serial_ardinoread(char *devicename,char *messege)
{
  char mes[255];
  char CR[2],LF[2];
  int flg,len;

  flg = 1;
  strcpy(mes,"");
  while(flg)
  {
    strcpy(data,"");
    len = read(fd,data,1);
    if(len==0)
    {
      printf("continue\n");
      continue;
    }
    else
    {
      strncat(mes,data,len);
      printf("accept : %c\n",data[0]);
      if(strstr(mes,CR)!=NULL || strstr(mes,LF)!=NULL)
      {
        flg=0;
      }
      break;
    }

  }

  return 0;
}
