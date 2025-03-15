#include "core.h"

static void eval(mpz_t r, const mpz_t x, const eccrypt_curve_t& curve) {
    mpz_t a, b;

    mpz_init(a);
    mpz_init(b);

    mpz_powm_ui(a, x, 3, curve.p);
    mpz_mul(b, x, curve.a4);
    mpz_mod(b, b, curve.p);
    mpz_add(r, a, b);
    mpz_add(r, r, curve.a6);

    mpz_clear(a);
    mpz_clear(b);
}

void eccrypt_embed(eccrypt_point_t& p, eccrypt_point_t& q, const mpz_t x, const eccrypt_curve_t& curve) {
    mpz_t f;
    mpz_t t;
    mpz_t one;

    mpz_init(f);
    mpz_init(t);
    mpz_init_set_ui(one, 1);
    mpz_set(p.x, x);

    bool done = 0;
    while (!done) {
        eval(f, p.x, curve);
        if (mpz_legendre(f, curve.p) > 0) {
            done = true;
        }
        else {
            mpz_add(p.x, p.x, one);
        }
    }

    mpz_set(q.x, p.x);
    sqrt(p.y, f, curve.p);
    mpz_set(t, p.y);
    mpz_add(t, t, curve.p);
    mpz_mod(t, t, curve.p);

    if (mpz_cmp(q.y, p.y) < 0) {
        mpz_swap(q.y, p.y);
    }

    mpz_clear(f);
    mpz_clear(t);
    mpz_clear(one);
}
