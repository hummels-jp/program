#include <iostream>
#include <omp.h>
using namespace std;

int main() 
{
    // Set the number of threads to 4

    int nthreads, tid;

    // Set the number of threads to 4
    omp_set_num_threads(4);
    // Parallel region
    // Each thread will execute the code inside the parallel region
    #pragma omp parallel private(nthreads, tid)
    {
        tid = omp_get_thread_num();
        cout << "Hello World from thread " << tid << endl;

        if (tid == 0) {
            nthreads = omp_get_num_threads();
            cout << "Number of threads = " << nthreads << endl;
        }
    } // implicit barrier here

    return 0;
}