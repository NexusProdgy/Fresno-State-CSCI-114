#include<iostream>
#include<fstream>
using namespace std;


//function to calculate of need instances
void calculateInstancesNeed(int need[10][10], int maxAllot[10][10],
    int rAllot[10][10], int p, int r)
{
    // Calculating Need of each Process 
    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
    
     need[i][j] = maxAllot[i][j] - rAllot[i][j];
}

// Function to find the system is in safe state or not  
void isSafeSystem(int process[], int rAvail[10], int maxAllot[][10], int rAllot[][10], int P, int R)
{
    int need[10][10];

    //calculate need matrix 
    calculateInstancesNeed(need, maxAllot, rAllot, P, R);


    bool finish[P] = { 0 };


    // To store safe sequence 
    int safeSeq[P];

    // Make a copy of available resources 
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = rAvail[i];

    // While all processes are not finished 
    // or system is not in safe state. 
    int count = 0;
    while (count < P)
    {
        // Find a process which is not finish and 
        // whose needs can be satisfied with current 
        // work[] resources. 
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            //check if a process is finished, 
           
            if (finish[p] == 0)
            { 
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                if (j == R)
                {
                    
                    for (int k = 0; k < R; k++)
                        work[k] += rAllot[p][k];

                    safeSeq[count++] = p;

                    finish[p] = 1;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe sequence. 
        if (found == false)
        {
            cout << "System is not in safe state";
            return;

        }
    }

    cout << "System is in safe state.\nSafe"
        " sequence is: ";
    for (int i = 0; i < P; i++)
        cout << safeSeq[i] << " ";
    return;
}
int main()
{
    ifstream ifile;
    int process[15]; //Process array of max size 15;

    int rAvail[10]; // available instances of resources
    int rAllot[10][10]; //alloted instances
    int maxAllot[10][10]; // maximum required instances of resources

    //read input file
    ifile.open("requests.txt");
    if (!ifile)
    {
        cout << "\nCan't open file";
        return 0;
    }
    int p, r;
    ifile >> p >> r; //read No of process and resources from requests.txt

    int i, j;

    //store process number to define sequence of safe processing
    for (i = 0; i < p; i++)
        process[i] = i;

    ifile >> rAvail[0] >> rAvail[1] >> rAvail[2]; //available instaces of resources

    //read alloted and maximum instances required of each resource
    for (i = 0; i < p; i++)
    {
        for (j = 0; j < r; j++)
        {
            ifile >> rAllot[i][j];

        }
        for (j = 0; j < r; j++)
        {
            ifile >> maxAllot[i][j];

        }
    }

    //function to find system is in safe state or not
    isSafeSystem(process, rAvail, maxAllot, rAllot, p, r);

    return 0;

}