#include <ctime>
#include <gmp.h>


struct eccrypt_point_t {
    mpz_t x;
    mpz_t y;
    bool infinity;
};

struct eccrypt_curve_t {
    mpz_t a4;
    mpz_t a6;
    mpz_t p;
    eccrypt_point_t g;
};

void eccrypt_point_init(eccrypt_point_t& p, bool infinity = false);
void eccrypt_point_set(eccrypt_point_t& p, const char* x, const char* y, int base);
void eccrypt_point_copy(eccrypt_point_t& r, const eccrypt_point_t& p);
bool eccrypt_point_eq(const eccrypt_point_t& p, const eccrypt_point_t& q);

void eccrypt_point_add(eccrypt_point_t& r, const eccrypt_point_t& p, const eccrypt_point_t& q, const eccrypt_curve_t& curve);
void eccrypt_point_mul(eccrypt_point_t& r, const eccrypt_point_t& p, const mpz_t scalar, const eccrypt_curve_t& curve);
void eccrypt_embed(eccrypt_point_t& p, eccrypt_point_t& q, const mpz_t x, const eccrypt_curve_t& curve);

bool sqrt(mpz_t r, const mpz_t n, const mpz_t p);
