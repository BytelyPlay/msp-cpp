module;

module FlexibleStreamBuf;

// PUBLIC
template <typename T>
FlexibleStreamBuf<T>::FlexibleStreamBuf(const T* start, const T* end)
{
    setg(start, start + 1 , end);
}
