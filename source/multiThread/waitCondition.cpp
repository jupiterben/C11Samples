#include <deque>
#include <thread>
#include <mutex>
#include <string>
#include <iostream>

std::mutex mt;
std::condition_variable cond;
std::deque<char> myQueue;

void popDataThread()
{
    while(true)
    {
        std::unique_lock<std::mutex> lk(mt);
        cond.wait(lk, [&]{ return !myQueue.empty(); });
        char ch = myQueue.front();
        myQueue.pop_front();
        lk.unlock();
        if(ch=='@')
            break;
        std::cout<<"pop char "<<ch << std::endl;
    }
}

void pushDataThread()
{
    std::string s = "hello world!@";
    for(size_t i=0;i<s.length();i++)
    {
        std::unique_lock<std::mutex> lk(mt);
        myQueue.push_back(s.at(i));
        lk.unlock();
        cond.notify_one();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}



int main()
{
    
    std::thread thread1(pushDataThread);
    std::thread thread2(popDataThread);



    thread1.join();
    thread2.join();

    return 1;
}