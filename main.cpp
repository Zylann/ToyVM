#include <iostream>
#include <vector>
#include <cmath>
#include "VM.hpp"

static int foo(VM & vm)
{
    // Note: arguments are reversed
    float a = vm.popFloat();
    float b = vm.popFloat();
    vm.pushFloat(sqrt(a*a + b*b));
    return 1;
}

int main(int argc, char * argv[])
{
    std::cout << "Hello world!" << std::endl;

    VM vm;

    vm.pushFloat(1);
    vm.pushString(" two ");
    vm.pushFloat(3);
    vm.add();
    String strResult = vm.popString();

    std::cout << "Result: " << strResult << std::endl;

    vm.pushFloat(3);
    vm.pushFloat(4);
    vm.pushCFunction(&foo);
    vm.call();
    float floatResult = vm.popFloat();

    std::cout << "Second result: " << floatResult << std::endl;

    getchar();

    return 0;
}

