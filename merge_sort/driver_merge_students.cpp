/**!
 *  @brief Testbed program for the merge and mergesort implementation.
 *  @date April, 4th
 *  @author Selan
 *
 */
#include <iostream> // cout, endl
#include <iterator> // distance
#include <algorithm> // copy
#include <array>
#include <functional>
#include <cstring>
//=== Aliases
using value_type = int;
using Compare = std::function<bool(value_type, value_type)>;

//=== Function impementation

/// Print out the elements in the requested rante [first;last).
void print( value_type *first, value_type *last )
{
	std::cout << "[ ";
	std::copy( first, last, std::ostream_iterator< value_type >(std::cout, " ") );
	std::cout << "]";
}


/**!
 * Merge two sorted ranges, `L`, and `R`,  into a single range, `A`.
 * The first sorted range is `[l_first; l_last)`.
 * The second sorted range is `[r_first; r_last)`.
 * \note The destination range begins at `a_first` and has enough storage
 * area to receive all elements of `L` and `R` ranges combined.
 * @param l_first the begining of the range `L`.
 * @param l_last address just past the last element of the range `L`.
 * @param r_first the begining of the range `R`.
 * @param r_last address just past the last element of the range `R`.
 * @param a_first the begining of the range `A`.
 * @param comp The comparison function that implements a _strict order_ binary relation among the elements we want to merge.
 */
void merge( value_type *l_first, value_type *l_last, // [l_first; l_last)
     value_type *r_first, value_type *r_last, // [r_first; r_last)
     value_type *a_first, Compare comp= std::less<value_type>() )
{
	int size = (r_last-r_first) + (l_last-l_first); 
	value_type* a_last = a_first + size; 
	while(a_first < a_last)
	{
		if(l_first == l_last) // copia o resto da direita para A
		{
			memcpy(a_first, r_first, (r_last-r_first)*sizeof(value_type)); // A = r_first ate r_last
			return;
		}	
		if(r_first == r_last) // copia o resto da esquerda para A
		{
			memcpy(a_first, l_first, (l_last-l_first)*sizeof(value_type)); // A = l_first ate l_last
			return;
		}
		if(*l_first < *r_first)
			*a_first = *l_first++;
		else
			*a_first = *r_first++;
		a_first++;	
	}
}

void merge_sort(value_type* first, value_type* last, Compare comp= std::less<value_type>())
{
	// divide array
	// Find out the size of the first half.
	if(last - first < 2)
		return;
	auto m( (last-first) / 2 );
	// Print each half.
	print( first, first+m );
	std::cout << " ";
	print( first+m, last);
	std::cout << '\n';

	// Create the left and right auxiliary arrays.
	auto L_sz = m; // `L` size.
	auto R_sz = (last-first)-L_sz; // `R` has the size of `A` minus the size of `L`.
	value_type *L = new value_type[ L_sz ]; // Dynamic allocation.
	value_type *R = new value_type[ R_sz ];

	// Copy elements from each sorted halves of 'A', respectively into 'L' and 'R'.
	std::copy( first, first+m, L );
	std::copy( first+m, last, R );

	merge_sort(L, L+L_sz, comp); // lado direito
	merge_sort(R, R+R_sz, comp); // lado direito
	// Merge the two sorted halves back into array 'A'.
	merge( L, L+L_sz, R, R+R_sz, first);

	// Free auxiliary memory to avoid any memory leak.
	delete [] L;
	delete [] R;
}
int main()
{
	// The container length.
	constexpr size_t AR_SIZE=11;
	// The array we wish to partition.
	std::array< value_type, AR_SIZE > A { { 9, 8, 1, 2, 10, 7, 5, 3, 4, 6, 0 } };

	// Print the original array.
	std::cout << ">>> Original array: ";
	print( A.begin(), A.end() );
	std::cout << std::endl;
	merge_sort(A.begin(), A.end());
	// Print the result: a sorted merged array.
	std::cout << ">>> Merged array: ";
	print( A.begin(), A.end() );
	std::cout << std::endl;

	return 0;
}
