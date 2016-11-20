
/*----------
alias template kind of like typedef, 
using : right to left  and can be template , more 
typedef : left to right 
----------*/
template<class T> using ptr = T* ;
template<class T> using mystring = std::basic_string<T, std::char_traits<T> >;
void aliasTemplate()
{
    ptr<int> x;    //int * x;
    mystring<char> str;
    //same as typdef 
    using myfunc = void(int,int);
    typedef void (&myfuncp)(int,int);
}
/*----------
Data Structure Alignment
align of , 
alignas : can only expand
----------*/
template <size_t s>
struct alignas(s) mystruct
{
    char a;
    int b;
    long long c;
};

#pragma pack(1)
struct mystructPack
{
    char a;
    int b;
    long long c;
};
#pragma pack()

void testAlignof()
{
    OUTPUT( alignof(mystructPack) );
    OUTPUT( sizeof(mystructPack) );

    using mystructN = mystruct<8>;
    OUTPUT( alignof(mystructN) );
    OUTPUT( sizeof(mystructN) );
    offsetof(mystructN, a);
}

/* -----  initializer_list -------*/
class MyClassInit
{
public: 
    template<class T>
    MyClassInit(std::initializer_list<T> t){ }
};
void testInitializerList()
{
    mystructPack mys{'c',1,1}; //init struct with list
    auto initlist = {1,2,3};
    std::vector<int> vlist = initlist;
    MyClassInit myCls(initlist);
    std::map<int, std::string> myMap = {
        {1,"a"},{2,"b"},
    };
}
/*----------- final ovveride
final :
override:
 ------- */
class BaseA
{
    virtual void f1(int) final;
    virtual void f1(float);
    virtual void f2(int );
};
class DerivedA : public BaseA
{
    //void f1(int);  //error 
    void f1(float) override;
    void f2(int) override ; //
};
/*------- range for -----------*/
void testRangeFor()
{
    std::vector<int> vList= {1,2,3};
    for(auto& item : vList )
    {
        item = 1;
    }
    std::map<int,std::string> vmap;
    for(auto& item : vmap ){
        if(1==item.first)
            item.second = "s";
    }
}
/*---------strong enums, add class -------*/
class Animal{
public:
    enum class sType{ _dog, _cat, }; //strong type
    enum wType{ _d, _c }; //weak type 
};
void testStrongEnums(){
    Animal::sType t =  Animal::sType::_dog;
    int it;
    //it = t;//error
    Animal::wType wt = Animal::_d;
    it  = wt;
}
/*-------- lambda ----------*/
void testLambda()
{
    //Fibonacci function
	std::function< int(int) > lfib = [&lfib](int n) {
        return n<2?1:lfib(n-1)+lfib(n-2);
	};
    OUTPUT(lfib(3));
    //sample lambda function
    std::function< int(double,double) > lf = [](double,double){ return int(1); };
}

int main()
{
    //testAlignof();
    //testLambda();



    return 1;
}