
#include "math/HashAlgorithm.h"
#include "math/TimeUtils.h"

unsigned int HashAlgorithm::PJWHash(const char* str, size_t len)
{
//    INIT_TIMER
//    START_TIMER
    unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
    unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
    unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
    unsigned int HighBits = (unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
    unsigned int hash = 0;
    unsigned int test = 0;

    for (size_t i = 0; i < len; i++)
    {
        hash = (hash << OneEighth) + str[i];

        if ((test = hash & HighBits) != 0)
        {
            hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
        }
    }
//    STOP_TIMER("HashAlgorithm::PJWHash")
    return hash;
}
/* End Of  P. J. Weinberger Hash Function */
