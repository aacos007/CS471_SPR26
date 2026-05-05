/* Write a program using the fork() system call to do the following:
The  =parent process (main program) forks a process (CHILD 1) to compute and print the sum of 
the n natural numbers (1,2,3,…,n) where n is a variable shared between the parent and CHILD 1. 
It also forks another process (CHILD 2) that finds the sum of cubes (^3) of the  same first n natural 
numbers (1,2,3,…,n) where n is a variable it shares with the parent. Let CHILD 1 print “The sum of the 
first ** natural numbers is: ****”. Let CHILD 2 print “The  sum of the cubes of the first ** natural 
numbers is: ****”. Have the parent invoke the wait () call to wait for both the child processes to complete 
before exiting the program.  */

#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {

    int n; // variable shared with the parent

    cout << "enter a value for n: ";
    cin >> n; // getting input 

    pid_t pid1, pid2; //creating processID's for each child 

    // CHILD1 forking
    pid1 = fork();

    // for if the fork fails 
    if (pid1 < 0) 
    {
        cerr << "fork failed" << endl;
        return 1;
    }

    if (pid1 == 0) 
    {
        // computing the sum of first n natural numbers
        int sum = 0;
        for (int i = 1; i <= n; i++) 
        {
            sum += i;
        }

        cout << "The sum of the first " << n 
             << " natural numbers is: " << sum << endl;

        return 0;  // child exits so that it does NOT execute parent code
    }

    // CHILD2 forking
    pid2 = fork(); // creates CHILD2

    // for if the fork fails 
    if (pid2 < 0) 
    {
        cerr << "fork failed" << endl;
        return 1;
    }

    if (pid2 == 0) 
    {
        // compute sum of cubes of first n natural numbers
        int cubeSum = 0;
        for (int i = 1; i <= n; i++) 
        {
            cubeSum += i * i * i;
        }

        cout << "The sum of the cubes of the first " << n
             << " natural numbers is: " << cubeSum << endl;

        return 0;  // child exits
    }

    // parent waits for BOTH child process to complete 
    wait(NULL);
    wait(NULL);

    cout << "parent process has finished." << endl;

    return 0; // parent exits
}
