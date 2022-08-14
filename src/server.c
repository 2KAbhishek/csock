#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define LISTEN_PORT 8080

int main() {
  int fd = 0;
  char buff[BUF_SIZE];
  memset(buff, '0', sizeof(buff));

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("Server Error: Socket not created succesfully");
    return 0;
  }

  struct sockaddr_in server;
  memset(&server, '0', sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(LISTEN_PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  bind(fd, (struct sockaddr *)&server, sizeof(server));

  int in;

  listen(fd, 10);
  while ((in = accept(fd, (struct sockaddr *)NULL, NULL))) {
    int childpid, n;
    if ((childpid = fork()) == 0) {
      close(fd);
      bzero(buff, 256);

      while ((n = recv(in, buff, 256, 0)) > 0) {

        if (strcmp(buff, "shutdown") == 10) {
          printf("\nServer is shutting down\n");
          close(in);
          close(fd);
          break;
        }

        printf("Server Received: %s", buff);
        bzero(buff, 256);
      }
      close(in);
      exit(0);
    }
  }
}
