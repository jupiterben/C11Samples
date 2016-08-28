class base
{
public:
    virtual void f(short){}
};

class derived : public base
{
public:
    virtual void f(short) override {}
    //error
    //virtual void f(int) override {}
};

int main()
{
    return 1;
}