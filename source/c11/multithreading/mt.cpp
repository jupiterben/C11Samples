#include <atomic>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <iostream>



std::recursive_mutex countMutex;



int main()
{
    auto threadtask = [](int threadId)
	{
        for(int i=0;i<100;i++)
        {
			std::unique_lock<std::recursive_mutex> lock(countMutex);
			countMutex.lock();
            std::cout<<"thread "<<threadId<<":"<<i<<std::endl;
			countMutex.unlock();
			lock;
        }
    };

	
    std::thread t1(threadtask,1);
    std::thread t2(threadtask,2);
	std::thread t = std::move(t1);
	
	

	if(t1.joinable())
		t1.join();
    if(t2.joinable())
		t2.join();
	
    
    return 1;
}