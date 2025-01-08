# include<iostream>
# include<fstream>
#include<thread>
using namespace std;

int Matrix_A[50][50];
int Matrix_B[50][50];
int increment1=0, increment2=0;// help us with incrementing one everytime we go into the thread

void Matrix_C_worker(int M, int N, int K)
{

int Matrix_C[N][K];
int sum[50],Row[50];
int Coloumn[50];



for(int i=0; i <5;i++)
{
	for(int j=0; j <6; j++) 
	{
		for(int P =0 ; P< 5; P++)
		{
			
			Matrix_C[i][j]+= Matrix_A[i][P]*Matrix_B[P][j];
		//Matrix_C[0][0]+= (Matrix_A[i][j]*Matrix_B[j][i]);
		//cout << Matrix_A[i][P]<<  endl;
		//cout << Matrix_B[P][j] << endl << endl;	
		}
		
	}
	
}



int counter=0;

for(int i=0; i <5;i++)
{
	for(int j=0; j <6; j++) 
	{
		//cout << Matrix_C[i][j] << " ";
		//counter++;
		if(counter==6)
		{
			cout << endl;
			counter=0;
		}
		else
			continue;
		
	}
	
}

for(int i=0; i <5;i++)
{
	for(int j=0; j <6; j++) 
	{
		cout << "Row = " << Matrix_A[i][j] << " " ;
		cout << "Coloumn = " << Matrix_B[j][i] << endl; 
		counter++;
		if(counter==5)
		{
			counter =0; 
			cout << endl;
		}
		else 
			continue;
		
	}
	
}



cout << Matrix_A[1][0];
}

//to display Matrix_C;
void Matrix_A_worker(int M, int N)
{
	
	// open files and check
ifstream inFile_A;
inFile_A.open("A.txt");
	if(inFile_A.is_open())
		cout <<"Success in opening File A\n";
	else
		cout << "Failed to open A.txt\n";
	
	
	//store into 2d array
	
	//Store values from A.txt
	for(int i = 0; i < M; i++)
	{
	for(int j=0; j<N; j++)
		{
		inFile_A>> Matrix_A[i][j];
		}		
	}
	
	
	
	
	
	
//Display Matrix_A properly, then use it for C

	cout << "\n=====MATRIX A========\n";
	for(int i = 0; i < M; i++)
	{
	for(int j=0; j<N; j++)
		{
		cout <<  Matrix_A[i][j]<< " ";
		 if (j==(N-1))
		  cout << "\n";
	     else
		   continue;
			
		}		
	}
	
	
	
}

//matrix B thread
void Matrix_B_worker(int N, int K)
{
	
	
	ifstream inFile_B;
	inFile_B.open("B.txt");
	
	if(inFile_B.is_open())
		cout << "\n\n\nSuccess in opening B file";
	else
		cout << "Failed to open B file";
	
	
	//Store Values from B.txt
	for(int i = 0; i < N; i++)
	{
	for(int j=0; j<K; j++)
		{
		inFile_B>> Matrix_B[i][j];
		}		
	}
	
	
	
//Display Matrix_B properly, then use it for C
cout << "\n\n=====MATRIX B========\n";
	for(int i = 0; i < N; i++)
	{
	for(int j=0; j<K; j++)
		{
		cout <<  Matrix_B[i][j]<< " ";
		 if (j==(K-1))
		  cout << "\n";
	     else
		   continue;
			
		}		
	}
	
	
	
	
}


int main(int argc, char** argv)
{
	

	//store the values that comes after ./a.exe X Y Z
	int M, N, K;
	

	//convert argv[1],argv[2],argv[3] into int
	M= stoi(argv[1]);
	N= stoi(argv[2]);
	K= stoi(argv[3]);
	
	
	
	
	
	
	thread threadObj(Matrix_A_worker, M, N);
		threadObj.join();
	thread threadObj2(Matrix_B_worker, N, K);
	threadObj2.join();

	thread mainThread(Matrix_C_worker, M, N,K);
	mainThread.join();


	
	
	
	return 0;
}



/*

 12345
 23456
 65432
 54321



*/