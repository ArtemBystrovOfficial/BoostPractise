
#include <boost/scope_exit.hpp>
#include <iostream>
#include <functional>

class Test {
public:
    void Do() { std::cout << "Do\n"; throw 0; }
    void Undo() { std::cout << "Undo\n"; };
};

class SCOPED_EXIT {
public:
std::function<void()> func;
~SCOPED_EXIT() {func();}
};

void foo() {
    bool commit = false;
    Test test;
    BOOST_SCOPE_EXIT(&commit, &test) {
        if (!commit) test.Undo();   
    } BOOST_SCOPE_EXIT_END

    test.Do();         
    commit = true;                          
}

void foo2() {
    bool commit = false;
    Test test;

    SCOPED_EXIT a([&commit, &test](){
        if (!commit) test.Undo();
    });

    test.Do();
    commit = true;                          
}



int main() {
    try {
        foo();
    } catch(...) {}

    try {
        foo2();
    } catch(...) {}


}