#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc,char *argv[])
{
	int ret,n,fd,sock;
	char buf[65536];
	struct addrinfo addr,*res;
	char *service = "12345";
	struct timeval s,e;

	if(argc != 3){
		fprintf(stderr,"Usage: %s hostname filename\n",argv[0]);
		return 1;
	}

	fd = open(argv[2],O_RDONLY);
	if(fd < 0){
		perror("open");
		return 1;
	}

	memset(&addr,0,sizeof(addr));
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_family = PF_UNSPEC;
	
	ret = getaddrinfo(argv[1],service,&addr,&res);
	if(ret != 0){
		printf("getaddrinfo");
		return 1;
	}

	sock = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
	if(sock < 0){
		perror("socket");
		return -1;
	}

	gettimeofday(&s,NULL);
	printf("time = %lf\n", (s.tv_sec + s.tv_usec)*1.0E-6);

	ret = connect(sock,res->ai_addr,res->ai_addrlen);
	if(ret != 0){
		close(sock);
		return -1;
	}

	freeaddrinfo(res);

	while((n = read(fd,buf,sizeof(buf)))>0){
		ret = write(sock,buf,n);
		if(ret < 1){
			perror("write");
			break;
		}

		printf("write data to host \n");
		break;
	}

	close(sock);

	return 0;
}
