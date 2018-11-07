
#ifndef _HASHALGORITHM_H_
#define _HASHALGORITHM_H_

#include <stddef.h>

class HashAlgorithm {

public:
    static unsigned int PJWHash(const char* str, size_t len);
};


#endif /* _HASHALGORITHM_H_ */
