/*Write a program to implement LRU replacement policy. For simplicity,  assume  you are already given a set of page references for a process.
 Run the program and show  the output for a process assuming 3 frames (F0, F1, F2) allocated to this process. 
 The reference string is : 0, 3, 5, 1, 1, 2, 5, 4, 3, 2, 1, 2, 5, 4, 6, 7, 5, 4, 7,8, 9, 10, 5, 6, 10, 1, 2, 3.  
Show the output as:  
Page reference# Result Frame allocated to  
0 Page Fault F0  
3 Page Fault F1  
5 Page Fault F2  
1 Page Fault F0  
1 No Page Fault F0  
2 Page Fault F1  
5 No Page Fault F2  
4 Page Fault F0  
3 Page Fault F1  
2 Page Fault F2  
1 Page Fault F0  
2 No Page Fault F2  
… … …  
  
Total #of references:  
Total #of page faults:  
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    vector<int> referenceString = {0, 3, 5, 1, 1, 2, 5, 4, 3, 2, 1, 2, 5, 4, 6, 7, 5, 4, 7, 8, 9, 10, 5, 6, 10, 1, 2, 3}; // the given reference string
    int framesCount = 3; // the 3 frames - F0, F1, F2
    vector<int> frames;
    vector<int> lastUsed; // for tracking
    int pageFaults = 0; // initally page faults are 0

    cout << left << setw(17) << "Page reference#" 
         << setw(15) << "Result" 
         << setw(17) << "Frame allocated to" << endl;

    for (int i = 0; i < referenceString.size(); i++) 
    {
        int page = referenceString[i];
        auto it = find(frames.begin(), frames.end(), page);

        if (it != frames.end()) 
        {
            //  no page fault; page is already in frames/memory 
            cout << setw(15) << page << setw(15) << "No Page Fault";

            int frameIndex = distance(frames.begin(), it);
            cout << setw(15) << ("F" + to_string(frameIndex)) << endl;

            // updating order of LRU 
            auto lastIt = find(lastUsed.begin(), lastUsed.end(), frameIndex);
            lastUsed.erase(lastIt);
            lastUsed.push_back(frameIndex);
        } 
        else 
        {
            // a page fault is occuring
            pageFaults++;
            cout << setw(15) << page << setw(15) << "Page Fault";

            int frameIndex;
            if (frames.size() < framesCount) 
            {
                // now an empty frame is available
                frames.push_back(page);
                frameIndex = frames.size() - 1;
            } 
            else 
            {
                // we replace the least recently used page
                frameIndex = lastUsed.front(); // this is theoldest used frame
                lastUsed.erase(lastUsed.begin());
                frames[frameIndex] = page;
            }

            cout << setw(15) << ("F" + to_string(frameIndex)) << endl;
            lastUsed.push_back(frameIndex);
        }
    }

    cout << "\nTotal # of references: " << referenceString.size() << endl;
    cout << "Total # of page faults: " << pageFaults << endl;

    return 0;
}