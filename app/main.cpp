#include "core.h"

void init_curve(eccrypt_curve_t& curve)
{
    mpz_init_set_str(curve.p, "23", 10);
    mpz_init_set_str(curve.a4, "1", 10);
    mpz_init_set_str(curve.a6, "1", 10);
}

int main()
{
    eccrypt_curve_t curve;
    eccrypt_point_t p, q, r, s;
    init_curve(curve);
    eccrypt_point_init(p);
    eccrypt_point_init(q);
    eccrypt_point_init(r);
    eccrypt_point_init(s);
    eccrypt_point_set(p, "0", "1", 10);
    eccrypt_point_set(q, "9", "7", 10);

    eccrypt_point_add(r, p, p, curve);

    gmp_printf("(%Zd, %Zd)\n", r.x, r.y);

    mpz_t k;
    mpz_init_set_str(k, "28", 10);

    eccrypt_point_mul(s, p, k, curve);
    gmp_printf("(%Zd, %Zd)\n", s.x, s.y);

    mpz_t x;
    mpz_init_set_ui(x, 13);

    eccrypt_embed(p, q, x, curve);
    gmp_printf("(%Zd, %Zd)\n", p.x, p.y);
    gmp_printf("(%Zd, %Zd)\n", q.x, q.y);
}
