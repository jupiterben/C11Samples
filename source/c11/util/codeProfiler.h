#include <chrono>
#include <iostream>

class CCodeProfiler
{
public:
    typedef std::chrono::duration<double, std::chrono::seconds::period> time_span;
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;


};

