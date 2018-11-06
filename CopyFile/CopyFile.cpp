#include <iostream>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sendfile.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

#include "CopyFile.h"

bool copyFile(const char* source, const char* copy) {
	int source_d;
	int copy_d;

	source_d = open(source, O_RDONLY);
	if(source_d == -1)
	{
		std::cout << "Can`t open " << source << " | Error: " << std::strerror(errno) << std::endl;
		return false;
	}

	struct stat s_stat;
	if(fstat(source_d, &s_stat) == -1)
	{
		std::cout << "Can`t get stat source file | Error: " << std::strerror(errno) << std::endl;
		close(source_d);
		return false;	
	}

	copy_d = open(copy, O_CREAT | O_WRONLY | O_TRUNC, s_stat.st_mode);
	
	if(copy_d == -1)
	{
		std::cout << "Can`t open " << copy << " | Error: " << std::strerror(errno) << std::endl;
		close(source_d);
		return false;
	}

	if(sendfile(copy_d, source_d, 0, s_stat.st_size) == -1)
	{
		std::cout << "Can`t copy | Error: " << std::strerror(errno) << std::endl;
		close(source_d);
		close(copy_d);
		return false;
	}

	close(source_d);
	close(copy_d);
	return true;
}
