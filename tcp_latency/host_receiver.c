#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc,char *argv[])
{
	int fd,sfd,ret,n,sock;
	char buf[65536];
	socklen_t len;
	struct sockaddr_in cli;
	struct addrinfo addr,*res;
	struct timeval e;

	if(argc != 2){
		fprintf(stderr,"Usage: %s",argv[0]);
		return -1;
	}

	fd = open(argv[1],O_WRONLY | O_CREAT, 0600);
	if(fd < 0){
		perror("open");
		return -1;
	}

	memset(&addr,0,sizeof(addr));
	addr.ai_family = AF_INET;
	addr.ai_flags = AI_PASSIVE;
	addr.ai_socktype = SOCK_STREAM;

	ret = getaddrinfo(NULL,"12345",&addr,&res);
	if(ret != 0){
		printf("getaddrinfo\n");
	}

	sock = socket(res->ai_family,res->ai_socktype,0);
	if(fd < 0){
		perror("bind");
	}

	ret = bind(sock,res->ai_addr,res->ai_addrlen);
	if(ret != 0){
		perror("bind");
		return -1;
	}

	freeaddrinfo(res);

	listen(sock,5);

	len = sizeof(cli);
	sfd = accept(sock,(struct sockaddr *)&cli,&len);
	if(sfd < 0){
		perror("accept");
		return -1;
	}

	while((n = read(sfd,buf,sizeof(buf))) > 0){
		ret = write(fd,buf,n);
		if(ret < 1){
			perror("write");
			break;
		}

		gettimeofday(&e,NULL);
		printf("time = %lf\n", (e.tv_sec + e.tv_usec)*1.0E-6);

		printf("receive data from vm\n");
		break;
	}

	close(sfd);

	close(fd);

	return 0;
}
