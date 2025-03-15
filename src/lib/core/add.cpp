#include "core.h"

void eccrypt_point_add(eccrypt_point_t& r, const eccrypt_point_t& p, const eccrypt_point_t& q, const eccrypt_curve_t& curve)
{
    mpz_t x;
    mpz_t y;
    mpz_t u;
    mpz_t v;
    mpz_t s;

    mpz_init(x);
    mpz_init(y);
    mpz_init(u);
    mpz_init(v);
    mpz_init(s);

    // Calculate slope
    mpz_mul(u, p.x, p.x);
    mpz_mod(u, u, curve.p);
    mpz_mul(v, q.x, q.x);
    mpz_mod(v, v, curve.p);
    mpz_mul(s, p.x, q.x);
    mpz_mod(s, s, curve.p);
    mpz_add(s, s, u);
    mpz_add(s, s, v);
    mpz_add(s, s, curve.a4);
    mpz_mod(s, s, curve.p);
    mpz_add(u, p.y, q.y);
    mpz_invert(u, u, curve.p);
    mpz_mul(s, s, u);

    // Calculate coordinates
    mpz_mul(x, s, s);
    mpz_sub(x, x, p.x);
    mpz_sub(x, x, q.x);
    mpz_mod(x, x, curve.p);
    mpz_sub(y, p.x, x);
    mpz_mul(y, y, s);
    mpz_sub(y, y, p.y);
    mpz_mod(y, y, curve.p);

    // Return
    mpz_set(r.x, x);
    mpz_set(r.y, y);

    mpz_clear(x);
    mpz_clear(y);
    mpz_clear(u);
    mpz_clear(v);
    mpz_clear(s);
}
