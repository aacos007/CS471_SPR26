/* Modify your program from Question 8 to also implement the FIFO (First In, First-Out) page replacement policy. 
Use the same reference string and assume the process is  allocated 3 frames (F0, F1, F2) and compare total page faults*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

int main() {
    vector<int> referenceString = {0, 3, 5, 1, 1, 2, 5, 4, 3, 2, 1, 2, 5, 4, 6, 7, 5, 4, 7, 8, 9, 10, 5, 6, 10, 1, 2, 3};
    int framesCount = 3; // the 3 frames - F0, F1, F2

    vector<int> FIFOframes;       // stores the pages in frames
    vector<int> FIFOorder;        // tracks the order of insertion for FIFO
    int fifoPageFaults = 0;

    cout << left << setw(17) << "Page reference#" 
         << setw(15) << "Result" 
         << setw(17) << "Frame allocated to" << endl;

    for (int i = 0; i < referenceString.size(); i++) 
    {
        int page = referenceString[i];
        auto it = find(FIFOframes.begin(), FIFOframes.end(), page);

        if (it != FIFOframes.end()) 
        {
            // no page fault is occuring
            cout << setw(15) << page << setw(15) << "No Page Fault";
            int frameIndex = distance(FIFOframes.begin(), it);
            cout << setw(15) <<"F" << frameIndex << endl;
        } 
        else 
        {
            // a page fault is occuring
            fifoPageFaults++;
            cout << setw(15) << page << setw(15) << "Page Fault";

            int frameIndex;
            if (FIFOframes.size() < framesCount) {
                // now an empty frame is available
                FIFOframes.push_back(page);
                frameIndex = FIFOframes.size() - 1;
                FIFOorder.push_back(frameIndex); // track order
            } else {
                // we replace the oldest page in FIFO
                frameIndex = FIFOorder.front();
                FIFOorder.erase(FIFOorder.begin());
                FIFOframes[frameIndex] = page;
                FIFOorder.push_back(frameIndex);
            }

            cout << setw(15) <<  "F" << frameIndex << endl;
        }
    }

    cout << "\nTotal # of references: " << referenceString.size() << endl;
    cout << "Total # of page faults: " << fifoPageFaults << endl;

    return 0;
}