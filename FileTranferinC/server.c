#include <dirent.h>
#include <sys/types.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define portno 5000
char str_Mohsin[1024];
int t=1;
char paths[100][100];
int counter=0;
int walker( char *searching, char *result ) {
	DIR *d;
	char sq[15];
	char sw[50];
	struct dirent *dir;
	struct stat st;
	int size = 0;
	d = opendir( "." );
	strcmp( result, "" );
	//strcpy(str_Mohsin,"");
	if( d == NULL ) {
		return 1;
	}
	while( ( dir = readdir( d ) ) ) {
		if( strcmp( dir->d_name, "." ) == 0 || strcmp( dir->d_name, ".." ) == 0 ) {
		continue;
	}
	//printf("\n %s\t\t\t\t%s\t\t\t\t%s", getcwd(NULL,MAXPATHLEN), dir->d_name,searching);
	if( dir->d_type == DT_DIR ) {
	//printf("\n d_type : %s",DT_DIR);
	chdir( dir->d_name );
	walker( searching, result );
	chdir( ".." );
	//printf("danyal\n");
	} else {
	//printf("%s string read",str_Mohsin);
	//printf("welcome!!! \t\t %s\t\t %s\n",dir->d_name, searching);
	if( strcmp( dir->d_name, searching ) == 0 ) {
		int len;
		//printf("d_name : %s\n",dir->d_name);
		getcwd( result, MAXPATHLEN );
		len = strlen( result );
		snprintf( result + len, MAXPATHLEN - len, "/%s", dir->d_name );
		sprintf(sq, "%d : ", t);
		strcat(str_Mohsin,sq);
		strcat(str_Mohsin,result);
		strcpy(paths[counter],result);
		stat(result, &st);
		size = st.st_size;
		sprintf(sw, " : %d", size);
		strcat(str_Mohsin," size");
		strcat(str_Mohsin,sw);
		strcat(str_Mohsin," Bytes");
		//printf("\nfile size%d\n",size);
		counter++;
		strcat(str_Mohsin,"\n");
	//sprintf( str_Mohsin, str_Mohsin+result );
		t++;
		//printf("%d\n",t);
	}
	}
}
	//printf("string mohsin %s\n",result);
	closedir( d );
	return *result == 0;
}


void error(const char *msg)
{
	perror(msg);
	exit(1);
}
int main(int argc, char *argv[])
{
	int sockfd, newsockfd,size=0;
	struct stat st;
		char sq[15];
	char sw[50];
	socklen_t clilen;
	char buffer[1024];
	char search[1024];
	//char buf[MAXPATHLEN] = { 0 };
	char buf[2000] = { 0 };
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
		bzero((char *) &serv_addr, sizeof(serv_addr));
		serv_addr.sin_family = AF_INET;
		serv_addr.sin_addr.s_addr = INADDR_ANY;
		serv_addr.sin_port = htons(portno);
		if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
			error("ERROR on binding");
		while(1){
			listen(sockfd,5);
			clilen = sizeof(cli_addr);
			newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
			if (newsockfd < 0)
				error("ERROR on accept");
				bzero(buffer,256);
				n = read(newsockfd,buffer,100);
			if (n < 0) error("ERROR reading from socket");
				printf("Here is the message: %s",buffer);
				strcpy(search , buffer);
				printf("searching for %s", search);
				const char s[2] = "\n";
				char *token;
			/* get the first token */
			token = strtok(buffer, s);
			/*if( walker(token, buf ) == 0 ) {
				printf( "Found: %s\n", buf );
				//printf("Paths %s\n",str_Mohsin);
			} else {
				printf( "Not found \n" );
			}*/
			/*if(strcmp(buf,"")==0){
			n = write(newsockfd,"File not Found",18);
			}else{*/
			//printf("\nmohsin string %s\n",str_Mohsin);
						
			stat(token, &st);
			size = st.st_size;
			sprintf(sw, " : %d", size);
			strcat(str_Mohsin," size");
			strcat(str_Mohsin,sw);
			strcat(str_Mohsin," Bytes");
			strcpy(buf,str_Mohsin);
				n = write(newsockfd,buf,255);
			strcpy(buf,"");
			//}
			if (n < 0) error("ERROR writing to socket");
			//n = read(newsockfd,buffer,255);
			/*if (n < 0) error("ERROR reading from socket");
				printf("Your selection is: %s",buffer);
			int b;
			b= atoi(buffer);*/


			FILE *fp = fopen(token,"rb");
			if(fp==NULL)
			{
				printf("File opern error");
				return 1;
			}
			while(1)
			{
				/* First read file in chunks of 256 bytes */
				unsigned char buff[256]={0};
				int nread = fread(buff,1,256,fp);
				printf("Bytes read %d \n", nread);
				/* If read was success, send data. */
				if(nread > 0)
				{
					printf("Sending \n");
					write(newsockfd, buff, nread);
				}
				/*
					* There is something tricky going on with read ..
					* Either there was error, or we reached end of file.
				*/
				if (nread < 256)
				{
					if (feof(fp))
					break;
					if (ferror(fp))
						printf("Error reading\n");
	break;
				}
			}
				int i=0;
			for(i=0;i<5;i++){
				printf("%s\n",paths[i]);
			}
			strcpy(str_Mohsin,"");
			t=1;
			counter=0;
			close(newsockfd);
			}
				close(sockfd);
			return 0;
	}
