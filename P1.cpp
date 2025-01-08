/*

In order to run program, assuming cpp file is put directly in cygwin location.
if you can't find proper path, please open cywgin terminal, and copy this line to it, it'll find the path,
so just follow and put the file there: cygpath -w ~

=============== Steps to run cygwin and program======================
1.Use any type of file : docx,pdf,etc, and put it in the directory where the cpp is at.

2. open cygwin terminal, and FIRSTLY, convert the file you chose to "data.in" file
		this can be done by this command, which you can copy : mv (Your file choice) data.in 
		example of mv (Your file) command -> mv sample.docx data.in
		sample is the file i am using, docx is the type, if using pdf, should be sample.pdf
		
		**** You'll notice in your folder that your file you chose , is now a data.in file *****
	
3. Return to your cygwin terminal, and use command  g++ with the cpp file name inbetween like this: g++ CSci114_P1.cpp
	after running this, you'll notice in the folder that a executable was created named: a.exec
	
	**** we can name our executable and run our cpp in one line by doing:  g++ -o P1 CSci114_P1.cpp
	this will create a P1.exe, which we can run the way as step 4, but by replacing a.exe, with our name.
	
4. run a.exe with this command : ./a.exe


5. A data.out file should have been created, which we can open by right clicking file, then hovering to open with
	while choosing what to use to open. 
	
	






*/

#include<iostream>
#include <fstream>
using namespace std;
int main()
{
	ifstream inFile;
	ofstream outFile;
	streampos sizeFile,begin, end;
	char * memory;
	int size;
	
	// should open file
	inFile.open("data.in", ios::in | ios::binary | ios::ate);// ate and trunc are needed in order to work properly, otherwise writes nothing
	
	//check if file is open properly
	if(inFile.is_open())
	{
		cout << "Success in opening file";
		begin=inFile.tellg();
		
		inFile.seekg(0,ios::beg);
		
		sizeFile=inFile.tellg();
		
		memory = new char [sizeFile];
		
		
		end=inFile.tellg();
		//cout << "Size of " << sizeof(memory);
		

	}
	else
	{
		cout << "Failure in opening file";
		exit(0); // forces the program to stop since there's nothing to do if it cant open
	}
	
	inFile.read(memory,sizeFile);
	outFile.open("data.out", ios::binary| ios::out| ios::trunc);

	if(outFile.is_open())
	{
		outFile.write(memory,sizeFile);	
		cout << "\nWriting....";
		
	
	}
	else 
	{
		cout << "Failed to open";
	}

	
	

	//close files
	inFile.close();
	outFile.close();
	
	cout << "Finished";
	return 0;
}