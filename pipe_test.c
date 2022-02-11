# include <fcntl.h>
# include "string.h"
# include <unistd.h>

int main()
{
	int pipe_fds[2];
	pipe(pipe_fds);

	printf("Antes de redirecionar...\n");
	int file_fd = open("whatever", O_RDWR);

	char buffer[1024];
	int read_return; 
	
	dup2(pipe_fds[1], STDOUT_FILENO);	// Taquei stdout na saída do cano
	printf("oi!\n");					// Escrevi no cano
	close(pipe_fds[1]);					// Fechei a saída do cano
	read_return = read(pipe_fds[0], buffer, 1024); // Li do cano
	close(pipe_fds[0]);					// Fechei a entrada do cano (ja li né)
	write(file_fd, buffer, strlen(buffer)); // Escrevi do buffer (lido do cano 🎉)
	
	exit(0);
}
	