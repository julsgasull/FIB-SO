#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error_y_exit(char *msg,int exit_status){
    perror(msg);
    exit(exit_status);
}

struct sigaction sa;
sigset_t mask;

void reset(int s){
    sigemptyset(&mask);
    sigaddset(&mask, s);
    sigprocmask(SIG_BLOCK,&mask, NULL);
    sa.sa_handler = SIG_DFL;
    sa.sa_flags = SA_RESETHAND;
    sigfillset(&sa.sa_mask);
    if (sigaction(s, &sa, NULL) < 0) error_y_exit("sigaction", 1);
}

int segundos = 0;
void funcion_alarma(int s){
    char buff[80];
    segundos++;

    // SIGUSR1
    if (s == SIGUSR1){
        segundos = 0;
        reset(s);
    }

    // SIGUSR2
    else if (s == SIGUSR2){
        sprintf(buff, "TIEMPO: %d segundos\n",segundos);
        write(1, buff, strlen(buff));
        reset(s);
    }

}
int main (int argc,char * argv[]){
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    sigprocmask(SIG_BLOCK,&mask, NULL);

    /* REPROGRAMAMOS EL SIGNAL SIGALRM Y SIGUSR1*/
    sa.sa_handler = &funcion_alarma;
    sa.sa_flags = SA_RESTART;
    sigfillset(&sa.sa_mask);

    if (sigaction(SIGALRM, &sa, NULL) < 0) error_y_exit("sigaction_SIGALRM", 1);
    if (sigaction(SIGUSR1, &sa, NULL) < 0) error_y_exit("sigaction_SIGUSR1", 1);
    if (sigaction(SIGUSR2, &sa, NULL) < 0) error_y_exit("sigaction_SIGUSR2", 1);

    while (1){
        alarm(1);
        sigfillset(&mask);
        sigdelset(&mask, SIGALRM);
        sigdelset(&mask, SIGUSR1);
        sigdelset(&mask, SIGUSR2);
	    sigdelset(&mask, SIGINT);
        sigsuspend(&mask);
    }
}
