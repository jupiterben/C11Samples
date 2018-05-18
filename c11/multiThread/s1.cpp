

#include <thread>
#include <string>
#include <vector>
#include <iterator>
#include <numeric>
#include <list>
#include "../cpputil/util.h"

using namespace std;


void acculateSample();
void threadInitSample();


int main()
{
    acculateSample();
    return 1;    
}


template<typename Iterator, class T>
class accBlock
{
public:
    void operator()(Iterator b, Iterator e, T& result){
        result = std::accumulate(b,e, result);
    }
};

template<typename Iterator, class T>
T paralleAcc(Iterator first, Iterator last, T init)
{
    int nThreadNum = std::thread::hardware_concurrency();

    int nBlockSize = std::distance(first, last)/nThreadNum;

    auto blockStart = first;

    std::vector<std::thread> threadList(nThreadNum-1);
    std::vector<T> resultList(nThreadNum,0);

    for(int i=0;i<nThreadNum-1; ++i){
        auto blockEnd = blockStart;
        std::advance(blockEnd,nBlockSize);
        threadList[i] = std::thread( accBlock<Iterator,T>(), blockStart, blockEnd, 
            std::ref(resultList[i])
        );
        blockStart = blockEnd;
    }
    accBlock<Iterator,T>()(blockStart,last,resultList[nThreadNum-1]);
    for(auto& item : threadList){
        item.join();
    }

   return std::accumulate(resultList.begin(),resultList.end(),init);
}

void acculateSample()
{
   std::list<int> vList(10000000,1);

   int nRet = paralleAcc(vList.begin(),vList.end(),0);

   OUTPUT(nRet);
}

/////////
class Task
{
public:	
	void operator()() {}
	void doSomthing() {}
};
class Foo {};
void doTask(Foo& a)
{
}
void doTask2(const string & s) {}
void threadInitSample()
{
	//init with obj define
	thread tx{ Task() };
	thread tx2((Task()));

	{//init with class member
		Task a;
		thread t2(&Task::doSomthing, &a);
	}

	{//passing pararmeters,if want to pass ref use std::ref, otherwise the thread will copy it
		Foo a;
		thread t1(doTask, std::ref(a));
	}
	//need to 
	{
		char strbuf[1024];
		thread twrong(doTask2, strbuf);  //may crash , 
		thread tright(doTask2, string(strbuf)); //right
	}

}
