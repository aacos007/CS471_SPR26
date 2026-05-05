/* Write a multithreaded program that outputs prime numbers. This
program should work as follows: The user will run the program and will 
enter a number on the command line. The program will then create a separate 
thread that outputs all the prime numbers less than or equal to the number 
entered by the user. Run and submit your code and output screenshot of the program. */

#include <iostream>
#include <thread>
#include <cmath>

using namespace std; 

// isPrime function will check whether or not a number is prime
bool isPrime(int num) {
    if(num < 2) return false; // the only numbers less than 2, 0 and 1, are not prime numbers
    for(int i = 2; i <= sqrt(num); i++) {
        if(num % i == 0) return false; // any number that is divisible is not a prime number
    }
    return true; // if it passes the above checks (not divisble and isn't the number 0 or 1), it's a prime number
}

// printPrimeNumbers function will print all prime numbers less than or equal to n that were entered by the user
// note: this function runs in a seperate thread 
void printPrimeNumbers(int n)
{
    for(int i = 2; i <= n; i++) {
        if(isPrime(i)) // checks if the nubmer is prime
        {
            cout << i << endl; // if the number is prime, it will be printed in the output 
        }
    }
}

// main fuction
int main(int argc, char* argv[])
{
    if(argc !=2) // ensures that exactly 1 argument was provided by the user 
    {
        cout << "Usage: " << argv[0] << " <number>" << endl; 
        return 1;
    }

    int n = stoi(argv[1]); // converting the argument (entered by the user) from a string to an integer

    thread primeThread(printPrimeNumbers, n); // creating a thread which runs printPrimeNumbers function with n being the argument

    primeThread.join(); // waiting for the thread to finish before exiting the program

    return 0;
}