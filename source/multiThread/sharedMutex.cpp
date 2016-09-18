
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
            return true;
        } 
        return false;
    }

protected:
    std::map<int , std::string> m_map;
    mutable boost::shared_mutex mutex_;
};

int main()
{
    


    return 1;
}