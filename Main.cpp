#include <iostream>
#include <cstdint>
//#include <cmath>
#include "Fraction.hpp"

using namespace dd;

void test01 (Fraction<int32_t> const& f1, Fraction<int32_t> const& f2)
{
    Fraction<int32_t> f {0,1};
    std::cout << f1 << " + " << f2 << " = ";
    f=f1+f2;
    std::cout << f << std::endl;
    std::cout << f1 << " - " << f2 << " = ";
    f=f1-f2;
    std::cout << f << std::endl;
    std::cout << f1 << " * " << f2 << " = ";
    f=f1*f2;
    std::cout << f << std::endl;
    std::cout << f1 << " / " << f2 << " = ";
    f=f1/f2;
    std::cout << f << std::endl;
    if (f1<f2) std::cout << f1 << " < " << f2 << std::endl;
    if (f1<=f2) std::cout << f1 << " <= " << f2 << std::endl;
    if (f1>f2) std::cout << f1 << " > " << f2 << std::endl;
    if (f1>=f2) std::cout << f1 << " >= " << f2 << std::endl;
    if (f1==f2) std::cout << f1 << " == " << f2 << std::endl;
    if (f1!=f2) std::cout << f1 << " != " << f2 << std::endl;
}

int main()
{
    std::cout << "Test 1: Nominal case (positive values)" << std::endl;
    Fraction<int32_t> f1 {100,150};
    Fraction<int32_t> f2 {2,5};
    test01(f1,f2);
    std::cout << std::endl << "Test 2: Nominal case (positive and negative values)" << std::endl;
    Fraction<int32_t> f3 {30,15};
    Fraction<int32_t> f4 {242,-10};
    test01(f3,f4);
    std::cout << std::endl << "Test 3: Nominal case (negative values)" << std::endl;
    Fraction<int32_t> f5 {-3,33};
    Fraction<int32_t> f6 {7,-21};
    test01(f5,f6);
    std::cout << std::endl << "Test 4: limit test (with 0 et 1)" << std::endl;
    Fraction<int32_t> f7 {0,33};
    Fraction<int32_t> f8 {241,241};
    test01(f7,f8);
    std::cout << std::endl << "Test 5: test of contract on division" << std::endl;
    Fraction<int32_t> f9 {1};
    Fraction<int32_t> f10 {};
//    test01(f9,f10);
    std::cout << std::endl << "Test 6: test of contract on constructor" << std::endl;
//    Fraction<int32_t> f11 {1,0};
    Fraction<int32_t> f12 {3,241};
//    test01(f11,f12);
    std::cout << std::endl << "Test 7: test of contract on Invariant" << std::endl;
    Fraction<int32_t> f13 {1};
    Fraction<int32_t> f14 {3,241};
    f14.bug ();
//    test01(f13,f14);
    std::cout << std::endl << "Test 8: test of Overflow on multiplication" << std::endl;
    Fraction<int32_t> f15 {-1,(int32_t(1))<<30};
    Fraction<int32_t> f16 {7, ((int32_t(1))<<30)-1};
 //   test01(f15,f16);
    std::cout << std::endl << "Test 8: test of Overflow on addition" << std::endl;
    Fraction<int32_t> f17 {200, (int32_t(1))<<30};
    Fraction<int32_t> f18 {300, ((int32_t(1))<<30)-1};
    test01(f17,f18);

    return 0;
}
