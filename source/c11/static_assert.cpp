template <typename T1, typename T2>
auto add(T1 t1, T2 t2) -> decltype(t1 + t2)
{
   static_assert(std::is_integral<T1>::value, "Type T1 must be integral");
   static_assert(std::is_integral<T2>::value, "Type T2 must be integral");
 
   return t1 + t2;
}

int main()
{
    return 1;
}