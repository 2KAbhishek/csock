#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define LISTEN_PORT 8080

int main(int argc, char *argv[]) {
  int fd = 0;
  char buff[BUF_SIZE];

  memset(buff, '0', sizeof(buff));

  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    perror("Client Error: Socket not created succesfully");
    return 0;
  }

  struct sockaddr_in server;
  memset(&server, '0', sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(LISTEN_PORT);

  int in = inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
  in = connect(fd, (struct sockaddr *)&server, sizeof(server));
  if (in < 0) {
    perror("Client Error: Connection Failed.");
    return 0;
  }

  while (1) {
    printf("Enter the message: ");
    bzero(buff, 256);
    fgets(buff, 255, stdin);

    if (strcmp(buff, "bye\n") == 0) {
      send(fd, buff, strlen(buff), 0);
      printf("Client: Exiting\n");
      close(fd);
      close(in);
      break;
    }

    in = send(fd, buff, strlen(buff), 0);
    if (in < 0) {
      perror("\nClient Error: Cannot write to server");
      return 0;
    }

    bzero(buff, 256);
  }
  close(fd);
  return 0;
}
