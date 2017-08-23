#include <chrono>
#include <iostream>

class CCodeProfiler
{
public:
    typedef std::chrono::steady_clock clock;
    typedef std::chrono::duration<double, std::chrono::seconds::period> duration;
    typedef std::chrono::time_point<clock,duration> time_point;

    void start(){
        m_startT = clock::now();
    }
    duration end(){
        auto ret = clock::now() - m_startT;
        return ret;
    }
private:
    time_point m_startT;
};
