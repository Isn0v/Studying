#include <iostream>

template <int I, int J>
struct IsPrimeHelper
{
    static const bool value = (J * J > I) ? true : (I % J) && IsPrimeHelper<I, J + 2>::value;
};

template <int I>
struct IsPrimeHelper<I, I>
{
    static const bool value = true;
};

// template <int I>
// struct IsPrime
// {
//     static const bool value = (I % 2) ? IsPrimeHelper<I, 3>::value : false;
// };
template <int I, bool = (I % 2) == 1>
struct IsPrime
{
    static const bool value = IsPrimeHelper<I, 3>::value;
};

template <>
struct IsPrime<2>
{
    static const bool value = true;
};

template <int I>
struct IsPrime<I, false>
{
    static const bool value = false;
};

template <int N, int P = 2, int C = 0>
struct NthPrime
{
    static const int value = NthPrime<N, P + 1, C + IsPrime<P>::value>::value;
};

template <int N, int P>
struct NthPrime<N, P, N>
{
    static const int value = P - 1;
};

int main()
{
    std::cout << NthPrime<100>::value << std::endl;
}