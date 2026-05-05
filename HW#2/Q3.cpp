/* Write a program for two threads to share a single resource (e.g., a license). Use  Peterson’s solution to 
implement it. Each thread independently requests for the resource, but only one  thread at a time can get it. 
Once a thread gets the resource, it keeps it for a random time, and releases it.  Then, if another thread is waiting 
on it, it will get it. Here, the variables turn, flag1 and flag2 are shared  variables. Variable turn is set by either 
thread. Variable flag1 is set by thread 1 and flag2 by thread2. Let  each thread request and release the resource 3 times, 
each time holding it for a random time and releasing  it. Write the program in any language of your choice provided it 
allows you to create threads. Output  should look something like this.  
  
Time: 3:01:021.50 Thread 1 requested the resource 
Time: 3:01:021.54 Thread 1 received the resource  
Time: 3:01:025.01 Thread 2 requested the resource  
Time: 3:01:032.26 Thread 1 released the resource  
Time: 3:01:032.28 Thread 2 received the resource  
Time: 3:01:040.12 Thread 1 requested the resource  
Time: 3:01:040.36 Thread 2 released the resource  */

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

using namespace std;

// the shared variables for Peterson's solution
bool flag[2] = {false, false}; 
int turn;

// randomDelay functions to simulate (random) holding time
void randomDelay()
{
    int delay = rand() % 3 + 1; // random delay between 1 and 3 seconds 
    this_thread::sleep_for(chrono::milliseconds(delay));
}

// threadFunction, as the name suggests, will be the function that each thread executes
void threadFunction(int threadID)
{
    int other = 1 - threadID; // the ID of the other thread

    for(int i = 0; i < 3; i++) 
    {
        cout << "Thread" << threadID + 1 << " requested the resource" << endl;

        //?Peterson's algorithm starts now
        // entry section 
        flag[threadID] = true; // this thread wants to enter the critical section
        turn = other; 

        while(flag[other] && turn == other) 
            ; // wait 

        // critical section 
        cout << "Thread" << threadID + 1 << " received the resource" << endl;
        randomDelay(); // simulating holding the resource for a random time
        cout << "Thread" << threadID + 1 << " released the resource" << endl;

        // exit section 
        flag[threadID] = false; // thread is leaving the critical section
        randomDelay(); // simulating some time again, before the next request
    }
}

// main function
int main() 
{
    srand(time(0)); 

    thread t1(threadFunction, 0); // creating thread 1
    thread t2(threadFunction, 1); // creating thread 2

    t1.join(); // waits for thread 1 to finish
    t2.join(); // waits for thread 2 to finish

    return 0;
}