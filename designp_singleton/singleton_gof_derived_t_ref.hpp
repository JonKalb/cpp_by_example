// cppmsg.com Boost 1.0 license.
// see: GOF 1995-SS 1.Singleton; Vlissides 1998-ch2,ch3; Larman 2005-SS 26.5; Robert Martin 2002-Singleton and Monstate; Headington 1996-SS2.7 p79; Cline 1999-ch16-?;
#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Singleton_gof_base_t_ref {           // NOTE: In fact since I have more than one singletons in here it is more of a registry as mentioned in GOF.
protected:
    Singleton_gof_base_t_ref() noexcept = default;
public:
    virtual ~Singleton_gof_base_t_ref()                                                   = default;
    Singleton_gof_base_t_ref(Singleton_gof_base_t_ref const &   )                         = delete;  // TODO??: Should this be explicit? and then so what?
    Singleton_gof_base_t_ref(Singleton_gof_base_t_ref       &&  )                         = delete;
    Singleton_gof_base_t_ref & operator=( Singleton_gof_base_t_ref const &  ) noexcept    = delete;
    Singleton_gof_base_t_ref & operator=( Singleton_gof_base_t_ref       && ) noexcept    = delete;
    Singleton_gof_base_t_ref & operator()()                                    = delete;     // Redundant since it isn't rule of 5/6.
    static T & instance() {        // TODO??: Could this be by value instead?  I guess not since then there would be copies??  But still access() would get the right thing, but the user might not use access and get to the values some other way??
        static T _instance;
        return   _instance;
    };
};

class S_gof_derived_t_ref final : public Singleton_gof_base_t_ref< S_gof_derived_t_ref > {  // CRTP TODO??: how does modern c++ obviate this approach?
    //friend SingletonBase SingletonBase<Singleton_subclassed>::instance();
public:
    int my_int {99};
};

void test_singleton_gof_derived_t_ref() {
    cout<< "test_singleton_gof_derived_t_ref()" << endl;
    S_gof_derived_t_ref & s_g_d_t1      { S_gof_derived_t_ref::instance()};
    int                   s_g_d_t1_int   { s_g_d_t1.my_int};
    S_gof_derived_t_ref & s_g_d_t2      { S_gof_derived_t_ref::instance()};

    cout << "t1:" << s_g_d_t1.my_int << endl ;
    cout << "t2:" << s_g_d_t2.my_int << endl ;
    cout << "++int1:" << ++s_g_d_t1_int << endl ;
    cout<< "set only int2 to 42." << endl;
    s_g_d_t2.my_int = 42;
    cout << "t2:" << s_g_d_t2.my_int << endl ;
    cout << "t1:" << s_g_d_t2.my_int << endl ;
    cout<< "BAD ptr1 was not updated but shows it was." << endl;
    //s_g_d_t1 = s_g_d_t2;
    S_gof_derived_t_ref & s_g_d_t3 { s_g_d_t1 };  // TODO??: why does this compile? I thought I =delete'd this
}
