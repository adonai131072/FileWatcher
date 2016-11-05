#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <algorithm>
#include <tuple>


namespace Fuhihi {

    template<typename InputIt1, typename InputIt2, typename OutputIt1, typename OutputIt2, typename Compare>
    std::tuple<OutputIt1, OutputIt1, OutputIt2> set_change(InputIt1 first1, InputIt1 last1,
                                                        InputIt2 first2, InputIt2 last2,
                                                        OutputIt1 o_first1, OutputIt1 o_first2, OutputIt2 o_first3,
                                                        Compare comp)
    {
        while(true) {
            if(first1 == last1) {
                OutputIt1 o_last2 = std::copy(first2, last2, o_first2);
                return std::tie(o_first1, o_last2, o_first3);
            }
            if(first2 == last2) {
                OutputIt1 o_last1 = std::copy(first1, last1, o_first1);
                return std::tie(o_last1, o_first2, o_first3);
            }
            if(comp(*first1, *first2)) {
                *o_first1++ = *first1++;
            }
            else {
                if(!comp(*first2, *first1)) {
                    *o_first3++ = std::tie(*first1++, *first2);
                }
                else {
                    *o_first2++ = *first2;
                }
                ++first2;
            }
        }
        return std::tie(o_first1, o_first2, o_first3);
    }

}

#endif // ALGORITHM_H
