/* Modify and run the program shown below in the following way. 
There  is an array of 20 elements defined in the program. 
The elements of the array are:  [20 18 16 14 12 10 8 6 4 2 -20 -18 -16 -14 -12 -10 -8 -6 -4 -2]. 
Thread 1 adds the first four  elements [20, 18, 16, 14], Thread 2 adds the next four elements [12,10, 8, 6], …, 
Thread 5 adds  the last four elements [-8, -6, -4, -2]. Finally, the sum of all the 20 elements is printed by 
the  main program. The parent must wait for all threads to complete before printing the output. 
Run and show the output. */

// GIVEN CODE:
#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 
#define NUM_THREADS 5 // @CHANGED - changed from 3 to 5; because the array contains 20 elements and each thread must handle 4 elements; so,20 elements / 4 per thread = 5 threads

//int counter = 1; // @CHANGED - this counter variable is removed because we are not changing or making modifications to a shared counter, instead we are summing the elements of an array 

// @CHANGED - this array is added to the code; it is the 20 element array that was given to us
int arr[20] = {20, 18, 16, 14,
               12, 10, 8, 6,
               4, 2, -20, -18,
               -16, -14, -12, -10,
               -8, -6, -4, -2};

int partial_sums[NUM_THREADS];  // @CHANGED - this array is added to store the each threads sum; helps with preventing race condition!
              

/*void* PrintHello(void* threadid) 
{ 
    counter = 2 * counter + (int)threadid; 
    printf("\n Thread Id: %d Counter: %d\n", threadid, counter); 
    pthread_exit(NULL); 
} */ // @CHANGED - this is removed and replaced with the function below which sums the elements of the array

void* sumArray(void* threadid)
{
    long tid = (long)threadid;

    int start = tid * 4; // calculate starting index
    int end = start + 4; // calculate ending index

    partial_sums[tid] = 0; // initializing the sum

    for (int i = start; i < end; i++)
    {
        partial_sums[tid] += arr[i];  // sum array values together 
    }

    printf("thread %ld computed sum: %d\n", tid, partial_sums[tid]);

    pthread_exit(NULL);
}

int main(int argc, char* argv[]) 
{ 
    pthread_t threads[NUM_THREADS]; 
    int rc;
    long t; 

    for (t = 0; t < NUM_THREADS; t++) 
    { 
        printf("Creating thread %d\n", t); 
        // rc = pthread_create(&threads[t], NULL, PrintHello, (void*)t); // @CHANGED - the only thing changed in this line is which function is being called (remember that PrintHello was removed & replaced with sumArray)
        rc = pthread_create(&threads[t], NULL, sumArray, (void*)t);
        if (rc) 
        { 
            printf("ERROR; return code from pthread_create() is %d\n", rc); 
            exit(1); 
        } 
    } 

    // printf("\n Counter: %d\n", counter); // @CHANGED - removed since counter no longer exists; parent is waiting for all threads 
    
    for (t = 0; t < NUM_THREADS; t++) // @CHANGED - added to ensure synchronization
    {
        pthread_join(threads[t], NULL); // @CHANGED - added to ensure synchronization
    }

    // @CHANGED - added to compute the final total 
    int total = 0;

    for (t = 0; t < NUM_THREADS; t++)
    {
        total += partial_sums[t];
    }

    printf("\nFinal Sum of all 20 elements: %d\n", total);
}
// my changes are dentoed with comments containing "@CHANGED" in the comments


