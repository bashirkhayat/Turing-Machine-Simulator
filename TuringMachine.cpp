#include "Controller.cpp"


template<typename Input, typename Transitions, typename StartState>
struct TuringMachine {
    typedef Input input;
    typedef Transitions transitions;
    typedef StartState start_state;

    typedef Controller<Configuration<Input, StartState, 0>, Transitions> controller;
    typedef typename controller::history history;
    typedef typename controller::end_config end_config;
    typedef typename controller::end_input end_input;
    typedef typename controller::end_state end_state;
    constexpr static int end_position = controller::end_position;
};