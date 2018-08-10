#include <typeinfo>
#include <iostream>
#include "TuringMachine.cpp"
//#include "Rule.cpp"
#include "Misc.cpp"

using namespace std;

typedef TypeList<int, char, int, long, double> primitiveList;
typedef typename primitiveList::type head;
typedef typename primitiveList::tail tail; 
typedef TypeList<int, char, bool, long, double> primList;
typedef TypeList<char, char, char, char> charList;
int sizebla = GetSize<primList>::value;
typedef typename ConcatList<primList, charList>::type cc; 
typedef typename AppendItem<float, primList>::type appended;
typedef typename PrependItem<float, primList>::type prepended;
typedef typename GetItem<primList, 0>::type zeroth; 
typedef typename GetItem<primList, 2>::type second; 

template <typename T>
struct Wrapper {
    typedef T type;
};
typedef TypeList< Wrapper<int>, Wrapper<double>, Wrapper<bool> > wrappers;
template <typename Item, typename T>
struct Matcher {
    static constexpr bool value = IsSame<Item, Wrapper<T>>::value;
};
typedef typename FindItem<wrappers, Matcher, bool>::type boolWrapper;




typedef typename ReplaceItem<charList, 1, int>::type almostCharList;

//errors check - enable one at each time to check for the error

//typedef typename GetItem<primList, -1>::type error;//Will create static assertion error "index cannot be negative"
//typedef typename GetItem<primList, 10>::type error2; //Will create static assertion error "index too high"
//typedef typename FindItem<wrappers, Matcher, float>::type error3;//Will create static assertion error "Could not match any item"
//typedef typename ReplaceItem<charList, -1, int>::type error4;//Will create static assertion error "index cannot be negative"
//typedef typename ReplaceItem<charList, 4, int>::type error5;//Will create static assertion error "index too high"


template<>
char const* Input<-1>::name = "_";
char const* QAccept::name = "qaccept";
char const* QReject::name = "qreject";




void recived_data_test(){
    DEF_INPUT(1, x);
    DEF_INPUT(2, x_tag);
    DEF_INPUT(3, split);
    DEF_STATE(0, start);
    DEF_STATE(1, find_blank);
    DEF_STATE(2, go_back);
    typedef TypeList<
            Rule<start, x, find_blank, x_tag, Right>,
            Rule<find_blank, x, find_blank, x, Right>,
            Rule<find_blank, split, find_blank, split, Right>,
            Rule<find_blank, InputBlank, go_back, x, Left>,
            Rule<go_back, x, go_back, x, Left>,
            Rule<go_back, split, go_back, split, Left>,
            Rule<go_back, x_tag, start, x, Right>,
            Rule<start, split, QAccept, split, Left>> rules;

    typedef TuringMachine<TypeList<x, x, split>, rules, start> double_it;
    static_assert(IsSame<double_it::end_input,
            TypeList<x, x, split, x, x>>::value,"Hmm... Check your code!");

    static_assert (double_it::end_position==1,"fail");
    static_assert (IsSame<double_it::end_state,QAccept>::value,"fail");
    static_assert(IsSame<double_it::end_config,Configuration<TypeList<Input<1>,Input<1>,Input<3>,Input<1>,Input<1>>,QAccept,1>>::value,"fail");
    static_assert(IsSame<double_it::history::type,Configuration<TypeList<Input<1>,Input<1>,Input<3>>,start,0>>::value , "fail"); // check if we put the first config in the list
    static_assert(GetSize<double_it::history>::value==16,"fail");
    static_assert(IsSame<GetItem <double_it::history,15>::type,Configuration<TypeList<Input<1>,Input<1>,Input<3>,Input<1>,Input<1>>,QAccept,1>>::value , "fail"); // check if we put the last config in the list

//def check
    static_assert(IsSame<Identity<cc>::type,Identity<TypeList<int, char, bool, long, double, char, char, char, char>>::type>::value ,"fail");
    static_assert(IsSame<Identity<appended>::type,Identity<TypeList<int, char, bool, long, double, float>>::type>::value,"fail" );
    static_assert(IsSame<Identity<prepended>::type,Identity<TypeList<float, int, char, bool, long, double>>::type >::value,"fail");
    static_assert(IsSame<Identity<zeroth>::type,Identity<int>::type>::value , "fail");
    static_assert(GetSize<primList>::value==5, "fail" );
    static_assert(IsSame<Identity<second>::type,Identity<bool>::type>::value,"fail" );
    static_assert(IsSame<Identity<boolWrapper>::type,Identity<Wrapper<bool>>::type>::value , "fail" );
    static_assert(IsSame<Identity<almostCharList>::type,Identity<TypeList<char, int, char, char>>::type>::value , "fail" );


}

