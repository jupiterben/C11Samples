class base
{
public: 
    virtual void f() final;
};

class derived : public base
{
public:
    //void f();   //error;
};

int main()
{
    return 1;
}