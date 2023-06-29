#include <cstddef>

class ArrayD {
public:
    ArrayD() = default;
    ArrayD(const std::ptrdiff_t size);
    ArrayD(const ArrayD& lhs);
    ~ArrayD();

    ArrayD& operator=(const ArrayD& rhs);
    double& operator[] (const std::ptrdiff_t indx);
    const double& operator[](const std::ptrdiff_t indx) const;

    ptrdiff_t ssize() const noexcept;
    void resize(const std::ptrdiff_t new_size);
    void insert(std::ptrdiff_t i, const double value);
    void remove(std::ptrdiff_t i);

private:
    std::ptrdiff_t capacity_{ 0 };
    ptrdiff_t size_{ 0 };
    double* data_ = nullptr;
};

//bool notError(std::ptrdiff_t a, std::ptrdiff_t b);