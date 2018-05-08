#include <iostream>
#include <cassert>
#include "CarMap.h"

int main()
{
	CarMap m;
	assert(m.fleetSize() == 0);
	m.addCar("1234");
	m.addCar("abcd");
	m.addCar("xyz");
	assert(m.fleetSize() == 3);
	assert(m.addGas("1234", 0) && m.gas("1234") == 0);
	assert(m.addGas("1234", 20) && m.gas("1234") == 20);
	assert(!m.addGas("1234", -1) && m.gas("1234") == 20);
	assert(!m.useGas("1234", 25) && m.gas("1234") == 20);
	assert(m.useGas("1234", 5) && m.gas("1234") == 15);
	m.addCar("");
	assert(m.fleetSize() == 4);
	m.print();


	std::cout << "all testCarMap tests succeeded" << std::endl;
}