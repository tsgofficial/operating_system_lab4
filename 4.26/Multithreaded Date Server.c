#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <arpa/inet.h>

void *handle_client(void *arg)
{
    int sock = *(int *)arg;
    free(arg);

    char buffer[128];
    time_t now = time(NULL);
    snprintf(buffer, sizeof(buffer), "Date: %s", ctime(&now));
    write(sock, buffer, strlen(buffer));
    close(sock);
    return NULL;
}

int main()
{
    int server_fd, new_sock;
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(6017);

    bind(server_fd, (struct sockaddr *)&addr, sizeof(addr));
    listen(server_fd, 5);

    while (1)
    {
        new_sock = accept(server_fd, (struct sockaddr *)&addr, &addrlen);
        int *client_sock = malloc(sizeof(int));
        *client_sock = new_sock;
        pthread_t tid;
        pthread_create(&tid, NULL, handle_client, client_sock);
        pthread_detach(tid);
    }
    return 0;
}
