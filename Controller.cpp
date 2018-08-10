//
// Created by jeries on 1/17/17.
//

#include "Configuration.cpp"
#include "list.cpp"
#include "Input.cpp"
#include "Rule.cpp"

template<typename Config, typename Transitions, typename = void>
struct Controller {

    //נשמור בשדות את המידע המעניין מהקונפיגורציה
    typedef  Config config;
    constexpr static int position = config::position; //נשמור את מיקום הראש בקבוע position

    //שלב #1
    constexpr static int list_size = GetSize<typename config::tape>::value;
    typedef typename Conditional< (list_size > position),Identity<typename config::tape>,AppendItem<InputBlank,typename config::tape>>::type::type input; //the list

    //שלב #2
    typedef typename config::state state;
    typedef typename GetItem<input, position>::type cell;

    //שלב #3
    template<typename rule, typename State, typename Cell>
    struct Matcher {
        typedef typename rule::old_state checking_state;
        typedef typename rule::input checking_input;
        enum { value = IsSame<State, checking_state>::value &&
                       IsSame<Cell,  checking_input>::value
        };
    };
    typedef typename FindItem<Transitions, Matcher, state, cell>::type found_rule;

    //שלב #4
    typedef typename ReplaceItem<input,position, typename found_rule::output>::type new_input;

    typedef typename found_rule::new_state new_state;
    typedef Configuration<new_input,
            new_state,
            Max<position + found_rule::direction, 0>::value> new_config;

    typedef Controller<new_config, Transitions> next_step;
    typedef typename next_step::end_config end_config;
    typedef typename next_step::end_input end_input;
    typedef typename next_step::end_state end_state;
    enum { end_position = next_step::end_position };
    typedef typename PrependItem<config, typename next_step::history>::type history;
};


template<typename Input, typename State, int Position, typename Transitions>
struct Controller<Configuration<Input, State, Position>, Transitions,
        typename EnableIf<IsSame<State, QAccept>::value ||
                          IsSame<State, QReject>::value>::type> {
    typedef Configuration<Input, State, Position> config;
    enum { position = config::position };
    typedef typename Conditional<
            static_cast<int>(GetSize<typename config::tape>::value)
            <= static_cast<int>(position),
            AppendItem<InputBlank, typename config::tape>,
            Identity<typename config::tape>>::type::type input;
    typedef typename config::state state;

    typedef config end_config;
    typedef input end_input;
    typedef state end_state;
    typedef typename AppendItem<config, TypeList<> >::type history;
    // typedef TypeList<config> history;
    enum { end_position = position };

};