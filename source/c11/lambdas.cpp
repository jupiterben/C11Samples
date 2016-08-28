
#include <functional>
#include <algorithm>
#include <vector>

using namespace std;
int main()
{

    int x = 0;
    //& means can visit all reference to scope variants
    auto func = [&](int n){ 
        x += 1;
    };

	std::vector<int> v;
	std::for_each(begin(v), end(v), func);
	//Fibonacci function
	std::function< int(int) > lfib = [&lfib](int n) {
        return n<2?1:lfib(n-1)+lfib(n-2);
	};

	int fib3 = lfib(3);

	std::function<int(int, double)> f = [](int, double) { return 1;  };
    return 1;
}