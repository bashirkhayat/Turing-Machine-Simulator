//
// Created by jeries on 1/17/17.
//
//mevnii #1

enum Direction {
    Left = -1,
    Stay = 0,
    Right = 1
};

template<typename OldState, typename Input, typename NewState,
        typename Output,Direction Move>
struct Rule {
    typedef OldState old_state;
    typedef Input input;
    typedef NewState new_state;
    typedef Output output;
    static Direction const direction = Move;
};




