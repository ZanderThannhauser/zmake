
#ifndef STRUCT_MPZ
#define STRUCT_MPZ

#include "../mp_limb_t.h"

struct mpz
{
    int _mp_alloc;    /* Number of *limbs* allocated and pointed to by the
                         _mp_d field.  */
    
    int _mp_size;     /* abs(_mp_size) is the number of limbs the last field
                         points to.  If _mp_size is negative this is a negative
                         number.  */
    
    mp_limb_t *_mp_d; /* Pointer to the limbs.  */
};

typedef struct mpz mpz_t[1];


#endif
