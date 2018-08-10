//
// Created by jeries on 1/17/17.
//
#include "State.cpp"


template<typename Tape, typename State, int Position>
struct Configuration {
    typedef Tape tape;
    typedef State state;
    enum { position = Position };
};
