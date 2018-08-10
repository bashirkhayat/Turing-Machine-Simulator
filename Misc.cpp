#ifndef MISC
#define MISC

//Like static_if
template<bool C, typename A, typename B>
struct Conditional {
    typedef A type;
};

template<typename A, typename B>
struct Conditional<false, A, B> {
    typedef B type;
};

template<bool C, typename = void>
struct EnableIf { };

template<typename Type>
struct EnableIf<true, Type> {
    typedef Type type;
};

template<typename T>
struct Identity {
    typedef T type;
};


template<typename A, typename B>
struct IsSame {
    constexpr static bool value = false;
};

template<typename A>
struct IsSame<A, A> {
    constexpr static bool value = true;
};

template<int A, int B>
struct Max {
    constexpr static int value = A > B ? A : B;
};

#endif