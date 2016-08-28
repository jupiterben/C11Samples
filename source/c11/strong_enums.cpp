class Animal
{
public:
enum class Type{ Dog, Pig, Bird, }; 
enum WeakType{ D, P, B, };
};


int main()
{
    //strong enums
    Animal::Type t =  Animal::Type::Dog;   
    //wrong
    //Animal::Type t =  Animal::Dog; 
    //int it = t;

    Animal::WeakType wt = Animal::D;
    int iwt = wt;

    return 1;
}