#include "Misc.cpp"

template<int n>
struct Input {
    constexpr static int value = n;
    static char const * name;
};

template<int n>
char const* Input<n>::name = "unnamed";

#define DEF_INPUT(ID, NAME) \
    typedef Input<ID> NAME ; \
    NAME :: name = #NAME ;

typedef Input<-1> InputBlank;
