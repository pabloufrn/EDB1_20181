#include <iostream>  // cout, endl
#include <algorithm> // copy
#include <iterator>  // ostream_iterator, begin(), end()
#include <cmath>     // sqrt()
#include <string>    // string, stoi
#include <chrono>    // duration, steady_clock::now()
#include <fstream>   // osfstream
#include <iomanip>   // setw()

using namespace std;
using namespace chrono;
typedef struct function{
	int* (*ref) (int*, int*, int); // pointer to function
	string name;                   // name of function
	float *time;                   // execution time of the function 
}Function, FunctionList[];

/// Implements an iterative linear seach on an range [first; last) of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or last, in case the value is not in the range.
 */
int* lsearch(int *first, int *last, int value )
{
	while(first < last){
		if(*first == value)
			return first;
		first++;
	}
	return last;
}
/// Implements an interative binary search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or last, in case the value is not in the range.
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
	return last; 
}
/// Implements a recursive binary search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or nullptr, in case the value is not in the range.
 */
int* run_rbsearch(int *first, int *last, int value )
{
	if(first == last)
		return nullptr;
	int m = distance(first, last);
	int *middle = first + (m/2);
	if(*middle == value){
		return middle;
	}
	if(value < *middle){
		last = middle;
		return run_rbsearch(first, last, value); 
	}
	else {
		first = middle+1;;
		return run_rbsearch(first, last, value);
	}	 
}
/// Implements a wrapper function to run_rbsearch.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or last, in case the value is not in the range.
 */
int* rbsearch(int *first, int *last, int value )
{
	int* result = run_rbsearch(first, last, value);
	if(result)
		return result;
	else
		return last;
}
/// Implements an interative ternary search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or last, in case the value is not in the range.
 */
int* tsearch(int* first, int* last, int value)
{
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
				t1 = first + (aux-first)/3;
				t2 = t1 + (t1-first);
				continue;
			}
			else{
				first  = t1+1;
				aux = t2; 
				t1 = first + (aux-first)/3;
				t2 = t1 + (t1-first);
				continue;
			}
		}
		else{
			aux = t1; 
			t1 = first + (aux-first)/3;
			t2 = t1 + (t1-first);
			continue;
		}
	}
	return last; 
}
/// Implements a recursive ternary search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or nullptr, in case the value is not in the range.
 */
int* run_rtsearch(int* first, int* last, int value)
{
	int *t1 = first + (last-first)/3;
	int *t2 = t1 + (t1-first); 
	if(value == *t1)
		return t1; 
	if(value == *t2)
		return t2; 
	if(value > *t1){
		if(value > *t2){
			return run_rtsearch(t2+1, last, value);
		}
		else{
			return run_rtsearch(t1+1, t2, value);
		}
	}
	else{
		return run_rtsearch(first, t1, value);
	}
	return last; 
}
/// Implements a wrapper function to run_rtsearch.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or last, in case the value is not in the range.
 */
int* rtsearch(int* first, int* last, int value){
	int* result = run_rbsearch(first, last, value);
	if(result)
		return result;
	else
		return last;
}
/// Implements a jump search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or last, in case the value is not in the range.
 */
int* jsearch(int *first, int *last, int value )
{
	int n = last-first;
	int m = sqrt(n);
	int *e = first+m;
	int *result;
	while(e < last){
		if(value == *e)
			return e;
		else if(value < *e){
			result = lsearch(e-m, e, value);
			if(result == e)
				return last;
			return result;
		}
		else{
			e+=m;
			continue;
		}
	}
	return lsearch(e-m, last, value);
}
/// Implements a fibbonacci ternary search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or last, in case the value is not in the range.
 */
