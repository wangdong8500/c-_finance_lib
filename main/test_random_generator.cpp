/*
Test various random number generator
*/

#include <iostream>
#include <ParkMiller.h>
#include <Arrays.h>
#include <Antithetic.h>

using namespace std;

int main(){
	MJArray random_variate(1), antithetic_variate(1);
	RandomParkMiller generator(1);
	generator.Skip(10);
	Antithetic antithetic_g(generator);
	antithetic_g.Skip(20);

	for (int i=0; i<50; i++){
		generator.GetUniforms(random_variate);
		antithetic_g.GetUniforms(antithetic_variate);
		cout << random_variate[0] << "," << antithetic_variate[0]<<endl;
	}
	return 0;
}