void test_1(){
    DEF_INPUT(1, x);
    DEF_INPUT(2, x_tag);
    DEF_INPUT(3, split);
    DEF_STATE(0, start);
    DEF_STATE(1, find_blank);
    DEF_STATE(2, go_back);

    typedef TypeList<
            Rule<start, x, find_blank, x_tag, Right>,
            Rule<find_blank, x, find_blank, x, Right>,
            Rule<find_blank, split, find_blank, split, Right>,
            Rule<find_blank, InputBlank, go_back, x, Left>,
            Rule<go_back, x, go_back, x, Left>,
            Rule<go_back, split, go_back, split, Left>,
            Rule<go_back, x_tag, start, x, Right>,
            Rule<start, split, QAccept, split, Left>> rules;

    typedef TuringMachine<TypeList<x, x, x, x, x, split>, rules, start> double_it;
    static_assert(IsSame<double_it::end_input,
                          TypeList<x, x, x, x, x, split, x, x, x, x, x>>::value, "Hmm... Check your code!");


    static_assert (double_it::end_position==4,"fail");
    static_assert (IsSame<double_it::end_state,QAccept>::value,"fail");
    static_assert(IsSame<double_it::end_config,Configuration<TypeList<Input<1>,Input<1>,Input<1>,Input<1>,Input<1>,Input<3>,Input<1>,Input<1>,Input<1>,Input<1>,Input<1>>,QAccept,4>>::value,"fail");
    static_assert(IsSame<double_it::history::type,Configuration<TypeList<Input<1>,Input<1>,Input<1>,Input<1>,Input<1>,Input<3>>,start,0>>::value , "fail"); // check if we put the first config in the list
    static_assert(IsSame<GetItem <double_it::history,GetSize<double_it::history>::value - 1>::type,Configuration<TypeList<Input<1>,Input<1>,Input<1>,Input<1>,Input<1>,Input<3>,Input<1>,Input<1>,Input<1>,Input<1>,Input<1>>,QAccept,4>>::value , "fail"); // check if we put the last config in the list

}


