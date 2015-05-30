#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

struct sigaction interrupt;
struct sigaction qt;
struct sigaction stp;

int interruptFlag = 0;
int quit = 0;
int stop = 0;

void inthandle(int signum, siginfo_t *info, void *ptr ){
    interruptFlag = 1; 
}

void quithandle(int signum, siginfo_t *info, void *ptr ){
    quit = 1;
}

void stophandle(int signum, siginfo_t *info, void *ptr ){
    stop = 1;
}

int main(int argc, char **argv){
    int c,q,s = 0;
    interrupt.sa_sigaction = inthandle;
    interrupt.sa_flags = SA_SIGINFO;
    qt.sa_sigaction = quithandle;
    qt.sa_flags = SA_SIGINFO;
    stp.sa_sigaction = stophandle;
    stp.sa_flags = SA_SIGINFO;

    if(-1 == sigaction(SIGINT, &interrupt, NULL)){
        perror("sigaction");
        exit(0);
    }
    if(-1 == sigaction(SIGQUIT, &qt, NULL)){
        perror("sigaction");
        exit(0);
    }    
    if(-1 == sigaction(SIGTSTP, &stp, NULL)){
        perror("sigaction");
        exit(0);
    }

    while(1){
        if(interruptFlag){
            std::cout << "\nc" << std::endl;
            c++;
            interruptFlag =0;
        }
        if(quit){
            std::cout << "\n\\" << std::endl;
            q++;
            quit =0;
        }
        if(stop){
            std::cout << "\ns" << std::endl;
            s++;
            if(s!=3)
                raise(SIGSTOP);
            stop = 0;
        }

        if(s == 3){
            std::cout << "Interrupt was called: " << c << " times" << std::endl;
            std::cout << "Quit was called: " << q << " times" << std::endl;
            std::cout << "Stop was called: " << s << " times" << std::endl;
            return 0;
        }
        std::cout << "x" << std::endl;
        std::cout.flush();
        sleep(1);
    }
    return 0;
}
