/*Write a program that implements the FCFS disk-scheduling algorithms.
Your program will service a disk with 5,000 cylinders numbered 0 to 4,999
The program will generate a random series of 1,000 cylinder requests
and service them according to the algorithms.  The program will be passed the initial 
position of the disk head (as a parameter on the command  line) and report the total amount of head movement required by each algorithm
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

const int max_cylinders = 4999; // given disk with 5000 cylinders
const int num_requests = 1000; // number of cylinders requested

int main(int argc, char* argv[]) 
{
    // checking the command line arguments 
    if (argc != 2) {
        cerr << "Usage: ./Q6 <initial_head_position>" << endl;
        return 1;
    }

    int initial_head_position = atoi(argv[1]); // converting text from string to integer

    // ensuring input is valid
    if(initial_head_position < 0 || initial_head_position > max_cylinders) 
    {
        cout << "Initial head position must be between 0 and " << max_cylinders << "." << endl;
        return 1;
    }

    // generating random cylinder requests
    srand(time(0)); // seed for random number generator
    vector<int> requests(num_requests);

    // generate random requests (1000)
    for (int i = 0; i < num_requests; i++) 
    {
        requests[i] = rand() % (max_cylinders + 1); // random cylinder request between 0 and 4999
    }

    int total_head_movement = 0; // keeps track of head movements
    int current_position = initial_head_position; // ensures starting position of the head

    // FCFS implementation
    for(int i = 0; i < num_requests; i++) 
    {
        int movement = abs(current_position - requests[i]); // calculating movement from current position to requested cylinder
        total_head_movement += movement;// calculating head movement
        current_position = requests[i]; // move head to the requested cylinder
    }

    cout << "initial head position: " << initial_head_position << endl;

    cout << "Total head movement (FCFS): " << total_head_movement << endl; // outputs total head movement

    return 0; 

}