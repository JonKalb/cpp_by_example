/** NOT PRODUCTION QUALITY CODE, just shows learning/teaching example, not real programming, don't copy this style, just playing around
   Copyright Grant Rostig 2015 - 2023. Distributed under the Boost Software License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)
   Reminder of usefull resources:
   https://coliru.stacked-crooked.com/
   https://godbolt.org/
   https://cppinsights.io/
   https://Wandbox.org
   https://arnemertz.github.io/online-compilers/
    //[[maybe_unused]] int * my_new_var8 = ::new (22,int);
 */

//#include <bits/stdc++.h>
#include <chrono>
#include <csignal>
#include <iostream>
#include <iterator>
#include <map>
#include <source_location>
#include <stacktrace>
#include <utility>

using std::cin; using std::cout; using std::cerr; using std::clog; using std::endl; using std::string;  // using namespace std;
using namespace std::string_literals;
using namespace std::chrono_literals;
template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
/* OLDER simple STUFF
// Another approach to print, from: Josuttis
template <class T>
inline void PRINT_ELEMENTS (const T& coll, string optcstr="") {
    typename T::const_iterator pos;
    std::cout << optcstr;
    for (pos=coll.begin(); pos!=coll.end(); ++pos)
        std::cout << *pos << ' ';
    std::cout << std::endl;
}
// Prints contents of a container such as a vector of int's.
// Insertable Concept used by Templated Function definition.
// Older version is here for the record:
        template<class T> std::ostream & operator<<(std::ostream & out, std::vector<T> const & v) { // utility f() to print vectors
        if ( not v.empty() ) {
            out<<'['; std::copy(v.begin(), v.end(), std::ostream_iterator<T>(out, ", ")); out<<"\b\b]";
        }
            return out;
        }
*/
#define LOGGER_(  msg )  using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<    "["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<           "."    <<endl;cout.flush();cerr.flush();
#define LOGGER_R( msg )  using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<"\r\n["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<           ".\r\n"<<endl;cout.flush();cerr.flush();
#define LOGGERX(  msg, x)using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<    "["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<".:{"<<x<<"}."    <<endl;cout.flush();cerr.flush();
#define LOGGERXR( msg, x)using loc = std::source_location;std::cout.flush();std::cerr.flush();std::cerr<<"\r\n["<<loc::current().file_name()<<':'<<std::setw(4)<<loc::current().line()<<','<<std::setw(3)<<loc::current().column()<<"]`"<<loc::current().function_name()<<"`:" <<#msg<<".:{"<<x<<"}.\r\n"<<endl;cout.flush();cerr.flush();

template<typename First, typename Second, typename Third>  // this forward declaration is definitely required to compile
std::ostream & operator<<( std::ostream & out, std::tuple<First,Second,Third> const & my_tuple);

template<class First, class Second>
std::ostream &
operator<<( std::ostream & out, std::pair<First,Second> const & my_pair) {
    out << "PAIR_MEMBERS["; out << my_pair.first  <<","<< my_pair.second; out << "]"; return out; }

template<class First, class Second, class Third>  // TODO??: make it variadic. TODO??: what about something like this: std::copy(my_pair.begin(), my_pair.end(), std::ostream_iterator< typename Container::value_type >( out, ">,<" ));
std::ostream &
operator<<( std::ostream & out, std::tuple<First,Second,Third> const & my_tuple) {
 out << "TUPLE_MEMBERS["; out << std::get<0>(my_tuple) << "," << std::get<1>(my_tuple) << "," << std::get<2>(my_tuple); out << "]"; return out; }  //out << "\b\b\b>]"; out.width(); out << std::setw(0);


template <class T>
concept Streamable
    = requires( std::ostream & out_concept_parameter ) {
//    requires not std::same_as<std::string, T>;
    { out_concept_parameter << T {} } -> std::convertible_to<std::ostream &>;   // bool concept_function definition()
};

template <class Container>
concept Streamable_container
    = requires( std::ostream & out ) {
    requires not std::same_as<std::string, Container>;                          // bool concept_requires requirement()
    requires     Streamable<typename Container::value_type>;
    // OLD WORKING STUFF { out << typename Container::value_type {} } -> std::convertible_to<std::ostream & >; // OR just $ { out << typename Container::value_type {} };
};

template<Streamable_container SC>    // Function Template with typename concept being restricted to SC in this case. Similar to Value template
std::ostream &
operator<<( std::ostream & out, SC const & sc) {
    LOGGER_()
    if ( not sc.empty() ) {
        out << "[";                    //out.width(9);  // TODO??: neither work, only space out first element. //out << std::setw(9);  // TODO??: neither work, only space out first element.
        // TODO??: why compile error on?: std::copy(sc.begin(), sc.end(), std::ostream_iterator< typename SC::value_type >( out, ">,<" ));
        bool first{ true };
        for(auto &i : sc) { // this works, but why not std::copy?
            if(first) {
                first = false;
                out << "<" << i;
            } else {
                out << ">,<" << i;
            }
        }
        out << ">]" << " ";             // out.width(); out << std::setw(0);
    } else
        out << "[CONTAINTER IS EMPTY]";

    return out;
}


int main ( int argc, char* arv[] ) { string my_arv { *arv}; cout << "~~~ argc,argv:"<<argc<<","<<my_arv<<"."<<endl;
    using My_tuple = std::tuple<int,float,std::string>;
    std::pair<int,float>                my_fundamental_pair {2, 3.3f};
    My_tuple                            my_tuple            {2, 3.3f, "threethreethree"s};
    std::map<int, My_tuple>::value_type my_value_type       {};
    std::pair                           my_tuple_pair       {my_tuple,my_tuple};
    std::vector                         v_int               {1,2,3};
    std::vector                         v_cstring           {"one","two","three"};
    std::vector                         v_string            {"one"s,"two"s,"three"s};
    std::vector                         v_fund_pair         {my_fundamental_pair,my_fundamental_pair,my_fundamental_pair};
    std::vector                         v_tuple             {my_tuple,my_tuple,my_tuple};
    std::vector                         v_value_type        {my_value_type, my_value_type, my_value_type};
    std::map<int, My_tuple>             my_map              { {10,my_tuple} };
    std::map<int, My_tuple>             my_map2             { { 10,{11,12.0f,"1st string"s}}, {20,{21,22.0f,"2nd string"s}} };

    cout << "$$My value_type      :"<< my_value_type << endl;
    cout << "$$My v_value_type    :"<< v_value_type << endl;
    cout << "$$My fundamental pair:"<< my_fundamental_pair << endl;        //cout << my_pair.first <<", " << my_pair.second << endl;
    cout << "$$My tuple           :"<< my_tuple << endl;                             //cout << std::get<0>(my_tuple) <<"," << std::get<1>(my_tuple) << "," << std::get<2>(my_tuple) << endl;
    cout << "$$My tuple pair      :"<< my_tuple_pair << endl;
    cout << "$$My v_int           :"<< v_int << endl;
    cout << "$$My v_cstring       :"<< v_cstring << endl;
    cout << "$$My v_string        :"<< v_string << endl;
    cout << "$$My v_fund_pair     :"<< v_fund_pair << endl;  // ERROR
    cout << "$$My map2            :"<< my_map2 << endl;
    cout << "$$My map             :"<< my_map << endl;

    cout << "###" << endl;
    return EXIT_SUCCESS;
}
