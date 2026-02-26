module;

module VectorStreamBuf;

// PUBLIC
template <typename T>
VectorStreamBuf<T>::VectorStreamBuf(std::vector<T>& vec)
{
    setg(vec.cbegin(), vec.cend());
}
