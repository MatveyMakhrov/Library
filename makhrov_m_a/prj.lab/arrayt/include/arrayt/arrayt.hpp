#include <cstddef>
#include <exception>


const std::exception out_of_range("Error: Out of range");

template <typename T>

class ArrayT {
public:
	ArrayT() = default;
	ArrayT(const ArrayT& arr);
	explicit ArrayT(const std::ptrdiff_t size);
	ArrayT& operator=(const ArrayT& rhs);
	~ArrayT() { delete[] data_; }
	std::ptrdiff_t Ssize() const noexcept { return size_; };
	T& operator[](const std::ptrdiff_t i);
	const T& operator[](const std::ptrdiff_t i) const;
	void Resize(const std::ptrdiff_t size);
	void Remove(std::ptrdiff_t index);
	void Insert(T val, std::ptrdiff_t index);

	std::ptrdiff_t ssize() const noexcept { return size_; };
	void resize(const std::ptrdiff_t size);
	void remove(std::ptrdiff_t index);
	void insert(T val, std::ptrdiff_t index);
private:
	std::ptrdiff_t capacity_{ 0 };
	std::ptrdiff_t size_{ 0 };
	T* data_{ nullptr };
};

template<typename T>
ArrayT<T>::ArrayT(const ArrayT& arr) {
	capacity_ = arr.Ssize();
	size_ = arr.Ssize();
	data_ = new T[size_];
	for (std::ptrdiff_t i = 0; i < arr.size_; i++) {
		data_[i] = arr.data_[i];
	}
}

template<typename T>
ArrayT<T>::ArrayT(const std::ptrdiff_t size) {
	if (size < 0) {
		throw out_of_range;
	}
	else {
		size_ = size;
		capacity_ = size;
		data_ = new T[size];
		for (std::ptrdiff_t i = 0; i < size; ++i) {
			data_[i] = 0;
		}
	}
}

template<typename T>
ArrayT<T>& ArrayT<T>::operator=(const ArrayT<T>& rhs) {
	if (&rhs != this) {
		delete[] data_;
		size_ = rhs.Ssize();
		capacity_ = rhs.Ssize();
		data_ = new T[size_];
		for (std::ptrdiff_t i = 0; i < size_; ++i) {
			data_[i] = rhs[i];
		}
	}
	return *this;
}

template<typename T>
T& ArrayT<T>::operator[](const std::ptrdiff_t i) {
	if (0 <= i && i < size_) {
		return data_[i];
	}
	else {
		throw out_of_range;
	}
}

template<typename T>
const T& ArrayT<T>::operator[](const std::ptrdiff_t i) const {
	if (0 <= i && i < size_) {
		return data_[i];
	}
	else {
		throw out_of_range;
	}
}

template<typename T>
void ArrayT<T>::Resize(const std::ptrdiff_t size) {
	if (size < 1) {
		throw out_of_range;
	}
	else if (capacity_ <= size) {
		T* temp = new T[size * 2];
		for (std::ptrdiff_t i = 0; i < size * 2; i++) {
			temp[i] = 0;
		}
		for (std::ptrdiff_t i = 0; i < size_; i++) {
			temp[i] = data_[i];
		}
		size_ = size;
		capacity_ = size * 2;
		delete[] data_;
		data_ = temp;
		temp = nullptr;
	}
	else {
		size_ = size;
		for (std::ptrdiff_t i = size; i < capacity_; i++) {
			data_[i] = 0;
		}
	}
}

template<typename T>
void ArrayT<T>::Remove(std::ptrdiff_t index) {
	if (index<0 || index>size_) {
		throw out_of_range;
	}
	else {
		T last = data_[size_ - 1];
		this->Resize(size_ - 1);
		T* temp = new T[size_];
		for (std::ptrdiff_t i = 0; i < index; i++) {
			temp[i] = data_[i];
		}
		for (std::ptrdiff_t i = index; i < size_ - 1; i++) {
			temp[i] = data_[i + 1];
		}
		temp[size_ - 1] = last;
		delete[] data_;
		data_ = temp;
		temp = nullptr;
	}
}

template<typename T>
void ArrayT<T>::Insert(T val, std::ptrdiff_t index) {
	if (index<0 || index>size_) {
		throw out_of_range;
	}
	else {
		this->Resize(size_ + 1);
		T* temp = new T[size_];
		for (std::ptrdiff_t i = 0; i < index; i++) {
			temp[i] = data_[i];
		}
		temp[index] = val;
		for (std::ptrdiff_t i = index + 1; i < size_; i++) {
			temp[i] = data_[i - 1];
		}
		delete[] data_;
		data_ = temp;
		temp = nullptr;
	}
}

template<typename T>
void ArrayT<T>::resize(const std::ptrdiff_t size) {
	if (size < 1) {
		throw out_of_range;
	}
	else if (capacity_ <= size) {
		T* temp = new T[size * 2];
		for (std::ptrdiff_t i = 0; i < size; i++) {
			temp[i] = 0;
		}
		for (std::ptrdiff_t i = 0; i < size_; i++) {
			temp[i] = data_[i];
		}
		size_ = size;
		capacity_ = size * 2;
		delete[] data_;
		data_ = temp;
		temp = nullptr;
	}
	else {
		size_ = size;
		for (std::ptrdiff_t i = size; i < capacity_; i++) {
			data_[i] = 0;
		}
	}
}

template<typename T>
void ArrayT<T>::remove(std::ptrdiff_t index) {
	if (index<0 || index>size_) {
		throw out_of_range;
	}
	else {
		this->resize(size_ - 1);
		T* temp = new T[size_ - 1];
		for (std::ptrdiff_t i = 0; i < index; i++) {
			temp[i] = data_[i];
		}
		for (std::ptrdiff_t i = index; i < size_ - 1; i++) {
			temp[i] = data_[i + 1];
		}
		delete[] data_;
		data_ = temp;
		temp = nullptr;
	}
}

template<typename T>
void ArrayT<T>::insert(T val, std::ptrdiff_t index) {
	if (index<0 || index>size_) {
		throw out_of_range;
	}
	else {
		this->resize(size_ + 1);
		T* temp = new T[size_ + 1];
		for (std::ptrdiff_t i = 0; i < index; i++) {
			temp[i] = data_[i];
		}
		temp[index] = val;
		for (std::ptrdiff_t i = index + 1; i < size_ + 1; i++) {
			temp[i] = data_[i - 1];
		}
		delete[] data_;
		data_ = temp;
		temp = nullptr;
	}
}