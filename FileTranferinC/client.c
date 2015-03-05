#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <arpa/inet.h>
#define portno 5000
void error(const char *msg)
{
	perror(msg);
exit(0);
}
int main(int argc, char *argv[])
{
	int sockfd, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	int bytesReceived = 0;
	char recvBuff[256];
	char buffer[256];
	while(1){
	//portno = atoi(argv[1]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	server = gethostbyname("localhost");
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		exit(0);
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
	(char *)&serv_addr.sin_addr.s_addr,
	server->h_length);
	serv_addr.sin_port = htons(portno);
	printf("\nprompt> C: Connecting...");
	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
	error("ERROR connecting");
	else
	printf("\nprompt> C: Connected.");
	printf("\nprompt> S: Hello. This is your server at X.X.X.X. Please enter the name of the file you want to search: abc.txt\n");
	bzero(buffer,256);
	fgets(buffer,255,stdin);
	//printf("\nprompt> S: Searching... ");
	n = write(sockfd,buffer,strlen(buffer));
	if (n < 0)
		error("ERROR writing to socket");
		bzero(buffer,256);
		n = read(sockfd,buffer,255);
	if (n < 0)
		error("ERROR reading from socket");
		//printf("\nprompt> S: Following files match the criteria:\n");
		printf("%s\n",buffer);
	if(strcmp(buffer,"")==0)
	{
		continue;
	}
		printf("\nMake your selection:\n");
		bzero(buffer,256);
		//fgets(buffer,255,stdin);
		//printf("\nprompt> S: Getting ready to transfer file");
		//n = write(sockfd,buffer,strlen(buffer));
		printf("\nprompt> C: Ready\nprompt> C: receiving…");
		FILE *fp;
		fp = fopen("sample_fil2.txt", "ab");
		if(NULL == fp)
		{
			printf("Error opening file");
			return 1;
		}
		//memset(recvBuff, '0', sizeof(recvBuff));
		/* Receive data in chunks of 256 bytes */
		while((bytesReceived = read(sockfd, recvBuff, 256)) > 0)
		{
			printf("Bytes received %d\n",bytesReceived);
			// recvBuff[n] = 0;
			//printf("%s\n",recvBuff);
			fwrite(recvBuff, 1,bytesReceived,fp);
			// printf("%s \n", recvBuff);
			if(bytesReceived < 0)
		{
			printf("\n Read Error \n");
		}
		}
		fflush(fp);
		fclose(fp);
		printf("\nprompt> C: File received and saved at sample_file1.txt\n");
		}
	close(sockfd);
	return 0;
}
