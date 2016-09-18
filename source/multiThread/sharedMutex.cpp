
#include <boost/thread/shared_mutex.hpp>
#include <boost/format.hpp>
#include <string>
#include <map>
#include <thread>

std::mutex coutMutex;

class ThreadSafeMap
{
public:
    bool getString(int nKey, std::string& val)const
    {
        boost::shared_lock<boost::shared_mutex> lock(mutex_); //many thread can enter here, except  
        auto iter = m_map.find(nKey);
        if(iter!=m_map.end())
        {
            val = iter->second;
            return true;
        } 
        return false;
    }
    void setString(int nKey, const std::string& val)
    {
        std::lock_guard<boost::shared_mutex> lock(mutex_);
        m_map[nKey] = val;     
    }
protected:
    std::map<int , std::string> m_map;
    mutable boost::shared_mutex mutex_;
};

#define MAX_SIZE 10
void readThread(const ThreadSafeMap& m)
{
    for(int i=0;i<MAX_SIZE*10;i++)
    {
        int nrand = rand()%MAX_SIZE;
        std::string s;
        if( m.getString(nrand, s) )
        {    
            std::lock_guard<std::mutex> lk(coutMutex);
            boost::format fmtstr("thread %1% get %2% at %3%");
            fmtstr % std::this_thread::get_id() % s % nrand;
            std::cout<< fmtstr << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
void writeThread(ThreadSafeMap& m)
{
    for(int i=0;i<MAX_SIZE;i++)
    {
        std::string s = "h";
        m.setString(i, s);
        {
            std::lock_guard<std::mutex> lk(coutMutex);
            boost::format fmtstr("thread %1% set %2% at %3%");
            fmtstr % std::this_thread::get_id() % s % i;
            std::cout<< fmtstr << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main()
{
    ThreadSafeMap m;

    std::thread threadWrite(writeThread, std::ref(m));
    std::thread threadReader1(readThread, std::ref(m));
    std::thread threadReader2(readThread, std::ref(m));


    threadReader1.join();
    threadReader2.join();
    threadWrite.join();

    return 1;
}