void test_2(){
    DEF_INPUT(1, a);
    DEF_INPUT(2, b);
    DEF_INPUT(3, del);
    DEF_INPUT(4, d);
    DEF_INPUT(5, s);
    DEF_STATE(0, start);
    DEF_STATE(1, find_d);
    DEF_STATE(2, remove);
    //DEF_STATE(2, go_back);

    typedef TypeList<
            Rule<start, s, find_d, s, Right>,
            Rule<find_d, b, find_d, d, Right>,
            Rule<find_d, a, find_d, b, Right>,
            Rule<find_d, d, remove, d, Stay>,
            Rule<find_d, del, find_d, del, Right>,
            Rule<find_d, InputBlank,QReject, del, Stay>,
            Rule<remove, d, remove, del, Left>,
            Rule<remove, del, remove, del, Left>,
            Rule<remove, b, find_d, b, Stay>,
            Rule<remove, a, find_d, a, Stay>,
            Rule<remove, s, find_d, s, Right> > rules;



    typedef TuringMachine<TypeList<s ,a, a, b, d, d, d>, rules, start> do_it;
    static_assert(IsSame<do_it::end_input,
            TypeList<s,del,del,del,del,del,del,del>>::value, "Hmm... Check your code!");

    static_assert (do_it::end_position==7,"fail");
    static_assert (IsSame<do_it::end_state,QReject>::value,"fail");
    static_assert(IsSame<do_it::end_config,Configuration<TypeList<Input<5>,Input<3>,Input<3>,Input<3>,Input<3>,Input<3>,Input<3>,Input<3>>,QReject,7>>::value,"fail");
    static_assert(IsSame<do_it::history::type,Configuration<TypeList<Input<5>,Input<1>,Input<1>,Input<2>,Input<4>,Input<4>,Input<4>>,start,0>>::value , "fail"); // check if we put the first config in the list
    static_assert(IsSame<GetItem <do_it::history,GetSize<do_it::history>::value - 1>::type,Configuration<TypeList<Input<5>,Input<3>,Input<3>,Input<3>,Input<3>,Input<3>,Input<3>,Input<3>>,QReject,7>>::value,"fail"); // check if we put the last config in the list


}
//for the test below


typedef TypeList<int, char, char, char, char, char> list2;
typedef TypeList<char, char, char, char> charList2;
typedef typename ConcatList<list2::tail, charList2>::type chars; // TypeList<char,char,char,char,char,char,char,char,char>
typedef typename AppendItem<int, chars>::type appendedchar;// TypeList<char,char,char,char,char,char,char,char,char,int>
typedef typename PrependItem<int, appendedchar>::type prependedcharint; //TypeList<int,char,char,char,char,char,char,char,char,char,int>
typedef typename GetItem<prependedcharint, 0>::type int1;
typedef typename GetItem<prependedcharint, 10>::type int2;
template <typename Item, typename T>
struct Matcher2 {
    static constexpr bool value = IsSame<Item, T>::value;
};
typedef typename FindItem<prependedcharint, Matcher2, int>::type itint;
typedef typename ReplaceItem<prependedcharint, 0, char>::type list3;//TypeList<char,char,char,char,char,char,char,char,char,char,int>
typedef typename FindItem<prependedcharint, Matcher2, int>::type itint2;
typedef typename ReplaceItem<list3, 10, char>::type list4;//TypeList<char,char,char,char,char,char,char,char,char,char,char>


//typedef typename FindItem<list4, Matcher2, int>::type itint3 ; //error- Will create static assertion error "Could not match any item"
void  functions_test(){

    static_assert(IsSame<Identity<chars>::type,Identity<TypeList<char,char,char,char,char,char,char,char,char>>::type>::value ,"fail");
    static_assert(IsSame<Identity<appendedchar>::type,Identity<TypeList<char,char,char,char,char,char,char,char,char,int>>::type>::value,"fail" );
    static_assert(IsSame<Identity<prependedcharint>::type,Identity<TypeList<int,char,char,char,char,char,char,char,char,char,int>>::type >::value,"fail");
    static_assert(IsSame<Identity<int1>::type,Identity<int>::type>::value , "fail");
    static_assert(IsSame<Identity<int2>::type,Identity<int>::type>::value , "fail");
    static_assert(GetSize<prependedcharint>::value==11, "fail" );

    static_assert(IsSame<Identity<itint>::type,Identity<int>::type>::value,"fail" );
    static_assert(IsSame<Identity<itint2>::type,Identity<int>::type>::value , "fail" );
    static_assert(IsSame<Identity<list4>::type,Identity<TypeList<char,char,char,char,char,char,char,char,char,char,char>>::type>::value , "fail" );

}

int main() {

    recived_data_test();
    cout << "recived_data_test [OK]" << endl;
    test_1();
    cout << "test_1 [OK]" << endl;
    test_2();
    cout << "test_2 [OK]" << endl;
    functions_test();
    cout << " functions_test [OK]" << endl;

    return 0;

}