// test the wrapper class

// need PayOff.cpp

#include <iostream>
#include <wrapper.h>
#include <PayOff.h>

int main(){
	double S;
	double K1,K2,K3;

	std::cout << "spot\n";
	std::cin >> S;

	std::cout << "strike1\n";
	std::cin >> K1;

	std::cout << "strike2\n";
	std::cin >> K2;

	CallPayOff one(K1);
	PutPayOff two(K2);

	PayOff* p = one.clone();
	Wrapper<PayOff> four = p;

	{
		PayOff* q = two.clone();
		Wrapper<PayOff> five = q;

		std::cout << "four:";
		std::cout << (*four)(S) << " five:" << (*five)(S) << std::endl;

		four = five;
	}

	std::cout << "four: " << (*four)(S) <<std::endl;

}
