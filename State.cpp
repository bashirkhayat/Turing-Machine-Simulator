template<int n>
struct State {
    static constexpr int value = n;
    static char const * name;
};

template<int n>
char const* State<n>::name = "unnamed";

struct QAccept {
    static constexpr int value = -1;
    static char const* name;
};

struct QReject {
    static constexpr int value = -2;
    static char const* name;
};

#define DEF_STATE(ID, NAME)\
    typedef State<ID> NAME; \
    NAME :: name = #NAME;

