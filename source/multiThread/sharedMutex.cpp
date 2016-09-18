
#include <boost/thread/shared_mutex.hpp>
#include <string>
#include <map>
#include <thread>



class ThreadSafeMap
{
public:
    bool getString(int nKey, std::string& val)const
    {
        boost::shared_lock<boost::shared_mutex> lock(mutex_);
        auto iter = m_map.find(nKey);
        if(iter!=m_map.end())
        {
            val = iter->second;
            lock.unlock();
            std::cout<<"get string " << nKey << " : " << val << std::endl;
            return true;
        } 
        return false;
    }
    void setString(int nKey, const std::string& val)
    {
        std::lock_guard<boost::shared_mutex> lock(mutex_);
        m_map[nKey] = val;     
        std::cout<< "set string" << nKey << " : " << val << std::endl;
    }
protected:
    std::map<int , std::string> m_map;
    mutable boost::shared_mutex mutex_;
};

#define MAX_SIZE 1000
void readThread(const ThreadSafeMap& m)
{
    for(int i=0;i<MAX_SIZE*100;i++)
    {
        int nrand = rand()%MAX_SIZE;
        std::string s;
        m.getString(nrand, s);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
void writeThread(ThreadSafeMap& m)
{
    for(int i=0;i<MAX_SIZE;i++)
    {
        std::string s = "h";
        m.setString(i, s);
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