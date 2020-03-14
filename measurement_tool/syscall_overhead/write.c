#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc,char *argv[])
{
	int fd,ret;
	struct timeval s,e;
	char *buf = "aaaaaaaaaaaaaaaaa";

	if(argc != 2){
		printf("usage\n");
		return -1;
	}

	gettimeofday(&s,NULL);

	fd = open(argv[1],O_WRONLY | O_CREAT,0600);
	if(fd < 0){
		perror("open");
		return -1;
	}

	ret = write(fd,buf,sizeof(buf));
	if(ret < 1){
		perror("write");
		return -1;
	}

	gettimeofday(&e,NULL);
	printf("time = %f\n", ((e.tv_sec-s.tv_sec) + ((e.tv_usec-s.tv_usec)/1000000.0)));

	return -1;
}
