#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
	pid_t pid1,pid2,p;
	pid1 = fork();
	if(pid1>0)
		p=pid1;
	if(pid1 == 0){
		p=getpid();
		printf("Child %d\n",p);
		pid_t p1,p2;
		if((p1=fork()) == 0){
			printf("Childs's child %d parent %d\n",getpid(),p);
		}else if((p2=fork()) == 0){
			printf("Child's child %d parent %d\n",getpid(),p);
		}
		pid2=fork();
	}
	if(pid2>0)
		p=pid2;
	 if(pid2 == 0){
		p=getpid();
		printf("Child %d\n",p);
		pid_t p1,p2;
		pid_t p=getppid();
		if((p1=fork()) == 0){
			printf("Childs's child %d parent %d\n",getpid(),p);
		}else if((p2=fork()) == 0){
			printf("Child's child %d parent %d\n",getpid(),p);
		}
	}else{
		int s;
		wait(&s);
	}
}
