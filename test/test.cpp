#include <gtest/gtest.h>
#include "core.h"

void init_curve(eccrypt_curve_t& curve)
{
    mpz_init_set_str(curve.p, "23", 10);
    mpz_init_set_str(curve.a4, "1", 10);
    mpz_init_set_str(curve.a6, "1", 10);
}

TEST(Add, AddPoints)
{
    eccrypt_curve_t curve;
    eccrypt_point_t p, q, r, e;
    init_curve(curve);
    eccrypt_point_init(p);
    eccrypt_point_init(q);
    eccrypt_point_init(r);
    eccrypt_point_init(e);
    eccrypt_point_set(p, "0", "1", 10);
    eccrypt_point_set(q, "12", "4", 10);
    eccrypt_point_set(e, "1", "16", 10);

    eccrypt_point_add(r, p, q, curve);

    ASSERT_TRUE(eccrypt_point_eq(r, e));
}
