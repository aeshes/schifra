#include "core.h"

void eccrypt_point_mul(eccrypt_point_t& r, const eccrypt_point_t& p, const mpz_t scalar, const eccrypt_curve_t& curve) {
    eccrypt_point_t q;

    eccrypt_point_init(q);
    eccrypt_point_copy(q, p);

    int i = mpz_sizeinbase(scalar, 2) - 2;
    while (i >= 0) {
        eccrypt_point_add(q, q, q, curve);
        if (mpz_tstbit(scalar, i)) {
            eccrypt_point_add(q, q, p, curve);
        }
        i--;
    }

    eccrypt_point_copy(r, q);
    mpz_clear(q.x);
    mpz_clear(q.y);
}
