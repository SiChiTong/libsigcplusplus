// -*- c++ -*-
/* Copyright 2002, The libsigc++ Development Team
 *  Assigned to public domain.  Use as you wish without restriction.
 */

#include <sigc++/adaptors/bind_return.h>
#include <sigc++/functors/slot.h>
#include <iostream>
#include <string>

SIGC_USING_STD(cout)
SIGC_USING_STD(endl)
SIGC_USING_STD(string)

struct foo 
{
  void operator()(int i) 
    {std::cout << "foo(int "<<i<<")"<<std::endl; }
  float operator()(float i) 
    {std::cout << "foo(float "<<i<<")"<<std::endl; return i*5;}
};

struct bar : public sigc::trackable
{
  bar(int i=0) : i_(i) {}
  operator int() {return i_;}
  int i_;
};

int main()
{
  std::cout << sigc::bind_return(foo(),-12345)(5) << std::endl;

  // test references
  std::string str("guest book");
  sigc::bind_return<std::string&>(foo(),str)(6) = "main";
  std::cout << str << std::endl;

  sigc::slot<bar,int> sl; // bar, not bar&: slots cannot return references
  {
    bar choco(-1);
    sl = sigc::bind_return(foo(),sigc::ref(choco));
    std::cout << sl(7) << std::endl;
  } // auto-disconnect
  std::cout << sl(8) << std::endl;
}
