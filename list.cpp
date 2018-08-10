//
// Created by jeries on 1/17/17.
//

#include <iostream>
#include "Misc.cpp"
using namespace std;

template<typename...>
struct TypeList;

template<typename T, typename... TT>
struct TypeList<T, TT...>  {
    typedef T type;
    typedef TypeList<TT...> tail;
};

template<>
struct TypeList<> {}; //EmptyList

template<typename List>
struct GetSize;

template<typename... List>
struct GetSize<TypeList<List...>> {
    enum { value = sizeof...(List) };
};


template<typename... T>
struct ConcatList;

template<typename... First, typename... Second>
struct ConcatList<TypeList<First...>, TypeList<Second...>> {
    typedef TypeList<First..., Second...> type;
};

template<typename T>
struct ConcatList<T> {
    typedef T type;
};

template<typename NewItem, typename List>
struct AppendItem;

template<typename NewItem, typename...List>
struct  AppendItem<NewItem, TypeList<List...>> {
    typedef TypeList<List..., NewItem> type;
};

template<typename NewItem, typename... List>
struct PrependItem;

template<typename NewItem, typename...List>
struct PrependItem<NewItem, TypeList<List...>> {
    typedef TypeList<NewItem, List...> type;
};

template<typename List, int n>
struct GetItem {
    static_assert(n > 0, "index cannot be negative");
    static_assert(GetSize<List>::value > 0 , "index too high");
    typedef typename GetItem<typename List::tail, n-1>::type type;
};


template<typename List>
struct GetItem<List, 0> {
    static_assert(GetSize<List>::value > 0 , "index too high");
    typedef typename List::type type;
};

template<typename List, template<typename, typename...> class Matcher, typename... Keys>
struct FindItem {
    static_assert(GetSize<List>::value > 0, "Could not match any item.");
    typedef typename Conditional<Matcher< typename List::type, Keys...>::value,
            Identity<typename List::type>,
            FindItem<typename List::tail, Matcher, Keys...>>::type::type type;
};


template<typename List, int i, typename NewItem>
struct ReplaceItem {
    static_assert(i > 0, "index cannot be negative");
    static_assert(GetSize<List>::value > 0, "index too high");
    typedef typename PrependItem<typename List::type,
            typename ReplaceItem<typename List::tail, i-1,
                    NewItem>::type>
    ::type type;
};

template<typename NewItem, typename Type, typename... List>
struct ReplaceItem<TypeList<Type, List...>, 0, NewItem> {
    typedef TypeList<NewItem, List...> type;
};





