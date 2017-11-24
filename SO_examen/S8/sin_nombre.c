#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>


void exitError(char buff[50])
{
	write(1,buff,strlen(buff));
	exit(1);
}


int main()
{
	int fds[2];
	int ret = pipe(fds);
	if (ret < 0) exitError("Error al crear pipe\n");

	char buff[8];
	
	if (ret < 0) exitError("Error al escribir\n");	

	ret = fork();
	if (ret < 0) 
	{	// error
		exitError("Error al crear hijo\n");
	}
	else if (ret == 0)
	{	//hijo
		dup2(fds[0],0);
		close(fds[0]);
		close(fds[1]);
		execlp("cat","cat",(char *)0);
	}
	else 
	{	//padre
		sprintf(buff,"Inicio\n");
		ret = write(fds[1],buff,strlen(buff));
		close(fds[0]);
		//close(fds[1]);

		waitpid(-1,NULL,0);
		sprintf(buff,"Fin\n");
		write(1,buff,strlen(buff));
		exit(0);
	}
}