int *fsearch(int* first, int* last, int value)
{
	/* Initialize fibonacci numbers */
	int fibm2 = 0;   // (m-2)'th Fibonacci No.
	int fibm1 = 1;   // (m-1)'th Fibonacci No.
	int fibm = fibm2 + fibm1;  // m'th Fibonacci

	/* fibm is going to store the smallest Fibonacci
	   Number greater than or equal to n */
	while (fibm < value)
	{
		fibm2 = fibm1;
		fibm1 = fibm;
		fibm  = fibm2 + fibm1;
	}

	// Marks the eliminated range from front
	int offset = -1;
	int n = last-first;
	/* while there are elements to be inspected. Note that
	   we compare arr[fibmm2] with x. When fibM becomes 1,
	   fibmm2 becomes 0 */
	while (fibm > 1)
	{
		// Check if fibmm2 is a valid location
		int i = min(offset+fibm2, n-1);

		/* If x is greater than the value at index fibmm2,
		   cut the subarray array from offset to i */
		if (first[i] < value)
		{
			fibm  = fibm1;
			fibm1 = fibm2;
			fibm2 = fibm - fibm1;
			offset = i;
		}

		/* If x is greater than the value at index fibmm2,
		   cut the subarray after i+1  */
		else if (first[i] > value)
		{
			fibm  = fibm2;
			fibm1 = fibm1 - fibm2;
			fibm2 = fibm - fibm1;
		}

		/* element found. return index */
		else return &first[i];
	}
	if(fibm1 && first[offset+1]==value)return &first[offset+1];

	/*element not found. return -1 */
	return last;
}
// Driver function.
int main(int argc, char* argv[])
{
	string arg;
	int start = 10, limit = 11, i = 0, j, size, n = 10, jump;
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
	if(jump < 1)
		return 1;
	size = start;
	int* A;
	A = (int*) malloc(sizeof(int)*limit);
	for(i = 0; i < limit; i++)
		A[i] = i;
	FunctionList f = {(Function) {lsearch, "Linear Search"}, (Function) {bsearch, "Binary Search"}, (Function) {rbsearch, "Rec Bin Search"}, (Function) {bsearch, "Ternary Search"}, 
		(Function) {rtsearch, "Rec Ternary Search"}, (Function) {jsearch, "Jump Search"}, (Function) {fsearch, "Fibbonacci Search"}};
	for(Function & ef : f)
		ef.time = (float*) malloc(sizeof(float)*n);
	time_point<steady_clock> t0; // start timepoint
	time_point<steady_clock> t1; // end timepoint
	// Executes several searchs in the data container.
	for(i = 0; size <= limit; size+=jump, i++){
#ifdef DEBUG
		cout << "Array: [ ";
		copy(A, A+size, ostream_iterator<int>( cout , " " ) );
		cout << "]\n";
#endif
		for(Function & ef : f){
#ifdef DEBUG
			cout << "------------------------------\nalgorithm = " << ef.name << ".\n------------------------------\n";
			int value = size;
			auto result = ef.ref( A, A+size, value);
#endif
			ef.time[i] = 0.0;
			for(j = 1; j < 101; j++){
				t0 = steady_clock::now();
				ef.ref( A, A+size, size-1);
				t1 = steady_clock::now();
				ef.time[i] = ((duration<float, milli> (t1 - t0).count()) - ef.time[i]) / j;
			}	
#ifdef DEBUG
			cout << "- time = " << ef.time[i] << " ms.\n";
			if (result != A+size)
			{
				cout << ">>> Found \"" << value << "\" at position " << distance(A, result) << ".\n";
			}
			else
			{
				cout << ">>> Value \"" << value << "\" not found in array!\n";
			}
#endif
		}
	}
	/// save results in a file.
	ofstream file("result.txt");
	file << setw(10) << left << "# N";
	for(Function & ef : f){
		file << left << setw(20) << ef.name;
	}
	size = start;
	file << endl;
	for(i = 0; i < n; i++, size += jump){
		file << setw(10) << size;
		for(Function & ef : f){
			file << setw(20) << left << ef.time[i];
		}
		file << endl;
	}
	return 0;
}






