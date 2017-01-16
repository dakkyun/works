#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

#define BAUDRATE B9600
#define SERIAL_PORT "/dev/rfcomm3"        /* シリアルインターフェースに対応するデバイスファイル */

int main(int argc, char *argv[])
{
        char buf[255] = [0];              /* バッファ */
        int fd;                           /* ファイルディスクリプタ */
        struct termios oldtio, newtio;    /* シリアル通信設定 */
                    
        fd = open(SERIAL_PORT, O_RDWR);   /* デバイスをオープンする */
                            
        ioctl(fd, TCGETS, &oldtio);       /* 現在のシリアルポートの設定を待避させる */
        newtio = oldtio;                  /* ポートの設定をコピー */
        newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;
        newtio.c_iflag = IGNPAR;          /* ポートの設定をおこなう 詳細はtermios(3)参照 */
        newtio.c_oflag = 0;
        ioctl(fd, TCSETS, &newtio);       /* ポートの設定を有効にする */

        newtio.c_lflag = 0;   
        
        newtio.c_cc[VTIME] = 0;
        newtio.c_cc[VMIN] = 5;
                                             
      //read(fd, buf, sizeof(buf));       /* デバイスから2バイト読み込み */
        buf[0] = 123;
        write(fd, buf, 1);                /* デバイスへ1バイト書き込み */
                                                            
        ioctl(fd, TCSETS, &oldtio);       /* ポートの設定を元に戻す */
        close(fd);                        /* デバイスのクローズ */

        return 0;
}
