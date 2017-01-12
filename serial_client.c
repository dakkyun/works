#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define SERIAL_PORT "/dev/rfcomm4"        /* $B%7%j%"%k%$%s%?!<%U%'!<%9$KBP1~$9$k%G%P%$%9%U%!%$%k(B */

int main(int argc, char *argv[])
{
        int buf[2];                       /* $B%P%C%U%!(B */
        int fd;                           /* $B%U%!%$%k%G%#%9%/%j%W%?(B */
        struct termios oldtio, newtio;    /* $B%7%j%"%kDL?.@_Dj(B */
                    
        fd = open(SERIAL_PORT, O_RDWR);   /* $B%G%P%$%9$r%*!<%W%s$9$k(B */
                            
        ioctl(fd, TCGETS, &oldtio);       /* $B8=:_$N%7%j%"%k%]!<%H$N@_Dj$rBTHr$5$;$k(B */
        newtio = oldtio;                  /* $B%]!<%H$N@_Dj$r%3%T!<(B */
        newtio.c_cflag = IGNBRK;          /* $B%]!<%H$N@_Dj$r$*$3$J$&(B $B>\:Y$O(Btermios(3)$B;2>H(B */
        ioctl(fd, TCSETS, &newtio);       /* $B%]!<%H$N@_Dj$rM-8z$K$9$k(B */
                                                
        read(fd, buf, sizeof(buf));       /* $B%G%P%$%9$+$i(B2$B%P%$%HFI$_9~$_(B */
      //write(fd, buf, sizeof(buf));      /* $B%G%P%$%9$X(B2$B%P%$%H=q$-9~$_(B */
                                                            
        ioctl(fd, TCSETS, &oldtio);       /* $B%]!<%H$N@_Dj$r85$KLa$9(B */
        close(fd);                        /* $B%G%P%$%9$N%/%m!<%:(B */

        return 0;
}
