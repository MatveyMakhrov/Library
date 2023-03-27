#include "include/rational/rational.hpp"
#include <iostream>

Rational::Rational() {
    num_ = 0;
    denum_ = 1;
}
Rational::Rational(int32_t numberInp) {
    num_ = numberInp;
    denum_ = 1;
}
Rational::Rational(const Rational& rhs) {
    num_ = rhs.num_;
    denum_ = rhs.denum_;
}
Rational::Rational(const int32_t num_inp,
    const int32_t denum_inp) {
    reducing();
    if (denum_inp == 0) {
        throw std::invalid_argument("Expected positive denominator");
    }
    if (denum_inp < 0) {
        num_ = -num_inp;
        denum_ = -denum_inp;
    }
    else {
        num_ = num_inp;
        denum_ = denum_inp;
    }
}


Rational& Rational::operator=(const Rational& rhs) {  // assignment operators from here
    num_ = rhs.num_;
    denum_ = rhs.denum_;
    return *this;
}

Rational& Rational::operator+=(const Rational& rhs) {
    int32_t cd = rhs.denum_ / gcd(denum_, rhs.denum_);
    num_ *= cd;
    denum_ *= cd;
    num_ += denum_ / rhs.denum_ * rhs.num_;
    reducing();
    return *this;
}

Rational& Rational::operator-=(const Rational& rhs) {
    int32_t cd = rhs.denum_ / gcd(denum_, rhs.denum_);
    num_ *= cd;
    denum_ *= cd;
    num_ -= denum_ / rhs.denum_ * rhs.num_;
    reducing();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    num_ *= rhs.num_;
    denum_ *= rhs.denum_;
    reducing();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.isZero()) {
        throw std::overflow_error("Divide by zero exception");
    }
    num_ *= rhs.denum_;
    denum_ *= rhs.num_;
    reducing();
    return *this;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}

Rational& Rational::operator--() {
    *this -= 1;
    return *this;
}

Rational& Rational::operator%=(const Rational& rhs) {
    int32_t cd = rhs.denum_ / gcd(denum_, rhs.denum_);
    num_ *= cd;
    denum_ *= cd;
    num_ %= denum_ / rhs.denum_ * rhs.num_;
    reducing();
    return *this;
}

bool Rational::isPositive() const {  // sign-like methods
    return num_ > 0;
}

bool Rational::isZero() const {
    return num_ == 0;
}

bool Rational::isNegative() const {
    return num_ < 0;
}

std::ostream& operator<<(std::ostream& ostrm,
    const Rational& rhs) {
    return rhs.writeTo(ostrm);
}
std::istream& operator>>(std::istream& istrm,
    Rational& rhs) {
    return rhs.readFrom(istrm);
}

Rational& operator+(Rational& rhs) {

    return rhs;
}

Rational& operator-(Rational& rhs) {
    Rational tmp;
    tmp -= rhs;
    return tmp;
}

Rational operator+(Rational lhs, const Rational& rhs) { // these use assignment analogs
    lhs += rhs;
    return lhs;
}
Rational operator-(Rational lhs, const Rational& rhs) {
    lhs -= rhs;
    return lhs;
}
Rational operator*(Rational lhs, const Rational& rhs) {
    lhs *= rhs;
    return lhs;
}
Rational operator/(Rational lhs, const Rational& rhs) {
    lhs /= rhs;
    return lhs;
}
Rational operator%(Rational lhs, const Rational& rhs)
{
    lhs %= rhs;
    return lhs;
}

Rational sqr(Rational myRat) {
    myRat *= myRat;
    return myRat;
}
Rational pow(Rational myRat, int32_t power) {
    Rational answer(1);
    while (power) {
        if (power & 1) {
            answer *= myRat;
        }
        myRat = sqr(myRat);
        power >>= 1;
    }
    return answer;
}

bool operator==(Rational lhs, const Rational& rhs) {
    lhs -= rhs;
    return lhs.isZero();
}
bool operator>(Rational lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.Rational::isPositive();
}
bool operator<(Rational lhs, const Rational& rhs) {
    Rational diff = lhs - rhs;
    return diff.Rational::isNegative();
}
bool operator!=(const Rational& lhs,
    const Rational& rhs) {
    return !operator==(lhs, rhs);
}
bool operator<=(const Rational& lhs,
    const Rational& rhs) {
    return !operator>(lhs, rhs);
}
bool operator>=(const Rational& lhs,
    const Rational& rhs) {
    return !operator<(lhs, rhs);
}

int32_t Rational::gcd(int32_t a, int32_t b) const {
    while (a != 0) {
        if (a < b) {
            std::swap(a, b);
        }
        a %= b;
    }
    return b;
}

void Rational::reducing() {  // always reduce to optimize space
    int32_t dev = gcd(std::abs(num_), denum_);
    num_ /= dev;
    denum_ /= dev;
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const
{
    ostrm << num_ << slash << denum_;
    return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm)
{
    int32_t numInp(0);
    char separator(0);
    int32_t denomInp(0);
    istrm >> numInp >> separator >> denomInp;
    if (istrm.good()) {
        if (Rational::slash == separator) {
            if (denomInp <= 0) {
                throw std::invalid_argument("Expected positive denominator");
            }
            num_ = numInp;
            denum_ = denomInp;
            reducing();
        }
        else {
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}