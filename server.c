#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int
main()
{
     int sock0;
     struct sockaddr_in addr;
     struct sockaddr_in client;
     int len;
     int sock;

     /* $B%=%1%C%H$N:n@.(B */
     sock0 = socket(AF_INET, SOCK_STREAM, 0);

     /* $B%=%1%C%H$N@_Dj(B */
     addr.sin_family = AF_INET;
     addr.sin_port = htons(12345);
     addr.sin_addr.s_addr = INADDR_ANY;
     bind(sock0, (struct sockaddr *)&addr, sizeof(addr));

     /* TCP$B%/%i%$%"%s%H$+$i$N@\B3MW5a$rBT$F$k>uBV$K$9$k(B */   
     listen(sock0, 5);

     /* TCP$B%/%i%$%"%s%H$+$i$N@\B3MW5a$r<u$1IU$1$k(B */
     len = sizeof(client);
     sock = accept(sock0, (struct sockaddr *)&client, &len);

     /* 5$BJ8;zAw?.(B */
     write(sock, "5", 1);

     /* TCP$B%;%C%7%g%s$N=*N;(B */
     close(sock);

     /* listen $B$9$k(Bsocket$B$N=*N;(B */
     close(sock0);

     return 0;
}
