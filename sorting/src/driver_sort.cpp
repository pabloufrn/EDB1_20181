#include <iostream>  // cout, endl
#include <iterator>  // begin, end, ostream_iterator, distance()
#include <algorithm> // copy(), shuffle(), reverse()
#include <numeric>   // iota()
#include <random>    // random_device, mt19937
#include <sstream>   // istringstream
#include <functional>// std::function<>, std::less<>

#define DEFAULT_SAMPLE_SIZE 10

#include "../include/sorting_alg.h"

/// === Function prototypes
void print_array( sorting::iterator , sorting::iterator );
constexpr bool my_less ( const sorting::value_type&, const sorting::value_type& );
constexpr bool my_greater( const sorting::value_type&, const sorting::value_type& );

/// === Driver function
int main( int argc, char *argv[] )
{
    int N( DEFAULT_SAMPLE_SIZE ); // sample size
    sorting::Function f[] = {(sorting::Function) {sorting::insertion_sort, "INSERTION SORT"}, (sorting::Function) {sorting::selection_sort, "SELECTION SORT"}};
    if ( argc == 2 )
    {
        // Read the second argument
        std::istringstream iss( argv[1] );
        iss >> N;
        if ( iss.fail()  or N < 0  )
            N = DEFAULT_SAMPLE_SIZE;
    }

    // AVERAGE CASE
    {
        // Average case is all elements in no particular order.
        sorting::value_type *A = new sorting::value_type[ N ]; //!< The data structure
        // Prepare data for each running case
        std::iota( A, A+N, 1 ); // fill up array with sequential numbers starting at 1.
        // Average case is shuffled elements
	std::cout << "------------------------------------------------------\n";
	std::cout << "-------------------- AVERAGE CASE --------------------\n";
	std::cout << "------------------------------------------------------\n";
#ifdef RANDOM
        std::random_device rd;
        std::mt19937 g(rd()); // random seed.
#else
        std::mt19937 g(1); // fixed seed
#endif
        std::shuffle( A, A+N, g ); // shuffle numbers in the array.
        // Original array
	std::cout << " >> Function = ";
        std::cout << ">>> Array BEFORE selection sorting: ";
        print_array( A, A+N ); std::cout << "\n";

        // Sort elements in the data structure
        auto nc = sorting::selection_sort( A, A+N, my_less );
        std::cout << ">>> # of comparisons done: " << nc << std::endl;

        // Sorted array
        std::cout << ">>> Array AFTER selection sorting: ";
        print_array( A, A+N ); std::cout << "\n\n";

        delete [] A; // free up memory
    }
    // WORST CASE
    {
        // Worst case is all elements in reverse sorted order.
        sorting::value_type *A = new sorting::value_type[ N ]; //!< The data structure
        // Prepare data for each running case
        std::iota( A, A+N, 1 ); // fill up array with sequential numbers starting at 1.
        // Worst case is all elements in reverse order.
        std::reverse( A, A+N );
        // Original array
        std::cout << ">>> Array BEFORE selection sorting: ";
        print_array( A, A+N ); std::cout << "\n";

        // Sort elements in the data structure
        auto nc = sorting::selection_sort( A, A+N , my_less );
        std::cout << ">>> # of comparisons: " << nc << std::endl;

        // Sorted array
        std::cout << ">>> Array AFTER selection sorting: ";
        print_array( A, A+N ); std::cout << "\n\n";

        delete [] A; // free up memory
    }

    // BEST CASE
    {
        // Best case is all elements in sorted order.
        sorting::value_type *A = new sorting::value_type[ N ]; //!< The data structure
        // Prepare data for each running case
        std::iota( A, A+N, 1 ); // fill up array with sequential numbers starting at 1.
        // Original array
        std::cout << ">>> Array BEFORE selection sorting: ";
        print_array( A, A+N ); std::cout << "\n";

        // Sort elements in the data structure
        auto nc = sorting::selection_sort( A, A+N, my_less );
        std::cout << ">>> # of comparisons: " << nc << std::endl;

        // Sorted array
        std::cout << ">>> Array AFTER selection sorting: ";
        print_array( A, A+N ); std::cout << "\n\n";

        delete [] A; // free up memory
    }

    
    return 0;
}

///=== Function implementation

constexpr bool my_less( const sorting::value_type& a, const sorting::value_type& b )
{
    return a < b;
}
constexpr bool my_greater( const sorting::value_type& a, const sorting::value_type& b )
{
    return a > b;
}


/// Prints a range on the standard output.
void print_array( sorting::iterator first, sorting::iterator last )
{
    std::cout << "[ ";
    std::copy( first, last, std::ostream_iterator< int >( std::cout, " " ) );
    std::cout << "], size = " << std::distance( first, last );
    std::cout.flush();
}

//==== THE END ===//
