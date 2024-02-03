#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 5500

/*
    client_fd: client file descriptor (the connecting socket)
    AF_INET: represents the IPv4 address of the client to which a connection should be made
    SOCK_STREAM: defines a reliable connection-oriented service (used in later function calls that operate on sockets)
    sockaddr_in: specifies a transport address and port for the AF_INET address family
    htons(): translates a short integer from host byte order to network byte order
    socket(): create an unbound socket in a communications domain
    inet_pton(): converts an Internet address in its standard text format into its numeric binary form
*/

int main()
{
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
	char name[1024];
    char pass[1024];
	char server_reply[1024];
	struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(SERVER_PORT);
    server_address.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) == -1)
	{
        perror("Error connecting to the server");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        fflush(stdin);

        printf("Enter username: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0'; // Remove the newline character at the end of the input

        fflush(stdin);

        send(client_socket, name, strlen(name), 0);

        printf("Enter password: ");
        fgets(pass, sizeof(pass), stdin);
        pass[strcspn(pass, "\n")] = '\0';

        send(client_socket, pass, strlen(pass), 0);

        printf("\nReceiving reply from server...\n");
        if (recv(client_socket, server_reply, 1024, 0) < 0)
        {
            printf("Reply error\n");
            continue;
        }

        if (strcmp(server_reply, "Confirmed") == 0)
        {
            break;
        }

        printf("Invalid data\n\n");
    }

    printf("%s username and password\n\n", server_reply);
    
    printf("************************\n");
    printf("*   Login Successful   *\n");
    printf("************************\n");

    close(client_socket);

    return 0;
}

