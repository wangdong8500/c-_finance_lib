#include <ConvergenceTable.h>
using namespace std;

StatisticsMC* ConvergenceTable::clone() const{
	return new ConvergenceTable(*this);
}

void ConvergenceTable::DumpOneResult(double x){
	inner->DumpOneResult(x);
	path_done++;

	// update table
	if (path_done == stopping_point){
		stopping_point *= 2;
		vector< vector<double> > this_results = inner->GetResultsSoFar();
		for (unsigned long i=0; i < this_results.size(); i++){
			this_results[i].push_back(path_done);
			table.push_back(this_results[i]);
		}
	}
	return;
}

vector< vector<double> > ConvergenceTable::GetResultsSoFar() const{
	vector < vector<double> > temp(table);
	if (stopping_point != 2*path_done){
		vector< vector<double> > this_result = inner->GetResultsSoFar();
		for (unsigned long i=0; i < this_result.size(); i++){
			this_result[i].push_back(path_done);
			temp.push_back(this_result[i]);
		}
	}
	return temp;
}