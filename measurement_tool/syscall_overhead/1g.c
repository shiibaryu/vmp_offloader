#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/time.h>

int main(int argc,char *argv[])
{
	int wfd,rfd,ret;
	struct timeval s,e;
	char buf[65356];

	if(argc != 3){
		printf("usage: wr rd \n");
		return -1;
	}

	rfd = open(argv[1],O_RDONLY | O_CREAT,0600);
	if(rfd < 0){
		perror("open");
		return -1;
	}

	wfd = open(argv[2],O_WRONLY | O_CREAT,0600);
	if(wfd < 0){
		perror("open");
		return -1;
	}

	gettimeofday(&s,NULL);

	while((read(rfd,buf,sizeof(buf)) >= 1)){
		ret = write(wfd,buf,sizeof(buf));
		if(ret < 1){
			perror("open");
			return -1;
		}
	}

	gettimeofday(&e,NULL);
	printf("time = %f\n", ((e.tv_sec-s.tv_sec) + ((e.tv_usec-s.tv_usec)/1000000.0)));

	return -1;
}
