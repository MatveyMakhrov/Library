#include <arrayd/arrayd.hpp>
#include <stdexcept>

ArrayD::ArrayD(const std::ptrdiff_t size) {
    if (size < 0) {
        throw std::invalid_argument("Size of the new array must be greater than 0");
    }
    if (size > 0) {
        resize(size);
    }
}

ArrayD& ArrayD::operator=(const ArrayD& other) {
    if (this != &other) {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;

        if (other.capacity_ > 0) {
            data_ = new double[other.capacity_];
            capacity_ = other.capacity_;
            for (std::ptrdiff_t i = 0; i < other.size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
        size_ = other.size_;
    }
    return *this;
}

ArrayD::ArrayD(const ArrayD& other) {
    size_ = other.size_;
    capacity_ = other.capacity_;

    if (capacity_ > 0) {
        data_ = new double[capacity_];
        for (std::ptrdiff_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }
    else {
        data_ = nullptr;
    }
}

ArrayD::~ArrayD() {
    delete[] data_;
}

[[nodiscard]] double& ArrayD::operator[](const std::ptrdiff_t i) {
    if (i < 0 || i >= size_) {
        throw std::out_of_range("Index out of range");
    }
    return data_[i];
}

[[nodiscard]] const double& ArrayD::operator[](const std::ptrdiff_t i) const {
    if (i < 0 || i >= size_)
        throw std::out_of_range("Index out of range");
    return data_[i];
}

[[nodiscard]] std::ptrdiff_t ArrayD::ssize() const noexcept {
    return size_;
}

void ArrayD::resize(const std::ptrdiff_t new_size) {
    if (new_size <= 0) {
        throw std::invalid_argument("New size must be greater than 0");
    }
    if (new_size <= size_) {
        size_ = new_size; 
        return;
    }
    if (new_size > capacity_) {
        double* new_data = new double[new_size] {};
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = data_[i];
        }
        delete[] data_;
        data_ = new_data;
        size_ = new_size;
        capacity_ = new_size * 2;
        return;
    }
    if (new_size <= capacity_) {
        size_ = new_size;
    }
}

void ArrayD::insert(const std::ptrdiff_t i, const double value) {
    if (i < 0 || i > size_) {
        throw std::invalid_argument("Index out of range");
    }
    if (size_ == capacity_) {
        resize(size_ + 1);
    }
    if (size_ == 0) {
        data_[0] = value;
    }
    else {
        for (ptrdiff_t j = size_ - 1; j >= i; --j) {
            data_[j + 1] = data_[j];
        }
        data_[i] = value;
    }
    size_++;
}

void ArrayD::remove(const std::ptrdiff_t i) {
    if (size_ == 0) {
        return;
    }
    if (i < 0 || i >= size_) {
        throw std::invalid_argument("Index out of range");
    }
    for (ptrdiff_t j = i; j < size_ - 1; ++j) {
        data_[j] = data_[j + 1];
    }
    size_--;
}