#include <PathDependent.h>

PathDependent::PathDependent(const MJArray& look_at_times_):
	look_at_times(look_at_times_){}
	

const MJArray& PathDependent::GetLookAtTimes() const{
	return look_at_times;
}

