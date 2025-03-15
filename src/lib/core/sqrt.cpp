#include "core.h"

gmp_randstate_t state;

void ff_rand_init() {
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, std::time(NULL));
}

void ff_rand(mpz_t n, const mpz_t modulus) {
    mpz_urandomb(n, state, 256);
    mpz_mod(n, n, modulus);
}

bool ff_cmp_ui(mpz_t a, long b, const mpz_t p) {
    mpz_t t;

    mpz_init_set(t, a);
    mpz_mod(t, t, p);

    int r = mpz_cmp_ui(t, b);

    mpz_clear(t);

    return r == 0;
}


bool sqrt(mpz_t r, const mpz_t n, const mpz_t p) {
    mpz_t q;
    mpz_t t;
    mpz_t u;
    mpz_t v;
    mpz_t z;
    mpz_t c;
    mpz_t x;
    mpz_t y;
    mpz_t b;

    if (mpz_legendre(n, p) < 0) {
        return false;
    }

    mpz_init(q);
    mpz_init(t);
    mpz_init(u);
    mpz_init(v);
    mpz_init(z);
    mpz_init(c);
    mpz_init(x);
    mpz_init(y);
    mpz_init(b);

    mpz_sub_ui(q, p ,1);

    long s = 0;
    while (mpz_tstbit(q, 0) == 0) {
        mpz_divexact_ui(q, q, 2);
        s++;
    }

    if (s == 1) {
       mpz_set(t, p);
       mpz_add_ui(t, t, 1);
       mpz_divexact_ui(t, t, 4);
       mpz_powm(r, n, t, p);

       mpz_clear(q);
       mpz_clear(t);
       mpz_clear(u);
       mpz_clear(z);
       mpz_clear(c);
       mpz_clear(x);
       mpz_clear(y);
       mpz_clear(b);

       return true;
    }

    long i = 1;
    while (i >= 0) {
        ff_rand(z, p);
        i = mpz_legendre(z, p);
    }

    gmp_printf("Random non-residue: %Zd\n", z);

    mpz_powm(c, z, q, p);

    gmp_printf("c = %Zd\n", c);

    mpz_add_ui(u, q, 1);
    mpz_divexact_ui(u, u, 2);
    mpz_powm(r, n, u, p);
    mpz_powm(t, n, q, p);

    gmp_printf("r = %Zd\n", r);
    gmp_printf("t = %Zd\n", t);

    long m = s;

    while (true) {
        if (ff_cmp_ui(t, 1, p)) {
            mpz_clear(q);
            mpz_clear(t);
            mpz_clear(u);
            mpz_clear(z);
            mpz_clear(c);
            mpz_clear(x);
            mpz_clear(y);
            mpz_clear(b);

            return true;
        }
        else {
            long i = 1;
            mpz_set(x, t);
            while (i < m) {
                mpz_powm_ui(x, x, 2, p);
                if (mpz_cmp_ui(x, 1) == 0) {
                    break;
                }
                i++;
            }

            gmp_printf("i = %d\n", i);

            long e = m - i - 1;
            mpz_set(b, c);
            while (e > 0) {
                mpz_powm_ui(b, b, 2, p);
                e--;
            }
            mpz_mul(c, b, b);
            mpz_mod(c, c, p);

            mpz_mul(t, t, c);
            mpz_mod(t, t, p);

            mpz_mul(r, r, b);
            mpz_mod(r, r, p);

            m = i;
        }
    }

    return false;
}
