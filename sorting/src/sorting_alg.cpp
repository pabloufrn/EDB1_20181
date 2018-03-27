#include "../include/sorting_alg.h"
namespace sorting {

    size_t selection_sort( iterator first_ , iterator last_, Compare comp_ )
    {
    	auto last_element = first_;
	auto sm = last_element; // smaller element
	int count = 0;
	// find smaller
	while(last_element != last_)
	{
		sm = last_element;
		for(auto aux = last_element; aux != last_; aux++)
		{
			count++;
			if(*aux < *sm)
			{
				sm = aux;
			}
		}
		std::swap(*sm, *(last_element));
		last_element++;
	}
	return count;

    }
    size_t insertion_sort( iterator first_ , iterator last_, Compare comp_ )
    {
        auto l( first_ );
        size_t ncomp(0);

        while ( l != last_ )
        {
            size_t nc(0);
            auto value( *l ); // value to be sort-inserted
            l = insert_sorted( first_, l, value, comp_, nc );

            // Accumulate the total number of comparisons so far.
            ncomp += nc;
        }

        return ncomp; // total number of comparisons made.
    }

    iterator insert_sorted( iterator first_, iterator last_, value_type value, Compare comp_, size_t &ncomp_ )
    {
        // reset comparison count.
        ncomp_ = 0;

        // Pos points to the last valid element in the range.
        auto pos( last_ -1 );

        // --------------------------------------------------------------------------------
        // P: [first;last) is a valid range that mighe have zero or more elements.
        // --------------------------------------------------------------------------------
        // *** Loop invariant: All elements in [pos+1;last) are greater than 'value'. ***
        // --------------------------------------------------------------------------------

        // We should traverse the range from the last elemento until the first,
        // trying to find the proper location for the new value so that the
        // sorting of the range is preserved.
        while( pos >= first_ and comp_( value, *pos ) )
        {
            ncomp_++; // Number of comparisons.

            // Shift the element that 'pos' points to one position to the right.
            // This opens up a "hole" to hold the new value.
            *(pos+1) = *pos; // You might want to use std::swap(*(pos+1), pos) for better performance.

            // Move 'pos' towards the begining of the range.
            pos--;
            // --------------------------------------------------------------------------------
            // *** Loop invariant: All elements in [pos+1;last) are greater than 'value'. ***
            // --------------------------------------------------------------------------------
        }

        // --------------------------------------------------------------------------------
        // Q: 'pos' points to a position just ahead of the local of insertion.
        // --------------------------------------------------------------------------------
        *(pos+1) = value; // Insert the new value, preserving the sorting order.

        return last_+1; // Return the new last.
    }
}
