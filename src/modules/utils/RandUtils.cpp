module;
#include <random>

module RandUtils;

/*long long RandUtils::randRange(long long min, long long max)
{
    static std::random_device randDevice;
    static auto rand = std::mt19937(randDevice());

}
int RandUtils::randRange(int min, int max)
{

}

double RandUtils::randRange(double min, double max)
{

}
float RandUtils::randRange(float min, float max)
{

}
*/
void RandUtils::randBytes(size_t amount, unsigned char* begin)
{
    static std::random_device randDevice;
    static auto rand = std::mt19937(randDevice());

    static
    std::
    uniform_int_distribution
    <unsigned char>
    dist(0x00, 0xFF);

    for (size_t i = 0; i < amount; i++)
        begin[i] = dist(rand);
}
