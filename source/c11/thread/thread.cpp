
#include <thread>
#include <iostream>
#include <chrono>


int main()
{
    auto threadtask = [](int threadId)
	{
        for(int i=0;i<100;i++)
        {
            std::cout<<"thread "<<threadId<<":"<<i<<std::endl;           
        }
    };
	
	//constructor
    std::thread t1(threadtask,1);
    std::thread t2(threadtask,2);
    std::thread t3;      //empty thread
    // move           
    std::thread t4(std::move(t1));   //
    t3 = std::move(t4);              //t3 will become t1
    
	//detach
    t3.detach();  //once thread is detached, the thread will not controlleble;

    //joinable 
    t1.joinable(); //true;
	t2.joinable();
	

	std::thread::hardware_concurrency();   //return the 

	//this thread
	std::this_thread::yield();
	std::this_thread::get_id();
	std::this_thread::sleep_for(std::chrono::nanoseconds(2));

	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::this_thread::sleep_until(now);

	//
	t1.native_handle();
	//swap
	swap(t1, t2);
	t1.swap(t2);
    //join : wait until execution finished.
    t1.join();
    t2.join();

    
    return 1;
}