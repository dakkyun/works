#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int
main()
{
     struct sockaddr_in server;
     int sock;
     char buf[32];
     int n;

     /* $B%=%1%C%H$N:n@.(B */
     sock = socket(AF_INET, SOCK_STREAM, 0);

     /* $B@\B3@h;XDjMQ9=B$BN$N=`Hw(B */
     server.sin_family = AF_INET;
     server.sin_port = htons(12345);
     server.sin_addr.s_addr = inet_addr("127.0.0.1");

     /* $B%5!<%P$K@\B3(B */
     connect(sock, (struct sockaddr *)&server, sizeof(server));

     /* $B%5!<%P$+$i%G!<%?$r<u?.(B */
     for(;;){
        memset(buf, 0, sizeof(buf));
        n = read(sock, buf, sizeof(buf));

        printf("%d, %s\n", n, buf);
     }

     /* socket$B$N=*N;(B */
     close(sock);

     return 0;
}
