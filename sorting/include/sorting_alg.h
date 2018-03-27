#ifndef _SORTING_ALG_H_
#define _SORTING_ALG_H_

#include <functional>// std::function<>, std::less<>

namespace sorting
{
	/// === Alias
	using iterator = int *; //!< alias for the type of range pointer.
	using value_type = int;     //!< data type used in this example code.
	using Compare = std::function< bool( const value_type&, const value_type& ) >; //!< Comparison function alias.

	struct Function{
		size_t (*fp) (iterator first_ , iterator last_, Compare comp_);
		char fname[30];	

	};
	/// === Function prototypes
	/*!
	 * Insert a new value in the sorted range [first;last), preserving the original sorting order.
	 * @param first Pointer the the first element in the range [first;last)
	 * @param last Pointer to the past-the-end position.
	 * @param value Value we want to insert.
	 * @param comp The comparison function we're using to sort the elements.
	 * @param ncomp Reference to the number of comparisons made during the insertion process.
	 * @return Pointer to the new last, after the insertion.
	 */
	iterator insert_sorted( iterator first_, iterator last_, value_type value_, Compare comp, size_t &ncomp );

	/*!
	 * Sorts a range of integers in [first;last) based the insertion sort algorithm.
	 * @param first_ iterator to the first element in the range.
	 * @param last_ iterator to the position past-the-last valid element.
	 * @param comp_ The comparison function we're using to sort the elements.
	 * @return The total number of comparisons made during the sorting process.
	 */
	size_t insertion_sort( iterator first_ , iterator last_, Compare comp_ );

	/*!
	 * Sorts a range of integers [first;last) based on the selection sort algorithm.
	 * @param first_ iterator to the first element in the range.
	 * @param last_ iterator to the position past-the-last valid element.
	 * @param comp_ The comparison function we're using to sort the elements.
	 * @return The total number of comparisons made during the sorting process.
	 */
	size_t selection_sort( iterator first_ , iterator last_, Compare comp_ );
}

#endif
