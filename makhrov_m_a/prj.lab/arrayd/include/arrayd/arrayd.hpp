#include <cstddef>

class ArrayD {
public:
    ArrayD();
    ArrayD(const ArrayD&);
    ArrauD(const std::ptrdiff_t size);
    explicit ArrayD(const std::ptrdiff_t size = 0);
    ~ArrayD();

    ArrayD operator=(const ArrayD&);
    ArrayD operator[]();


};