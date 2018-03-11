#include <iostream>  // cout, endl
#include <algorithm> // copy
#include <iterator>  // ostream_iterator, begin(), end()
#include <cmath>     // sqrt()
#include <string>    // string, stoi
#include <vector>
#include <chrono>      
/// Implements an iterative linear seach on an range [first; last) of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or nullptr, in case the value is not in the range.
 */

using namespace std;
using namespace chrono;
typedef struct function{
	int* (*ref) (int*, int*, int);
	string name;
	duration<long int, std::ratio<1l, 1000000000l>> time; // trabalhando diretamente com o retorno do duration::count()
}Function, FunctionList[];
int* lsearch(int *first, int *last, int value )
{
	while(first != last){
		if(*first == value)
			return first;
		first++;
	}
	return nullptr; // STUB
}

/// Implements an interative binary search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or nullptr, in case the value is not in the range.
 */
int* bsearch(int *first, int *last, int value )
{
	int m = distance(first, last);
	int *middle = first + (m/2);
	int *aux = last;
	while(first != aux){
		if(*middle == value){
			return middle;
		}
		if(value < *middle){
			aux = middle;
			m = distance(first, aux);
			middle = first + (m/2);
			continue; 
		}
		else {
			first = middle+1;
			m = distance(first, aux);
			middle = first + (m/2);
			continue;
		}	
	}
	return nullptr; 
}
int* tsearch(int* first, int* last, int value){
	int *t1 = first + (last-first)/3;
	int *t2 = t1 + (t1-first);
	int *aux = last; 
	while(first != aux){
		if(value == *t1)
			return t1; 
		if(value == *t2)
			return t2; 
		if(value > *t1){
			if(value > *t2){
				first = t2+1;
				t1 = first + (aux-first)/2;
				t2 = t1 + (t1-first);
				continue;
			}
			else{
				first  = t1+1;
				aux = t2; 
				t1 = first + (aux-first)/2;
				t2 = t1 + (t1-first);
				continue;
			}
		}
		else{
			aux = t1; 
			t1 = first + (aux-first)/2;
			t2 = t1 + (t1-first);
			continue;
		}
	}
	return nullptr; 
}
int* jsearch(int *first, int *last, int value )
{
	int n = last-first;
	int m = sqrt(n);
	int *e = first+m;
	while(e <= last){
		if(e == last){
			if(value == *(e-1))
				return e-1;
			else
				return nullptr;
		}
		//cout << "e: " << *e << "\n last: " << *last << endl;
		if(value == *e)
			return e;
		else if(value < *e)
			return lsearch(e-m, e, value);
		else{
			e+=m;
			continue;
		}
	}
	return nullptr;
}

// Driver function.
int main(int argc, char* argv[])
{
	string arg;
	int start = 0, limit = 10, i, size, n = 10, jump;
	if(argc > 1){
		for(int i = 1; i < argc; i++){
			arg = argv[i];
			if(arg == "-l" or arg == "--limit"){
				arg = argv[i+1];
				limit = stoi(arg, nullptr, 10);
			}else if(arg == "-n" or arg == "--number"){
				arg = argv[i+1];
				n = stoi(arg, nullptr, 10);
			}else if(arg == "-s" or arg == "--start"){
				arg = argv[i+1];
				start = stoi(arg, nullptr, 10);
			}

		}
	}
	jump = ((limit - start)/n);
	size = start;
	int* A;
	A = (int*) malloc(sizeof(int)*limit);
	for(i = 0; i < limit; i++)
		A[i] = i;
	int targets[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , -4, 20, 100000 }; // Target values for testing.
	int targets_size = distance(begin(targets), end(targets));
	//int* (*f[]) (int*, int*, int) = {lsearch, jsearch, bsearch, tsearch};
	FunctionList f = {(Function) {lsearch, "Linear Search"}, (Function) {bsearch, "Binary Search"}, (Function) {bsearch, "Ternary Search"}, (Function) {jsearch, "Jump Search"}};
	time_point<steady_clock> t0; // start timepoint
	time_point<steady_clock> t1; // end timepoint
	// Executes several searchs in the data container.
	for(; size < limit; size+=jump){
#ifdef DEBUG
		cout << "Array: [ ";
		copy(A, A+size, ostream_iterator<int>( cout , " " ) );
		cout << "]\n";
#endif
		for(Function & ef : f){
#ifdef DEBUG
			cout << "------------------------------\nalgorithm = " << ef.name << ".\n------------------------------\n";
#endif
			for(i = 0; i < targets_size; i++)
			{
				// Look for target in the entire range."
				t0 = steady_clock::now();
				auto result = ef.ref( A, A+size, targets[i]);
				t1 = steady_clock::now();
				//ef.time += ((t1-t0) - ef.time) / (i+1);	
				//ef.time = t1-t0;	
				cout << "- time = " << duration_cast<milliseconds> (t1-t0).count() << " ns.\n";

#ifdef DEBUG
				if (result)
				{
					cout << ">>> Found \"" << targets[i] << "\" at position " << distance(A, result) << ".\n";
				}
				else
				{
					cout << ">>> Value \"" << targets[i]<< "\" not found in array!\n";
				}
#endif
			}
			//cout << "- time = " << duration_cast<seconds> ef.time << " ns.\n";
		}
	}
	return 0;
}
