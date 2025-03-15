#include "core.h"

void eccrypt_point_init(eccrypt_point_t& p, bool infinity)
{
    mpz_init(p.x);
    mpz_init(p.y);
    p.infinity = infinity;
}

void eccrypt_point_set(eccrypt_point_t& p, const char* x, const char* y, int base)
{
    mpz_init_set_str(p.x, x, base);
    mpz_init_set_str(p.y, y, base);
}

void eccrypt_point_copy(eccrypt_point_t& r, const eccrypt_point_t& p)
{
    mpz_set(r.x, p.x);
    mpz_set(r.y, p.y);
}

bool eccrypt_point_eq(const eccrypt_point_t& p, const eccrypt_point_t& q)
{
    return mpz_cmp(p.x, q.x) == 0 && mpz_cmp(p.y, q.y) == 0;
}
