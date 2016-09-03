#include <omp.h>
#include <chrono>
#include <iostream>
#include <array>


//sum up a int array 
template<class T>
void SumUp(const T& a )
{
    int sum = 0;
   
    int coreNum = omp_get_num_procs();//get the number of core
    int* sumArray = new int[coreNum];// 
    for (int i=0;i<coreNum;i++)//
        sumArray[i] = 0;
 #pragma omp parallel for
     for (int i=0;i<(int)a.size();i++)
     {
         int k = omp_get_thread_num();//获得每个线程的ID
         sumArray[k] = sumArray[k]+a[i];
     }
     for (int i = 0;i<coreNum;i++)
         sum = sum + sumArray[i];
     std::cout<<"sum: "<<sum<<std::endl;     
     delete []sumArray;
}

//sum up  array use reduction, 
//for each thread it will have a copy of sum , 
//at the end it add all sum together. +,-,*,&,|,&&,||
template<class T>
void SumUp2(const T& a )
{
    int sum = 0;   
     #pragma omp parallel for  reduction (+:sum)
     for (int i=0;i<(int)a.size();i++)
         sum += a[i];
     std::cout<<"sum: "<<sum<<std::endl;     
}
//get max number in the array, use critical to protect variant max
template<class T>
void MaxNum(const T& a )
{
    int max = 0;   
 #pragma omp parallel for 
     for (int i=0;i<(int)a.size();i++)
     {
         int temp = a[i];
         #pragma omp critical
         if(max < temp)
            max = temp
     }   
     std::cout<<"max: "<<max<<std::endl;     
}
//
void Section()
{
    #pragma omp parallel sections
    {
        #pragma omp section
        {

        }
        #pragma omp section
        {

        }
    }   
}
//task
void TaskGroup()
{
    #pragma omp taskgroup
    {
        for (int tmp = 0; tmp < 32; tmp++)
        { 
            #pragma omp task
            for (long l = tmp * 32; l < tmp * 32 + 32; l++)
            {
            }    
        }
    }
}

int main()
{
    
   auto tstart = std::chrono::steady_clock::now();

    std::array<int , 10000> array;
    int i=0;
    for(int& item : array)
    {
        item = i++;
    }
/*openmp code*/
    for(int i=0;i<1000;i++)
    {
         SumUp2(array);
    }   
/*open mp code end*/
   auto tend = std::chrono::steady_clock::now();
   auto duration = tend - tstart;
   std::cout<<"cost " << duration.count() << std::endl;
    return 1;
}