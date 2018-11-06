#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

int main(int argc, char* argv[]) {
	if(argc != 2)
	{
		std::cout << "Format: pathetic_excuses file_name" << std::endl;
		return 1;
	}

	int hd = open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if(hd == -1)
	{
		std::cout << "Can`t open: " << argv[1] << " | Error: " << strerror(errno) << std::endl;
		return false;
	};

	int pipes[2];
	pipe(pipes);

	pid_t pid = fork();

	if(pid)
	{
		const int buf_size = 256;
		char buf[buf_size];
		
		int length;
		
		close(pipes[1]);
		
		while ((length = read(pipes[0], buf, buf_size)) != 0)
			write(hd, buf, length);

		char output[] = "Hello.";

		write(hd, output, sizeof(output) - 1);
		close(pipes[0]);
		close(hd);
	}
	else
	{
		char output[] = "Hi daddy, I’m your child.";

		close(pipes[0]);
		write(pipes[1], output, sizeof(output) - 1);
		close(pipes[1]);
	}
}
