#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(){
	// 1. Create socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
	// 2. Describe the server
	struct sockaddr_in server_addr = {0};
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(12345);
	int ip_conversion = inet_pton(AF_INET, "127.0.0.1",&server_addr.sin_addr);
	if (ip_conversion != 1){
		printf("invalid ip or addressfamily\n");
		exit(-1);
	}

	// 3. Connect to localhost:12345
	int connect_ret_value= connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	if(connect_ret_value == -1){
		printf("Connection failed\n");
		exit(connect_ret_value);
	}

	// 4. Send data
	char msg[] = "Say Hello\n";

	send(sockfd, msg, strlen(msg), 0);

	// 5. Receive response
	char buffer[1024];

	int n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);

	if (n > 0) {
        	buffer[n] = '\0';
        	printf("Server: %s\n", buffer);
	}else if(n == 0){
		printf("Server connection closed.");
	}

	// 6. Close socket
	int close_ret_val = close(sockfd);
	if (close_ret_val == 0){
		printf("Connection closed sussfully.\n");
	}else{
		printf("Something went wrong while closing the connection.");
	}

	return 0;
}
