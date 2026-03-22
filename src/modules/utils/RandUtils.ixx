module;
#include <cstdint>

export module RandUtils;

// Not meant for cryptographic randomness, use openssl for that
export namespace RandUtils
{
    /* long long randRange(long long min, long long max);
    int randRange(int min, int max);

    double randRange(double min, double max);
    float randRange(float min, float max);
*/
    void randBytes(std::size_t amount, unsigned char* begin);
}