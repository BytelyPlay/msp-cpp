module;
#include <fstream>
#include <vector>

export module VectorStreamBuf;

export template<typename T>
class VectorStreamBuf<T> : std::basic_streambuf<T>
{
public:
    VectorStreamBuf(std::vector<T>& vec);
};
