#include <omp.h>
#include <chrono>
#include <iostream>

void test()
{
    int a = 0;
    for (int i=0;i<1000000000;i++)
       a++;
}


int main()
{
    
    auto tstart = std::chrono::steady_clock::now();
/*openmp code*/
 #pragma omp parallel for
   for (int i=0;i<8;i++)
        test();
/*open mp code end*/
   auto tend = std::chrono::steady_clock::now();
   auto duration = tend - tstart;
    return 1;
}