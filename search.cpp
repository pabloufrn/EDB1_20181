#include <iostream>  // cout, endl
#include <algorithm> // copy
#include <iterator>  // ostream_iterator, begin(), end()
#include <cmath>     // sqrt
/// Implements an iterative linear seach on an range [first; last) of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or NULL, in case the value is not in the range.
 */

using namespace std;

int* lsearch(int *first, int *last, int value )
{
    while(first != last){
        if(*first == value)
            return first;
        first++;
    }
    return NULL; // STUB
}

/// Implements an interative binary search on an array of integers.
/*!
 * \param first Pointer to the first element in the range.
 * \param last Pointer past the last valid element in the range.
 * \param value The target value we are looking for within the range.
 * \return A pointer to the target value within the range; or NULL, in case the value is not in the range.
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
    return NULL; 
}

int* jsearch(int *first, int *last, int value )
{
    int n = last-first+1;
    int m = sqrt(n);
    int i;
    int *e;
    for(i = m; i < n; i+=m){
        e = first+i;
        if(value == *e)
            return e;
        else if(value < *e)
            return lsearch(e-i, e, value);
        else
            continue;
    }
    return NULL;
}

// Driver function.
int main()
{
    int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // Data container.
    int targets[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , -4, 20 }; // Target values for testing.
    int* (*f[]) (int*, int*, int) = {lsearch, bsearch, jsearch};
    // Prints out the original data container.
    cout << "Array: [ ";
    copy(begin(A), end(A), ostream_iterator<int>( cout , " " ) );
    cout << "]\n";

    // Executes several searchs in the data container.
    for(int c = 0; c < 3; c++){
        cout << "------------------------------\nExecutando algoritmo numero " << c << ".\n------------------------------\n";
        for( const auto & e : targets )
        {
            // Look for target in the entire range.
            auto result = f[c]( begin(A), end(A), e);
            // Process the result
            if (result)
            {
                cout << ">>> Found \"" << e << "\" at position "
                    << distance(begin(A), result) << ".\n";
            }
            else
            {
                cout << ">>> Value \"" << e << "\" not found in array!\n";
            }
        }
    }
    return 0;
}
