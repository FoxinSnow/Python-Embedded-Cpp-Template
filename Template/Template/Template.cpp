#include <iostream>
#include <memory>
#include "SomeClass.h"

int main()
{
	std::cout << "Python Embedded C++ Template" << std::endl;
	std::unique_ptr<SomeClass> p = std::make_unique<SomeClass>();
	p->callScript();
}

