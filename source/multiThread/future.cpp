#include <future>
#include <iostream>

/*
each future object contains a flag to indicate the data is set .
promise shares the same flag.  
*/

int Accumlate(int start)
{
    std::cout<<"this thread id is "<<std::this_thread::get_id() << std::endl;
    auto startT = std::chrono::high_resolution_clock::now();
    
    for(int i=0;i<100;i++)
    {
        start += i;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::cout<<"add "<<i<<std::endl;
    }

    auto endT = std::chrono::high_resolution_clock::now();
    
using namespace std::chrono;
  
    duration<double, milliseconds::period> tSpan(endT - startT);
    std::cout << "use "<< tSpan.count() << "milliseconds" << std::endl; 

    return start;
}

void backThread(std::future<int>& f)
{
    try
    {
        std::cout<< f.get() << std::endl;
    }catch(std::exception& e)
    {
        std::cout<< e.what() << std::endl;
    }
   
}


void test()
{
    std::condition_variable cv;
    bool done;
    std::mutex m;
    auto wait_loop = [&]{
        auto const  timeout = std::chrono::steady_clock::now() + std::chrono::milliseconds(500);
        std::unique_lock<std::mutex> lk(m);
        while(!done){
            if(cv.wait_until(lk, timeout) == std::cv_status::timeout)
                break;
        }
        return done;
    };
    wait_loop();
}



int main()
{
    std::cout<<"main thread id is "<< std::this_thread::get_id() << std::endl;


    { //method 1
        auto future = std::async(std::launch::async,  Accumlate, 10);
        std::cout<<"get num " <<future.get()<<std::endl;       
    }
    { //method 2
        std::packaged_task<int(int)> task(Accumlate);
        auto future = task.get_future();
        std::thread t(std::move(task), 10);
        std::cout<<"get num " <<future.get()<<std::endl;       
        t.join();
    }
    { //use promise 
        std::promise<int> pm;
        auto future =  pm.get_future();
        std::thread t( backThread, std::ref(future) );
        try{
            pm.set_value(3);
        }
        catch(std::exception&){
            pm.set_exception(std::current_exception());
        }
        t.join();
    }
    
    return 1;
}