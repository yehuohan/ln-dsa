
#include "usestl.h"
#include <bitset>

/*!
 * @brief bitset结构
 *
 */
void container_bitset(void)
{
    PutTitle("\nContainer bitset begin.\n");

    const int N = 32;
    std::bitset<N> bs;

    bs.set(0);
    PutContent("bitset string: " << bs);
    if (bs.any()) PutContent("any\n");

    bs.set();
    PutContent("bitset string: " << bs);
    if (bs.all()) PutContent("all\n");

    bs.reset();
    PutContent("bitset string: " << bs);
    if (bs.none()) PutContent("none\n");

    bs.set(10);
    if (bs.test(10))
        PutContent("bit10: " << bs[10]);

    PutTitle("\nContainer bitset end.\n");
}
