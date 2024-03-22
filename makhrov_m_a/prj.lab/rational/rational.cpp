#include "include/rational/rational.hpp"
#include <iostream>

Rational::Rational() {
    num = 0;
    denom = 1;
}
Rational::Rational(int32_t numberInp) {
    num = numberInp;
    denom = 1;
}
Rational::Rational(const Rational& myRat) {
    num = myRat.num;
    denom = myRat.denom;
}

Rational operator-(const Rational rhs) {
    return (rhs * Rational(-1, 1));
}


Rational::Rational(const int32_t numInp,
    const int32_t denomInp) {
    reducing();
    if (denomInp == 0) {
        throw std::invalid_argument("Expected positive denominator");
    }

    if (denomInp < 0) {
        num = -numInp;
        denom = -denomInp;
    }
    else {
        num = numInp;
        denom = denomInp;
    }


}

Rational& Rational::operator=(const Rational& rhs) {  // assignment operators from here
    num = rhs.num;
    denom = rhs.denom;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs) {
    int32_t mult = rhs.denom / gcd(denom, rhs.denom);
    num *= mult;
    denom *= mult;
    num += denom / rhs.denom * rhs.num;
    reducing();
    return *this;
}
Rational& Rational::operator-=(const Rational& rhs) {
    int32_t mult = rhs.denom / gcd(denom, rhs.denom);
    num *= mult;
    denom *= mult;
    num -= denom / rhs.denom * rhs.num;
    reducing();
    return *this;
}
Rational& Rational::operator*=(const Rational& rhs) {
    num *= rhs.num;
    denom *= rhs.denom;
    reducing();
    return *this;
}
Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.isZero()) {
        throw std::overflow_error("Divide by zero exception");
    }
    num *= rhs.denom;
    denom *= rhs.num;
    reducing();
    return *this;
}

Rational& Rational::operator++() {
    *this += 1;
    return *this;
}
Rational Rational::operator++(int) {
    Rational tmp(*this);
    ++(*this);
    return tmp;
}
Rational& Rational::operator--() {
    *this -= 1;
    return *this;
}
Rational Rational::operator--(int) {
    Rational tmp(*this);
    --(*this);
    return tmp;
}

Rational& Rational::operator%=(const Rational& rhs) {
    int32_t mult = rhs.denom / gcd(denom, rhs.denom);
    num *= mult;
    denom *= mult;
    num %= denom / rhs.denom * rhs.num;
    reducing();
    return *this;
}                                                     // till here

bool Rational::isPositive() const {  // sign-like methods
    return num > 0;
}
bool Rational::isZero() const {
    return num == 0;
}
bool Rational::isNegative() const {
    return num < 0;
}

std::istream& operator>>(std::istream& istrm,
    Rational& rhs) {
    return rhs.readFrom(istrm);
}


Rational& operator+(Rational& rhs) {
    return rhs;
}


Rational operator+(Rational lhs, const Rational& rhs) {
    Rational a = lhs;
    a += rhs;
    return a;
}
Rational operator-(Rational lhs, const Rational& rhs) {
    Rational a = lhs;
    a -= rhs;
    return a;
}
Rational operator*(Rational lhs, const Rational& rhs) {
    Rational a = lhs;
    a *= rhs;
    return a;
}
Rational operator/(Rational lhs, const Rational& rhs) {
    Rational a = lhs;
    a /= rhs;
    return a;
}
Rational operator%(Rational lhs, const Rational& rhs)
{
    Rational a = lhs;
    a %= rhs;
    return a;
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

Rational operator+(const Rational& rhs, const int& a) {
    Rational b(a);
    Rational c = rhs;
    c += b;
    return c;
}

Rational operator+(const int& a, const Rational& rhs) {
    Rational b(a);
    Rational c = rhs;
    c += b;
    return c;
}

Rational operator-(const Rational& rhs, const int& a) {
    Rational b(a);
    Rational c = rhs;
    c -= b;
    return c;
}

Rational operator-(const int& a, const Rational& rhs) {
    Rational b(a);
    Rational c = rhs;
    b -= c;
    return b;
}

Rational operator*(const int& a, const Rational& rhs) {
    Rational b(a);
    Rational c = rhs;
    c *= b;
    return c;
}

Rational operator*(const Rational& rhs, const int& a) {
    Rational b(a);
    Rational c = rhs;
    c *= b;
    return c;
}

Rational operator/(const Rational& lhs, const int32_t& rhs)
{
    Rational div(lhs);
    div /= rhs;
    return div;
}

Rational operator/(const int32_t& lhs, const Rational& rhs)
{
    Rational div(lhs, 1);
    div /= rhs;
    return div;
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
    int32_t dev = gcd(std::abs(num), denom);
    num /= dev;
    denom /= dev;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) {
    return rhs.writeTo(ostrm);
}

std::ostream& Rational::writeTo(std::ostream& ostrm) const noexcept {
    ostrm << num / gcd(std::abs(num), denom) << slash << denom / gcd(std::abs(num), denom);
    return ostrm;
}

std::istream& Rational::readFrom(std::istream& istrm) {
    char comma{ 0 };
    int32_t numerator{ 0 };
    int32_t denumerator{ 0 };
    istrm >> numerator;
    if (isspace(istrm.peek())) {
        istrm.setstate(std::ios_base::failbit);
        istrm.setstate(std::ios_base::eofbit);
    }
    istrm >> comma;
    if (int(comma) != 47 || isspace(istrm.peek())) {
        istrm.setstate(std::ios_base::failbit);
        istrm.setstate(std::ios_base::eofbit);
    }
    istrm >> denumerator;
    if (denumerator <= 0) {
        istrm.setstate(std::ios_base::failbit);
        istrm.setstate(std::ios_base::eofbit);
    }
    if (istrm.fail() == false) {
        num = numerator;
        denom = denumerator;
        reducing();
    }
    return istrm;
}