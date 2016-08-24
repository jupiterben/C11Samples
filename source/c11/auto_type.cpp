#include <vector>

struct BasicStruct
{
    int x;
    double y;
};

BasicStruct b{1,2};
BasicStruct get_struct()
{
    return {1,2};
}

class SequenceClass
{
public:
    SequenceClass(std::initializer_list<int> list){

    }
};
SequenceClass sc = {1,2,3};
std::vector<std::string> v = {"x","y","z"};

int main()
{
    std::vector<int> list;
    auto itrList = list.begin();
    return 1;
}