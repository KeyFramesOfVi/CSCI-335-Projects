i) All parts of the assignment were completed, following the comments in main.cpp, and being able to print all of the required output successfully. I also managed to use move assignment when transferring temp to whatever Chain that was called during the cin sections. Move Constructor was never used during this program, although I did not see a situation that called for it. Although I am not sure I had to test for it given the instructions of the assignment, some situations such as when () inputted instead of integers will cause the program to crash. Otherwise it doesn't seem like anything specific happens, and when the user inputs properly the program compiles properly.

ii) No bugs based on the instructions given were found. The only possible one if you were to do so is if you add too many numbers to both inputs, while all of the functions would work, at the very end of the function when destroying all of the pointers, it will actually crash, saying:


iii) When compiling on a Linux terminal, with the files on your home/user folder/folder where you put the files in your directory, you can simply write:
make all
./ChainProgram
		
iv) There are no input and output files for this program.



