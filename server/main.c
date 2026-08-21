#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
	// 1. Create socket
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	// 2. Describe the server address
	struct sockaddr_in server_addr = {0};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345);

	int ip_conversion = inet_pton(AF_INET, "127.0.0.1",&server_addr.sin_addr);
	if(ip_conversion != 1){
		printf("It is an invalid ip or address family.\n");
		exit(-1);
	}

	// 3. Bind socket to localhost:12345
	int bind_ret = bind(server_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(bind_ret == -1){
		perror("Some problem binding with the port.\n");
		exit(-1);
	}

	// 4. Listen for incoming connections
	int listen_ret = listen(server_fd, 5);
	if(listen_ret == -1){
		perror("The listen function failed.\n");
	}

	printf("Server listening on 127.0.0.1:12345...\n");
	while(1){
		// 5. Accept a client connection
		int client_fd = accept(server_fd, NULL, NULL);

		printf("Client connected!\n");

		// 6. Receive data from client
		char buffer[1024];

		int n = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		if (n > 0) {
        		buffer[n] = '\0';
        		printf("Client: %s\n", buffer);
		}

		// 7. Send response to client
		char msg[] = "Hello";
		send(client_fd, msg, strlen(msg), 0);
		// 8. Close client connection
		//close(client_fd);
	}

	// 9. Close server socket
	close(server_fd);

	return 0;
}
