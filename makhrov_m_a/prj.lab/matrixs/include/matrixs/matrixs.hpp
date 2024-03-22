#pragma once
#ifndef matrixs_matrixs_HPP_20231503 
#define matrixs_matrixs_HPP_20231503

#include <iosfwd>
#include <cstddef>
#include <utility>
#include <iostream>

class MatrixS {
public:
	using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

public:
	explicit MatrixS(const SizeType& size = { 0,0 });
	MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n);
	MatrixS(const MatrixS& rhs);
	~MatrixS();

	MatrixS& operator=(const MatrixS& rhs);

	[[nodiscard]] int& at(const SizeType& elem);
	[[nodiscard]] const int& at(const SizeType& elem) const;
	[[nodiscard]] int& at(const std::ptrdiff_t i, const std::ptrdiff_t j);
	[[nodiscard]] const int& at(const std::ptrdiff_t i, const std::ptrdiff_t j) const;

	void resize(const SizeType& new_size);
	void resize(const std::ptrdiff_t i, const std::ptrdiff_t j);



	[[nodiscard]] const SizeType& ssize() const noexcept;
	[[nodiscard]] std::ptrdiff_t nRows() const noexcept;
	[[nodiscard]] std::ptrdiff_t nCols() const noexcept;

private:
	int** data_{ nullptr };
	ptrdiff_t m_{ 0 };
	ptrdiff_t n_{ 0 };
	SizeType size_{ m_,n_ };
};



#endif