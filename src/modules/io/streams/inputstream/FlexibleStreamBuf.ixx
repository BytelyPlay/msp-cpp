module;
#include <fstream>
#include <vector>

export module FlexibleStreamBuf;

export template<typename T>
class FlexibleStreamBuf<T> : public std::basic_streambuf<T>
{
public:
    FlexibleStreamBuf(const T* start, const T* end);
};
