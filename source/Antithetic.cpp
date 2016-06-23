#include <Antithetic.h>

RandomBase* Antithetic::clone() const{
	return new Antithetic(*this);
}

void Antithetic::GetUniforms(MJArray& variates){
	if (odd_path){
		inner_generator->GetUniforms(variates);
		for (int i=0; i < GetDimensionality(); i++){
			next_path[i] = 1. - variates[i];
		}
		odd_path = false;
	}
	else{
		variates = next_path;
		odd_path = true;
	}
}

void Antithetic::Skip(unsigned long number_of_paths){
	if (number_of_paths == 0)
		return;
	// this part is different from the book, I think the book is wrong.
	if (not odd_path){
		odd_path = true;
		number_of_paths--;
	}
	inner_generator->Skip(number_of_paths/2);
	if(number_of_paths % 2){
		MJArray temp(GetDimensionality());
		GetUniforms(temp);
	}
}

void Antithetic::SetSeed(unsigned long seed){
	inner_generator->SetSeed(seed);
	odd_path = true;
}

void Antithetic::Reset(){
	inner_generator->Reset();
	odd_path = true;
}

void Antithetic::ResetDimensionality(unsigned long new_dimensionality){
	inner_generator->ResetDimensionality(new_dimensionality);
	odd_path = true;
	next_path.resize(new_dimensionality);
	RandomBase::ResetDimensionality(new_dimensionality);
}






