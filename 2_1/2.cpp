#include<iostream>
#include<sys/types.h>
#include<unistd.h>
using namespace std;

int main(){
    int pid = fork();
    if(pid>0){
        cout<<"Parent alive"<<endl;
        sleep(4);
    }
    else if(pid==0){
        cout<<"child "<<getpid()<<" parent "<<getppid()<<endl;
        int pd=fork();
        if(pd>0){
            cout<<"Parent dead"<<endl;
            cout<<"Child orphan"<<endl;
        }else if(pd==0){
            cout<<"child "<<getpid()<<" parent "<<getppid()<<endl;
            sleep(4);
            cout<<"Parent sleeping, so process is zombie"<<endl;
        }
    }
    return 0;
}