#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid1,pid2;

	if((pid1 = fork()) == 0){
		printf("Child %d\n",getpid());
		pid_t p1,p2;
		if((p1=fork()) == 0){
			printf("Childs's child %d\n",getpid());
		}else if((p2=fork()) == 0){
			printf("Child's child %d\n",getpid());
		}
	} else if((pid2=fork()) == 0){
		printf("Child %d\n",getpid());
		pid_t p1,p2;
		if((p1=fork()) == 0){
			printf("Childs's child %d\n",getpid());
		}else if((p2=fork()) == 0){
			printf("Child's child %d\n",getpid());
		}
	}else{
		int s;
		wait(&s);
	}
}
