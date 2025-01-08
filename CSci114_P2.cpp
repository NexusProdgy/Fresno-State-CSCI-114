/*
=============Instructions to run in cygwin =============

**************this cpp should can only run in cygwin, visual studio, etc doesn't recognize fork() as a function

Assuming you have put the file : CSci114_P2 into your folder containing cygwin
steps:

1.  Open CSci114_P1.cpp and edit line with inFile.open, only "H.docx" part to the type and name of the file
    we will be using

    save and exit once the change has been done

2. Run Cygwin then type "g++ CSci114_P1.cpp" without quatation marks, and a space between g++ and CSci

3. after the second step, we execute the program by doing this:      ./a.exe
    a.exe is the excution, but we need ./ before it.
    Also, typing:        ls         allows us to bring up the files in the folder

4. After running ./a.exe, and typing ls, we will see a  "data.out"      file

    type in the terminal : mv data.out sample.docx
    after that  visit your folder containing the new file, we should be able to open the file

    NOTE: sample.docx will now be a copy of the original file, so we could have named it anything.
        Such as : apple.docx        dog.docx

        if the file we are reading from is a pdf, then it would be sample.pdf

**************************Problems with program****************************************
1. program copies what is needed, but when doing mv, it gets corrupted

2. data.in causes error called stack dump 
*/

#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <sys/wait.h>   /* Wait for Process Termination */
#include <stdlib.h>     /* General Utilities */
#include<iostream>
#include<fstream>

int A_to_B[2];
char * memory;
char * memory2;

using namespace std;
int main()
{
	int status;
	ifstream inFile;
	ofstream outFile;
	pipe(A_to_B);
	streampos size,size2;
	
	//creating process A
	inFile.open("data.in", ios::in|ios::binary|ios::ate);
		size= inFile.tellg();
		memory=new char[size];
	if(fork()==0)
	{
		cout << "In PA\n";
		close(A_to_B[0]);
		
		//inFile.seekg(0, ios::end);
		
		
		//while(!inFile.eof()){
		inFile.read(memory,size);
			 write(A_to_B[1], memory, size);
			sleep(1);
		//}
		inFile.close();
		return 0;
	}
	
	
	if(fork()==0)
	{
		cout << "In PB\n";
		close(A_to_B[1]);
		//sleep(1);
		memory2= new  char[size];
		outFile.open("data.out", ios::out|ios::binary| ios::trunc);
		read(A_to_B[0],memory,size);
		/*
		for(int j=0; j< 10; j++)
		{
			sleep(1);
			int nbytes = read(A_to_B[0], memory2, sizeof(10));
			printf("PB bytes:%d \n", nbytes);
		}
*/			
	write(A_to_B[1],memory2,size2);
	outFile.write(memory2,size2);
	outFile.close();
	return (0);
	
	}


delete [] memory ;
delete [] memory2;
	
	wait(&status);
	wait(&status);
	cout << "Finished";
	return 0;
	
	
	
	
}