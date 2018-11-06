#include <iostream>
#include "CopyFile.h"

int main(int argc, char* argv[]) {
	if(argc != 3) {
		std::cout << "Format: pathetic_excuses source_file to_file" << std::endl;
		return 1;
	}

	return !copyFile(argv[1], argv[2]);
}