#include <PayOffFactory.h>
#include <iostream>
using namespace std;

PayOffFactory& PayOffFactory::Instance(){
	static PayOffFactory the_factory;
	return the_factory;
}

void PayOffFactory::RegisterPayOff(string id, CreatePayOffFunction create_fun_ptr){
	TheCreatorFunctions.insert(pair<string,CreatePayOffFunction>(id,create_fun_ptr));
}

PayOff* PayOffFactory::CreatePayOff(string id, double strike){
	map<std::string, CreatePayOffFunction>::const_iterator i = TheCreatorFunctions.find(id);
	if(i == TheCreatorFunctions.end()){
		cout << id << "is an unknown pay off" << endl;
		return 0;
	} 
	return (i->second)(strike);
}

